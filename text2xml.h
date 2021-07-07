#ifndef SNDAT2GKF_H
#define SNDAT2GKF_H

#include "record.h"
#include <istream>
#include <vector>
#include <list>
#include <set>
#include <unordered_map>
#include <algorithm>

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
  std::set<std::string> known_coordinates_;
  std::set<std::string> unknown_coordinates_;
  std::string k_(std::string id) { known_coordinates_.insert(id); return id; }
  std::string u_(std::string id) { unknown_coordinates_.insert(id); return id; }

  std::string cluster_;
  std::string from_;      // observation set (DB)
  std::list<std::string> traverse_points_;
  void close_cluster_if_opened();
  void separate_angle_ids(std::string triple,  // separated by 2 hyphens (-)
                          std::string& from, std::string& bs, std::string& fs);
  std::string bearing2azimuth(std::string);

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
  void write_record_M ();
  void write_record_B ();

  void write_record_ORDER();
  std::string g2_axes_xy_{"ne"};

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
    {"T",  ""},     // traverse point
    {"M",  ""},     // 2d: angle and distance ??? obs ???
    {"B",  "obs"},

    {".ORDER",""},  // [NE/EN] [AtFromTo/FromAtTo],
  };
};

}}     //namespace GNU_Gama::local
#endif // SNDAT2GKF_H
