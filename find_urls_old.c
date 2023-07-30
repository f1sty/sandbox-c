#include <regex.h>
#include <stdio.h>
#include <string.h>

#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))

int main(int argc, char *argv[]) {
  static const char *const str = "Hello there, just https://here.com today\n and then he saw "
              "https://fuckall.org some http://links.also and "
              "https://whoknows.lol\nhttp://sfde.d/te.html?a=1&ab[0]=23; https://last.fm";
  static const char *const re = "https?://[a-zA-Z0-9.-]+\\.[a-zA-Z]{1,6}(/[^[:space:]]*)?";
  static const char *s = str;
  char *token = NULL;
  char *matches[256] = { NULL };
  regex_t regex;
  regmatch_t pmatch[1];
  regoff_t len;

  if (regcomp(&regex, re, REG_EXTENDED))
    return -1;

  for (unsigned int i = 0;; i++) {
    if (regexec(&regex, s, ARRAY_SIZE(pmatch), pmatch, 0))
      break;

    len = pmatch[0].rm_eo - pmatch[0].rm_so;
    /* printf("#%zu:\n", i); */
    /* printf("offset = %jd; length = %jd\n", (intmax_t)off, (intmax_t)len); */
    /* sprintf(&matches[i], "%.*s\n", len, s + pmatch[0].rm_so); */
    matches[i] = strndup(s + pmatch[0].rm_so, len);

    s += pmatch[0].rm_eo;
  } 

  for (int i = 0; matches[i] != NULL; i++) {
    printf("%s\n", matches[i]);
  }

  return 0;

  /* for (int i = 0; url_start_patterns[i] != NULL; i++) { */
  /*   char *url_str = strdup(str); */
  /*   char *url_start_pattern = url_start_patterns[i]; */
  /*   size_t url_len = 0; */
  /*   char *url = ""; */
  /*   while ((url_str = strstr(url_str, url_start_pattern)) != NULL) { */
  /*     url_len = strspn(url_str, url_chars); */
  /*     url = strndup(url_str, url_len); */
  /*     printf("%s\n", url); */
  /*     url_str += url_len; */
  /*   } */
  /* } */

  /* return 0; */
}
