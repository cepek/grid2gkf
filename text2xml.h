#ifndef SNDAT2GKF_H
#define SNDAT2GKF_H

#include "record.h"
#include <istream>
#include <vector>
#include <unordered_map>

namespace GNU_gama { namespace local {

class Text2xml
{
public:
    Text2xml(std::istream&, std::ostream&);

    void exec();
    int  status() const;

    std::string version() const;

private:

#define Text2xml_debug 0
#ifdef  Text2xml_debug
    void print() const;
#endif

    void error(std::string);
    void gkf_begin();
    void gkf_end();

    std::istream& inp_;
    std::ostream& out_;
    int status_;

    std::vector<Record> records_;
    std::vector<Record>::size_type index_;
    std::string cluster_;
    std::string from_;      // observation set (DB)
    std::string prev_;      // traverse previous point (TB)
    void close_cluster_if_opened();
    std::string find_next_traverse_point();

    std::vector<std::string> words_;
    void write_record();
    void write_record_C();
    void write_record_A();
    void write_record_D();
    void write_record_DB();
    void write_record_DE();
    void write_record_DN();
    void write_record_DM();
    void write_record_TB();
    void write_record_TE();
    void write_record_T ();

    const std::unordered_map<std::string, std::string> tagmap_
    {
      {"A",  "obs"},  // angle
      {"C",  ""},     // point coordinates
      {"D",  "obs"},  // distance
      {"DB", ""},     // direction begin
      {"DE", ""},     // direction end
      {"DN", ""},     // direction reading
      {"DM", ""},     // direction with all measurements
      {"TB", ""},     // traverse begin
      {"TE", ""},     // traverse end
      {"T",  ""}      // traverse point
    };

};

}}     //namespace GNU_Gama::local
#endif // SNDAT2GKF_H
