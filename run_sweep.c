#include "hp8648c_hp436a_sweeper.h"
#include "widget_structure.h"
#include "callback-gpib.h"
#include "gpib-functions.h"
#include "widget.h"
#include <math.h>
#include <unistd.h>

#define DEBUG_LEVEL_2

static FILE 	*output_fd ;
static uint		hp8648c_delay = 30;
static uint		hp436a_delay = 100;

gboolean timer_sweep (gpointer data)
{
	time_t      timeStamp;
	struct tm 	*timeInfo;
	char        buffer[80];
	char 		reply[GPIB_LENGTH];
	char 		dummy[GPIB_LENGTH];	

	sweeper_data *wdg_data = (sweeper_data *) data;
	
	if(output_fd == NULL)	{
		
		if (hp8648c_delay == 30)	{
			set_mode_hp8648c(MOD_OFF, 0, RF_OFF);
			set_level_hp8648c(hp8648c_data.rl_start);
			set_frequency_hp8648c(hp8648c_data.f_start);			
		}
		else
		if (hp8648c_delay > 0)
			hp8648c_delay --;

		if(hp436a_delay == 100)	{
			set_mode_hp436a("9D-R");
		}
		else
		if(hp436a_delay > 0)
			hp436a_delay --;

		if( (hp436a_delay == 0) & (hp8648c_delay == 0))
		{
			time( &timeStamp );
			timeInfo = localtime( &timeStamp );

			strftime( buffer, 60, "%Y%m%d%H%M%S-hp8648c_hp436a.csv", timeInfo );

			output_fd = fopen(buffer, "w");
		
			if(output_fd == NULL){
				fprintf(stderr,"no file handle\n\r");
				wdg_data->statusbar_buffer = g_strdup_printf("No file handle for csv-file");
				return -1;
			}
			wdg_data->statusbar_buffer = g_strdup_printf("Open csv-file:%s",buffer);
			hp8648c_data.f = hp8648c_data.f_start;
			hp8648c_data.rl = hp8648c_data.rl_start;
			set_mode_hp8648c(MOD_OFF, 0, RF_ON);
			sample_data.sample = 0;
			sample_data.avg_value = 0;
			fprintf(output_fd,"Frequncy;Ref-Level;Level,RMSE\n\r");
			#ifdef DEBUG_LEVEL_2			
				fprintf(stderr,"Frequncy;Ref-Level;Level,RMSE\n\r");
			#endif
		}		
	}
	else
	{
		ib_read(hp436a_data.ud, 14, reply);
		sscanf(reply,"%3s%le",dummy,&sample_data.value[sample_data.sample]);
		if (reply[0] == 'P')	//valid measurement
		{
			sample_data.avg_value = sample_data.avg_value + sample_data.value[sample_data.sample];
			sample_data.diff_avg = fabs((sample_data.avg_value/(sample_data.sample) - sample_data.value[sample_data.sample]));
			if(sample_data.diff_avg > 0.05)	{
				sample_data.avg_value = 0;
				sample_data.sample= 0;
			}
			else
				sample_data.sample++;
		}
		else
		if (reply[0] == 'S'){	//underflow
			sample_data.avg_value = -174;
			sample_data.sample ++;
		}			
						
		if(sample_data.sample >= sample_data.avg_count)
		{
			sample_data.avg_value = sample_data.avg_value / sample_data.sample;
			sample_data.diff_avg = 0;
			
			int n;
			for (n = 0; n < sample_data.sample; n ++)	{
				sample_data.diff_avg = sample_data.diff_avg + fabs((sample_data.avg_value - sample_data.value[n]));
			
				#ifdef DEBUG_LEVEL_3
					fprintf(stderr,"%lf avg=%lf %lf %lf\n\r",hp8648c_data.f,hp8648c_data.rl,sample_data.avg_value,sample_data.diff_avg);	
				#endif
				
			}
		
			sample_data.rmsd  = pow((sample_data.diff_avg/(sample_data.sample-1)),0.5);
			

			fprintf(output_fd,"%lf; %lf; %lf; %lf\n\r",hp8648c_data.f,hp8648c_data.rl,sample_data.avg_value, sample_data.rmsd);

			wdg_data->statusbar_buffer = g_strdup_printf("%lf %lf %lf %lf\n\r",hp8648c_data.f,hp8648c_data.rl,sample_data.avg_value, sample_data.rmsd);

			if(hp8648c_data.run_f == 1){
				if (hp8648c_data.f < hp8648c_data.f_stop)	{
					hp8648c_data.f = hp8648c_data.f  + hp8648c_data.f_step;
				}
				else	{
					fclose (output_fd);					
					hp8648c_data.run = 0;		
					g_source_remove (wdg_data->sweep_timer);
				}

			}
			else
			if(hp8648c_data.run_f == 0){
				if (hp8648c_data.f < hp8648c_data.f_stop)	{
					hp8648c_data.f = hp8648c_data.f  + hp8648c_data.f_step;
				}
				else	{
					fclose (output_fd);
					hp8648c_data.run = 0;		
					g_source_remove (wdg_data->sweep_timer);					
				}
			}
		
		}				
	}

    return 1;
}
	
