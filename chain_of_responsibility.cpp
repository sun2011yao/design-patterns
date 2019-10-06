#include <iostream>
#include <vector>
#include <ctime>

class Base {
 public:
  Base() { }
  void SetNext(Base *next) {
    next_ = next;
  }
  void Add(Base *node) {
    if (next_) {
      next_->Add(node);
    } else {
      next_ = node;
    }
  }
  virtual void Handle(int i) = 0;
 protected:
  Base *next_ = nullptr;
};

class Handler1 : public  Base {
 public:
  void Handle(int i) override {
    if (rand() % 3) {
      std::cout << "H1 passed " << i << " ";
      if (next_ != nullptr) {
        next_->Handle(i);
      }
    } else {
      std::cout << "H1 handled " << i << "\n";
    }
  }
};

class Handler2 : public  Base {
 public:
  void Handle(int i) override {
    if (rand() % 3) {
      std::cout << "H2 passed " << i << " ";
      if (next_ != nullptr) {
        next_->Handle(i);
      }
    } else {
      std::cout << "H2 handled " << i << "\n";
    }
  }
};

class Handler3 : public  Base {
 public:
  void Handle(int i) override {
    if (rand() % 3) {
      std::cout << "H3 passed " << i << " ";
      if (next_ != nullptr) {
        next_->Handle(i);
      }
    } else {
      std::cout << "H3 handled " << i << "\n";
    }
  }
};

int main(int argc, char ** argv) {
  srand(time(0));
  Handler1 root;
  Handler2 two;
  Handler3 thr;
  root.Add(&two);
  root.Add(&thr);
  thr.SetNext(&root);
  for (int i = 0; i < 10; ++i) {
    root.Handle(i);
    std::cout << "\n";
  }
  return 0;
}

