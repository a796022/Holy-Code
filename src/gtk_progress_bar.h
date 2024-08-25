#include <gtk/gtk.h>

extern GtkWidget *MAIN_PROGRESS_BAR;

/**
 * Initializes the progress bar.
 * 
 * @return void
*/
void init_progress_bar();

/**
 * Sets the progress bar value.
 * 
 * @param value Progress value
 * 
 * @return void
*/
void set_progress_bar_value(gdouble value);

/**
 * Hide the progress bar.
 * 
 * @return void
 */
void hide_progress_bar();

/**
 * Show the progress bar.
 * 
 * @return void
 */
void show_progress_bar();