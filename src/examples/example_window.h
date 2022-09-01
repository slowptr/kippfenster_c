#ifndef EXAMPLE_WINDOW_H
#define EXAMPLE_WINDOW_H

#include <Windows.h>
#include <stdbool.h>

HWND example_get_handle ();
bool example_initialize ();
WPARAM example_msg_loop ();

#endif // EXAMPLE_WINDOW_H
