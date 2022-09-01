#include "kf_wnd.h"

bool
kf_wc_create (WNDPROC wndproc, const char *name, WNDCLASS *out)
{
  WNDCLASS wc;
  memset (&wc, 0, sizeof (WNDCLASS));

  wc.style = CS_HREDRAW | CS_VREDRAW; // redraw on resize
  wc.lpfnWndProc = wndproc;
  wc.hInstance = GetModuleHandle (NULL);
  wc.hCursor = LoadCursor (NULL, IDC_ARROW);
  wc.lpszClassName = name;

  if (!RegisterClass (&wc))
    return false;

  *out = wc;

  return true;
}
kf_wnd_t
kf_wnd_create (WNDCLASS wndclass, const char *name, DWORD style, int *pos,
               int *size)
{
  kf_wnd_t wnd;
  wnd.name = name;
  wnd.wc = wndclass;
  wnd.hwnd = NULL;
  wnd.style = style;

  // memcpy_s (wnd.pos, sizeof (wnd.pos), pos, sizeof (pos));
  // memcpy_s (wnd.size, sizeof (wnd.size), size, sizeof (size));

  wnd.pos[0] = pos[0];
  wnd.pos[1] = pos[1];

  wnd.size[0] = size[0];
  wnd.size[1] = size[1];

  return wnd;
}
bool
kf_wnd_init (kf_wnd_t *wnd)
{
  if (wnd->hwnd != NULL)
    return false;

  wnd->hwnd
      = CreateWindowEx (0, wnd->wc.lpszClassName, wnd->name, wnd->style,
                        wnd->pos[0], wnd->pos[1], wnd->size[0], wnd->size[1],
                        NULL, NULL, wnd->wc.hInstance, NULL);

  if (wnd->hwnd == NULL)
    return false;

  ShowWindow (wnd->hwnd, SW_SHOW);

  return true;
}
void
kf_wnd_destroy (kf_wnd_t *wnd)
{
  DestroyWindow (wnd->hwnd);
}
WPARAM
kf_wnd_msg_loop (kf_wnd_t *wnd)
{
  MSG msg;
  while (GetMessage (&msg, NULL, 0, 0))
    {
      TranslateMessage (&msg);
      DispatchMessage (&msg);
    }

  return msg.wParam;
}
