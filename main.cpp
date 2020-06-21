#include <gtk/gtk.h>

#include "SurfaceTest.hpp"
#include "Font.hpp"
#include "Sprite.hpp"
#include "FrameBuffer.hpp"

#include <iostream>
#include <math.h>
#include <fstream>

// PS1 resolution: 640, 480 ARMor8 resolution: 128, 64
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SCREEN_COLOR_FORMAT CP_FORMAT::RGB_24BIT

#define FONT_FILE_SIZE 779

#define SPRITE_FILE_SIZE 88365

GError    *error        = NULL;
GtkWidget *window       = NULL;
GtkWidget *screen       = NULL;
GdkPixbuf *frame_buffer = NULL;
guchar    *fb_pixels    = NULL;
guint     fb_pixel_length;

uint8_t*     my_pixels       = nullptr;
SurfaceTest* surface         = nullptr;

char         my_font[FONT_FILE_SIZE];
Font*        my_font_ptr = nullptr;

char         test_sprite[SPRITE_FILE_SIZE];
Sprite*      test_sprite_ptr = nullptr;

gint draw_frame (gpointer data)
{
	// actual drawing code
	surface->draw();

	if ( surface->getPixelWidthInBits() == 1 )
	{
		for ( unsigned int pixel = 0; pixel < (SCREEN_WIDTH * SCREEN_HEIGHT); pixel++ )
		{
			unsigned int byte = std::floor( pixel / 8 );
			unsigned int realPixel = 7 - (pixel % 8);
			uint8_t realPixelMask = ( 1 << realPixel );
			if ( my_pixels[byte] & realPixelMask )
			{
				fb_pixels[(pixel * 3) + 0] = 255;
				fb_pixels[(pixel * 3) + 1] = 255;
				fb_pixels[(pixel * 3) + 2] = 255;
			}
			else
			{
				fb_pixels[(pixel * 3) + 0] = 0;
				fb_pixels[(pixel * 3) + 1] = 0;
				fb_pixels[(pixel * 3) + 2] = 0;
			}
		}
	}
	else
	{
		memcpy( fb_pixels, my_pixels, (SCREEN_WIDTH * SCREEN_HEIGHT * 3) );
	}

	// reset image widget
	gtk_image_set_from_pixbuf (GTK_IMAGE (screen), frame_buffer);

	return TRUE;
}

static void activate (GtkApplication* app, gpointer user_data)
{
	// create context
	surface = new SurfaceTest( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_COLOR_FORMAT );

	// get access to pixels in framebuffer
	const FrameBuffer* fb = surface->getFrameBuffer();
	my_pixels = surface->getFrameBuffer()->getPixels();

	// load image into pixbuf and error check
	frame_buffer = gdk_pixbuf_new( GdkColorspace::GDK_COLORSPACE_RGB, false, 8, SCREEN_WIDTH, SCREEN_HEIGHT );
	if (error != NULL)
	{
		fprintf (stderr, "Unable to read file: %s\n", error->message);
		g_error_free (error);
	}

	// create new application window and image widget to display
	window  = gtk_application_window_new (app);
	screen  = gtk_image_new_from_pixbuf (frame_buffer);

	// set window options
	gtk_window_set_title (GTK_WINDOW (window), "Window");
	gtk_window_set_default_size (GTK_WINDOW (window), 200, 200);

	// add image widget to window and show
	gtk_container_add (GTK_CONTAINER (window), screen);
	gtk_widget_show_all (window);

	// get low-level access to pixels in frame buffer
	fb_pixels = gdk_pixbuf_get_pixels_with_length (frame_buffer, &fb_pixel_length);

	// connect frame draw function to timer (roughly 30 frames per second)
	g_timeout_add(33, draw_frame, user_data);
}

int main (int argc, char **argv)
{
	unsigned int nSize = FONT_FILE_SIZE;
	std::ifstream fontFile;
	fontFile.open( "./Smoll.sff" );
	fontFile.read( my_font, nSize );
	fontFile.close();

	Font font( (uint8_t*)my_font );
	my_font_ptr = &font;

	nSize = SPRITE_FILE_SIZE;
	std::ifstream spriteFile;
	spriteFile.open( "./TestImage.sif" );
	spriteFile.read( test_sprite, nSize );
	spriteFile.close();

	Sprite sprite( (uint8_t*)test_sprite );
	test_sprite_ptr = &sprite;

	GtkApplication *app;
	int status;

	app = gtk_application_new ("org.siike92.software_renderer", G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);

	return status;
}
