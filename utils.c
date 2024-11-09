#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/ioctl.h>

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

int find_min(int n1, int n2) {
  if (n1 > n2) {
    return n2;
  }
  return n1;
}

int find_max(int n1, int n2) {
  if (n1 > n2) {
    return n1;
  }
  return n2;
}
