#include <gtk/gtk.h>
#include <cairo.h>

extern void k_plot(cairo_t *cr, gint	width, gint height);
extern void plot(cairo_t *cr, gint	width, gint height);
extern void create_png(GtkWidget *widget, gpointer data);
extern void create_pdf(GtkWidget *widget, gpointer data);
