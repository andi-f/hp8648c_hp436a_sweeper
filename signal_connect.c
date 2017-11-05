#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <glib/gprintf.h>

#include "debug.h"
#include "callback_widget.h"

void connection_mapper (GtkBuilder *builder, GObject *object,
	const gchar *signal_name, const gchar *handler_name,
	GObject *connect_object, GConnectFlags flags, sweeper_data *wdg_data)	{
	g_print ("Connect %s with %s\n", signal_name, handler_name);

	if (g_strcmp0 (handler_name, "on_window_main_destroy") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_window_main_destroy), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_imagemenuitem_new_activate") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_imagemenuitem_new_activate), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_imagemenuitem_open_activate") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_imagemenuitem_open_activate), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_imagemenuitem_save_activate") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_imagemenuitem_save_activate), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_imagemenuitem_save_as_activate") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_imagemenuitem_save_as_activate), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_imagemenuitem_export_pdf_activate") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_imagemenuitem_export_pdf_activate), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_imagemenuitem_export_png_activate") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_imagemenuitem_export_png_activate), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_imagemenuitem_quit_activate") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_imagemenuitem_quit_activate), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_gpib_address_activate") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_gpib_address_activate), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_imagemenuitem_about_activate") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_imagemenuitem_about_activate), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_cairo_drawing_configure_event") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_cairo_drawing_configure_event), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_cairo_drawing_draw") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_cairo_drawing_draw), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_frequency_sweep_rb_clicked") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_frequency_sweep_rb_clicked), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_power_sweeper_rb_clicked") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_power_sweeper_rb_clicked), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_rmsd_settings_value_changed") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_rmsd_settings_value_changed), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_start_level_value_changed") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_start_level_value_changed), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_stop_level_value_changed") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_stop_level_value_changed), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_step_level_value_changed") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_step_level_value_changed), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_number_avg_value_changed") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_number_avg_value_changed), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_start_frequency_value_changed") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_start_frequency_value_changed), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_stop_frequency_value_changed") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_stop_frequency_value_changed), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_step_frequency_value_changed") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_step_frequency_value_changed), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_log_scale_clicked") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_log_scale_clicked), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_band_2_clicked") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_band_2_clicked), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_band_70_clicked") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_band_70_clicked), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_band_23_clicked") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_band_23_clicked), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_band_13_clicked") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_band_13_clicked), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_gpib_address_dialog_destroy") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_gpib_address_dialog_destroy), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_hp8648c_gpib_spinbutton_value_changed") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_hp8648c_gpib_spinbutton_value_changed), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_start_button_clicked") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_start_button_clicked), wdg_data);
	else
		g_print ("\nunknown callback %s %s\n\n",signal_name, handler_name);
}
