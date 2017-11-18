#include "hp8648c_hp436a_sweeper.h"
#include "widget_structure.h"
#include "callback-gpib.h"
#include "gpib-functions.h"
#include "debug.h"
#include <glib.h>
#include <glib/gstdio.h>

int write_config_file(sweeper_data *wdg_data,hp8648c_record *hp8648c, hp436a_record *hp436a)	{
    GKeyFile *key_file;
    GError *error;
    gchar *dir_name;

    key_file = g_key_file_new();
	error = NULL;
	
	dir_name = g_build_filename (g_get_home_dir (), ".hp8648c_hp436a_sweeper/", NULL);
   
	if(g_chdir(dir_name)!= 0)
    	if(g_mkdir(dir_name,0700)!=0)
			return -1;
	
	dir_name = g_build_filename (dir_name, "config.ini", NULL);

	g_key_file_set_integer(key_file, "GBIB", "HP436A",hp436a->device );
	g_key_file_set_integer(key_file, "GBIB", "HP8648C", hp8648c->device);
        
	g_key_file_set_double(key_file, "SETTINGS", "f_start",hp8648c-> f_start);
	g_key_file_set_double(key_file, "SETTINGS", "f_stop",hp8648c->f_stop);
	g_key_file_set_double(key_file, "SETTINGS", "f_Step",hp8648c->f_step);	
	
	g_key_file_set_double(key_file, "SETTINGS", "rl",hp8648c->rl);
	g_key_file_set_double(key_file, "SETTINGS", "rl_start",hp8648c->rl_start);
	g_key_file_set_double(key_file, "SETTINGS", "rl_stop",hp8648c->rl_stop);
	g_key_file_set_double(key_file, "SETTINGS", "rl_step",hp8648c->rl_step); 
	
	g_key_file_set_double(key_file, "SETTINGS", "rsmd",gtk_spin_button_get_value(GTK_SPIN_BUTTON(wdg_data->rmsd_settings)));
	
	g_key_file_set_double(key_file, "SETTINGS", "avg_count",gtk_spin_button_get_value(GTK_SPIN_BUTTON(wdg_data->number_avg)));
	       
	if(g_key_file_save_to_file (key_file,
		dir_name,
		&error)!= TRUE)
	g_debug("%s", error->message);
   
	g_free(dir_name);
	return 0;
}
	
int init(sweeper_data *wdg, hp8648c_record *hp8648c, hp436a_record *hp436a, sample_record *sample_data)	{
    GKeyFile *key_file;
    GError *error;
    gchar *dir_name;

    key_file = g_key_file_new();
	error = NULL;
	
	dir_name = g_build_filename (g_get_home_dir (), ".hp8648c_hp436a_sweeper/", "config.ini", NULL);

    if(!g_key_file_load_from_file(key_file,
		dir_name,
		G_KEY_FILE_KEEP_COMMENTS | 
		G_KEY_FILE_KEEP_TRANSLATIONS,
		&error))
    {
        g_debug("%s", error->message);
        return -1;
    }
    else    {
		hp436a->device = g_key_file_get_integer(key_file, "GBIB", "HP436A",&error);
		if(error != 0x0){
			g_debug("%s", error->message);			
			hp436a->device = HP436A_GPIB_ADR;
		}
		gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg->hp436a_gpib_spinbutton), hp436a->device);
					
		hp8648c->device = g_key_file_get_integer(key_file, "GBIB", "HP8648C", &error);
		if(error != 0x0){
			g_debug("%s", error->message);			
			hp8648c->device = HP8648C_GPIB_ADR;
		}
		gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg->hp8648c_gpib_spinbutton),hp8648c->device);		
		
		hp8648c-> f_start = g_key_file_get_double(key_file, "SETTINGS", "f_start",&error);
		if(error != 0x0){
			g_debug("%s", error->message);			
			hp8648c->f_start = MINF;
		}
		gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg->start_frequency),hp8648c->f_start);
		
		hp8648c->f_stop = g_key_file_get_double(key_file, "SETTINGS", "f_stop",&error);
		if(error != 0x0){
			g_debug("%s", error->message);	
			hp8648c->f_stop = MAXF;
		}
		gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg->stop_frequency),hp8648c->f_stop);
	
		hp8648c->f_step = g_key_file_get_double(key_file, "SETTINGS", "f_Step",&error);	
		if(error != 0x0){
			g_debug("%s", error->message);	
			hp8648c->f_step = (hp8648c->f_stop - hp8648c->f_stop) / 100;
		}
		gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg->step_frequency),hp8648c->f_step);		
		
		hp8648c->rl = g_key_file_get_double(key_file, "SETTINGS", "rl",&error);
		if(error != 0x0){
			g_debug("%s", error->message);			
		}
		
		hp8648c->rl_start =g_key_file_get_double(key_file, "SETTINGS", "rl_start",&error);
		if(error != 0x0){
			g_debug("%s", error->message);
			hp8648c->rl_start = MINL;
		}
		gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg->start_level),hp8648c->rl_start);	

		hp8648c->rl_stop = g_key_file_get_double(key_file, "SETTINGS", "rl_stop",&error);
		if(error != 0x0){
			g_debug("%s", error->message);
			hp8648c->rl_stop = -20;	
		}
		gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg->step_level),hp8648c->rl_stop);						
		
		hp8648c->rl_step = g_key_file_get_double(key_file, "SETTINGS", "rl_step",&error);        
		if(error != 0x0){
			g_debug("%s", error->message);	
			hp8648c->rl_step = 0.1;
		}
		gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg->step_level),hp8648c->rl_step);
		
		g_key_file_get_double(key_file, "SETTINGS", "rsmd", &error);		
		if(error != 0x0){
			g_debug("%s", error->message);	
			sample_data->rmsd = 0.15;
		}
		gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg->rmsd_settings),sample_data->rmsd);		
		
		sample_data->avg_count = g_key_file_get_double(key_file, "SETTINGS", "avg_count", &error);
		if(error != 0x0){
			g_debug("%s", error->message);		
			sample_data->avg_count = SAMPLE;
		}
		gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg->number_avg),sample_data->avg_count);
				
	}					

	g_free(dir_name);
	
	gtk_spin_button_set_range(GTK_SPIN_BUTTON (wdg->start_frequency), MINF,MAXF);
	gtk_spin_button_set_range(GTK_SPIN_BUTTON (wdg->stop_frequency), MINF,MAXF);
		
	gtk_spin_button_set_range(GTK_SPIN_BUTTON (wdg->start_level), MINL,MAXL);
	gtk_spin_button_set_range(GTK_SPIN_BUTTON (wdg->stop_level), MINL,MAXL);						

	gtk_spin_button_set_range(GTK_SPIN_BUTTON (wdg->step_frequency),0.1,500);
	gtk_spin_button_set_range(GTK_SPIN_BUTTON (wdg->step_level),0.1,10);		

	gtk_spin_button_set_range(GTK_SPIN_BUTTON (wdg->number_avg),2,SAMPLE);
				
	hp8648c->run_f = 1;
		
		
	#ifdef DUMMYRUN
	sample_data->avg_count = 2;
	gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg->number_avg),sample_data->avg_count);
	hp8648c->f_step = 500;
	gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg->step_frequency),hp8648c->f_step);
	#endif

	#ifndef DUMMYRUN
	if (set_mode_hp8648c(hp8648c->ud,MOD_OFF, 0, RF_OFF) != 1)
		return -1;
	if( set_level_hp8648c(hp8648c->ud,hp8648c->rl_start) !=1 )
		return -1;
	if (set_frequency_hp8648c(hp8648c->ud, hp8648c->f_start)!= 1)
		return -1;	
	if (set_mode_hp436a(hp436a->ud,"9D-R") != 1)
		return -1;				
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
