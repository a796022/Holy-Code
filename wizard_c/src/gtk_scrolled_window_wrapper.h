#pragma once

#include <gtk/gtk.h>

/**
 * @brief Creates a scrolled window.
 * 
 * @return GtkWidget* Scrolled window
 */
GtkWidget *init_scrolled_window();

/**
 * @brief Adds a widget to a scrolled window.
 * 
 * @param scrolled_window Scrolled window
 * @param widget Widget to add
 * 
 * @return void
 */
void add_widget_to_scrolled_window(GtkWidget *scrolled_window, GtkWidget *widget);