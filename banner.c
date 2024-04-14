#include "config.h"
#include <stdlib.h>
#include <string.h>

char *generateBannerBorder(int width, struct Configuration *config) {
  char prefix = config->prefix;
  char *border = (char *)malloc(((width) + 1) * sizeof(char));
  memset(border, prefix, width);
  border[width] = '\0';
  return border;
}
