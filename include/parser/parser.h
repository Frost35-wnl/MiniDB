#ifndef PARSER_H
#define PARSER_H
#include "./tokenizer.h"

typedef struct parser_type *ParesedCommand;

ParesedCommand parse_tokens(Tokens);
char *get_command_name(const ParesedCommand);
int get_args_count(const ParesedCommand);
char **get_args(const ParesedCommand);
void print_args(const ParesedCommand);
void free_parsed_command(ParesedCommand);

#endif // !PARSER_H
