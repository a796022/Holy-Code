#include <gtk/gtk.h>

/**
 * Sets the progress bar value.
 * 
 * @param value Progress value
 * 
 * @return void
*/
void set_progress_bar_value(GtkWidget* progress_bar, gdouble value) {
    // Update the progress bar
    gtk_progress_bar_set_fraction(GTK_PROGRESS_BAR(progress_bar), value);

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
void hide_progress_bar(GtkWidget* progress_bar) {
    gtk_widget_hide(progress_bar);
}

/**
 * Show the progress bar.
 * 
 * @return void
 */
void show_progress_bar(GtkWidget* progress_bar) {
    gtk_widget_show(progress_bar);
}