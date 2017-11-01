#include <gtk/gtk.h>

typedef struct {
GtkBuilder *builder;

GtkWidget *aboutdialog;
GtkWidget *aboutdialog_vbox;
GtkWidget *aboutdialog_action_area;

GtkAdjustment *adj_hp436a_gpib_spinbutton;
GtkAdjustment *adj_hp8648c_gpib_spinbutton;
GtkWidget *gpib_address_dialog;
GtkWidget *gpib_address_vbox;
GtkWidget *gpib_address_dialog_action_area;
GtkWidget *gpib_address_Cancle;
GtkWidget *gpib_address_OK;
GtkWidget *gpib_address_grid;
GtkWidget *hp8648c_gpib_spinbutton;
GtkWidget *hp436a_gpib_spinbutton;
GtkWidget *hp8648c_gpib_label;
GtkWidget *hp436a_gpib_label;

GtkAdjustment *adj_number_avg;
GtkAdjustment *adj_scale_adxxx;
GtkAdjustment *adj_start_frequency;
GtkAdjustment *adj_start_level;
GtkAdjustment *adj_step_frequency;
GtkAdjustment *adj_step_level;
GtkAdjustment *adj_stop_frequency;
GtkAdjustment *adj_stop_level;

GtkWidget *window_main;
GtkWidget *vbox_main;
GtkWidget *menubar1;
GtkWidget *menuitem_file;
GtkWidget *menu_file;
GtkWidget *imagemenuitem_new;
GtkWidget *imagemenuitem_open;
GtkWidget *imagemenuitem_save;
GtkWidget *imagemenuitem_save_as;
GtkWidget *separatormenuitem1;
GtkWidget *imagemenuitem_export_pdf;
GtkWidget *imagemenuitem_export_png;
GtkWidget *separatormenuitem2;
GtkWidget *imagemenuitem_quit;
GtkWidget *menuitem_settings;
GtkWidget *menu_settings;
GtkWidget *gpib_address;
GtkWidget *menuitem_help;
GtkWidget *menu_help;
GtkWidget *imagemenuitemabout;

GtkWidget *hbox_main;
GtkWidget *cairo_drawing;
GtkWidget *grid1;
GtkWidget *start_frequency_label;
GtkWidget *start_frequency;
GtkWidget *step__frequency_label;
GtkWidget *start_button;
GtkWidget *stop_frequency_label;
GtkWidget *stop_frequency;
GtkWidget *Start_level_label;
GtkWidget *start_level;
GtkWidget *stop_level_label;
GtkWidget *stop_level;
GtkWidget *label1;
GtkWidget *step_level;
GtkWidget *step_frequency;
GtkWidget *number_average_label;
GtkWidget *number_avg;
GtkWidget *log_scale;
GtkWidget *run_f_pwr;
GtkWidget *frequency_sweep_rb;
GtkWidget *power_sweeper_rb;
GtkWidget *dut;
GtkWidget *dut_description_label;
GtkWidget *dut_description;
GtkWidget *statusbar1;

GtkImage *export_pdf_image;
GtkImage *export_png_image;
GtkImage *gpib_settings;

GtkEntry *dut_desciption;
gchar *statusbar_buffer;
gchar *filename;
gchar *filename_bin;
const gchar *dut_desc_buffer;
gint context_id;
gint statusbar_timer;
gint sweep_timer;
gint timer_draw_diagram;

GtkEntryBuffer *dut_desc_entrybuffer;
} sweeper_data;
