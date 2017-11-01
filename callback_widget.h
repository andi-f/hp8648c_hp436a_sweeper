#include <gtk/gtk.h>
#include "widget_structure.h"

extern void *on_gpib_address_dialog_close(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_gpib_address_dialog_response(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_gpib_address_dialog_destroy(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_gpib_address_OK_clicked(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_gpib_address_Cancle_clicked(GtkWidget *widget, sweeper_data *wdg_data);
extern void on_hp8648c_gpib_spinbutton_change_value(GtkWidget *widget, sweeper_data *wdg_data);
extern void on_hp436a_gpib_spinbutton_change_value(GtkWidget *widget, sweeper_data *wdg_data);


extern void *on_window_main_destroy(GtkWidget *widget, sweeper_data *wdg_data);
extern void *menu_new_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *menu_open_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *menu_save_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *menu_save_as_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_imagemenuitem_export_pdf_activate(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_imagemenuitem_export_png_activate(GtkWidget *widget, sweeper_data *wdg_data);
extern void *menu_quit_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *menu_gpib_address(GtkWidget *widget, sweeper_data *wdg_data);
extern void *about(GtkWidget *widget, sweeper_data *wdg_data);

extern void *cairo_drawing_configure_event_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_cairo_drawing_draw(GtkWidget *widget, sweeper_data *wdg_data);
extern void *start_frequency_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *start_button_clicked_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *stop_frequency_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *start_level_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *stop_level_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *step_level_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *step_frequency_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *number_avg_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *log_scale_toggled_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *dut_desciption_changed_cb(GtkWidget *widget, sweeper_data *wdg_data);;

extern void on_hp8648c_gpib_spinbutton_change_value(GtkWidget *widget, sweeper_data *wdg_data);
extern void on_hp436a_gpib_spinbutton_change_value(GtkWidget *widget, sweeper_data *wdg_data);

extern void save_file(sweeper_data *wdg_data);
extern gboolean timer_statusbar (gpointer data);
extern gboolean timer_draw_diagram (gpointer data);
