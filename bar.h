// bar.h
// TO DO:  add header comment here.  Also add function header comments below.

#include "myrandom.h"
#include <iostream>
#include <string>
using namespace std;

class Bar {

private:
  string name;
  int value;
  string category;

public:
  Bar() {

    name = "";
    value = 0;
    category = "";
  }

  Bar(string name, int value, string category) {

    this->name = name;
    this->value = value;
    this->category = category;
  }

  virtual ~Bar() {
    // I am leaving empty because we are not allocating memory for this one
  }

  string getName() { return name; }

  int getValue() { return value; }

  string getCategory() { return category; }

  bool operator<(const Bar &other) const { return this->value < other.value; }

  bool operator<=(const Bar &other) const { return this->value <= other.value; }

  bool operator>(const Bar &other) const { return this->value > other.value; }

  bool operator>=(const Bar &other) const { return this->value >= other.value; }
};
