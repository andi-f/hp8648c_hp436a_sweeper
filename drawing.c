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
#include <math.h>

#include <cairo.h>
#include <cairo-pdf.h>

#include <kplot.h>

#include "hp8648c_hp436a_sweeper.h"
#include "hp8648c_hp436a.h"
#include "run_sweep.h"
#include "widget_structure.h"
#include "debug.h"

#define NODEBUG_LEVEL_1
#define MAXPOINTS 10000

void k_plot(cairo_t *cr, gint width, gint height)	{

	struct kpair	 points1[MAXPOINTS], points2[MAXPOINTS];
	struct kdata	*d1, *d2;
	struct kplot	*p;
	
	size_t		 i;

	cairo_status_t	 st;

	m_record	act_data;

	if (r_counter > MAXPOINTS)
		r_counter = MAXPOINTS;
		
	d1 = d2 = NULL;
	p = NULL;

	if (hp8648c.run_f != 0)	{
		for (i = 0; i < r_counter; i++) {
			act_data = g_array_index(m_data, m_record, i);	
			points1[i].x = act_data.frequency;
			points1[i].y = act_data.ref_level;
			points2[i].y = act_data.avg_value;
			points2[i].x = act_data.frequency;
		}
	}
	else
	for (i = 0; i < r_counter; i++) {
		act_data = g_array_index(m_data, m_record, i);	
		points1[i].x = act_data.avg_value;
		points1[i].y = act_data.ref_level;
	}

	
	if (NULL == (d1 = kdata_array_alloc(points1, r_counter))) {
		perror(NULL);
		goto out;
	} else if (NULL == (d2 = kdata_array_alloc(points2, r_counter))) {
		perror(NULL);
		goto out;
	} else if (NULL == (p = kplot_alloc(NULL))) {
		perror(NULL);
		goto out;
	} else if ( ! kplot_attach_data(p, d1, KPLOT_LINES, NULL)) {
		perror(NULL);
		goto out;
	} else if ( ! kplot_attach_data(p, d2, KPLOT_LINES, NULL)) {
		perror(NULL);
		goto out;
	}

	kdata_destroy(d1);
	kdata_destroy(d2);
	d1 = d2 = NULL;

	st = cairo_status(cr);
	if (CAIRO_STATUS_SUCCESS != st) {
		fprintf(stderr, "%s", cairo_status_to_string(st));
		kplot_free(p);
		return;
	}

	cairo_set_source_rgb(cr, 1.0, 1.0, 1.0); 
	cairo_rectangle(cr, 0.0, 0.0, width, height);
	cairo_fill(cr);
	kplot_draw(p, width, height, cr);

out:
	kplot_free(p);
	kdata_destroy(d1);
	kdata_destroy(d2);

}

void create_png(GtkWidget *widget, gpointer data) {

	gint width = 800, height = 800;					// Window width & height
	
	cairo_surface_t *surface;
	cairo_t *cr;

	surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
	cr = cairo_create(surface);

	k_plot(cr, width,height);

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

	surface = cairo_pdf_surface_create (buffer, width,height);
	
	cr = cairo_create(surface);

	k_plot(cr, width,height);
    	
	cairo_surface_destroy(surface);

	cairo_destroy(cr);

  return;
}	


void plot(cairo_t *cr, gint	width, gint height)	{

	m_record	act_data;
	double		X,Y;					// actual value
	
	double		X_DIV = 10.0;			// 10 div/x
	double		Y_DIV = 8.0;			// 10 div/y

	double		MAX_Y = 10.0;			// max Y scale
	double		MIN_Y = -70.0;			// min Y scale
	double		MAX_X = 3200.0;			// max X scale
	double		MIN_X = 1.0;			// min X scale

	gint 		XMAX;					// max dots x-scale
	gint 		YMAX;					// max dots y-scale
	
	gint 		XOFFSET;				// start of diagramm
	gint		YOFFSET;				// start of diagramm

	gint		x, y;					// actual plot postion
	gint		x_alt,y_alt;			// last plot postion
	double		x_scale,y_scale;		// scale for axis
	gint		x_zero,y_zero;			// point of origin
	char		string_buf[80];			// line buffer
	
	int			m = 0;					// counter Cario
	
	
	cairo_rectangle(cr, 0.0, 0.0, width, height);
	cairo_set_source_rgb(cr, 1.0, 1.0, 1.0);
	cairo_fill(cr);

	cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
 
	cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
	cairo_set_font_size(cr, 10.0);
	cairo_set_line_width(cr, 1.0);

	if (r_counter != 0)	{
		m = 0;
		act_data = g_array_index(m_data, m_record, m);
		
		MAX_Y = act_data.avg_value;
		MIN_Y = MAX_Y;
			
		for(m = 1; m <= r_counter-1; m ++)		{
			act_data = g_array_index(m_data, m_record, m);
			Y = act_data.avg_value;
			if(Y > MAX_Y)
				MAX_Y = Y;
			else
			if(Y<MIN_Y)
				MIN_Y = Y;				
			
			if(MIN_Y > MAX_Y)
				MAX_Y = MIN_Y;
		}
	}
	else	{
		MAX_Y = hp8648c.rl_stop;
		MIN_Y = hp8648c.rl_start;
	}
	
	if (fabs(MAX_Y-MIN_Y) <1)	{
		MAX_Y = MAX_Y + fabs(MAX_Y/10.0);
		MIN_Y = MIN_Y - fabs(MIN_Y/10.0);
	}	
		
	if (hp8648c.run_f != 0)	{
		MAX_X = hp8648c.f_stop;
		MIN_X = hp8648c.f_start;
	}
	else{
		MAX_X = hp8648c.rl_stop;
		MIN_X = hp8648c.rl_start;
	}	

	XMAX = 0.8 * width;
	YMAX = 0.8 * height;
	
	XOFFSET = 0.5 * (width-XMAX);
	YOFFSET = 0.5 * (height-YMAX);

	x_scale = XMAX / (MAX_X-MIN_X);
	y_scale = YMAX / (MAX_Y-MIN_Y);		
	
	x_zero = XOFFSET - MIN_X * x_scale;
	y_zero = YOFFSET + YMAX - MIN_Y * y_scale;
	
	cairo_move_to(cr,XOFFSET,YMAX+YOFFSET);
	cairo_line_to(cr,XOFFSET+XMAX,YMAX+YOFFSET);
	cairo_line_to(cr,XOFFSET+XMAX,YOFFSET);
	cairo_line_to(cr,XOFFSET,YOFFSET);
	cairo_line_to(cr,XOFFSET,YMAX+YOFFSET);

	for(m = 0; m < X_DIV+1;m ++)	{
		x =  m * XMAX / X_DIV + XOFFSET;
		if( (x >= XOFFSET) && (x <= XOFFSET+XMAX) )	{
			cairo_move_to(cr,x,YMAX+YOFFSET-10);
			cairo_line_to(cr,x,YMAX+YOFFSET);
		}
		sprintf(string_buf,"% 3.1f", MIN_X + m / X_DIV * (MAX_X-MIN_X));
		cairo_move_to(cr,x,YOFFSET+YMAX+10);
		cairo_show_text(cr, string_buf);		
	}
	
	for(m = 0; m < Y_DIV+1;m ++)	{
		y =  YMAX + YOFFSET - m * YMAX / Y_DIV ;

		cairo_move_to(cr,XOFFSET,y);
		cairo_line_to (cr,XOFFSET+10,y);
		
		sprintf(string_buf,"% 3.1f", MIN_Y + m / Y_DIV * (MAX_Y-MIN_Y));
		cairo_move_to(cr,0.0,y);
		cairo_show_text(cr, string_buf); 	
	}
	cairo_stroke(cr);

	cairo_set_source_rgb(cr, 1.0, 0.0, 0.0);
	if (r_counter != 0)	{
		m = 0;
		act_data = g_array_index(m_data, m_record, m);
		
		Y = act_data.avg_value;
		if (hp8648c.run_f != 0)	{
			X = act_data.frequency;
		}
		else	{
			X = act_data.ref_level;
		}
	
		if(Y > MAX_Y)
		{
			Y = MAX_Y;
		}
		else
		if(Y < MIN_Y)
		{
			Y = MIN_Y;
		}
		x_alt =  x_zero + X * x_scale;
		y_alt =  y_zero - Y * y_scale;
		
		for(m = 1; m <= r_counter-1; m ++)
		{
			act_data = g_array_index(m_data, m_record, m);
			Y = act_data.avg_value;
			if (hp8648c.run_f != 0)	{
				X = act_data.frequency;
			}
			else	{
				X = act_data.ref_level;
			}
		
			if(Y > MAX_Y)
			{
				Y = MAX_Y;
			}
			else
			if(Y < MIN_Y)
			{
				Y = MIN_Y;
			}
			fprintf(stderr,"\n%f %f %i %i\n",x_scale,y_scale,x_zero, y_zero);

			x =  x_zero + X * x_scale;
			y =  - y_zero + Y * y_scale;
						
			fprintf(stderr,"%u %u\n",x,y);


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
