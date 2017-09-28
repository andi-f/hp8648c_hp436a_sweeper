#include "hp8648c_hp436a_sweeper.h"
#include "widget_structure.h"
#include "callback-gpib.h"
#include "gpib-functions.h"
#include "widget.h"
#include <math.h>
#include <unistd.h>


	
int run_sweep_f(sweeper_data *wdg_data)	{
	char reply[GPIB_LENGTH];
	char dummy[GPIB_LENGTH];
	double value[SAMPLE];
	double avg_value=0;
	double diff_value=0;
	double rmsd=0;			// root mean square deviation
	double delta_value=0;	//error

	time_t      timeStamp;
	struct tm * timeInfo;
	char        buffer[80];
	gdouble old_level = 0;
	gdouble diff_level = 0;
	gdouble diff_avg = 0;
	
	if (init_gpib_devices(wdg_data) != 1)	{
		return -1;
	}
		
	hp8648c_data.f = 144.2;
	hp8648c_data.rl_start = -55;
	hp8648c_data.rl_stop = -20.1;
	hp8648c_data.rl_step = 1;
/*
	set_mode_hp8648c(MOD_OFF, 0, RF_OFF);
	set_level_hp8648c(-100);
	usleep(100000);
	set_mode_hp436a("9Z-R");
	sleep(10);	
*/
	set_mode_hp436a("9D-R");
	sleep(10);
	
	set_level_hp8648c(hp8648c_data.rl_start);
	sleep(3);
	set_mode_hp8648c(MOD_OFF, 0, RF_ON);
	set_frequency_hp8648c(hp8648c_data.f);
	usleep(100000);
	
	time( &timeStamp );
	timeInfo = localtime( &timeStamp );

	strftime( buffer, 60, "%Y%m%d%H%M%S-hp8648c_hp436a.csv", timeInfo );

	output_fd = fopen(buffer, "w");

	if(output_fd == NULL){
		fprintf(stderr,"no file handle\n\r");
		return -1;
	}
	else {
		fprintf(output_fd,"Level;Ua_avg;Diff;Qrmsd; Delta_value\n\r");
		fprintf(stderr,"Level;Ua_avg;Diff;Qrmsd; Delta_value\n\r");

		for (gdouble level = hp8648c_data.rl_start;level < hp8648c_data.rl_stop; level = level + hp8648c_data.rl_step)	{
			set_level_hp8648c(level);
			usleep(100000);
			avg_value = 0;
			for (int n = 0;n < SAMPLE;n++)	{
				do {
					ib_read(hp436a_data.ud, 14, reply);
					sscanf(reply,"%3s%le",dummy,&value[n]);

					if (reply[0] == 'P')	//valid measurement
					{
						avg_value = avg_value + value[n];
						diff_avg = fabs((avg_value/(n) - value[n]));
						fprintf(stderr,"n=%i %3s value[n]=%lf avg=%lf %lf\n\r",n,dummy,value[n],avg_value,diff_avg);	
						
						if (diff_avg > 0.05)	{

							avg_value = 0;
							n = 0;
							sleep(1);
						}
					}
					else
					if (reply[0] == 'S'){	//underflow
						level = level + hp8648c_data.rl_step;
						set_level_hp8648c(level);
						avg_value = 0;
						n = 0;
						sleep(10);						
					}							
					
				} while(reply[0]!= 'P');
			}
			avg_value = avg_value / SAMPLE;

			for (int n = 0;n < SAMPLE;n++)	{
				diff_value = diff_value + pow((value[n]-avg_value),2);
			}
			rmsd  = pow((diff_value/(SAMPLE-1)),0.5);
			delta_value = rmsd / pow(SAMPLE,0.5);

			diff_level = avg_value - old_level;
			fprintf(output_fd,"%lf; %lf; %lf; %lf; %lf ;\n\r",level, avg_value, diff_level, rmsd, delta_value);
			fprintf(stderr,"%lf; %lf; %lf; %lf; %lf ;\n\r",level, avg_value, diff_level, rmsd, delta_value);
			old_level = avg_value;
		}
	}
	fclose(output_fd);
	return 0;
}

