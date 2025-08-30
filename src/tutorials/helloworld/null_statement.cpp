#include <cstdio>
#include <cstdlib>

char *myStrCpy(char *Dest, const char *Source) {
  char *DestStart = Dest;
  // Assign value pointed to by Source to Dest until the end-of-string 0 is
  // encountered.
  while ((*Dest++ = *Source++))
    ; // Null Statement
  return DestStart;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) {
  char dest_str[128]{0};

  myStrCpy(dest_str, "Bork and Heck!");

  printf("myStrCpy: %s\n", dest_str);
  return EXIT_SUCCESS;
}