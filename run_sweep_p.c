/*
 *      This program is free software: you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation, either version 3 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *      You should have received a copy of the GNU General Public License
 *      along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "hp8648c_hp436a_sweeper.h"
#include "callback-gpib.h"
#include "gpib-functions.h"
#include "widget.h"
#include <math.h>
#include <unistd.h>
}
	
void run()	{
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
	gdouble diff_level =0;
	gdouble diff_avg = 0;
	
	init_gpib_devices();

	record_hp8648c.f = 144.2;
	record_hp8648c.rl_start = -55;
	record_hp8648c.rl_stop = -20.1;
	record_hp8648c.rl_step = 0.1;
/*
	set_mode_hp8648c(MOD_OFF, 0, RF_OFF);
	set_level_hp8648c(-100);
	usleep(100000);
	set_mode_hp436a("9Z-R");
	sleep(10);	
*/
	set_mode_hp436a("9D-R");
	sleep(10);
	
	set_level_hp8648c(record_hp8648c.rl_start);
	sleep(3);
	set_mode_hp8648c(MOD_OFF, 0, RF_ON);
	set_frequency_hp8648c(record_hp8648c.f);
	usleep(100000);
	
	time( &timeStamp );
	timeInfo = localtime( &timeStamp );

	strftime( buffer, 60, "%Y%m%d%H%M%S-hp8648c_hp436a.csv", timeInfo );
	FILE *output_fd ;
	output_fd = fopen(buffer, "w");

	if(output_fd == NULL){
		fprintf(stderr,"no file handle\n\r");
		return -1;
	}
	else {
		fprintf(output_fd,"Level;Ua_avg;Diff;Qrmsd; Delta_value\n\r");
		fprintf(stderr,"Level;Ua_avg;Diff;Qrmsd; Delta_value\n\r");

		for (gdouble level = record_hp8648c.rl_start;level < record_hp8648c.rl_stop; level = level + record_hp8648c.rl_step)	{
			set_level_hp8648c(level);
			usleep(100000);
			avg_value = 0;
			for (int n = 0;n < SAMPLE;n++)	{
				do {
					ib_read(record_hp436a.ud, 14, reply);
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
						level = level + record_hp8648c.rl_step;
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
}

