#ifndef RECORD_H
#define RECORD_H

#include <string>

class Record
{
public:
  Record(std::string line, std::string desc=std::string());

  std::string code() const;
  std::string data() const;
  std::string note() const;

private:
  std::string code_, data_, note_;
};

#endif // RECORD_H
