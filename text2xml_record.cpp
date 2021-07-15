#include "text2xml_record.h"

#include <sstream>

namespace GNU_gama {
  namespace local {

    Text2xmlRecord::Text2xmlRecord(std::string line, std::string desc)
    {
      if (desc.size() > 1) note_ = desc.substr(1);

      std::istringstream istr(line);
      std::string word;
      istr >> word;
      if (word.empty()) return;   // this should never happen ...
      for (auto& c : word) c = std::toupper(c);
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

    std::string Text2xmlRecord::code() const
    {
      return code_;
    }

    std::string Text2xmlRecord::data() const
    {
      return data_;
    }

    std::string Text2xmlRecord::note() const
    {
      return note_;
    }

  } // namespace local
} // namespace GNU_gama
