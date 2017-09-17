#include <gtk/gtk.h>

extern void connection_mapper (GtkBuilder *builder, GObject *object,
	const gchar *signal_name, const gchar *handler_name,
	GObject *connect_object, GConnectFlags flags, gpointer user_data);

