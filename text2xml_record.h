#ifndef GNU_GAMA_LOCAL_TEXT2XML_RECORD_H
#define GNU_GAMA_LOCAL_TEXT2XML_RECORD_H

#include <string>
#include <vector>

namespace GNU_gama {
  namespace local {

    class Text2xmlRecord
    {
    public:
      Text2xmlRecord(std::string line);

      std::string code() const;
      std::string note() const;
      bool empty() const;
      std::string::size_type size() const;
      const std::vector<std::string>& tokens() const;

    private:
      std::string code_, data_, note_;
      std::vector<std::string> tokens_;
    };

  } // namespace local
} // namespace GNU_gama

#endif // GNU_GAMA_LOCAL_TEXT2XML_RECORD_H
