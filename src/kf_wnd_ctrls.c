#include "kf_wnd_ctrls.h"
#include <CommCtrl.h>

#define MAX_ITEMS 32

typedef struct kf_ctrl_item_s
{
  const char *identifier;
  HWND handle;
} kf_ctrl_item_t;

static int cur_item_list_idx = 0;
kf_ctrl_item_t ctrl_item_list[MAX_ITEMS];

void
add_item (kf_ctrl_item_t item)
{
  if (cur_item_list_idx > MAX_ITEMS)
    return;

  ctrl_item_list[cur_item_list_idx] = item;
  cur_item_list_idx++;
}

HWND
kf_wnd_ctrls_get_by_id (const char *identifier)
{
  for (int i = 0; i < MAX_ITEMS; i++)
    {
      if (ctrl_item_list[i].identifier == identifier)
        return ctrl_item_list[i].handle;
    }
  return NULL;
}
HWND
kf_wnd_ctrls_add_button (kf_wnd_t *wnd, const char *identifier,
                         const char *text, int *pos, int *size)
{
  // TODO: implement menu and style specification
  kf_ctrl_item_t item;
  item.identifier = identifier;
  item.handle = CreateWindow (
      WC_BUTTON, text, WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
      pos[0], pos[1], size[0], size[1], wnd->hwnd, NULL, wnd->wc.hInstance,
      NULL);

  add_item (item);
  return item.handle;
}