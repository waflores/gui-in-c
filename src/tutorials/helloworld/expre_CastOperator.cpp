// expre_CastOperator2.cpp
// The following sample shows how to define and use a cast operator.
#include <cstdint>
#include <iostream>
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

struct message_header {
  uint32_t type;
  uint32_t source;
  uint32_t destination;
};

std::ostream &operator<<(std::ostream &s, const message_header &mh) {
  return s << "type: " << std::to_string(mh.type)
           << ", source: " << std::to_string(mh.source)
           << ", destination: " << std::to_string(mh.destination);
}

int main() {
  const char *kStr = "Excitinggg";
  CountedAnsiString myStr(kStr, 8);

  const char *pRaw = myStr.GetRawBytes();
  printf("RawBytes truncated to 10 chars:   %.10s\n", pRaw);

  const char *pCast = myStr; // or (const char *)myStr;
  printf("Casted Bytes:   %s\n", pCast);

  puts("Note that the cast changed the raw internal string");
  printf("Raw Bytes after cast:   %s\n", pRaw);

  message_header m{0x50, 32, 33};
  std::cout << "size of message header: " << sizeof(m) << std::endl;
  std::cout << "message header: " << m << std::endl;

  uint32_t bare_header[]{0x50, 33, 32};
  auto converted_header = reinterpret_cast<message_header &>(bare_header);
  std::cout << "our new message header: " << converted_header << std::endl;
}