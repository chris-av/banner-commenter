#include "banner.h"
#include "config.h"
#include "utils.h"
#include "version.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

struct Configuration config = {
    .prefix = '#',
    .margin = 10,
    .padding = 10,
    .maxlen = 80,
};

int main(int argc, char *argv[]) {

  struct winsize sz;
  get_terminal_dim(&sz);

  if (sz.ws_col <= 50) {
    printf("screen size too small!\n");
    return EXIT_FAILURE;
  }

  int opt;
  char *message = NULL;
  size_t non_option_len = 0;

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
    }
  }

  for (int i = optind; i < argc; i++) {
    non_option_len += strlen(argv[i]);
  }

  message = malloc(non_option_len + argc - optind + 1);
  if (message == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return EXIT_FAILURE;
  }

  strcpy(message, "");
  for (int i = optind; i < argc; i++) {
    strcat(message, argv[i]);
    if (i < argc - 1) {
      strcat(message, " ");
    }
  }

  convertUpperCase(message);
  int msglen = (int)strlen(message);
  int maxlen = config.maxlen;

  int windowWidth = sz.ws_col;
  int bannerWidth = find_min(windowWidth, maxlen);

  char *horizontalBorder = generateBannerBorder(&config, bannerWidth);
  char *verticalBorder = generateBannerBorder(&config, 4);


  printf("\n");
  printf("%s\n", horizontalBorder);
  printf("%s\n", horizontalBorder);

  int counter = 0;
  printf("%s", verticalBorder);
  char *str_rest = (char *)malloc(maxlen-counter + 1);
  char *blank_line = (char *)malloc(maxlen);

  blank_line = memset(blank_line, ' ', maxlen-8);
  printf("%s%s\n", blank_line, verticalBorder);

  for (int i = 0; i < msglen; i++) {
    if (i == 0) {
      // just print the vertical border and move on
      printf("%s ", verticalBorder);
    } else if (i % (maxlen-10) == 0) {
      // you've reached the end of a line:
      //   print a vertical border, break line, 
      //   and then another border and continue printing msg
      printf(" %s\n%s ", verticalBorder, verticalBorder);
      counter = 0;
    }
    printf("%c", message[i]);
    counter++;
  }

  memset(str_rest, 0, strlen(str_rest));
  str_rest = memset(str_rest, ' ', maxlen-counter-9);
  printf("%s%s", str_rest, verticalBorder);

  printf("\n");
  printf("%s%s%s", verticalBorder, blank_line, verticalBorder);

  printf("\n");
  printf("%s\n", horizontalBorder);
  printf("%s\n", horizontalBorder);
  printf("\n");
  printf("\n");

  free(message);

  return 0;
}
