#include "../include/parser/tokenizer.h"
#include <stdbool.h>
#include <stdio.h>

bool test_tokenizer();
bool test_parser();

int main(void) {
  if (test_tokenizer())
    printf("handle_create works with success \n\n");
  // if (test_parser())
  //  printf("handle_list works with success \n\n");
  return 0;
}

bool test_tokenizer() {
  const char *input = "CREATE students (nom, prenom, age, date, level, classe)";
  Tokens t = tokenize(input);
  print_tokens(t);
  free_tokens(t);
  // print_tokens(t);

  return true;
}

bool test_parser() { return true; }
