#include "callback_widget.h"
#include "signal_connect.h"

void wdg_main(sweeper_data *wdg_data)	{
	wdg_data->builder = gtk_builder_new();
	gtk_builder_add_from_file (wdg_data->builder, "hp8648c_hp436a_sweeper.glade", NULL);	wdg_data->aboutdialog = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "aboutdialog"));
	wdg_data->aboutdialog_vbox = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "aboutdialog_vbox"));
	wdg_data->aboutdialog_action_area = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "aboutdialog_action_area"));
	wdg_data->image1 = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "image1"));
	wdg_data->image2 = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "image2"));
	wdg_data->window_main = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "window_main"));
	wdg_data->vbox_main = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "vbox_main"));
	wdg_data->menubar1 = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "menubar1"));
	wdg_data->menuitem_file = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "menuitem_file"));
	wdg_data->menu_file = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "menu_file"));
	wdg_data->imagemenuitem_new = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "imagemenuitem_new"));
	wdg_data->imagemenuitem_open = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "imagemenuitem_open"));
	wdg_data->imagemenuitem_save = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "imagemenuitem_save"));
	wdg_data->imagemenuitem_save_as = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "imagemenuitem_save_as"));
	wdg_data->separatormenuitem1 = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "separatormenuitem1"));
	wdg_data->imagemenuitem_quit = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "imagemenuitem_quit"));
	wdg_data->menuitem_settings = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "menuitem_settings"));
	wdg_data->menu_settings = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "menu_settings"));
	wdg_data->imagemenuitem_hp8648c_gpib_address = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "imagemenuitem_hp8648c_gpib_address"));
	wdg_data->imagemenuitem_hp436a_gpib_address = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "imagemenuitem_hp436a_gpib_address"));
	wdg_data->menuitem_refresh = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "menuitem_refresh"));
	wdg_data->menuitem_help = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "menuitem_help"));
	wdg_data->menu_help = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "menu_help"));
	wdg_data->imagemenuitemabout = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "imagemenuitemabout"));
	wdg_data->hbox_main = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "hbox_main"));
	wdg_data->cairo_drawing = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "cairo_drawing"));
	wdg_data->grid1 = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "grid1"));
	wdg_data->start_frequency_label = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "start_frequency_label"));
	wdg_data->start_frequency = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "start_frequency"));
	wdg_data->step__frequency_label = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "step__frequency_label"));
	wdg_data->start_button = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "start_button"));
	wdg_data->stop_frequency_label = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "stop_frequency_label"));
	wdg_data->stop_frequency = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "stop_frequency"));
	wdg_data->Start_level_label = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "Start_level_label"));
	wdg_data->start_level = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "start_level"));
	wdg_data->stop_level_label = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "stop_level_label"));
	wdg_data->stop_level = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "stop_level"));
	wdg_data->label1 = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "label1"));
	wdg_data->step_level = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "step_level"));
	wdg_data->step_frequency = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "step_frequency"));
	wdg_data->frequency_sweep_rb = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "frequency_sweep_rb"));
	wdg_data->number_average_label = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "number_average_label"));
	wdg_data->number_avg = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "number_avg"));
	wdg_data->power_sweeper_rb = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "power_sweeper_rb"));
	wdg_data->statusbar1 = GTK_WIDGET(gtk_builder_get_object(wdg_data->builder, "statusbar1"));
	gtk_builder_connect_signals_full (wdg_data->builder, connection_mapper, (gpointer*) wdg_data);
	g_object_unref(wdg_data->builder);
;}
