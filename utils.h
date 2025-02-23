#ifndef BANNERCOM_UTILS_H
#define BANNERCOM_UTILS_H
struct winsize;
void cpyargs(int n, char *args_orig[], char *args_cpy[]);
void convertUpperCase(char *txt);
void get_terminal_dim(struct winsize *sz);
int find_min(int n1, int n2);
int find_max(int n1, int n2);
#endif
