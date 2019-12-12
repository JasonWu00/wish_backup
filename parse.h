struct parse_output{
  char ** output;
  int lastToken;
};

struct parse_output parse_args( char * line);
void run_cmds(struct parse_output outstruct, int parentPID);
