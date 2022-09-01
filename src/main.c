#include "examples/example_window.h"

int
main ()
{
  if (!example_initialize ())
    return 1;
  return example_msg_loop ();
}
