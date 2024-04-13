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

char *generateBannerBorder(int width) {
  char prefix = config.prefix;
  char *border = (char *)malloc(((width) + 1) * sizeof(char));
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

  struct option long_opts[] = {
      {"help", no_argument, NULL, 'h'},
      {"version", no_argument, NULL, 'v'},
      {"show-config", no_argument, NULL, 's'},
      {"padding", no_argument, NULL, 'p'},
      {"margin", no_argument, NULL, 'm'},
      {"length", no_argument, NULL, 'l'},
      {"out", no_argument, NULL, 'o'},
      {NULL, 0, NULL, 0},
  };
  char *short_opts = "hvsp:m:l:o:";

  while ((opt = getopt_long(argc, argv, short_opts, long_opts, NULL)) != -1) {
    switch (opt) {
    case 'p': {
      int padding;
      char *endptr;
      padding = strtol(optarg, &endptr, 10);
      config.padding = padding;
      break;
    }

    case 'm': {
      int margin;
      char *endptr;
      margin = strtol(optarg, &endptr, 10);
      config.margin = margin;
      break;
    }

    case 'l': {
      int maxlen;
      char *endptr;
      maxlen = strtol(optarg, &endptr, 10);
      config.maxlen = maxlen;
      break;
    }

    case 'h': {
      printf("\n");
      printf("  -h, --help       help, run `man banner-commenter` for full "
             "docs\n");
      printf("  -v, --version    get running version\n");
      printf("  -p, --padding    set padding\n");
      printf("  -m, --margin     set margin\n");
      printf("  -o, --out        pass string argument, must be wrapped in "
             "quotes\n");
      printf("\n");
      printf("\n");
      return 0;
    }

    case 'v': {
      printf("banner-commenter %s\n", PROGRAM_VERSION);
      return 0;
    }

    case 's': {
      printf("showing config : \n");
      printf("  margin \t: \t%d\n", config.margin);
      printf("  padding \t: \t%d\n", config.padding);
      printf("  prefix \t: \t%d\n", config.prefix);
      printf("  maxlen \t: \t%d\n", config.maxlen);
      break;
    }

    case 'o': {
      char *message = NULL;
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

      return 0;
    }

    default: {
      printf("unexpected case\n");
      return EXIT_FAILURE;
    }
    }
  }

  return 0;
}
