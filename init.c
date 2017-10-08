#include "hp8648c_hp436a_sweeper.h"
#include "widget_structure.h"
#include "callback-gpib.h"
#include "gpib-functions.h"
	
#define MINF 0.15
#define MAXF 3200
#define MINL -136
#define MAXL 13

#define NO_DEBUG_LEVEL_1
		
int init(sweeper_data *wdg, hp8648c_record *hp8648c, hp436a_record *hp436a, sample_record *sample_data)	{

//	if (hp436a->device == 0)	{
		hp436a->device = HP436A_GPIB_ADR;
		gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg->hp436a_gpib_spinbutton), hp436a->device);
//	}

//	if (hp8648c->device == 0)	{
		hp8648c->device = HP8648C_GPIB_ADR;
		gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg->hp8648c_gpib_spinbutton),hp8648c->device);
//	}

		hp8648c->run_f = 1;

		sample_data->avg_count = 10;
		gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg->number_avg),sample_data->avg_count);
		
	if (hp8648c->f_stop < 3200)	{
		hp8648c->f_stop = 3200;
		gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg->stop_frequency),hp8648c->f_stop);
	}
	
	if (hp8648c->f_start < 0.10)	{
		hp8648c->f_start = 1;
		gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg->start_frequency),hp8648c->f_start);
	}
	
	if (hp8648c->f_start > hp8648c->f_stop)	{
		hp8648c->f_start = hp8648c->f_stop;
		gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg->stop_frequency),hp8648c->f_stop);		
	}

	if (hp8648c->f_step != 0.1)	{
		hp8648c->f_step = (hp8648c->f_stop - hp8648c->f_stop) / 100;
		gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg->step_frequency),hp8648c->f_step);		
	}
	
	if (hp8648c->rl_start != -50)	{
		hp8648c->rl_start = -20;
		gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg->start_level),hp8648c->rl_start);				
	}
	
	if (hp8648c->rl_stop > -20)	{
		hp8648c->rl_stop = -20;
		gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg->step_level),hp8648c->rl_stop);						
	}
	
	if (hp8648c->rl_step < 0.1)	{
		hp8648c->rl_step = 0.1;
		gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg->step_level),hp8648c->rl_step);								
	}

	if (hp8648c->rl_start > hp8648c->rl_stop)	{
		hp8648c->rl_start = hp8648c->rl_stop;
		gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg->stop_level),hp8648c->rl_stop);				
	}
	
	if (set_mode_hp8648c(hp8648c->ud,MOD_OFF, 0, RF_OFF) != 1)
		return -1;
	if( set_level_hp8648c(hp8648c->ud,hp8648c->rl_start) !=1 )
		return -1;
	if (set_frequency_hp8648c(hp8648c->ud, hp8648c->f_start)!= 1)
		return -1;
	#ifdef DEBUG_LEVEL_1			
		fprintf(stderr,"Init HP8648A\n\r");
	#endif
	if (set_mode_hp436a(hp436a->ud,"9D-R") != 1)
		return -1;
	#ifdef DEBUG_LEVEL_1		
		fprintf(stderr,"Init HP436A\n\r");
	#endif
	return 0;
}

int init_gpib_devices(sweeper_data *wdg_data, hp8648c_record *hp8648c, hp436a_record *hp436a)	{
	hp8648c->device = HP8648C_GPIB_ADR;
	hp436a->device = HP436A_GPIB_ADR;
	hp436a->ud = set_device(GPIB_INTERFACE,hp436a->device);
	if(hp436a->ud < 0)
	{
		fprintf(stderr,"ibdev hp436a error\n");
		wdg_data->statusbar_buffer = g_strdup_printf("ibdev hp436a error");
		return -1;
	}

	hp8648c->ud = set_device(GPIB_INTERFACE,hp8648c->device);
	if(hp8648c->ud < 0)
	{
		fprintf(stderr,"ibdev hp8648c error\n");
		wdg_data->statusbar_buffer = g_strdup_printf("ibdev hp8648c error");		
		return -1;
	}
	wdg_data->statusbar_buffer = g_strdup_printf("hp8648c/hp436a ready");		
	return 1;
}
