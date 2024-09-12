#pragma once

#include <gtk/gtk.h>

/**
 * Sets the progress bar value.
 * 
 * @param value Progress value
 * 
 * @return void
*/
void set_progress_bar_value(GtkWidget* progress_bar, gdouble value);

/**
 * Hide the progress bar.
 * 
 * @return void
 */
void hide_progress_bar(GtkWidget* progress_bar);

/**
 * Show the progress bar.
 * 
 * @return void
 */
void show_progress_bar(GtkWidget* progress_bar);