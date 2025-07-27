// expre_CastOperator2.cpp
// The following sample shows how to define and use a cast operator.
#include <stdio.h>
#include <string.h>

const auto sizeOfBuffer = 20;

class CountedAnsiString {
public:
  // Assume source is not null terminated
  CountedAnsiString(const char *pStr, size_t nSize)
      : m_pStr{new char[sizeOfBuffer]}, m_nSize(nSize) {

    strncpy(m_pStr, pStr, m_nSize);
    memset(&m_pStr[m_nSize], '!', 9); // for demonstration purposes.
  }

  // Various string-like methods...
  const char *GetRawBytes() const { return (m_pStr); }

  //
  // operator to cast to a const char *
  //
  operator const char *() {
    m_pStr[m_nSize] = '\0';
    return (m_pStr);
  }

private:
  char *m_pStr;
  const size_t m_nSize;
};

int main() {
  const char *kStr = "Excitinggg";
  CountedAnsiString myStr(kStr, 8);

  const char *pRaw = myStr.GetRawBytes();
  printf("RawBytes truncated to 10 chars:   %.10s\n", pRaw);

  const char *pCast = myStr; // or (const char *)myStr;
  printf("Casted Bytes:   %s\n", pCast);

  puts("Note that the cast changed the raw internal string");
  printf("Raw Bytes after cast:   %s\n", pRaw);
}