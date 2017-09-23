#include "widget_structure.h"
#include "hp8648c_hp436a_sweeper.h"
#include "gpib-functions.h"
#include "init.h"

#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <gtk/gtk.h>

#define NODEBUG_LEVEL_3
#define NODEBUG_LEVEL_2
#define NODEBUG_LEVEL_1

static char ib_answer[16384];

hp436a_record hp436a_data;
hp8648c_record hp8648c_data;
sample_record sample_data;

int init_gpib_devices(sweeper_data *wdg_data)	{
	hp436a_data.ud = set_device(GPIB_INTERFACE,HP436A_GPIB_ADR);

	if(hp436a_data.ud < 0)
	{
		fprintf(stderr,"ibdev hp436a error\n");
		return -1;
	}

	hp8648c_data.ud = set_device(GPIB_INTERFACE,HP8648C_GPIB_ADR);
	if(hp8648c_data.ud < 0)
	{
		fprintf(stderr,"ibdev hp8648c error\n");
		return -1;
	}

	init(wdg_data,&hp8648c_data);
	
	return 1;
}

int set_mode_hp436a(char *mode)	{

		if (ib_write(hp436a_data.ud,mode)>0)
			fprintf(stderr,"Could not set HPP436A\n\r");
		else
			return 1;

		return -1;	
}


int set_mode_hp8648c(int mode, int mod, int output)	{
	switch(mode){
		case MOD_OFF:
		if (ib_write(hp8648c_data.ud,"AM:STAT OFF")>0)
			fprintf(stderr,"Could not set AM modulation off\n\r");
		if (ib_write(hp8648c_data.ud,"FM:STAT OFF")>0)
			fprintf(stderr,"Could not set FM modultion off\n\r");
		break;
	}
	switch(output){
		case RF_OFF:
		if (ib_write(hp8648c_data.ud,"OUTP:STAT OFF")>0)
			fprintf(stderr,"Could not set RF off\n\r");
		case RF_ON:
		if (ib_write(hp8648c_data.ud,"OUTP:STAT ON")>0)
			fprintf(stderr,"Could not set RF on\n\r");
		break;
	}
	switch(mod){
		case 100:
		if (ib_write(hp8648c_data.ud,"AM:INT:FREQ 400HZ")>0)
			fprintf(stderr,"Could not set RF off\n\r");
		case 400:
		if (ib_write(hp8648c_data.ud,"AM:INT:FREQ 400HZ")>0)
			fprintf(stderr,"Could not set RF on\n\r");
		break;
	}


	return 1;
}

int set_frequency_hp8648c(gdouble set_frequency)	{
	char cmd_buf[20];
	sprintf(cmd_buf,"FREQ:CW %4.5fMHZ",set_frequency);
	if(ib_write(hp8648c_data.ud,cmd_buf) !=0 ){
		fprintf(stderr,"Change fault fault %s\n\r", cmd_buf);
		return -1;
	}
	else
#ifdef DEBUG_LEVEL_1
		fprintf(stderr,"Change frequency %s\n\r", cmd_buf);
#endif
	return 1;
}

int set_level_hp8648c(gdouble set_level)	{
	char cmd_buf[20];
	//gdouble set_frequency = gtk_spin_button_get_value(GTK_SPIN_BUTTON(data->widget_set_frequency));
	sprintf(cmd_buf,"POW:AMPL %4.1fDBM",set_level);
	if (ib_write(hp8648c_data.ud,cmd_buf) != 0)	{
		fprintf(stderr,"Change level fault %s\n\r", cmd_buf);
		return -1;
	}
	else
#ifdef DEBUG_LEVEL_1
		fprintf(stderr,"Change level %s\n\r", cmd_buf);
#endif
	return 1;
}

double strip_answer(char *answer, char *para) {
	double value;
	char header[3];
	sscanf(answer, "%2s%le", header, &value);

	if(! strcmp(header,para)) {
#ifdef DEBUG_LEVEL_3
		fprintf(stderr,"Answer: %s Header %s Value: %f \n\r", answer, header, value);
#endif
		return value;
	}
	return 0;
}


uint16_t swap_uint16( uint16_t val ) {
    return (val << 8) | (val >> 8 );
}

void status_hp8648c(hp8648c_record *record)	{
	ib_write(hp8648c_data.ud,"*IDN?");
	usleep(10000);
/*
	if (ib_query(ud, 19,"OPCF?", ib_answer) > 0)	{
		record->cf= strip_answer(ib_answer,"CF");
	}
*/
}
