#include "hp8648c_hp436a_sweeper.h"
#include "hp8648c_hp436a.h"
#include "widget_structure.h"

#include "callback-gpib.h"
#include "gpib-functions.h"
#include "widget.h"
#include <math.h>
#include <unistd.h>

#define NO_DEBUG_LEVEL_1
#define NO_DEBUG_LEVEL_2
#define NO DEBUG_LEVEL_3
#define NO_DEBUG_LEVEL_4
#define DEBUG_LEVEL_5

FILE 		*output_fd ;
uint		hp8648c_delay = 1;
uint		hp436a_delay =  10;
uint		lock = FALSE;


gboolean timer_sweep (gpointer data)
{
	time_t      timeStamp;
	struct tm 	*timeInfo;
	char        buffer[80];
	char 		reply[16384]="PJD -47.90000";
	char 		dummy[16384];	

	sweeper_data *wdg_data = (sweeper_data *) data;

	#ifdef DEBUG_LEVEL_4
		fprintf(stderr,"%u %u %u \n\r",lock, hp8648c_delay,hp436a_delay);
	#endif

	if(lock == TRUE)
		return FALSE;
		
	lock = TRUE;
	
	if(output_fd == NULL)	{

		#ifdef DEBUG_LEVEL_4
			fprintf(stderr,"%u %u %u \n\r",lock, hp8648c_delay,hp436a_delay);
		#endif
					
		if (hp8648c_delay == 1)	{
			if (set_mode_hp8648c(hp8648c.ud,MOD_OFF, 0, RF_OFF) != 1)
				return FALSE;
			if( set_level_hp8648c(hp8648c.ud,hp8648c.rl_start) !=1 )
				return FALSE;
			if (set_frequency_hp8648c(hp8648c.ud, hp8648c.f_start)!= 1)
				return FALSE;
			#ifdef DEBUG_LEVEL_2			
				fprintf(stderr,"Init HP8648A\n\r");
			#endif
			hp8648c_delay --;
		}
		else
		if (hp8648c_delay > 0)
			hp8648c_delay --;

		if(hp436a_delay == 10)	{
			if (set_mode_hp436a(hp436a.ud,"9D-R") != 1)
				return FALSE;
			#ifdef DEBUG_LEVEL_2			
				fprintf(stderr,"Init HP436A\n\r");
			#endif
			hp436a_delay --;
		}
		else
		if(hp436a_delay > 0)
			hp436a_delay --;

		if( (hp436a_delay == 0) & (hp8648c_delay == 0))
		{
			#ifdef DEBUG_LEVEL_2			
				fprintf(stderr,"Init csv-File \n\r");
			#endif
			time( &timeStamp );
			timeInfo = localtime( &timeStamp );

			strftime( buffer, 60, "%Y%m%d%H%M%S-hp8648c_hp436a.csv", timeInfo );

			output_fd = fopen(buffer, "w");
		
			if(output_fd == NULL){
				fprintf(stderr,"no file handle\n\r");
				wdg_data->statusbar_buffer = g_strdup_printf("No file handle for csv-file");
				#ifdef DEBUG_LEVEL_2			
					fprintf(stderr,"No file handle for csv-file\n\r");
				#endif
				lock = FALSE;
				return FALSE;
			}
			wdg_data->statusbar_buffer = g_strdup_printf("Open csv-file:%s",buffer);

			hp8648c.f = hp8648c.f_start;
			hp8648c.rl = hp8648c.rl_start;
			set_mode_hp8648c(hp8648c.ud,MOD_OFF, 0, RF_ON);
			sample_data.sample = 0;
			sample_data.avg_value = 0;
			fprintf(output_fd,"Frequency;Ref-Level;Level,RMSE\n\r");
			#ifdef DEBUG_LEVEL_2			
				fprintf(stderr,"Frequency;Ref-Level;Level,RMSE\n\r");
			#endif
		}		
	}
	else
	{
		ib_read(hp436a.ud, 14, reply);
		sscanf(reply,"%3s %lf",dummy,&sample_data.value[sample_data.sample]);
		#ifdef DEBUG_LEVEL_5
			fprintf(stderr,"%s %lf %u\n\r",dummy,sample_data.value[sample_data.sample],sample_data.sample );	
		#endif

		if (reply[0] == 'P')	//valid measurement
		{
			sample_data.unterflow_counter = 0;									
			sample_data.avg_value = sample_data.avg_value + sample_data.value[sample_data.sample];
			sample_data.diff_avg = fabs((sample_data.avg_value/(sample_data.sample+1) - sample_data.value[sample_data.sample]));
			if(sample_data.diff_avg > 0.3)	{
				sample_data.avg_value = 0;
				sample_data.sample = 0;
			}
			else	{
				#ifdef DEBUG_LEVEL_3
					fprintf(stderr,"f=%lf rl=%lf N=%u M=%lf A=%lf D=%lf\n\r",hp8648c.f, hp8648c.rl, sample_data.sample, sample_data.value[sample_data.sample], sample_data.avg_value, sample_data.diff_avg);	
				#endif
				sample_data.sample++;				
			}
		}
		else
		if (reply[0] == 'S'){	//underflow
			sample_data.avg_value = -174;
			sample_data.sample = 0;			
			
			sample_data.unterflow_counter ++;
			if ( sample_data.unterflow_counter > 10)	{
				sample_data.unterflow_counter = 0;
				hp8648c.rl = hp8648c.rl  + hp8648c.rl_step;
				set_level_hp8648c(hp8648c.ud,hp8648c.rl);
			}
		}			
		else
		if (reply[0] == 'R'){	//overflow
			sample_data.avg_value = -174;
			sample_data.sample = 0;			
			hp8648c.rl = hp8648c.rl  - hp8648c.rl_step;
			set_level_hp8648c(hp8648c.ud,hp8648c.rl);
		}									

		if(sample_data.sample >= sample_data.avg_count)
		{
			sample_data.avg_value = sample_data.avg_value / (sample_data.sample);
			sample_data.diff_avg = 0;
			
			int n;
			for (n = 1; n < sample_data.sample; n ++)	{
				sample_data.diff_avg = sample_data.diff_avg + fabs((sample_data.avg_value - sample_data.value[n]));
			
				#ifdef DEBUG_LEVEL_3
					fprintf(stderr,"%lf avg=%lf %lf %lf\n\r",hp8648c.f,hp8648c.rl,sample_data.avg_value,sample_data.diff_avg);	
				#endif
				
			}
		
			sample_data.rmsd  = pow((sample_data.diff_avg/(sample_data.sample-1)),0.5);

			#ifdef DEBUG_LEVEL_2
				fprintf(stderr,"f=%lf l=%lf avg=%lf rmsd=%lf\n\r",hp8648c.f,hp8648c.rl,sample_data.avg_value, sample_data.rmsd);
			#endif
			
			if (sample_data.rmsd < 10){

				fprintf(output_fd,"%lf; %lf; %lf; %lf\n\r",hp8648c.f,hp8648c.rl,sample_data.avg_value, sample_data.rmsd);
				wdg_data->statusbar_buffer = g_strdup_printf("%lf %lf %lf %lf",hp8648c.f,hp8648c.rl,sample_data.avg_value, sample_data.rmsd);

				if(hp8648c.run_f == 1){
					if (hp8648c.f < hp8648c.f_stop)	{
						hp8648c.f = hp8648c.f  + hp8648c.f_step;
						set_frequency_hp8648c(hp8648c.ud,hp8648c.f);
					}
					else	{
						fclose (output_fd);					
						hp8648c.run = 0;		
						g_source_remove (wdg_data->sweep_timer);
						hp8648c_delay = 1;
						hp436a_delay =  10;						
					}

				}
				else
				if(hp8648c.run_f == 0){
					if (hp8648c.rl < hp8648c.rl_stop)	{
						hp8648c.rl = hp8648c.rl  + hp8648c.rl_step;
						set_level_hp8648c(hp8648c.ud,hp8648c.rl);
						hp436a_delay =  9;		
					}
					else	{
						fclose (output_fd);
						hp8648c.run = 0;		
						g_source_remove (wdg_data->sweep_timer);					
						hp8648c_delay = 1;
						hp436a_delay =  10;
					}
				}				
			}
			sample_data.sample = 0;
			sample_data.avg_value = 0;
		}				
	}
	lock = FALSE;
    return TRUE;
}
	
