#include "version.h"
#include <ctype.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

struct Configuration {
  char prefix;
  int margin;
  int padding;
  int maxlen;
};

struct Configuration config = {
    .prefix = '#',
    .margin = 10,
    .padding = 10,
    .maxlen = 80,
};

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

void convertUpperCase(char *txt) {
  for (int i = 0; txt[i] != '\0'; i++) {
    txt[i] = toupper(txt[i]);
  }
}

void get_terminal_dim(struct winsize *sz) {
  ioctl(0, TIOCGWINSZ, sz);
  return;
}

char* generateBannerBorder(int width) {
  char prefix = '#';
  char* border = (char *)malloc(((width) + 1) * sizeof(char));
  memset(border, prefix, width);
  border[width] = '\0';
  return border;
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
      {"help", no_argument, NULL, 'h'},
      {"message", no_argument, NULL, 'm'},
      {"version", no_argument, NULL, 'v'},
      {NULL, 0, NULL, 0},
  };

  char *message = NULL;

  while ((opt = getopt_long(argc, argv, "hvm:", long_options, NULL)) != -1) {
    switch (opt) {
    case 'h':
      printf("\n");
      printf("  -h, --help       help, run `man banner-commenter` for full "
             "docs\n");
      printf("  -v, --version    get running version\n");
      printf("  -m, --message    pass string argument, must be wrapped in "
             "quotes\n");
      printf("\n");
      printf("\n");
      break;

    case 'v':
      printf("banner-commenter %s\n", PROGRAM_VERSION);
      break;

    case 'm':
      message = optarg;
      convertUpperCase(message);
      int width = sz.ws_col;
      char *border = generateBannerBorder(width);

      printf("\n");

      printf("%s\n", border);
      printf("%s\n", border);
      printf("## \n");
      printf("## %s\n", message);
      printf("## \n");
      printf("%s", border);
      printf("%s", border);

      printf("\n");
      printf("\n");

      break;

    default:
      printf("unexpected case\n");
      return EXIT_FAILURE;
    }
  }

  return 0;
}
