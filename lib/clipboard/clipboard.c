#include <stdio.h>
#include <stdlib.h>

#include "../../external/sds/sds.h"

////////////////////////////////////////////////////////////////////////////////
// PUBLIC //////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Gets the content of the clipboard
 * 
 * - This function uses the X11 library to get the content of the clipboard
 * - The content is printed to the standard output
 * - If there is no content, a message is printed
 * 
 * @return char* The content of the clipboard
 */
char* get_clipboard_content() {
    FILE *pipe;
    char buffer[64];
    sds clipboard_content_sds = sdsempty();

    // Open a pipe to execute the xclip command
    pipe = popen("xclip -o -selection clipboard", "r");
    if (pipe == NULL) {
        perror("Error al ejecutar xclip");
    }

    // Read and show the content of the clipboard
    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        clipboard_content_sds = sdscat(clipboard_content_sds, buffer);
    }
    
    // Copy the content of the clipboard to a string
    char* clipboard_content = sdsnew(clipboard_content_sds);

    // Release the memory of the clipboard content
    sdsfree(clipboard_content_sds);

    // Close the pipe
    pclose(pipe);

    return clipboard_content;
}