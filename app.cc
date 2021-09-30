#include <cstdlib>
#include <iostream>

#include "module1.h"
#include "module2.h"

int main(int argc, char *argv[]) {
  std::cout << "module1::Next=" << module1::Next() << std::endl;
  std::cout << "module2::Next=" << module2::Next() << std::endl;
  return EXIT_SUCCESS;
}
