#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <getopt.h>
#include "version.h"


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

void get_terminal_dim(struct winsize *sz) {
  ioctl(0, TIOCGWINSZ, sz);
  return;
}

int main(int argc, char *argv[]) {

  struct winsize sz;
  get_terminal_dim(&sz);

  if (sz.ws_col <= 50) {
    printf("screen size too small!\n");
    return EXIT_FAILURE;
  }

  int opt;

  struct option long_options[] = {
    { "help", no_argument, NULL, 'h' },
    { "message", no_argument, NULL, 'm' },
    { "version", no_argument, NULL, 'v' },
    { NULL, 0, NULL, 0 },
  };

  char *message = NULL;

  while ((opt = getopt_long(argc, argv, "hvm:", long_options, NULL)) != -1) {
    switch (opt) {
      case 'h':
        printf("\n");
        printf("  -h, --help       help, run `man banner-commenter` for full docs\n");
        printf("  -v, --version    get running version\n");
        printf("  -m, --message    pass string argument, must be wrapped in quotes\n");
        printf("\n");
        printf("\n");
        break;
      case 'v':
        printf("banner-commenter %s\n", PROGRAM_VERSION);
        break;
      case 'm':
        message = optarg;
        printf("here is your message : %s\n", message);
        break;
      default:
        printf("unexpected case\n");
        return EXIT_FAILURE;
      
    }
  }

  return 0;
}
