#ifndef MENU_BAR_MANAGER
#define MENU_BAR_MANAGER

// "Archivo" Menu
extern GtkWidget *MENUBAR_SAVE;
extern GtkWidget *MENUBAR_OPEN_FILE;
extern GtkWidget *MENUBAR_CLOSE_WINDOW;
extern GtkWidget *MENUBAR_EXIT;

// "Editar" Menu
extern GtkWidget *MENUBAR_UNDO;
extern GtkWidget *MENUBAR_REDO;
extern GtkWidget *MENUBAR_DELETE;

// "Ayuda" Menu
extern GtkWidget *MENUBAR_SHOW_WINDOW_INFORMATION;

/**
 * @brief Initializes the main window menu.
 * 
 * - Creates the menu.
 * - Creates the tabs and adds the elements.
 * - Connects the signals.
 * 
 * @return GtkWidget* Menu bar
*/
GtkWidget *initialize_menu_bar_main_window();

#endif /* MENU_BAR_MANAGER */