#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cairo.h>
#include <gtk/gtk.h>

struct {
  cairo_surface_t *image;  
} glob;

void draw_number(cairo_t* cr, int width, int height);


static gboolean on_expose_event(GtkWidget *widget, cairo_t *cr, 
    gpointer user_data)
{      

	cr = gdk_cairo_create (gtk_widget_get_window (widget));
	
	cairo_scale (cr, 10, 10);
	cairo_set_source_surface(cr, glob.image, 0, 0);
	cairo_pattern_set_filter(cairo_get_source(cr), CAIRO_FILTER_NEAREST);
	cairo_paint(cr);
	draw_number(cr, 8, 8);   

  return FALSE;
}

void draw_number(cairo_t* cr, int width, int height) {
    //determine the box size that the number will be drawn in
    double box_x = 8;
    double box_y = 8;
    double box_width = width;
    double box_height = height;

    cairo_set_source_rgb(cr, 1.0, 0, 0);
	cairo_set_line_width(cr, 0.5);
    cairo_rectangle(cr, box_x, box_y, box_width, box_height);
    cairo_stroke_preserve(cr);
}


int main(int argc, char *argv[])
{
  GtkWidget *window;
  GtkWidget *darea;
  
  glob.image = cairo_image_surface_create_from_png("imagen.png");

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  darea = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER (window), darea);


  g_signal_connect(darea, "expose-event",
                 G_CALLBACK(on_expose_event), NULL);

  g_signal_connect(window, "destroy",
      G_CALLBACK (gtk_main_quit), NULL);

  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_default_size(GTK_WINDOW(window), 800, 512); 
  gtk_window_set_title(GTK_WINDOW(window), "Image");

  gtk_widget_show_all(window);

  gtk_main();

  cairo_surface_destroy(glob.image);

  return 0;
}
