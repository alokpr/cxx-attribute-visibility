#include "module2.h"

#include "generator.h"

namespace module2 {
int Next() { return Generator::Next(); }
}  // namespace module2
