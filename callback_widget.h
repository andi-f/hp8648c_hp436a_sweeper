#include <gtk/gtk.h>

#include "widget_structure.h"

extern void *on_window_main_destroy(GtkWidget *widget, sweeper_data *wdg_data);
extern void *menu_new_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *menu_open_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *menu_save_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *menu_save_as_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_window_main_destroy(GtkWidget *widget, sweeper_data *wdg_data);
extern void *menu_hp8648c_gp_ib_address(GtkWidget *widget, sweeper_data *wdg_data);
extern void *menu_hph463a_gpib_address(GtkWidget *widget, sweeper_data *wdg_data);
extern void *refresh_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *about(GtkWidget *widget, sweeper_data *wdg_data);
extern void *start_frequency_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *start_button_clicked_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *stop_frequency_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *start_level_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *stop_level_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *step_level_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *step_frequency_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *number_avg_value_changed_cb(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_frequency_sweep_rb_activate(GtkWidget *widget, sweeper_data *wdg_data);
extern void *on_power_sweeper_rb_activate(GtkWidget *widget, sweeper_data *wdg_data);
