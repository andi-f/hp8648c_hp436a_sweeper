#include "hp8648c_hp436a_sweeper.h"
#include "hp8648c_hp436a.h"
#include "widget_structure.h"
#include "callback-gpib.h"
#include "run_sweep.h"
#include "drawing.h"
#include "init.h"

#include <glib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <glib/gprintf.h>
#include <glib/gstdio.h>

static cairo_surface_t *surface;

void save_file(sweeper_data *wdg_data)	{
	uint m;
	m_record	act_data;
	FILE *fp = g_fopen(wdg_data->filename_bin,"w+b");
	if (fp == NULL)	{
		wdg_data->statusbar_buffer = g_strdup_printf("Can not save file: %s\n\r",wdg_data->filename_bin);
		return;
	}
	for (m = 0; m < r_counter;m++){
		act_data = g_array_index(m_data, m_record, m);
		fwrite(&act_data, sizeof(act_data), 1, fp);				
	}
	fclose(fp);	
	wdg_data->statusbar_buffer = g_strdup_printf("Save file: %s",wdg_data->filename_bin);	
}

void save_file_as_csv(sweeper_data *wdg_data)	{
	m_record	act_data;
	gint m;	
	
	FILE *fp = fopen(wdg_data->filename,"w+t");
	if (fp == NULL)	{
		wdg_data->statusbar_buffer = g_strdup_printf("Can not open file: %s",wdg_data->filename);
		return;	
	}
	for (m = 0; m < r_counter;m++)	{
		act_data = g_array_index(m_data, m_record, m);
		fprintf(fp," f=%f %f %f %f\n", act_data.frequency, act_data.ref_level,act_data.avg_value, act_data.rmsd);
	}
	fclose(fp);	
	wdg_data->statusbar_buffer = g_strdup_printf("Open: %s",wdg_data->filename_bin);
}

void open_file(sweeper_data *wdg_data)	{
	m_record	act_data;
	
	FILE *fp = fopen(wdg_data->filename_bin,"r+b");
	if (fp == NULL)	{
		wdg_data->statusbar_buffer = g_strdup_printf("Can not open file: %s",wdg_data->filename_bin);
		return;
	}
	g_array_free(m_data, TRUE);
	m_data = g_array_new(FALSE, FALSE, sizeof(m_record));
	r_counter = 0;
	
	if(fp != NULL)	{
		while(fread(&act_data, sizeof(act_data), 1, fp)) {
			#ifdef DEBUG_LEVEL_2
			fprintf(stderr,"f=%lf rl=%lf l=%lf rmsd=%lf\n", act_data.frequency, act_data.ref_level,act_data.avg_value, act_data.rmsd);		
			#endif
			g_array_append_vals(m_data, &act_data,1);
			r_counter ++;		
		}
		fclose(fp);	
		wdg_data->statusbar_buffer = g_strdup_printf("Open: %s",wdg_data->filename_bin);	
	}
	else
	wdg_data->statusbar_buffer = g_strdup_printf("Could not read: %s",wdg_data->filename_bin);	
}

void on_window_main_destroy(GtkWidget *widget, sweeper_data *wdg_data)	{
	g_fprintf(stderr,"Close main window\n\r");
	if (wdg_data->statusbar_buffer != NULL)
		g_free(wdg_data->statusbar_buffer);
	if(m_data != NULL)
		g_array_free(m_data,TRUE);
	g_free(wdg_data->filename);
	if(wdg_data->window_main != NULL)
		gtk_main_quit();
	if (surface)
		cairo_surface_destroy (surface);		
}

void menu_quit_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	on_window_main_destroy(NULL,wdg_data);
}

void menu_new_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	g_array_free(m_data, TRUE);
	m_data = g_array_new(FALSE, FALSE, sizeof(m_record));
	r_counter = 0;
	wdg_data->statusbar_buffer = g_strdup_printf("Erasing data");	
}

void menu_open_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	GtkWidget *dialog;
	gint res;
	GtkFileFilter *filter;

	dialog = gtk_file_chooser_dialog_new ("Open File",
				      GTK_WINDOW(wdg_data->window_main),
				      GTK_FILE_CHOOSER_ACTION_OPEN,
				      "_Cancle", GTK_RESPONSE_CANCEL,
				      "_Open", GTK_RESPONSE_ACCEPT,
				      NULL);

    filter = gtk_file_filter_new();
    gtk_file_filter_add_pattern(filter,"*.dat");
    gtk_file_filter_set_name(filter,"Sweeper-file");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);

	res = gtk_dialog_run (GTK_DIALOG (dialog));
	if (res == GTK_RESPONSE_ACCEPT)  {
		GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
		
		wdg_data->filename_bin = gtk_file_chooser_get_filename (chooser);

		open_file (wdg_data);
	}
	gtk_widget_destroy (dialog);
	
}

void menu_save_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	save_file(wdg_data);
}

void menu_save_as_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	GtkWidget *dialog;
	GtkFileFilter *filter;
	
	dialog = gtk_file_chooser_dialog_new ("Save File",
				      GTK_WINDOW(wdg_data->window_main),
				      GTK_FILE_CHOOSER_ACTION_SAVE,
				      "_Cancle", GTK_RESPONSE_CANCEL,
				      "_Save", GTK_RESPONSE_ACCEPT,
				      NULL);
	
    filter = gtk_file_filter_new();
    gtk_file_filter_add_pattern(filter,"*.dat");
    gtk_file_filter_set_name(filter,"Sweeper-file");
    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(dialog), filter);
    
	gtk_file_chooser_set_do_overwrite_confirmation (GTK_FILE_CHOOSER (dialog), TRUE);
	gtk_file_chooser_set_current_folder (GTK_FILE_CHOOSER (dialog), g_get_user_special_dir(G_USER_DIRECTORY_DOCUMENTS));
	gtk_file_chooser_set_current_name (GTK_FILE_CHOOSER (dialog), "Untitled document");

	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT)  {
		wdg_data->filename_bin = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (dialog));
		save_file(wdg_data);
	}
	gtk_widget_destroy (dialog);
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
		#ifdef DEBUG_LEVEL_2
		fprintf(stderr,"start_button_clicked_cb active: started\n");
		#endif		
		
		sample_data.sample = 0;
		sample_data.avg_value = 0;
		sample_data.diff_avg = 0;
		sample_data.rmsd = 0;

		GDateTime *datetime = g_date_time_new_now_utc ();
		gchar * timestamp = g_date_time_format (datetime,"%Y%m%d%H%M%S");
		
		if(wdg_data->dut_desc_buffer != NULL) {
			g_snprintf(wdg_data->filename , 255, "%s_%s_hp8648c_hp436a.csv",timestamp,wdg_data->dut_desc_buffer);
			g_snprintf(wdg_data->filename_bin, 255, "%s_%s_hp8648c_hp436a.dat",timestamp,wdg_data->dut_desc_buffer);
		}
		else
		{
			g_snprintf(wdg_data->filename , 255, "%s_hp8648c_hp436a.csv",timestamp);
			g_snprintf(wdg_data->filename_bin, 255, "%s_hp8648c_hp436a.dat",timestamp);
		}

	}
	else	{
		hp8648c.run = 0;		
		#ifdef DEBUG_LEVEL_2	
		fprintf(stderr,"start_button_clicked_cb active: stopped\n");
		#endif
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
	hp8648c.rl_stop = gtk_spin_button_get_value(GTK_SPIN_BUTTON(wdg_data->stop_level));
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

void log_scale_toggled_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"log_scale_toggled\n");
}

void cairo_drawing_configure_event_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	
}

gboolean timer_draw_diagram (gpointer data)	{
	sweeper_data *wdg_data = (sweeper_data *) data;

	cairo_t *cr;
	
	cr = gdk_cairo_create(gtk_widget_get_window(wdg_data->cairo_drawing));
	
	k_plot(cr, gtk_widget_get_allocated_width (wdg_data->cairo_drawing),gtk_widget_get_allocated_height (wdg_data->cairo_drawing));
	
	cairo_destroy(cr);
		
	gtk_widget_queue_draw_area (wdg_data->cairo_drawing, 0, 0, gtk_widget_get_allocated_width (wdg_data->cairo_drawing), gtk_widget_get_allocated_height (wdg_data->cairo_drawing));  	
	return TRUE;
}

gboolean on_cairo_drawing_draw(GtkWidget *widget, cairo_t *cr, sweeper_data *wdg_data)	{
	
	k_plot(cr, gtk_widget_get_allocated_width (wdg_data->cairo_drawing),gtk_widget_get_allocated_height (wdg_data->cairo_drawing));
	return TRUE;
}
	
gboolean timer_statusbar (gpointer data)	{
	sweeper_data *wdg_data = (sweeper_data *) data;
	gtk_statusbar_push (GTK_STATUSBAR(wdg_data->statusbar1), wdg_data->context_id, wdg_data->statusbar_buffer);
	return TRUE;
}

void dut_desciption_changed_cb(GtkWidget *widget, sweeper_data *wdg_data)	{
	wdg_data->dut_desc_buffer = gtk_entry_buffer_get_text (gtk_entry_get_buffer (wdg_data->dut_desciption));
	fprintf(stderr,"dut_desciption_changed %s\n",wdg_data->dut_desc_buffer);
}
	
void on_imagemenuitem_export_pdf_activate(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"on_imagemenuitem_export_pdf_activate active\n");
	create_pdf(widget, NULL);
}

void on_imagemenuitem_export_png_activate(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"on_imagemenuitem_export_png_activate active\n");
	create_png(widget, NULL);
}


void on_gpib_address_dialog_destroy(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"on_GPIB address_destroy active\n");
}

void on_hp8648c_gpib_spinbutton_change_value(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"on_hp8648c_gpib_spinbutton_change_value active\n");
}

void on_hp436a_gpib_spinbutton_change_value(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"on_hp436a_gpib_spinbutton_change_value active\n");
}

void on_gpib_address_dialog_response(GtkWidget *widget, sweeper_data *wdg_data)	{
	fprintf(stderr,"on_gpib_address_dialog_response active\n");
}

void menu_gpib_address(GtkWidget *widget, sweeper_data *wdg_data)	{
	
	if (hp8648c.run == 0 )	{
		int result = gtk_dialog_run (GTK_DIALOG (wdg_data->gpib_address_dialog));
		switch (result)	{
			case 1:	
				hp8648c.device = gtk_spin_button_get_value(GTK_SPIN_BUTTON (wdg_data->hp8648c_gpib_spinbutton));
				hp436a.device = gtk_spin_button_get_value(GTK_SPIN_BUTTON (wdg_data->hp436a_gpib_spinbutton));
				wdg_data->statusbar_buffer = g_strdup_printf("Change settings");
				init_gpib_devices(wdg_data,&hp8648c,&hp436a);
				#ifdef DEBUG_LEVEL_2
					fprintf(stderr,"New address  HP8648C:%u HP436A:%u\n", hp8648c.device,hp436a.device);
				#endif
			break;
			default:	
				gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg_data->hp436a_gpib_spinbutton), hp436a.device);
				gtk_spin_button_set_value(GTK_SPIN_BUTTON (wdg_data->hp8648c_gpib_spinbutton),hp8648c.device);
				#ifdef DEBUG_LEVEL_2
					fprintf(stderr,"Abort\n");
				#endif
			break;
		}
	}
	else
		wdg_data->statusbar_buffer = g_strdup_printf("Not allowed during testrun");
		gtk_widget_hide (wdg_data->gpib_address_dialog);		
}
