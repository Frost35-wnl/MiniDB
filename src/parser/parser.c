#include "../../include/parser/parser.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if !defined(PUBLIC) && !defined(PRIVATE)

#define PUBLIC
#define PRIVATE static

#endif /* ifndef */

struct parser_type {
  char *command;
  char **args;
  int arg_count;
};

PRIVATE void terminate(char *message) {
  fprintf(stderr, "%s\n", message);
  exit(EXIT_FAILURE);
}

PUBLIC ParesedCommand parse_tokens(Tokens t) {
  char **token_args = get_tokens_args(t);
  int tokens_count = get_tokens_count(t);

  ParesedCommand par = malloc(sizeof(struct parser_type));
  par->command = strdup(token_args[0]);
  if (par->command == NULL)
    terminate("Error in parse_tokens : strdup failed");
  par->arg_count = 0;
  par->args = NULL;

  char **ptr = token_args + 1;
  while (*ptr) {
    par->args = realloc(par->args, sizeof(char *) * (par->arg_count + 1));
    if (par->args == NULL)
      terminate("Error in parse_tokens : realloc failed");

    par->args[par->arg_count] = strdup(*ptr);
    if (par->args[par->arg_count] == NULL)
      terminate("Error in parse_tokens : strdup failed");

    par->arg_count++;
    ptr++;
  }

  par->args = realloc(par->args, sizeof(char *) * (par->arg_count + 1));
  if (par->args == NULL)
    terminate("Error in parse_tokens : realloc failed");

  par->args[par->arg_count] = NULL;
  free_tokens(t);
  return par;
}

PUBLIC void print_args(const ParesedCommand p) {
  if (!p)
    terminate("Error in print_tokens : tokens doesn't exist");

  fprintf(stdout, "[ ");
  for (size_t i = 0; i < p->arg_count; i++) {
    fprintf(stdout, " \"%s\",", p->args[i]);
  }
  fprintf(stdout, " \"%s\" ]\n", p->args[p->arg_count]);
}

PUBLIC void free_parsed_command(ParesedCommand p) {
  for (size_t i = 0; i < p->arg_count; i++) {
    free(p->args[i]);
  }
  free(p->command);
  free(p);
}

PUBLIC char *get_command_name(const ParesedCommand p) {
  if (!p || !p->command)
    return NULL;

  char *command = malloc(strlen(p->command) + 1);
  if (!command) {
    fprintf(
        stderr,
        "Error in get_command_in_parsed_command : memory allocation failed\n");
    return NULL;
  }

  strcpy(command, p->command);
  return command;
}

PUBLIC char **get_args(const ParesedCommand p) { return p->args; }

PUBLIC int get_args_count(const ParesedCommand p) { return p->arg_count; }
