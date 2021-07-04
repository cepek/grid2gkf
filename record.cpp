#include "record.h"

#include <sstream>

Record::Record(std::string line)
{
  std::istringstream istr(line);
  std::string word;
  istr >> word;
  if (word.empty()) return;   // this should never happen ...
  tag_ = word;

  istr >> code_;
  if (code_.empty()) return;  // no code

  char c;
  while (istr.get(c))
    {
      if (c == '\'') break;

      code_.push_back(c);
    }

  while (istr.get(c)) note_.push_back(c);

  // remove trailing spaces
  while(!code_.empty() && std::isspace(code_.back())) code_.pop_back();
  while(!note_.empty() && std::isspace(note_.back())) note_.pop_back();
}

std::string Record::tag() const
{
  return tag_;
}

std::string Record::code() const
{
  return code_;
}

std::string Record::note() const
{
  return note_;
}
