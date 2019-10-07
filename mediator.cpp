#include <string.h>

#include <iostream>

class FileSelectionDialog;

class Widget {
 public:
  Widget(FileSelectionDialog *mediator, char *name)
      : mediator_(mediator) {
    strcpy(name_, name);
  }
  virtual ~Widget() { }
  virtual void Changed();
  virtual void UpdateWidget() = 0;
  virtual void QueryWidget() = 0;
 protected:
  char name_[20];
 private:
  FileSelectionDialog *mediator_;
};

class List : public Widget {
 public:
  List(FileSelectionDialog *mediator, char *name) : Widget(mediator, name) { }
  void UpdateWidget() override {
    std::cout << name_ << " list updated\n";
  }
  void QueryWidget() override {
    std::cout << name_ << " list queried\n";
  }
};

class Edit : public Widget {
 public:
  Edit(FileSelectionDialog *mediator, char *name) : Widget(mediator, name) { }
  void UpdateWidget() override {
    std::cout << name_ << " edit updated\n";
  }
  void QueryWidget() override {
    std::cout << name_ << " edit queried\n";
  }
};

class FileSelectionDialog
{
 public:
  enum Widgets
  {
    FilterEdit, DirList, FileList, SelectionEdit
  };
  FileSelectionDialog()
  {
    components_[FilterEdit] =
        new Edit(this, const_cast<char *>("filter"));
    components_[DirList] =
        new List(this, const_cast<char *>("dir"));
    components_[FileList] =
        new List(this, const_cast<char *>("file"));
    components_[SelectionEdit] =
        new Edit(this, const_cast<char *>("selection"));
  }
  virtual ~FileSelectionDialog();
  void handleEvent(int which)
  {
    components_[which]->Changed();
  }
  virtual void widgetChanged(Widget *theChangedWidget)
  {
    if (theChangedWidget == components_[FilterEdit])
    {
      components_[FilterEdit]->QueryWidget();
      components_[DirList]->UpdateWidget();
      components_[FileList]->UpdateWidget();
      components_[SelectionEdit]->UpdateWidget();
    }
    else if (theChangedWidget == components_[DirList])
    {
      components_[DirList]->QueryWidget();
      components_[FileList]->UpdateWidget();
      components_[FilterEdit]->UpdateWidget();
      components_[SelectionEdit]->UpdateWidget();
    }
    else if (theChangedWidget == components_[FileList])
    {
      components_[FileList]->QueryWidget();
      components_[SelectionEdit]->UpdateWidget();
    }
    else if (theChangedWidget == components_[SelectionEdit])
    {
      components_[SelectionEdit]->QueryWidget();
      std::cout << "   file opened\n";
    }
  }
 private:
  Widget *components_[4];
};

FileSelectionDialog::~FileSelectionDialog() {
  for (int i = 0; i < 4; ++i) {
    delete components_[i];
  }
}

void Widget::Changed() {
  mediator_->widgetChanged(this);
}

int main()
{
  FileSelectionDialog fileDialog;
  int i;

  std::cout << "Exit[0], Filter[1], Dir[2], File[3], Selection[4]: ";
  std::cin >> i;

  while (i)
  {
    fileDialog.handleEvent(i - 1);
    std::cout << "Exit[0], Filter[1], Dir[2], File[3], Selection[4]: ";
    std::cin >> i;
  }
}