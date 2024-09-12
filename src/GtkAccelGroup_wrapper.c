#include <gtk/gtk.h>

#include "gtk_menu_bar_wrapper.h"
#include "window_manager.h"

/**
 * @brief Initializes the application's keyboard shortcuts
 * 
 * - Initializes the acceleration groups (one per window)
 * - Associates the keyboard shortcuts to the signals of the widgets
 * 
 * @param window Window to which the keyboard shortcuts will be associated.
 * 
 * @return void
*/
void init_keyboard_shortcuts(struct WindowStructure* window_structure) {
    // Get the data
    GtkWidget *window = window_structure->window;
    struct MenuBar *menu_bar = window_structure->menu_bar;

    // Create the acceleration groups
    GtkAccelGroup *accel_group = gtk_accel_group_new();

    // Associate the acceleration groups with the windows
    gtk_window_add_accel_group(GTK_WINDOW(window), accel_group);

    // Main window keyboard shortcuts
    gtk_widget_add_accelerator(menu_bar->new_file, "activate", accel_group, GDK_KEY_N, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator(menu_bar->open_file, "activate", accel_group, GDK_KEY_O, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator(menu_bar->save, "activate", accel_group, GDK_KEY_S, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator(menu_bar->close_window, "activate", accel_group, GDK_KEY_F4, GDK_MOD1_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator(menu_bar->exit, "activate", accel_group, GDK_KEY_Q, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);

    gtk_widget_add_accelerator(menu_bar->undo, "activate", accel_group, GDK_KEY_Z, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator(menu_bar->redo, "activate", accel_group, GDK_KEY_Y, GDK_CONTROL_MASK, GTK_ACCEL_VISIBLE);
    gtk_widget_add_accelerator(menu_bar->delete, "activate", accel_group, GDK_KEY_Delete, 0, GTK_ACCEL_VISIBLE);
}