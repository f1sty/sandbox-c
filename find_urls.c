#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void findurls(const char *str, char *urls[]) {
  static const char url_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                  "abcdefghijklmnopqrstuvwxyz"
                                  "0123456789-._~:/?#@!$&'*+,;=%[]";

  char *url_start_patterns[] = {"https://", "http://"};
  unsigned int j = 0;

  for (int i = 0; url_start_patterns[i] != NULL; i++) {
    static size_t url_len = 0;
    /* static char *url = ""; */
    char *url_str = strdup(str);
    char *url_start_pattern = url_start_patterns[i];

    while ((url_str = strstr(url_str, url_start_pattern)) != NULL) {
      url_len = strspn(url_str, url_chars);
      urls[j] = strndup(url_str, url_len);
      url_str += url_len;
      j += 1;
    }
  }
}

int main(int argc, char *argv[]) {
  char *str = "https://here.com today\n"
              "https://fuckall.org\n"
              "https://whoknows.lol\n"
              "https://last.fm";
  /* char *str = "https://here.com today\n and then he saw " */
  /*             "https://fuckall.org some http://links.also and " */
  /*             "https://whoknows.lol\nhttp://sfde.d/te.html?a=1&ab[0]=23; " */
  /*             "https://last.fm"; */
  char *urls[256] = {NULL};

  findurls(str, urls);

  for (int i = 0; urls[i] != NULL; i++) {
    printf("%s\n", urls[i]);
  }

  return 0;
}
