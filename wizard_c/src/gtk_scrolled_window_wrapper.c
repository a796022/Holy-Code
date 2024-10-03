#include <gtk/gtk.h>

/**
 * @brief Creates a scrolled window.
 * 
 * @return GtkWidget* Scrolled window
 */
GtkWidget *init_scrolled_window() {
    // Create the scrolled window
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);

    // Set the policy of the scrollbars
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

    return scrolled_window;
}

/**
 * @brief Adds a widget to a scrolled window.
 * 
 * @param scrolled_window Scrolled window
 * @param widget Widget to add
 * 
 * @return void
 */
void add_widget_to_scrolled_window(GtkWidget *scrolled_window, GtkWidget *widget) {
    gtk_container_add(GTK_CONTAINER(scrolled_window), widget);
}