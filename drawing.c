#include <ctype.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/time.h>      
#include <sys/types.h>
#include <sys/stat.h>
#include <gtk/gtk.h>

#include <cairo.h>
#include <cairo-pdf.h>

#include "run_sweep.h"

#define NODEBUG_LEVEL_1

void plot(cairo_t *cr, gint	width, gint height) {
	double		Y;						// actual value
	double 		T;
	
	double		X_DIV = 10.0;			// 10 div/x
	double		Y_DIV = 8.0;			// 10 div/y

	double		MAX_Y = 6000.0;			// max Y scale
	double		MIN_Y = 0.0;			// min Y scale
	double		MAX_X = 100.0;			// max X scale
	double		MIN_X = 0.0;			// min X scale

	double 		XMAX;					// max dots x-scale
	double 		YMAX;					// max dots y-scale
	double 		XOFFSET;				// start of diagramm
	double		YOFFSET;				// start of diagramm
	double		x, y;					// actual plot postion
	double		x_alt,y_alt;			// last plot postion
	double		x_scale,y_scale;		// scale for axis
	double		x_zero,y_zero;			// point of origin
	char		string_buf[80];			// line buffer
	
	int			m = 0;					// counter Cario
	
	cairo_rectangle(cr, 0.0, 0.0, width, height);
	cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
	cairo_fill(cr);

	cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
 
	cairo_set_font_size(cr, 10.0);
	cairo_set_line_width(cr, 1.0);

	XMAX = 0.8 * width;
	YMAX = 0.8 * height;

	XOFFSET = 0.5 * (width-XMAX);
	YOFFSET = 0.5 * (height-YMAX);

	x_scale = XMAX / (MAX_X-MIN_X);
	y_scale = YMAX / (MAX_Y-MIN_Y);		
	
	x_zero = - MIN_X * x_scale + XOFFSET;
	y_zero = YMAX - MIN_Y * y_scale + YOFFSET;
	cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
	
	sprintf(string_buf,"%s %s",PROGRAM,VERSION);
	cairo_move_to (cr,10, 0.2* YOFFSET);
	cairo_show_text(cr, string_buf); 	

	cairo_stroke(cr);

	for(m = 0; m < X_DIV+1;m ++)
	{
		x =  m * XMAX / X_DIV + XOFFSET;
		if( (x >= XOFFSET) && (x <= XOFFSET+XMAX) )
		{
			cairo_move_to(cr,x,YOFFSET);
			cairo_line_to(cr,x,YMAX+YOFFSET);
		}
		sprintf(string_buf,"% 3.1f",MIN_X + m / X_DIV * (MAX_X-MIN_X) );
		cairo_move_to(cr,x-10,YOFFSET+YMAX+10);
		cairo_show_text(cr, string_buf);
	}

	for(m = 0; m < Y_DIV+1;m ++)
	{
		y = m * YMAX / Y_DIV + YOFFSET;

		cairo_move_to(cr,XOFFSET,y);
		cairo_line_to (cr,XMAX+XOFFSET,y);
		
		sprintf(string_buf,"% 3.1f",MAX_Y - m / Y_DIV * (MAX_Y-MIN_Y) );
		cairo_move_to(cr,20,y);
		cairo_show_text(cr, string_buf); 	
	}

	cairo_move_to(cr,0,YMAX/2+YOFFSET);
	cairo_show_text(cr,"xx"); 	
	cairo_stroke(cr);

	cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);
	if (record_counter != 0)	{
		m = 0;
		record = g_array_index(m_data, struct m_record, m);
		Y = record.value;
		T = (double) record.timestamp;
	
		if(Y > MAX_Y)
		{
			Y = MAX_Y;
		}
		else
		if(Y < MIN_Y)
		{
			Y = MIN_Y;
		}
		x_alt =  x_zero + T * x_scale;
		y_alt =  y_zero - Y * y_scale;
		
		for(m = 1; m <= record_counter-1; m ++)
		{
			record = g_array_index(m_data, struct m_record, m);
			Y = record.value;
			T = (double) record.timestamp;
		
			if(Y > MAX_Y)
			{
				Y = MAX_Y;
			}
			else
			if(Y < MIN_Y)
			{
				Y = MIN_Y;
			}

			x =  x_zero + T * x_scale;
			y =  y_zero - Y * y_scale;

			//fprintf(stderr," %f %f \n\r",T,Y);
			
			if( (x_alt >= XOFFSET) && (x <= XOFFSET+XMAX) )
			{
				cairo_move_to(cr,x_alt,y_alt);
				cairo_line_to (cr,x,y);
			}				
			x_alt = x;
			y_alt = y;
		}
		cairo_stroke(cr);		
	}
	return;
}

void create_png(GtkWidget *widget, gpointer data) {

	gint width = 800, height = 800;					// Window width & height
	
	cairo_surface_t *surface;
	cairo_t *cr;

	surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
	cr = cairo_create(surface);

	//plot(cr, width,height,&record);

	time_t      timeStamp;
	struct tm * timeInfo;
	char        buffer[80];
 
	time( &timeStamp );
	timeInfo = localtime( &timeStamp );
 
	strftime( buffer, 60, "%Y%m%d%H%M%S_image.png", timeInfo );
    	
	cairo_surface_write_to_png(surface, buffer);
	
	cairo_surface_destroy(surface);

	cairo_destroy(cr);

  return;
}

void create_pdf(GtkWidget *widget, gpointer data) {
	gint width = 800, height = 800;					// Window width & height
	
	cairo_surface_t *surface;
	cairo_t *cr;

	time_t      timeStamp;
	struct tm * timeInfo;
	char        buffer[80];
 
	time( &timeStamp );
	timeInfo = localtime( &timeStamp );
 
	strftime( buffer, 60, "%Y%m%d%H%M%S_image.pdf", timeInfo );
	
	surface = cairo_pdf_surface_create (buffer, 800,800);
	
	cr = cairo_create(surface);

	//plot(cr, width,height,&record);

    	
	cairo_surface_write_to_png(surface, buffer);
	
	cairo_surface_destroy(surface);

	cairo_destroy(cr);

  return;
}	
