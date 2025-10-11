#include "../include/commands/dispatcher.h"
#include "../include/config.h"
#include "../include/parser/parser.h"
#include "../include/parser/tokenizer.h"
#include "../include/utils.h"
#include <stdio.h>
#include <string.h>

int main() {

  char input[MAX_BUFF];
  DBContext ctx = init_context();

  printf(">> ");
  for (;;) {
    read_line(input, MAX_BUFF);

    if (strcmp(input, "quit") == 0)
      break;

    Tokens t = tokenize(input);
    ParesedCommand cmd = parse_tokens(t);
    dispatch_command(ctx, cmd);
    printf("\n");
    free_parsed_command(cmd);
    printf(">> ");
  }

  free_context(ctx);
  return 0;
}
