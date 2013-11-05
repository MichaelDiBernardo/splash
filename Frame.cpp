#include "Frame.h"
#include <fstream>
using std::string;
using std::stringstream;
using std::ifstream;

Frame::Frame(ifstream* in_fp) {
  // Naming convenience.
  ifstream& fp = *in_fp;

  char line[1024];
  fp.getline(line, 1024);

  string lines(line);

  stringstream s(lines);
  int count = 0;
  
  while (!s.eof()) {
    double junk;
    s >> junk;
    count++;
  }
  
  numFields_ = count - 1;

  fields_ = new double[count];
  stringstream s2(lines);

  double tempTime;
  s2 >> tempTime;

  //convert from sec to ms
  time_ = static_cast<long>(ceil(tempTime * 1000));

  for (int i = 0; i < count; ++i)
    s2 >> fields_[i];
}

Frame::Frame(int nf) : numFields_(nf) {
  fields_ = new double[numFields_];
}

Frame::Frame(const Frame& rhs) {
  numFields_ = rhs.numFields_;
  time_ = rhs.time_;
  fields_ = new double[numFields_];
  
  for (int i = 0; i < numFields_; ++i)
    fields_[i] = rhs.fields_[i];
}

Frame::~Frame() {
  delete [] fields_;
}

int Frame::getNumFields() const
{
  return numFields_;
}

const double* Frame::getFields() const {
  return fields_;
}

unsigned long Frame::getTimeInMS() const {
  return time_;
}

Frame Frame::operator+(const Frame& rhs) const {
  Frame temp(this->getNumFields());

  for (int i = 0; i < this->getNumFields(); ++i)
    temp.fields_[i] = this->fields_[i] + rhs.fields_[i];

  temp.time_ = this->time_ + rhs.time_;
  return temp;
}

Frame Frame::operator-(const Frame& rhs) const {
  Frame temp(this->getNumFields());

  for (int i = 0; i < this->getNumFields(); ++i)
    temp.fields_[i] = this->fields_[i] - rhs.fields_[i];

  temp.time_ = this->time_ - rhs.time_;
  return temp;
}

Frame Frame::operator*(double scalar) const {
  Frame temp(this->getNumFields());

  for (int i = 0; i < this->getNumFields(); ++i)
    temp.fields_[i] = this->fields_[i] * scalar;

  temp.time_ = floorl(this->time_ * scalar);
  return temp;
}
