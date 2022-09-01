#include "example_window.h"
#include "../kf_wnd.h"
#include "../kf_wnd_ctrls.h"
#include <Windows.h>

#define EXAMPLE_CLASS_NAME "example class"
#define EXAMPLE_WINDOW_NAME "example window"
#define EXAMPLE_WINDOW_WIDTH 300
#define EXAMPLE_WINDOW_HEIGHT 300

kf_wnd_t window;
HBRUSH bg_handle = NULL;

void
window_process_commands (HWND hwnd, WPARAM wparam, LPARAM lparam)
{
  if (lparam == (LPARAM)kf_wnd_ctrls_get_by_id ("btn_test"))
    {
      MessageBox (hwnd, "you pressed the test button!", EXAMPLE_WINDOW_NAME,
                  MB_OK);
    }
}

void
window_draw_simple_text (HWND hwnd)
{
  RECT rect;
  PAINTSTRUCT ps;
  HDC hdc = BeginPaint (hwnd, &ps);
  GetClientRect (hwnd, &rect);
  FillRect (hdc, &rect, bg_handle);
  DrawText (hdc, "example test to draw", -1, &rect,
            DT_SINGLELINE | DT_CENTER | DT_VCENTER);
  EndPaint (hwnd, &ps);
}

LRESULT CALLBACK
window_process (HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
  if (bg_handle == NULL)
    bg_handle = GetStockObject (WHITE_BRUSH);

  switch (msg)
    {
    case WM_COMMAND:
      window_process_commands (hwnd, wparam, lparam);
      return 0;
    case WM_PAINT:
      window_draw_simple_text (hwnd);
      return 0;
    }
  return DefWindowProc (hwnd, msg, wparam, lparam);
}

void
window_populate_items ()
{
  int pos[2] = { 10, 10 };
  int size[2] = { 50, 20 };
  kf_wnd_ctrls_add_button (&window, "btn_test", "test", pos, size);
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

  window_populate_items ();

  return true;
}
WPARAM
example_msg_loop () { return kf_wnd_msg_loop (&window); }
