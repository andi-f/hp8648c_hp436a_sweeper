#include "hp8648c_hp436a_sweeper.h"
#include "widget_structure.h"
#include "callback-gpib.h"
#include "run_sweep.h"

#include <gtk/gtk.h>
#include <glib/gprintf.h>
#include <gtk/gtk.h>

#define NODEBUG_LEVEL_3
#define NODEBUG_LEVEL_2
#define NODEBUG_LEVEL_1

void on_window_main_destroy(GtkWidget *widget, sweeper_data *wdg_data)	{
	g_fprintf(stderr,"Leaving program\n\r");
    gtk_main_quit();
}

void menu_new_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"menu_new_cb active\n");
}

void menu_open_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"menu_open_cb active\n");
}

void menu_save_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"menu_save_cb active\n");
}

void menu_save_as_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"menu_save_as_cb active\n");
}

void menu_hp8648c_gp_ib_address(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"menu_hp8648c_gp_ib_address active\n");
}

void menu_hph463a_gpib_address(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"menu_hph463a_gpib_address active\n");
}

void refresh_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"refresh_cb active\n");
}

void about(GtkWidget *widget, sweeper_data *wdg_data)	{
    gtk_dialog_run( GTK_DIALOG( wdg_data->aboutdialog) );
    gtk_widget_hide( wdg_data->aboutdialog);
}

void start_frequency_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	hp8648c_data.f_start = gtk_spin_button_get_value(GTK_SPIN_BUTTON(wdg_data->start_frequency));
	#ifdef DEBUG_LEVEL_2	
		fprintf(stderr,"start_frequency_value_changed_cb active\n");
	#endif
}

void start_button_clicked_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	hp8648c_data.run = 1;
	if (hp8648c_data.f == 1)
		run_sweep_f();
	else
	if (hp8648c_data.f == 0)
		run_sweep_p();
		
	#ifdef DEBUG_LEVEL_2	
		fprintf(stderr,"start_button_clicked_cb active\n");
	#endif		
}

void stop_frequency_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	hp8648c_data.f_stop = gtk_spin_button_get_value(GTK_SPIN_BUTTON(wdg_data->stop_frequency));
	#ifdef DEBUG_LEVEL_2	
		fprintf(stderr,"stop_frequency_value_changed_cb active\n");
	#endif	
}

void start_level_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	hp8648c_data.rl_start = gtk_spin_button_get_value(GTK_SPIN_BUTTON(wdg_data->start_level));
	#ifdef DEBUG_LEVEL_2	
		fprintf(stderr,"start_level_value_changed_cb active\n");
	#endif
}

void stop_level_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	hp8648c_data.rl_start = gtk_spin_button_get_value(GTK_SPIN_BUTTON(wdg_data->step_level));
	#ifdef DEBUG_LEVEL_2	
		fprintf(stderr,"stop_level_value_changed_cb active\n");
	#endif		
}

void step_level_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	hp8648c_data.rl_step = gtk_spin_button_get_value(GTK_SPIN_BUTTON(wdg_data->step_level));
	#ifdef DEBUG_LEVEL_2	
		fprintf(stderr,"step_level_value_changed_cb active\n");
	#endif		
}

void step_frequency_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	hp8648c_data.f_step = gtk_spin_button_get_value(GTK_SPIN_BUTTON(wdg_data->step_frequency));
	#ifdef DEBUG_LEVEL_2	
		fprintf(stderr,"step_level_value_changed_cb active\n");
	#endif		
}

void number_avg_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	sample_data.avg_count = gtk_spin_button_get_value(GTK_SPIN_BUTTON(wdg_data->number_avg));
	#ifdef DEBUG_LEVEL_2	
	fprintf(stderr,"number_avg_value_changed_cb active\n");
	#endif		
}

void on_frequency_sweep_rb_activate(GtkWidget *widget, sweeper_data *wdg_data)	{
	hp8648c_data.run_f = 1;
	#ifdef DEBUG_LEVEL_2
	fprintf(stderr,"on_frequency_sweep_rb_activate active\n");
	#endif
}

void on_power_sweeper_rb_activate(GtkWidget *widget, sweeper_data *wdg_data)	{
	hp8648c_data.run_f = 0;
	#ifdef DEBUG_LEVEL_2	
	fprintf(stderr,"on_power_sweeper_rb_activate active\n");
	#endif
}


void on_hp8648c_gbip_dialog_destroy(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"on_hp8648c_gbip_dialog_destroy active\n");
}


/*
void on_window_main_destroy(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"on_window_main_destroy active\n");
}

void menu_new_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"menu_new_cb active\n");
}

void menu_open_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"menu_open_cb active\n");
}

void menu_save_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"menu_save_cb active\n");
}

void menu_save_as_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"menu_save_as_cb active\n");
}

void on_window_main_destroy(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"on_window_main_destroy active\n");
}

void menu_hp8648c_gp_ib_address(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"menu_hp8648c_gp_ib_address active\n");
}

void menu_hph463a_gpib_address(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"menu_hph463a_gpib_address active\n");
}

void refresh_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"refresh_cb active\n");
}

void about(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"about active\n");
}

void start_frequency_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"start_frequency_value_changed_cb active\n");
}

void start_button_clicked_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"start_button_clicked_cb active\n");
}

void stop_frequency_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"stop_frequency_value_changed_cb active\n");
}

void start_level_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"start_level_value_changed_cb active\n");
}

void stop_level_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"stop_level_value_changed_cb active\n");
}

void step_level_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"step_level_value_changed_cb active\n");
}

void step_frequency_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"step_frequency_value_changed_cb active\n");
}

void on_frequency_sweep_rb_activate(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"on_frequency_sweep_rb_activate active\n");
}

void number_avg_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"number_avg_value_changed_cb active\n");
}

void on_power_sweeper_rb_activate(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"on_power_sweeper_rb_activate active\n");
}




*/
