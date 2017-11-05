#include <gtk/gtk.h>

#include "widget_structure.h"

extern void *on_window_main_destroy(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_imagemenuitem_new_activate(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_imagemenuitem_open_activate(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_imagemenuitem_save_activate(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_imagemenuitem_save_as_activate(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_imagemenuitem_export_pdf_activate(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_imagemenuitem_export_png_activate(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_imagemenuitem_quit_activate(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_gpib_address_activate(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_imagemenuitem_about_activate(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_cairo_drawing_configure_event(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_cairo_drawing_draw(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_frequency_sweep_rb_clicked(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_power_sweeper_rb_clicked(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_rmsd_settings_value_changed(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_start_level_value_changed(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_stop_level_value_changed(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_step_level_value_changed(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_number_avg_value_changed(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_start_frequency_value_changed(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_stop_frequency_value_changed(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_step_frequency_value_changed(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_log_scale_clicked(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_band_2_clicked(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_band_70_clicked(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_band_23_clicked(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_band_13_clicked(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_gpib_address_dialog_destroy(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_hp8648c_gpib_spinbutton_value_changed(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_hp436a_gpib_spinbutton_value_changed(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_start_button_clicked(GtkWidget *widget, sweeper_data *wdg_data);

	
extern void save_file(sweeper_data *wdg_data);
extern gboolean timer_statusbar (gpointer data);
extern gboolean timer_draw_diagram (gpointer data);
