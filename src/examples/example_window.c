#include "example_window.h"
#include "../kf_wnd.h"
#include <Windows.h>

#define EXAMPLE_CLASS_NAME "example class"
#define EXAMPLE_WINDOW_NAME "example window"
#define EXAMPLE_WINDOW_WIDTH 300
#define EXAMPLE_WINDOW_HEIGHT 300

kf_wnd_t window;
HBRUSH bg_handle = NULL;

LRESULT CALLBACK
window_process (HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  if (bg_handle == NULL)
    bg_handle = GetStockObject (WHITE_BRUSH);

  switch (msg)
    {
    case WM_PAINT:
      RECT rect;
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint (hwnd, &ps);
      GetClientRect (hwnd, &rect);
      FillRect (hdc, &rect, bg_handle);
      DrawText (hdc, "example test to draw", -1, &rect,
                DT_SINGLELINE | DT_CENTER | DT_VCENTER);
      EndPaint (hwnd, &ps);
    }
  return DefWindowProc (hwnd, msg, wparam, lparam);
}

HWND
example_get_handle ()
{
  return window.hwnd;
}
bool
example_initialize ()
{
  WNDCLASS window_class;
  if (!kf_wc_create (window_process, EXAMPLE_CLASS_NAME, &window_class))
    return false;

  DWORD style = WS_OVERLAPPED;
  int pos[2] = { CW_USEDEFAULT, CW_USEDEFAULT };
  int size[2] = { EXAMPLE_WINDOW_WIDTH, EXAMPLE_WINDOW_HEIGHT };
  window = kf_wnd_create (window_class, EXAMPLE_WINDOW_NAME, style, pos, size);

  if (!kf_wnd_init (&window))
    return false;

  return true;
}
WPARAM
example_msg_loop () { return kf_wnd_msg_loop (&window); }
