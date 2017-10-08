#include "hp8648c_hp436a_sweeper.h"
#include "hp8648c_hp436a.h"
#include "widget_structure.h"
#include "callback-gpib.h"
#include "run_sweep.h"

#include <gtk/gtk.h>
#include <glib/gprintf.h>
#include <gtk/gtk.h>

#define MO_DEBUG_LEVEL_1

void on_window_main_destroy(GtkWidget *widget, sweeper_data *wdg_data)	{
	g_fprintf(stderr,"Leaving program\n\r");
	g_free(wdg_data->statusbar_buffer);
	g_array_free(m_data,TRUE);
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

void about(GtkWidget *widget, sweeper_data *wdg_data)	{
    gtk_dialog_run( GTK_DIALOG( wdg_data->aboutdialog) );
    gtk_widget_hide( wdg_data->aboutdialog);
}

void start_frequency_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	hp8648c.f_start = gtk_spin_button_get_value(GTK_SPIN_BUTTON(wdg_data->start_frequency));
	#ifdef DEBUG_LEVEL_1	
		fprintf(stderr,"start_frequency_value_changed_cb active\n");
	#endif
}

void start_button_clicked_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	
	if(hp8648c.run != 1){
		hp8648c.run = 1;
		sample_data.sample = 0;
		sample_data.avg_value = 0;
		sample_data.diff_avg = 0;
		sample_data.rmsd = 0;
		wdg_data->sweep_timer = g_timeout_add (1000, timer_sweep, wdg_data);	
		
	}
	else	{
		hp8648c.run = 0;		
		g_source_remove (wdg_data->sweep_timer);
	}
		
	#ifdef DEBUG_LEVEL_1	
		fprintf(stderr,"start_button_clicked_cb active\n");
	#endif		
}

void stop_frequency_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	hp8648c.f_stop = gtk_spin_button_get_value(GTK_SPIN_BUTTON(wdg_data->stop_frequency));
	#ifdef DEBUG_LEVEL_1	
		fprintf(stderr,"stop_frequency_value_changed_cb active\n");
	#endif	
}

void start_level_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	hp8648c.rl_start = gtk_spin_button_get_value(GTK_SPIN_BUTTON(wdg_data->start_level));
	#ifdef DEBUG_LEVEL_1	
		fprintf(stderr,"start_level_value_changed_cb active\n");
	#endif
}

void stop_level_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	hp8648c.rl_stop = gtk_spin_button_get_value(GTK_SPIN_BUTTON(wdg_data->step_level));
	#ifdef DEBUG_LEVEL_1	
		fprintf(stderr,"stop_level_value_changed_cb active\n");
	#endif		
}

void step_level_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	hp8648c.rl_step = gtk_spin_button_get_value(GTK_SPIN_BUTTON(wdg_data->step_level));
	#ifdef DEBUG_LEVEL_1	
		fprintf(stderr,"step_level_value_changed_cb active\n");
	#endif		
}

void step_frequency_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	hp8648c.f_step = gtk_spin_button_get_value(GTK_SPIN_BUTTON(wdg_data->step_frequency));
	#ifdef DEBUG_LEVEL_1	
		fprintf(stderr,"step_level_value_changed_cb active\n");
	#endif		
}

void number_avg_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	sample_data.avg_count = gtk_spin_button_get_value(GTK_SPIN_BUTTON(wdg_data->number_avg));
	#ifdef DEBUG_LEVEL_1	
	fprintf(stderr,"number_avg_value_changed_cb active\n");
	#endif		
}

void on_frequency_sweep_rb_toggled(GtkWidget *widget, sweeper_data *wdg_data)	{
	hp8648c.run_f = 1;
	#ifdef DEBUG_LEVEL_1
	fprintf(stderr,"on_frequency_sweep_rb_activate active\n");
	#endif
}

void on_power_sweeper_rb_toggled(GtkWidget *widget, sweeper_data *wdg_data)	{
	hp8648c.run_f = 0;
	#ifdef DEBUG_LEVEL_1	
	fprintf(stderr,"on_power_sweeper_rb_activate active\n");
	#endif
}

void on_hp8648c_gbip_dialog_destroy(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"on_hp8648c_gbip_dialog_destroy active\n");
}

gboolean timer_statusbar (gpointer data)	{
	sweeper_data *wdg_data = (sweeper_data *) data;
	
	gtk_statusbar_push (GTK_STATUSBAR(wdg_data->statusbar1), wdg_data->context_id, wdg_data->statusbar_buffer);
	
    return 1;
}

void menu_save_as_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"menu_save_as_cb active\n");
}

void menu_hp8648c_gp_ib_address(GtkWidget *widget, sweeper_data *wdg_data)	{
	int result = gtk_dialog_run (GTK_DIALOG (wdg_data->hp8648c_gbip_dialog));
	switch (result)
	{
		case GTK_RESPONSE_ACCEPT:
			fprintf(stderr,"menu_hp8648c_gp_ib_address changed\n");
		break;
		default:
			fprintf(stderr,"menu_hp8648c_gp_ib_address canceled\n");
		break;
	}
	gtk_widget_destroy (wdg_data->hp8648c_gbip_dialog);
	fprintf(stderr,"menu_hp8648c_gp_ib_address active\n");
}

void menu_hp436a_gpib_address(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"menu_hph436a_gpib_address active\n");
}

void refresh_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"refresh_cb active\n");
}

void log_scale_toggled_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"log_scale_toggled\n");
}

gboolean on_cairo_drawing_draw(GtkWidget *widget, cairo_t *cr, sweeper_data *wdg_data)	{
  guint width, height;
  GdkRGBA color;

  width = gtk_widget_get_allocated_width (widget);
  height = gtk_widget_get_allocated_height (widget);
  cairo_arc (cr,
             width / 2.0, height / 2.0,
             MIN (width, height) / 2.0,
             0, 2 * G_PI);

  gtk_style_context_get_color (gtk_widget_get_style_context (widget),
                               0,
                               &color);
  gdk_cairo_set_source_rgba (cr, &color);

  cairo_fill (cr);

 return FALSE;
}

void dut_desciption_changed_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"dut_desciption_changed\n");
}
