// Author: mikedebo@gmail.com (Michael DiBernardo)
// Copyright Michael DiBernardo 2006
//
// Functions to format data in various ways. Could have used a namespace
// instead of a class, but whatever...
#ifndef __FORMAT_H__
#define __FORMAT_H__

#include <string>
using std::string;

class Format {
 public:
  // Convert a span of time in milliseconds to a reading such as: 00:01:23.
  static string millisecondsToTicker(long ms);
  
  // Convert a span of time in seconds to a reading such as: 00:01:23.
  static string secondsToTicker(int s);

  // Convert an integer to a string.
  static string intToString(int number);

 private:
  // Don't allow instantiation of this "class".
  Format();
};

#endif
