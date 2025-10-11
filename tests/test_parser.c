#include "../include/parser/parser.h"
#include "../include/parser/tokenizer.h"
#include <stdbool.h>
#include <stdio.h>

bool test_tokenizer();
bool test_parser();

int main(void) {
  if (test_tokenizer())
    printf("test_tokenizer works with success \n\n");
  if (test_parser())
    printf("test_parser works with success \n\n");
  return 0;
}

bool test_tokenizer() {
  const char *input = "CREATE students (nom, prenom, age, date, level, classe)";
  Tokens t = tokenize(input);
  print_tokens(t);
  printf("The number of tokens : %d\n", get_tokens_count(t));
  free_tokens(t);
  return true;
}

bool test_parser() {
  const char *input = "CREATE students (nom, prenom, age, date, level, classe)";
  Tokens t = tokenize(input);
  ParesedCommand p = parse_tokens(t);
  printf("Command name : %s\n", get_command_name(p));
  printf("The number of args : %d\n", get_args_count(p));
  print_args(p);
  free_parsed_command(p);
  return true;
}
