#ifndef SNDAT2GKF_H
#define SNDAT2GKF_H

#include <istream>
#include <vector>
#include <list>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <cctype>

namespace GNU_gama { namespace local {

class Text2xml
{
public:
  Text2xml(std::istream&, std::ostream&);

  void exec();
  int  status() const;

  std::string version() const;

private:

  /**/ class Record
  /**/ {
  /**/ public:
  /**/   Record(std::string line, std::string desc=std::string());
  /**/
  /**/   std::string code() const;
  /**/   std::string data() const;
  /**/   std::string note() const;
  /**/
  /**/ private:
  /**/   std::string code_, data_, note_;
  /**/ };

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
  std::set<std::string> known_z_coordinates_;
  std::set<std::string> unknown_z_coordinates_;
  std::string zk_(std::string id) { known_z_coordinates_.insert(id); return id; }
  std::string zu_(std::string id) { unknown_z_coordinates_.insert(id); return id; }


  std::string cluster_;
  std::string from_;      // observation set (DB)
  std::list<std::string> traverse_points_;
  void close_cluster_if_opened();
  std::string string2lower(std::string);
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
  void write_record_L ();
  void write_record_E ();

  void process_ORDER();
  void process_NETDIM(int);
  struct GeneralOptions
  {
    // Coordinate Order ["ne", "en"] is set in gama_options.
    // Syntax .ORDER en is kept for backward compatibility.

    // Angle Data Station Order
    std::string angle_station_order {"at-from-to"};   // from-at-to

    // Two/three dimensional network mode (codes .2D / .3D)
    bool netdim2 {true};
    bool netdim3 {false};

  } general_options;

  void process_SET();
  struct GamaOptions
  {
    // <network />                           // ne sw es wn  for left-handed coordinate systems
    std::string axes_xy {"ne"};              // en nw se ws  for right-handed coordinate systems
    std::string angles  {"left-handed"};     // right-handed

    // <parameters />
    std::string sigma_apr {"10"};
    std::string conf_pr   {"0.95"};          // (0, 1)
    std::string tol_abs   {"1000"};
    std::string sigma_act {"aposteriori"};   // apriori

    // <points-observations />
    std::string distance_stdev     {"5.0"};  // "a b c" --> a + b*D^c, D in km
    std::string direction_stdev    {"10.0"};
    std::string angle_stdev        {"10.0"};
    std::string zenith_angle_stdev {"10.0"};
    std::string azimuth_stdev      {"10.0"};

  } gama_options;


  const std::unordered_map<std::string, std::string> codemap_
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
    {"L",  "height-differences"},
    {"E", ""},      // levelling point

    /* general options */

    {".2D", ""},    // network dimension can be switched anywhere inside input data
    {".3D", ""}
  };

};

}}     //namespace GNU_Gama::local
#endif // SNDAT2GKF_H
