#include "fun_use.h"

int main (void)
{
  srand ((unsigned int) time (0));

  init_window ();
  init_black();
  init_word ();

  draw_map ();
  draw_black ();
  put_word (30, 0);

  play ();

  closegraph ();

  return 0;
}
