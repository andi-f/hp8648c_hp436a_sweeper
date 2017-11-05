#include <gtk/gtk.h>
#include <math.h>
#include <unistd.h>
#include <glib.h>
#include <glib/gstdio.h>

#include "hp8648c_hp436a_sweeper.h"
#include "hp8648c_hp436a.h"
#include "callback-gpib.h"
#include "callback_widget.h"
#include "gpib-functions.h"
#include "widget.h"
#include "drawing.h"
#include "debug.h"

static FILE *output_fd = NULL;
uint		hp8648c_delay = 1;
uint		hp436a_delay =  10;
static uint	lock = FALSE;

gboolean timer_sweep (gpointer data)
{
	char 		reply[16384]="PJD -47.90000";
	char 		dummy[16384];	
	m_record	act_data;
	int 		m;

	sweeper_data *wdg_data = (sweeper_data *) data;

	if(lock == TRUE)	{
		#ifdef DEBUG_LEVEL_2
		fprintf(stderr,"Locked\n");		
		#endif
		return TRUE;
	}
	
	if(hp8648c.run != 1)	{
		#ifdef DEBUG_LEVEL_2
		fprintf(stderr,"not running \n");
		#endif
		return TRUE;		
	}
	#ifdef DEBUG_LEVEL_2
	fprintf(stderr,"running \n");
	#endif			
	
	if(output_fd == NULL)	{
		lock = TRUE;	

		#ifdef DEBUG_LEVEL_4
			fprintf(stderr,"%u %u %u \n",lock, hp8648c_delay,hp436a_delay);
		#endif
					
		if (hp8648c_delay == 1)	{
			if (set_mode_hp8648c(hp8648c.ud,MOD_OFF, 0, RF_OFF) && set_level_hp8648c(hp8648c.ud,hp8648c.rl_start) && set_frequency_hp8648c(hp8648c.ud, hp8648c.f_start) ) {
				#ifdef DEBUG_LEVEL_2			
				fprintf(stderr,"Init HP8648A\n");
				#endif
				hp8648c_delay = 0;
			}
			else	{
				hp8648c.run = 0;
				wdg_data->statusbar_buffer = g_strdup_printf("Init HP8648c aborted");
				return TRUE;
			}
		}
		else
		if (hp8648c_delay > 0)
			hp8648c_delay --;

		if(hp436a_delay == 10)	{
			if (set_mode_hp436a(hp436a.ud,"9D-R") )	{
				#ifdef DEBUG_LEVEL_2			
				fprintf(stderr,"Init HP436A\n");
				#endif
				hp436a_delay --;
			}
			else {
				hp8648c.run = 0;
				wdg_data->statusbar_buffer = g_strdup_printf("Init HP436c aborted");
				return TRUE;
			}
		}
		else
		if(hp436a_delay > 0)
			hp436a_delay --;

		if( (hp436a_delay == 0) && (hp8648c_delay == 0))
		{
			#ifdef DEBUG_LEVEL_2			
				fprintf(stderr,"Init csv-File \n");
			#endif

			output_fd = g_fopen(wdg_data->filename, "w+t");
		
			if(output_fd == NULL){
				fprintf(stderr,"no file handle\n");
				wdg_data->statusbar_buffer = g_strdup_printf("No file handle for csv-file");
				#ifdef DEBUG_LEVEL_2			
					fprintf(stderr,"No file handle for csv-file\n");
				#endif
				lock = FALSE;
				hp8648c.run = 0;
				return TRUE;
			}
			wdg_data->statusbar_buffer = g_strdup_printf("Open csv-file:%s",wdg_data->filename);

			g_array_free(m_data, TRUE);
			m_data = g_array_new(FALSE, FALSE, sizeof(m_record));
			r_counter = 0;
		
			hp8648c.f = hp8648c.f_start;
			hp8648c.rl = hp8648c.rl_start;
			set_mode_hp8648c(hp8648c.ud,MOD_OFF, 0, RF_ON);
			sample_data.sample = 0;
			sample_data.avg_value = 0;
			fprintf(output_fd,"Frequency;Ref-Level;Level;RMSD\n");
			#ifdef DEBUG_LEVEL_2			
				fprintf(stderr,"Frequency;Ref-Level;Level;RMSD\n");
			#endif

		}		
	}
	else
	{
		lock = TRUE;	
		#ifndef DUMMYRUN
		ib_read(hp436a.ud, 14, reply);
		#endif
		
		sscanf(reply,"%3s %lf",dummy,&sample_data.value[sample_data.sample]);
		#ifdef DEBUG_LEVEL_5
			fprintf(stderr,"%s %lf %u\n",dummy,sample_data.value[sample_data.sample],sample_data.sample );	
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
				#ifdef DEBUG_LEVEL_5
					fprintf(stderr,"f=%lf rl=%lf N=%u M=%lf A=%lf D=%lf\n",hp8648c.f, hp8648c.rl, sample_data.sample, sample_data.value[sample_data.sample], sample_data.avg_value, sample_data.diff_avg);	
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
			
			}
		
			sample_data.rmsd  = pow((sample_data.diff_avg/(sample_data.sample-1)),0.5);

			if (sample_data.rmsd < sample_data.rmsd_limit)	{

				fprintf(output_fd,"%lf %lf %lf %lf\n",hp8648c.f,hp8648c.rl,sample_data.avg_value, sample_data.rmsd);
				wdg_data->statusbar_buffer = g_strdup_printf("%lf %lf %lf %lf",hp8648c.f,hp8648c.rl,sample_data.avg_value, sample_data.rmsd);
			
				#ifdef DEBUG_LEVEL_1
					fprintf(stderr,"f=%lf l=%lf avg=%lf rmsd=%lf\n",hp8648c.f,hp8648c.rl,sample_data.avg_value, sample_data.rmsd);
				#endif

				act_data.frequency = hp8648c.f;
				act_data.ref_level = hp8648c.rl;
				act_data.avg_value = sample_data.avg_value;
				act_data.rmsd = sample_data.rmsd;
				g_array_append_vals(m_data, &act_data,1);
				r_counter ++;
				
				if(hp8648c.run_f == 1){
					if (hp8648c.f < hp8648c.f_stop)	{
						hp8648c.f = hp8648c.f  + hp8648c.f_step;
						set_frequency_hp8648c(hp8648c.ud,hp8648c.f);
					}
					else	{
						fclose (output_fd);	
						output_fd = NULL;				
						hp8648c.run = 0;		
						hp8648c_delay = 1;
						hp436a_delay =  10;						
						
						save_file(wdg_data);
						
						#ifdef DEBUG_LEVEL_1
						for (m = 0; m < r_counter;m++){
							act_data = g_array_index(m_data, m_record, m);
							fprintf(stderr," f=%f %f %f %f\n", act_data.frequency, act_data.ref_level,act_data.avg_value, act_data.rmsd);
						}
						#endif
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
						output_fd = NULL;
						hp8648c.run = 0;		
						g_source_remove (wdg_data->sweep_timer);					
						hp8648c_delay = 1;
						hp436a_delay =  10;
						save_file(wdg_data);
						for (m = 0; m < r_counter;m++){
							act_data = g_array_index(m_data, m_record, m);
							fprintf(stderr," f=%f %f %f %f\n", act_data.frequency, act_data.ref_level,act_data.avg_value, act_data.rmsd);
						}
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
