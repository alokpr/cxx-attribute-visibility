#ifndef NEXT_H_
#define NEXT_H_

class Generator {
public:
  static int Next() {
    static int next;
    return ++next;
  }
};

#endif // NEXT_H_
