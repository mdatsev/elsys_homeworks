// https://www.hackerrank.com/contests/numbers-1/challenges/numbers-4/submissions/code/1303741132

#include <iostream>
#include <sstream>
#include <iomanip>
#include <float.h>
using namespace std;
int main() {
  try {
    bool strict = false, integers_only = false;
    double min = DBL_MAX, max = -DBL_MAX, sum = 0;
    int numbers_count = 0;
    for (string input; input != "END"; cin >> input) {
      double number;
      istringstream in(input);
      if (in >> number) {
        numbers_count++;
        if (integers_only) {
          if (strict &&
              number != (int)number)  // check if number is not an integer
            throw "ERR: PROVIDE ONLY INTEGERS";
          number = (int)number;
        }
        sum += number;
        if (number < min) min = number;
        if (number > max) max = number;
      } else if (strict)
        throw "ERR: PROVIDE ONLY NUMBERS";
      if (numbers_count == 0) {
        integers_only = input.find("integers-only") != string::npos;
        strict = input.find("strict") != string::npos;
      }
    }
    if (numbers_count == 0) throw "ERR: PROVIDE AT LEAST ONE NUMBER";
    double average = sum / numbers_count;
    cout << setprecision(4) << min << " " << max << " "
         << (integers_only ? (int)average : average);
    return 0;
  } catch (const char *msg) {
    cout << msg;
    return -1;
  }
}