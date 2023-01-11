// barchartanimate.h
// TO DO:  add header comment here.  Also add function header comments below.

#include "barchart.h"
#include "myrandom.h" // used by graders, do not remove
#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unistd.h>
#include <vector>

using namespace std;

//
// BarChartAnimate
//
class BarChartAnimate {
private:
  //
  // Private member variables for the abstraction.
  // This implementation uses a low-level C array, bars, to store a list of
  // BarCharts.  As a result, you must also keep track of the number of
  // elements stored (size) and the capacity of the array (capacity).
  // This IS dynamic array, so it must expand automatically, as needed.
  //
  BarChart *barcharts; // pointer to a C-style array
  int size;
  int capacity;
  map<string, string> colorMap;
  string title;
  string xlabel;
  string source;

public:
  // a parameterized constructor:
  // Like the ourvector, the barcharts C-array should be constructed here
  // with a capacity of 4.
  BarChartAnimate(string title, string xlabel, string source) {

    this->title = title;
    this->xlabel = xlabel;
    this->source = source;
    barcharts = new BarChart[4];
    size = 0;
    capacity = 4;
  }

  virtual ~BarChartAnimate() {
    if (barcharts != nullptr) // then we have something to free:
    {
      delete[] barcharts;
    }
  }

  // addFrame:
  // adds a new BarChart to the BarChartAnimate object from the file stream.
  // if the barcharts has run out of space, double the capacity (see
  // ourvector.h for how to double the capacity).
  // See application.cpp and handout for pre and post conditions.
  void addFrame(ifstream &file) {
    if (size >= capacity) {
      capacity = capacity * 2;
      BarChart *newCharts = new BarChart[capacity];
      for (int i = 0; i < size; i++) {
        newCharts[i] = barcharts[i];
      }
      barcharts = newCharts;
    }
    BarChart tempChart;
    if (file.is_open()) {
      string line, word;
      int i = 0;
      while (getline(file, line)) {
        vector<string> columns;
        stringstream s(line);
        if (line == "") {
          if (i == 0) {
            continue;
          } else {
            break;
          }
        }
        i++;        
        while (getline(s, word, ',')) {
          columns.push_back(word);
        }
        if (columns.size() == 1) {
          BarChart tempChart (stoi(columns[0]));
        } else {
          tempChart.setFrame(columns[0]);
          tempChart.addBar(columns[2], stoi(columns[3]), columns[4]);
        }
       
      }
    }
    size++;
    barcharts[size] = tempChart;
   }

  // animate:
  // this function plays each frame stored in barcharts.  In order to see the
  // animation in the terminal, you must pause between each frame.  To do so,
  // type:  usleep(3 * microsecond);
  // Additionally, in order for each frame to print in the same spot in the
  // terminal (at the bottom), you will need to type: output << CLEARCONSOLE;
  // in between each frame.
  void animate(ostream &output, int top, int endIter) {
    unsigned int microsecond = 50000;

    stringstream chartDrawing("");
    map<string, string> mp;
    mp["North America"] = CYAN;
    mp["Asia"] = GREEN;
    mp["South America"] = GOLD;

    
    
    barcharts[0].graph(chartDrawing, mp, 3);
    //cout << chartDrawing.str();
    

    // TO DO:  Write this function.
  }

  int getSize() { return size; }

  BarChart &operator[](int i) {
    BarChart bc;

    if (i < 0 || i >= size) {
      throw out_of_range("Barchartanimate: i out of bounds");
    }
    return barcharts[i];
  }
};
