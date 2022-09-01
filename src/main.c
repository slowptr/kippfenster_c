#include "examples/example_window.h"
// #include "kf_utils.h"
#include <Windows.h>

int APIENTRY
WinMain (HINSTANCE inst, HINSTANCE prev_inst, PSTR cmdline, int cmdshow)
{
  // kf_utils_set_console (false);
  if (!example_initialize ())
    return 1;
  return example_msg_loop ();
}
