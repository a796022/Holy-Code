#include <gtk/gtk.h>

GtkWidget *MAIN_PROGRESS_BAR;

/**
 * Initializes the progress bar.
 * 
 * @return void
*/
void init_progress_bar() {
    MAIN_PROGRESS_BAR = gtk_progress_bar_new();
}

/**
 * Sets the progress bar value.
 * 
 * @param value Progress value
 * 
 * @return void
*/
void set_progress_bar_value(gdouble value) {
    // Update the progress bar
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(MAIN_PROGRESS_BAR), value);

    // Process the events
    while (gtk_events_pending()) {
        gtk_main_iteration();
    }
}

/**
 * Hide the progress bar.
 * 
 * @return void
 */
void hide_progress_bar() {
    gtk_widget_hide(MAIN_PROGRESS_BAR);
}

/**
 * Show the progress bar.
 * 
 * @return void
 */
void show_progress_bar() {
    gtk_widget_show(MAIN_PROGRESS_BAR);
}