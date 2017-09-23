#include "hp8648c_hp436a_sweeper.h"
#include "widget_structure.h"
#include <math.h>
	
int init(sweeper_data *wdg, hp8648c_record *hp8648c_settings)	{


	if (hp8648c_settings->f_stop < 3200)	{
		hp8648c_settings->f_stop = 3200;
		gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg->stop_frequency),hp8648c_settings->f_stop);
	}
	
	if (hp8648c_settings->f_start < 0.10)	{
		hp8648c_settings->f_start = 0.10;
		gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg->start_frequency),hp8648c_settings->f_start);
	}
	
	if (hp8648c_settings->f_start > hp8648c_settings->f_stop)	{
		hp8648c_settings->f_start = hp8648c_settings->f_stop;
		gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg->stop_frequency),hp8648c_settings->f_stop);		
	}

	if (hp8648c_settings->f_step < 0.001)	{
		hp8648c_settings->f_step = (hp8648c_settings->f_stop - hp8648c_settings->f_start) / 100;
		gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg->step_frequency),hp8648c_settings->f_step);		
	}
	
	if (hp8648c_settings->rl_start < -136)	{
		hp8648c_settings->rl_start = -136;
		gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg->start_level),hp8648c_settings->rl_start);				
	}
	
	if (hp8648c_settings->rl_stop > -20)	{
		hp8648c_settings->rl_stop = -20;
		gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg->step_level),hp8648c_settings->rl_stop);						
	}
	
	if (hp8648c_settings->rl_step < 0.1)	{
		hp8648c_settings->rl_step = 0.1;
		gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg->step_level),hp8648c_settings->rl_step);								
	}

	if (hp8648c_settings->rl_start > hp8648c_settings->rl_stop)	{
		hp8648c_settings->rl_start = hp8648c_settings->rl_stop;
		gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg->stop_level),hp8648c_settings->rl_stop);				
	}
	return 0;
}

