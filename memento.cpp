#include <iostream>
#include <string>

// 前向声明
class Number;

class Memento {
  friend class Number;
 public:
  Memento(int value) : state_(value) { }
 private:
  int state_;
};

class Number {
 public:
  Number(int value) : value_(value) { }
  void Dubble() {
    value_ = 2 * value_;
  }
  void Half() {
    value_ /= 2;
  }
  int GetValue() {
    return value_;
  }
  Memento* CreateMemento() {
    return new Memento(value_);
  }
  void ReinstateMemento(Memento *m) {
    value_ = m->state_;
  }
 private:
  int value_;
};

class Command {
 public:
  typedef void(Number:: *Action)();
  Command(Number *receiver, Action action) {
    receiver_ = receiver;
    action_ = action;
  }
  virtual void Execute() {
    memento_list_[num_commands_] = receiver_->CreateMemento();
    command_list_[num_commands_] = this;
    if (num_commands_ > high_water_) {
      high_water_ = num_commands_;
    }
    ++num_commands_;
    (receiver_->*action_)();
  }
  static void Undo() {
    if (num_commands_ == 0) {
      std::cout << "*** Attempt to run off the end!! ***\n";
      return;
    }
    command_list_[num_commands_-1]->receiver_->ReinstateMemento(
        memento_list_[num_commands_-1]);
    --num_commands_;
  }
  static void Redo() {
    if (num_commands_ > high_water_) {
      std:: cout << "*** Attempt to run off the end!! ***\n";
      return;
    }
    (command_list_[num_commands_]->receiver_->*(
        command_list_[num_commands_]->action_))();
    ++num_commands_;
  }

 protected:
  Number *receiver_;
  Action action_;
  static Memento *memento_list_[20];
  static Command *command_list_[20];
  static int num_commands_;
  static int high_water_;
};

Memento *Command::memento_list_[];
Command *Command::command_list_[];
int Command::num_commands_ = 0;
int Command::high_water_ = 0;


int main() {
  int i;
  std::cout << "Integer: ";
  std::cin >> i;
  Number *object = new Number(i);

  Command *commands[3];
  commands[1] = new Command(object, &Number::Dubble);
  commands[2] = new Command(object, &Number::Half);

  std::cout << "Exit[0], Double[1], Half[2], Undo[3], Redo[4]: ";
  std::cin >> i;

  while (i)
  {
    if (i == 3)
      Command::Undo();
    else if (i == 4)
      Command::Redo();
    else
      commands[i]->Execute();
    std::cout << "   " << object->GetValue() << std::endl;
    std::cout << "Exit[0], Double[1], Half[2], Undo[3], Redo[4]: ";
    std::cin >> i;
  }
  return 0;
}



