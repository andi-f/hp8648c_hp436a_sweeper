#include <gtk/gtk.h>
#include "widget_structure.h"

extern void *on_window_main_destroy(GtkWidget *widget, sweeper_data *wdg_data);
extern void *menu_new_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *menu_open_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *menu_save_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *menu_save_as_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_window_main_destroy(GtkWidget *widget, sweeper_data *wdg_data);
extern void *menu_hp8648c_gp_ib_address(GtkWidget *widget, sweeper_data *wdg_data);
extern void *menu_hp436a_gpib_address(GtkWidget *widget, sweeper_data *wdg_data);
extern void *refresh_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *about(GtkWidget *widget, sweeper_data *wdg_data);
extern void *start_frequency_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *start_button_clicked_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *stop_frequency_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *start_level_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *stop_level_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *step_level_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *step_frequency_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_frequency_sweep_rb_toggled(GtkWidget *widget, sweeper_data *wdg_data);
extern void *number_avg_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_power_sweeper_rb_toggled(GtkWidget *widget, sweeper_data *wdg_data);
extern void *log_scale_toggled_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_hp8648c_gbip_dialog_destroy(GtkWidget *widget, sweeper_data *wdg_data);
extern void *dut_desciption_changed_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern gboolean on_cairo_drawing_draw(GtkWidget *widget, cairo_t *cr, sweeper_data *wdg_data);


extern gboolean timer_statusbar (gpointer data);
