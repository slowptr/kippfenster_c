#ifndef KF_WND_H
#define KF_WND_H

#include <Windows.h>
#include <stdbool.h>

typedef struct kf_wnd_s
{
  const char *name;
  int pos[2];
  int size[2];
  WNDCLASS wc;
  HWND hwnd;
  DWORD style;
} kf_wnd_t;

bool kf_wc_create (WNDPROC wndproc, const char *name, WNDCLASS *out);
kf_wnd_t kf_wnd_create (WNDCLASS wndclass, const char *name, DWORD style,
                        int *pos, int *size);
bool kf_wnd_init (kf_wnd_t *wnd);
void kf_wnd_destroy (kf_wnd_t *wnd);
WPARAM kf_wnd_msg_loop (kf_wnd_t *wnd);

#endif // KF_WND_H
