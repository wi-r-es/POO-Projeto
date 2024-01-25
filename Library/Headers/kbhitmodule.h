//
// Created on 10/11/23.
//

#ifndef SRC_KBHITMODULE_H
#define SRC_KBHITMODULE_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#include <stdio.h>
#include <windows.h>

int kbhit()
{
    static HANDLE input_handle = NULL;
    INPUT_RECORD input_record;
    DWORD events_read;

    // Initialize the input handle on the first call
    if (input_handle == NULL)
    {
        input_handle = GetStdHandle(STD_INPUT_HANDLE);
        SetConsoleMode(input_handle, ENABLE_PROCESSED_INPUT);
    }

    // Check if there is any input available
    PeekConsoleInput(input_handle, &input_record, 1, &events_read);
    if (events_read != 0 && input_record.EventType == KEY_EVENT && input_record.Event.KeyEvent.bKeyDown)
    {
        return 1;
    }

    return 0;
}
#else
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>

int kbhit()
{
    struct termios oldt, newt;
    int oldf, newf;
    int ch;

    // Save the current terminal settings
    tcgetattr(STDIN_FILENO, &oldt);
    // Set the file status flags for stdin to non-blocking
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    // Set the terminal to raw mode
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Read one character from stdin
    ch = getchar();

    // Restore the terminal settings
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    // If a character was read, put it back on the input stream
    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}
#endif
#ifdef __cplusplus
}
#endif




#endif //SRC_KBHITMODULE_H
