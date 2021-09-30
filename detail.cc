#include "detail.h"

namespace detail {

int Next() {
  static int next;
  return ++next;
}

}  // namespace detail
