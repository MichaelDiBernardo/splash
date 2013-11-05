// Author: mikedebo@gmail.com (Michael DiBernardo)
// Copyright Michael DiBernardo 2006
//
// Basic helpers that swat certain dangerous C++ language features and random
// utility functions.
#ifndef __BASICS_H__
#define __BASICS_H__

#include <iterator>

// Stolen from Google's basictypes.h (specifically from libjingle: It's on
// Koders.com. 
#define DISALLOW_EVIL_CONSTRUCTORS(TypeName)    \
  TypeName(const TypeName&);                    \
  void operator=(const TypeName&)

// Free all pointers stored in a container from start to end. Thanks to folks
// from comp.lang.c++ and comp.std.c++ for reminding me how templated
// declarations work -- I'm such a tool.
template<class ForwardIterator>
void STLDeleteContainerPointers(ForwardIterator start, ForwardIterator end) {
  while (start != end) {
    delete *start;
    ++start;
  }
}

#endif
