#ifndef RECORD_H
#define RECORD_H

#include <string>

class Record
{
public:
  Record(std::string line, std::string desc=std::string());

  std::string tag () const;
  std::string code() const;
  std::string note() const;

private:
  std::string tag_, code_, note_;
};

#endif // RECORD_H
