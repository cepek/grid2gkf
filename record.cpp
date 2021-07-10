#include "record.h"

#include <sstream>

Record::Record(std::string line, std::string desc)
{
  if (desc.size() > 1) note_ = desc.substr(1);

  std::istringstream istr(line);
  std::string word;
  istr >> word;
  if (word.empty()) return;   // this should never happen ...
  code_ = word;

  istr >> data_;
  if (data_.empty()) return;  // no code

  char c;
  while (istr.get(c))
    {
      if (c == '\'') break;

      data_.push_back(c);
    }

  while (istr.get(c)) note_.push_back(c);

  // remove trailing spaces
  while(!data_.empty() && std::isspace(data_.back())) data_.pop_back();
  while(!note_.empty() && std::isspace(note_.back())) note_.pop_back();
}

std::string Record::code() const
{
  return code_;
}

std::string Record::data() const
{
  return data_;
}

std::string Record::note() const
{
  return note_;
}
