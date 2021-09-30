#include "module1.h"

#include "generator.h"

namespace module1 {
int Next() { return Generator::Next(); }
}  // namespace module1
