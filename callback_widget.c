#include <gtk/gtk.h>
#include <glib/gprintf.h>
#include <gtk/gtk.h>

#include "widget_structure.h"

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

void number_avg_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"number_avg_value_changed_cb active\n");
}


