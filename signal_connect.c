#include <gtk/gtk.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <glib/gprintf.h>

#include "callback_widget.h"

void connection_mapper (GtkBuilder *builder, GObject *object,
	const gchar *signal_name, const gchar *handler_name,
	GObject *connect_object, GConnectFlags flags, sweeper_data *wdg_data)	{
	g_print ("Verbinde %s mit %s\n", signal_name, handler_name);

	if (g_strcmp0 (handler_name, "on_window_main_destroy") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_window_main_destroy), wdg_data);
	else
	if (g_strcmp0 (handler_name, "menu_new_cb") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(menu_new_cb), wdg_data);
	else
	if (g_strcmp0 (handler_name, "menu_open_cb") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(menu_open_cb), wdg_data);
	else
	if (g_strcmp0 (handler_name, "menu_save_cb") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(menu_save_cb), wdg_data);
	else
	if (g_strcmp0 (handler_name, "menu_save_as_cb") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(menu_save_as_cb), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_window_main_destroy") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_window_main_destroy), wdg_data);
	else
	if (g_strcmp0 (handler_name, "menu_hp8648c_gp_ib_address") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(menu_hp8648c_gp_ib_address), wdg_data);
	else
	if (g_strcmp0 (handler_name, "menu_hp436a_gpib_address") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(menu_hp436a_gpib_address), wdg_data);
	else
	if (g_strcmp0 (handler_name, "refresh_cb") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(refresh_cb), wdg_data);
	else
	if (g_strcmp0 (handler_name, "about") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(about), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_cairo_drawing_draw") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_cairo_drawing_draw), wdg_data);
	else
	if (g_strcmp0 (handler_name, "start_frequency_value_changed_cb") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(start_frequency_value_changed_cb), wdg_data);
	else
	if (g_strcmp0 (handler_name, "start_button_clicked_cb") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(start_button_clicked_cb), wdg_data);
	else
	if (g_strcmp0 (handler_name, "stop_frequency_value_changed_cb") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(stop_frequency_value_changed_cb), wdg_data);
	else
	if (g_strcmp0 (handler_name, "start_level_value_changed_cb") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(start_level_value_changed_cb), wdg_data);
	else
	if (g_strcmp0 (handler_name, "stop_level_value_changed_cb") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(stop_level_value_changed_cb), wdg_data);
	else
	if (g_strcmp0 (handler_name, "step_level_value_changed_cb") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(step_level_value_changed_cb), wdg_data);
	else
	if (g_strcmp0 (handler_name, "step_frequency_value_changed_cb") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(step_frequency_value_changed_cb), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_frequency_sweep_rb_toggled") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_frequency_sweep_rb_toggled), wdg_data);
	else
	if (g_strcmp0 (handler_name, "number_avg_value_changed_cb") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(number_avg_value_changed_cb), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_power_sweeper_rb_toggled") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_power_sweeper_rb_toggled), wdg_data);
	else
	if (g_strcmp0 (handler_name, "log_scale_toggled_cb") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(log_scale_toggled_cb), wdg_data);
	else
	if (g_strcmp0 (handler_name, "on_hp8648c_gbip_dialog_destroy") == 0)
		g_signal_connect (object, signal_name, G_CALLBACK(on_hp8648c_gbip_dialog_destroy), wdg_data);
	else
		g_print ("unknown callback\n");
}
