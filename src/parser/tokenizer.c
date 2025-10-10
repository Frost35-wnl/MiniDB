#include "../../include/parser/tokenizer.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if !defined(PUBLIC) && !defined(PRIVATE)

#define PUBLIC
#define PRIVATE static

#endif /* ifndef */

struct tokens_type {
  char **tokens;
  int tokens_count;
};

PRIVATE void terminate(char *message) {
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}

// input : "CREATE students (nom, prenom, date)"
PUBLIC Tokens tokenize(const char *input) {
  Tokens t = malloc(sizeof(struct tokens_type));
  if (t == NULL)
    terminate("Error in tokenize : malloc failed");

  t->tokens_count = 0;
  t->tokens = NULL;

  size_t len = strlen(input);
  size_t i = 0;

  while (i < len) {
    while (i < len && (input[i] == ' ' || input[i] == '\t' || input[i] == ',' ||
                       input[i] == '(' || input[i] == ')')) {
      i++;
    }

    if (i >= len)
      break;

    size_t start = i;
    while (i < len && input[i] != ' ' && input[i] != '\t' && input[i] != ',' &&
           input[i] != '(' && input[i] != ')') {
      i++;
    }

    size_t token_len = i - start;

    char *token = malloc(token_len + 1);
    if (token == NULL)
      terminate("Error in tokenize : malloc failed");

    strncpy(token, input + start, token_len);
    token[token_len] = '\0';

    t->tokens = realloc(t->tokens, sizeof(char *) * (t->tokens_count + 1));
    if (t->tokens == NULL)
      terminate("Error in tokenize : realloc failed");

    t->tokens[t->tokens_count] = strdup(token);
    if (t->tokens[t->tokens_count] == NULL)
      terminate("Error in tokenize : strdup failed");
    t->tokens_count++;
  }

  t->tokens = realloc(t->tokens, sizeof(char *) * (t->tokens_count + 1));
  t->tokens[t->tokens_count] = NULL;

  return t;
}

PUBLIC void print_tokens(const Tokens t) {
  fprintf(stdout, "[ ");
  for (size_t i = 0; i < t->tokens_count; i++) {
    fprintf(stdout, " \"%s\",", t->tokens[i]);
  }
  fprintf(stdout, " \"%s\" ]\n", t->tokens[t->tokens_count]);
}

PUBLIC void free_tokens(Tokens t) {
  for (size_t i = 0; i < t->tokens_count; i++) {
    free(t->tokens[i]);
  }
  free(t->tokens);
}
