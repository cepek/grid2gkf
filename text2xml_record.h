#ifndef GNU_GAMA_LOCAL_TEXT2XML_RECORD_H
#define GNU_GAMA_LOCAL_TEXT2XML_RECORD_H

#include <string>

namespace GNU_gama {
  namespace local {

    class Text2xmlRecord
    {
    public:
      Text2xmlRecord(std::string line);

      std::string code() const;
      std::string data() const;
      std::string note() const;

      bool empty() const;

    private:
      std::string code_, data_, note_;
    };

  } // namespace local
} // namespace GNU_gama

#endif // GNU_GAMA_LOCAL_TEXT2XML_RECORD_H
