//
// Created by Jacob  Piazza on 1/2/24.
//

#include <stdio.h>
#include <unistd.h>
#include <termios.h>

struct termios orig_termios; /*Save copy of termios in orig state */

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

/* Turning off Echo --> Setting Raw mode */
/* Echo prints each key typed into terminal --> not useful for text editor with UI*/
void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios); /*Reading terminal attributes */
    atexit(disableRawMode); /*Calls func when program exits*/

    struct termios raw = orig_termios; /* Copying orig state for changes*/
    raw.c_lflag &= ~(ECHO | ICANON); /* Flipped bits in bitflag ECHO using bitwise-NOT (~) */
    /* ICANON flag ensures we are reading input byte by byte instead of line by line */
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw); /*Applying terminal attr changes */
    /*TCSAFLUSH discards unread input before applying changes to terminal */
}

int main () {

    enableRawMode();

    /* Reading keypresses from user */
        /* Default mode is canonical mode --> Input sent when user presses enter */
    char c;

    /* STDIN_FILENO is Input stream (input by user) for Unix Systems */
    /* https://man7.org/linux/man-pages/man3/stdin.3.html */
    while (read(STDIN_FILENO, &c, 1) == 1 && c!= 'q'); /* read 1 byte from std input into c, until no more*/
    return 0;
}