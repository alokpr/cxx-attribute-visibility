#include "module1.h"

namespace common {
int Next() {
  static int next;
  return ++next;
}
}  // namespace common
