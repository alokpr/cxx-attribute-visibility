#include <dlfcn.h>

#include <cstdlib>
#include <iostream>

using NextFunc = int (*)();

class Module {
 public:
  ~Module() {
    if (module_) dlclose(module_);
  }

  bool Init(const char *filename, const char *symbol) {
    module_ = dlopen(filename, RTLD_NOW | RTLD_LOCAL);
    if (!module_) {
      std::cerr << "Failed to open: " << filename << "\n";
      return false;
    }

    next_ = reinterpret_cast<NextFunc>(dlsym(module_, symbol));
    if (!next_) {
      std::cerr << "Failed to find symbol: " << symbol << "\n";
      return false;
    }

    return true;
  }

  int Next() { return next_(); }

 private:
  void *module_ = nullptr;
  NextFunc next_ = nullptr;
};

int main(int argc, char *argv[]) {
  Module module1;
  if (!module1.Init("libmodule1.so", "_ZN7module14NextEv")) {
    std::cerr << "Failed to init module1" << std::endl;
    return EXIT_FAILURE;
  }

  Module module2;
  if (!module2.Init("libmodule2.so", "_ZN7module24NextEv")) {
    std::cerr << "Failed to init module2" << std::endl;
    return EXIT_FAILURE;
  }

  std::cout << "module1::Next=" << module1.Next() << std::endl;
  std::cout << "module2::Next=" << module2.Next() << std::endl;
  return EXIT_SUCCESS;
}
