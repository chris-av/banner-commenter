#include "config.h"
#include <stdlib.h>
#include <string.h>

char *generateBannerBorder(struct Configuration *config, int width) {
  char prefix = config->prefix;
  char *border = (char *)malloc(((width) + 1) * sizeof(char));
  memset(border, prefix, width);
  border[width] = '\0';
  return border;
}
