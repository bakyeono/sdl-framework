#include "mystrcasecmp.h"

int mystrcasecmp(const char* const lhs, const char* const rhs) {
//  return stricmp(lhs, rhs) < 0;

//  return strcasecmp(lhs, rhs) < 0;

  std::string l = lhs;
  for (auto it = l.begin(); it != l.end(); ++it) {
    if ('A' <= *it && *it <= 'Z')
      *it = *it - ('A' - 'a');
  }
  std::string r = rhs;
  for (auto it = r.begin(); it != r.end(); ++it) {
    if ('A' <= *it && *it <= 'Z')
      *it = *it - ('A' - 'a');
  }
  return strcmp(l.c_str(), r.c_str());
}
