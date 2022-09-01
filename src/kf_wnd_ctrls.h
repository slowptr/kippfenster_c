#ifndef KF_WND_CTRLS
#define KF_WND_CTRLS

#include "kf_wnd.h"
#include <Windows.h>

HWND kf_wnd_ctrls_get_by_id (const char *identifier);
HWND kf_wnd_ctrls_add_button (kf_wnd_t *wnd, const char *identifier,
                              const char *text, int *pos, int *size);

#endif // KF_WND_CTRLS
