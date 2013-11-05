// Author: mikedebo@gmail.com (Michael DiBernardo)
// Copyright Michael DiBernardo 2006
// Implementation of class Format and related constructs.
#include "Format.h"
#include <stdio.h>
#include <sstream>
using std::stringstream;

const int kNumMillisecondsInSecond = 1000;
const int kNumMillisecondsInMinute = 60 * kNumMillisecondsInSecond;

string Format::millisecondsToTicker(long ms) {
  long minutes = ms / kNumMillisecondsInMinute;
  ms -= minutes * kNumMillisecondsInMinute;

  long seconds = ms / kNumMillisecondsInSecond;
  ms -= seconds * kNumMillisecondsInSecond;
  
  const int kBufSize = 9; // strlen("00:00:00") = 8, plus \0
  char buf[kBufSize];
  snprintf(buf, kBufSize, "%.2ld:%.2ld:%.2ld", minutes, seconds, ms);
  return string(buf);
}

string Format::secondsToTicker(int s) {
  return Format::millisecondsToTicker(s * 1000);
}

string Format::intToString(int num) {
  stringstream ss;
  string toReturn;
  ss << num;
  ss >> toReturn;
  return toReturn;
}

Format::Format() {
}
