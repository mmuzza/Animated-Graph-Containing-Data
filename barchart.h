// barchart.h
// TO DO:  add header comment here.  Also add function header comments below.

#include "bar.h"
#include "myrandom.h" // used in graders, do not remove
#include <algorithm>
#include <iostream>
#include <map>
#include <math.h>
#include <vector>

using namespace std;

// Constants used for bar chart animation.  You will primarily
// use these in barchartanimate.h, but you might find some useful here.
const string BOX = "\u29C8";
const string CLEARCONSOLE = "\033[2J";
const string RESET("\033[0m");

//
// NOTE: COMMENT AND UNCOMMENT AS NEEDED BASED ON YOUR TERMINAL
//
// Color codes for light mode terminals
// const string RED("\033[1;36m");
// const string PURPLE("\033[1;32m");
// const string BLUE("\033[1;33m");
// const string CYAN("\033[1;31m");
// const string GREEN("\033[1;35m");
// const string GOLD("\033[1;34m");
// const string BLACK("\033[1;37m");
// const vector<string> COLORS = {RED, PURPLE, BLUE, CYAN, GREEN, GOLD, BLACK};

// Color codes for darker mode terminals
const string CYAN("\033[1;36m");
const string GREEN("\033[1;32m");
const string GOLD("\033[1;33m");
const string RED("\033[1;31m");
const string PURPLE("\033[1;35m");
const string BLUE("\033[1;34m");
const string WHITE("\033[1;37m");
// const string RESET("\033[0m");
// const vector<string> COLORS = {CYAN, GREEN, GOLD, RED, PURPLE, BLUE, WHITE};

//
// BarChart
//
class BarChart {
private:
  Bar *bars;
  int capacity;
  int size;
  string frame;

public:
  BarChart() {
    bars = nullptr;
    capacity = 0;
    size = 0;
    frame = "";
  }

  BarChart(int n) {
    bars = new Bar[n];
    capacity = n;
    size = 0;
    frame = "";
  }

  BarChart(const BarChart &other) {
    this->capacity = other.capacity;
    this->size = other.size;
    this->bars = new Bar[capacity];
    for (int i = 0; other.size; i++) {
      Bar b = other.bars[i];
      this->bars[i] = Bar(b.getName(), b.getValue(), b.getCategory());
    }
  }

  BarChart &operator=(const BarChart &other) {
    BarChart bc = BarChart();
    bc.capacity = other.capacity;
    bc.size = other.size;
    bc.frame = other.frame;
    for (int i = 0; other.size; i++) {
      Bar b = other.bars[i];
      bars[i] = Bar(b.getName(), b.getValue(), b.getCategory());
    }
    return bc;
  }

  void clear() {

    delete[] bars;
    
    bars = nullptr;
    size = 0;
    capacity = 0;
  }

  virtual ~BarChart() {

    if(bars!=nullptr){ // then we have something to free
      delete[] bars;
    }
  }

  void setFrame(string frame) { this->frame = frame; }
  string getFrame() { return frame; }
  int getCapacity() { return capacity; }

  Bar &operator[](int i) {
    if (i < 0 || i >= size) {
      throw out_of_range("Barchart: i out of bounds");
    }
    return this->bars[i];
  }

  bool addBar(string name, int value, string category) {
    if (size >= capacity) {
      return false;
    }
    bars[size] = Bar(name, value, category);
    size++;
    return true;
  }

  int getSize() { return size; }

  // dump
  // Used for printing the BarChart object.
  // Recommended for debugging purposes.  output is any stream (cout,
  // file stream, or string stream).
  // Format:
  // "frame: 1
  // aname 5 category1
  // bname 4 category2
  // cname 3 category3" <-newline here
  void dump(ostream &output) {

    Bar* sortedBars = new Bar[size];
    for(int i = 0; i < size; i++){
      sortedBars[i] = bars[i];
    }

    sort(sortedBars, sortedBars + size, greater<Bar>());
    
    string out;
    out += "frame: " + frame + "\n";
    for (int i = 0; i < size; i++) {
      Bar b = sortedBars[i];
      out += b.getName() + " " + to_string(b.getValue()) + " " +
             b.getCategory() + "\n";
    }
    output << out << endl;
  }

  void graph(ostream &output, map<string, string> &colorMap, int top) {

    Bar* sortedBars = new Bar[size];
    for(int i = 0; i < size; i++){
      sortedBars[i] = bars[i];
    }

    int lenMax = 60;
    int biggestBoxSize = sortedBars[0].getValue();
    string color = "\033[1;36m";
    sort(sortedBars, sortedBars + size, greater<Bar>());
    for (int i = 0; i < top; i++) {
      string barStr = "";
      int boxSize =
          floor(float(float(sortedBars[i].getValue()) / biggestBoxSize) * 60);

      for (int j = 0; j < boxSize; j++) {
        barStr += BOX;
      }
      barStr += " " + sortedBars[i].getName() + " " + to_string(sortedBars[i].getValue());
      output << colorMap[sortedBars[i].getCategory()] << barStr << endl;
    }
  }
};
