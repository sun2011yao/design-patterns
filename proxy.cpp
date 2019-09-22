//
// Created by yaoyao.sun on 2019-09-22.
// Copyright (c) 2019 Horizon Robotics. All rights reserved.
//

#include <iostream>
#include <string>

class SchoolGirl {
 public:
  std::string GetName() const {
    return name_;
  }
  void SetName(const std::string &name) {
    name_ = name;
  }
 private:
  std::string name_;
};
class IGiveGift {
 public:
  virtual void GiveFlowers(const std::string &flower_name) = 0;
};

class Pursuit : public IGiveGift {
 public:
  Pursuit(SchoolGirl girl) : love_girl_(girl) { }
  void GiveFlowers(const std::string &flower_name) {
    std::cout << "give " << love_girl_.GetName() << " a " << flower_name << "\n";
  }
 private:
  SchoolGirl love_girl_;
};

class Proxy : public IGiveGift {
 public:
  Proxy(SchoolGirl girl) : pursuit_(girl) { }
  void GiveFlowers(const std::string &flower_name) {
    pursuit_.GiveFlowers(flower_name);
  }
 private:
  Pursuit pursuit_;
};

int main(int argc, char **argv) {
  SchoolGirl girl;
  girl.SetName("tong");

  Proxy yao(girl);
  yao.GiveFlowers("mudan");
  return 0;
}

