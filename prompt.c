#include "main.h"

/**
 * prompt - displays a prompt when in interactive mode
 */
void prompt(void)
{
  int i_mode = isatty(STDIN_FILENO);

  if (i_mode)
    write(STDOUT_FILENO, "$ ", 2);
}