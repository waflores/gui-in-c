#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *trim(char *szSource) {
  char *pszEOS = 0;

  // Set pointer to character before terminating NULL
  pszEOS = szSource + strlen(szSource) - 1;

  // iterate backwards until non '_' is found
  while ((pszEOS >= szSource) && (*pszEOS == '_')) {
    *pszEOS-- = '\0';
  }
  return szSource;
}

int main() {
  char szbuf[] = "12345________";
  printf("\nBefore trim: %s", szbuf);
  printf("\nAfter trim: %s\n", trim(szbuf));
  return EXIT_SUCCESS;
}