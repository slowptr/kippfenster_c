#include "example_window.h"
#include "../kf_wnd.h"
#include "../kf_wnd_ctrls.h"
#include <Windows.h>
#include <stdio.h>
#include <windowsx.h> // not sure if i should use these macros

#define EXAMPLE_CLASS_NAME "example class"
#define EXAMPLE_WINDOW_NAME "example window"
#define EXAMPLE_WINDOW_WIDTH 300
#define EXAMPLE_WINDOW_HEIGHT 300

kf_wnd_t window;
HBRUSH bg_handle = NULL;

void
window_process_commands (HWND hwnd, WPARAM wparam, LPARAM lparam)
{
  HWND combobox_handle = kf_wnd_ctrls_get_by_id ("cb_test");
  WPARAM combobox_selection = ComboBox_GetCurSel (combobox_handle);
  if ((int)combobox_selection < 0)
    return;

  if (lparam == (LPARAM)kf_wnd_ctrls_get_by_id ("btn_test"))
    {
      char combobox_text[32];
      ComboBox_GetLBText (combobox_handle, combobox_selection, &combobox_text);

      char buf[256];
      sprintf_s (buf, sizeof (buf), "the combobox entry selected is \"%s\"",
                 combobox_text);

      MessageBox (hwnd, buf, EXAMPLE_WINDOW_NAME, MB_OK);
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
  DrawText (hdc, "example text to draw", -1, &rect,
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
    case WM_CLOSE:
      kf_wnd_destroy (&window);
      return 0;
    case WM_DESTROY:
      PostQuitMessage (0);
      return 0;
    }
  return DefWindowProc (hwnd, msg, wparam, lparam);
}

void
window_populate_items (RECT rect)
{
  const int padding = 10;
  {
    int pos[2] = { 160, padding * 2 };
    int size[2] = { 90, 22 };
    kf_wnd_ctrls_add_button (&window, "btn_test", "test", pos, size);
  }
  {
    int pos[2] = { padding, padding * 2 };
    int size[2] = { 150, 100 };
    HWND combobox_handle
        = kf_wnd_ctrls_add_combobox (&window, "cb_test", pos, size);

    ComboBox_AddString (combobox_handle, "test entry");
    ComboBox_AddString (combobox_handle, "another test entry");
    ComboBox_AddString (combobox_handle, "yet another one");
  }
  {
    int pos[2] = { padding / 2, 0 };
    int size[2] = { rect.right - padding, 250 };
    kf_wnd_ctrls_add_groupbox (&window, "gb_test", "my groupbox :)", pos,
                               size);
  }
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

  DWORD style = WS_OVERLAPPED | WS_SYSMENU;
  int pos[2] = { CW_USEDEFAULT, CW_USEDEFAULT };
  int size[2] = { EXAMPLE_WINDOW_WIDTH, EXAMPLE_WINDOW_HEIGHT };
  window = kf_wnd_create (window_class, EXAMPLE_WINDOW_NAME, style, pos, size);

  if (!kf_wnd_init (&window))
    return false;

  RECT rect;
  GetClientRect (window.hwnd, &rect);
  window_populate_items (rect);

  return true;
}
WPARAM
example_msg_loop () { return kf_wnd_msg_loop (&window); }
