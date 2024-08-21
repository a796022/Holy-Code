#ifndef GTKACCELGROUP_WRAPPER_H
#define GTKACCELGROUP_WRAPPER_H

/**
 * @brief Initializes the application's keyboard shortcuts
 * 
 * - Initializes the acceleration groups (one per window)
 * - Associates the keyboard shortcuts to the signals of the widgets
 * 
 * @return void
*/
void initialize_keyboard_shortcuts();

#endif /* GTKACCELGROUP_WRAPPER_H */