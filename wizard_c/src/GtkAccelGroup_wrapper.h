#pragma once

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
void init_keyboard_shortcuts(struct WindowStructure* window_structure);