#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void cpyargs(int n, char *args_orig[], char *args_cpy[]) {
  for (int i = 0; i < n; i++) {
    args_cpy[i] = (char *)malloc(strlen(args_orig[i]) + 1);
    if (args_cpy[i] == NULL) {
      fprintf(stderr, "Memory allocation failed ... \n");
    }
    strcpy(args_cpy[i], args_orig[i]);
  }
  return;
}


void convertUpperCase(int n, char *args[]) {
  for (int i = 0; i < n; i++) {
    char *arg = args[i];
    for (int j = 0; arg[j] != '\0'; j++) {
      arg[j] = toupper(arg[j]);
    }
  }
}

int main(int argc, char *argv[]) {

  // create copy of every argv
  char **args = (char **)malloc(argc + 1);
  if (args == NULL) {
    fprintf(stderr, "Memory allocation failed ... \n");
  }

  cpyargs(argc, argv, args);
  convertUpperCase(argc, args);

  for (int i = 0; i < argc; i++) {
    printf("%d (argv) : %s\n", i, argv[i]);
    printf("%d (args) : %s\n", i, args[i]);
  }

  return 0;
}
