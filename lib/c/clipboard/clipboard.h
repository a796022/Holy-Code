#ifndef CLIPBOARD_H
#define CLIPBOARD_H

/**
 * @brief Gets the content of the clipboard
 * 
 * - This function uses the X11 library to get the content of the clipboard
 * - The content is printed to the standard output
 * - If there is no content, a message is printed
 * 
 * @return char* The content of the clipboard
 */
char* get_clipboard_content();

#endif // CLIPBOARD_H
