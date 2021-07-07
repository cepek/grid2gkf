#include "text2xml.h"

#include <string>
#include <iostream>
#include <sstream>

using namespace GNU_gama::local;

Text2xml::Text2xml(std::istream& inp, std::ostream& out)
  : inp_(inp), out_(out), status_(0)
{
  std::string s;
  while(std::getline(inp_, s))
    {
      // remove everything starting from hash (input data comment)
      auto hash = s.find('#');
      if (hash != std::string::npos) s.erase(hash);

      // remove everything starting from apostrophe (inline record description)
      auto apostrophe = s.find('\'');
      if (apostrophe != std::string::npos) s.erase(apostrophe);

      // check if some non-whitespace characters remained
      auto wsiter = std::find_if(s.begin(), s.end(),
                                 [](char c){return !std::iswspace(c);});
      if (wsiter != s.end())
        {
          Record rec(s);
          records_.push_back(rec);
        }
    }
}

void Text2xml::exec()
{
  gkf_begin();

  cluster_.clear();
  for (index_=0; index_<records_.size(); index_++)
    {
      const auto& rec = records_[index_];
      const auto& tag = rec.tag();
      auto iter = tagmap_.find(tag);
      if (iter == tagmap_.end())
        {
          error("undefined tag " + tag);
          continue;
        }

      std::string cluster_name = iter->second;

      if (cluster_name != cluster_)
        {
          if (!cluster_.empty()) out_ << "</" << cluster_ << ">\n";

          cluster_ = cluster_name;
          if (!cluster_.empty()) out_ << "\n<" << cluster_ << ">\n";
        }

      write_record();
    }

  gkf_end();
}

int Text2xml::status() const
{
  return status_;
}

std::string Text2xml::version() const
{
  return "0.03";
}


/********* private members  *********/

#ifdef Text2xml_debug
void Text2xml::print() const
{
  out_ << "<!--\n";

  for (int i=0; i<records_.size(); i++)
    {
      out_ << records_[i].tag() << " " << records_[i].code();
      auto note = records_[i].note();
      if (!note.empty()) out_ << " '" << records_[i].note();
      out_ << "\n";
    }

  out_ << "-->\n\n";
}
#endif

void Text2xml::error(std::string err)
{
  out_ << "<!-- error : " << err << " -->\n";
  status_++;
}

void Text2xml::gkf_begin()
{
  out_ << "<?xml version=\"1.0\" ?>\n"
       << "<gama-local xmlns=\"http://www.gnu.org/software/gama/gama-local\">\n"
       << "<network axes-xy=\"en\" angles=\"left-handed\">\n";

  out_ << "<!-- Generated by text2xml " + version() << " -->\n\n";

  out_ << "<parameters\n"
       << "   sigma-apr =\"5\"\n"
       << "   conf-pr=\"0.95\"\n"
       << "   tol-abs=\"1000\"\n"
       << "   sigma-act =\"aposteriori\"\n"
       << "/>\n\n";

  out_ << "<points-observations\n"
       << "   distance-stdev=\"5.0\"\n"
       << "   direction-stdev=\"10.0\"\n"
       << "   angle-stdev=\"10\"\n"
       << "   zenith-angle-stdev=\"10\"\n"
       << "   azimuth-stdev=\"10\">\n\n";
}

void  Text2xml::gkf_end()
{
  if (!cluster_.empty())
    {
      out_ << "</" << cluster_ << ">\n";
      cluster_.clear();
    }

  for (auto& key : known_coordinates_) unknown_coordinates_.erase(key);
  if (!unknown_coordinates_.empty()) out_ << "\n";
  for (auto& key : unknown_coordinates_)
    out_ << "<point id=\"" << key << "\" adj=\"xy\" />\n";

  out_ << "\n</points-observations>\n"
       << "</network>\n"
       << "</gama-local>\n";
}

void Text2xml::close_cluster_if_opened()
{
  if (!cluster_.empty())
    {
      out_ << "\n<" << cluster_ << ">\n";
      cluster_.clear();
    }
}

void Text2xml::separate_angle_ids(std::string triple,  // separated by 2 hyphens (-)
                                  std::string& from, std::string& bs, std::string& fs)
{
  std::istringstream istr(triple);
  std::getline(istr, from, '-');
  std::getline(istr, bs, '-');
  std::getline(istr, fs, '-');
}

void Text2xml::write_record()
{
  const auto& rec = records_[index_];
  const auto& tag = rec.tag();

  std::istringstream istr(rec.code());
  std::string s;
  words_.clear();
  while (istr >> s) words_.push_back(s);

  if      (tag == "C" ) write_record_C();
  else if (tag == "A" ) write_record_A();
  else if (tag == "D" ) write_record_D();
  else if (tag == "DB") write_record_DB();
  else if (tag == "DE") write_record_DE();
  else if (tag == "DM") write_record_DM();
  else if (tag == "TB") write_record_TB();
  else if (tag == "TE") write_record_TE();
  else if (tag == "T" ) write_record_T();
  else if (tag == "M" ) write_record_M();
  else if (tag == "B" ) write_record_B();
}

void Text2xml::write_record_C()
{
  auto n = words_.size();

  std::string xml_point, xml_xy, xml_type;
  if (n >= 1)
    {
      xml_point = "<point id='" + k_(words_[0]) + "' ";
      xml_type = "adj='xy' />";
    }
  if (n >= 3)
    {
      xml_xy = "x='" + words_[1] + "' y='" + words_[2] + "' ";
    }
  if (n > 4)
    {
      std::string iv = words_[3];
      if (iv[0] == '!') xml_type = "fix='xy' />";
      else              xml_type = "adj='xy' />";
    }

  out_ << xml_point << xml_xy << xml_type << "\n";
}

void Text2xml::write_record_A()
{
  auto n = words_.size();
  if (n != 2) return;

  std::string from, bs, fs;
  separate_angle_ids(words_[0], from, bs, fs);

  out_ << "<angle from='" << u_(from) << "' "
       << "bs='"  << u_(bs) << "' fs='" << u_(fs) << "' "
       << "val='" << words_[1] << "' />\n";
}

void Text2xml::write_record_D()
{
  auto n = words_.size();
  if (n != 2) return;

  std::string from, to;
  std::istringstream istr(words_[0]);
  std::getline(istr, from, '-');
  std::getline(istr, to, '-');

  out_ << "<distance from='" << u_(from) << "' "
       << "to='"  << u_(to) << "' "
       << "val='" << words_[1] << "' />\n";
}

void Text2xml::write_record_DB()
{
  auto n = words_.size();
  if (n != 1) return error("wrong usage of DB");

  close_cluster_if_opened();

  const auto& rec = records_[index_];
  from_ = rec.code();
  out_ << "\n<obs from='" << u_(from_) << "'>\n";
}

void Text2xml::write_record_DE()
{
  from_.clear();
  cluster_.clear();
  out_ << "</obs>\n";
}

void Text2xml::write_record_DN()
{

}

void Text2xml::write_record_DM()
{
  auto n = words_.size();
  if (n != 2 && n != 3) return error("wrong usage of DM");

  const Record& rec = records_[index_];
  std::istringstream istr(rec.code());
  std::string to, dir, dist;
  istr >> to >> dir >> dist;

  out_ << "<direction to='"  << u_(to) << "' val='" << dir  << "'/>\n";
  if (!dir.empty())
    out_ << "<distance to='" << u_(to) << "' val='" << dist << "'/>\n";
}

void Text2xml::write_record_TB()
{
  auto n = words_.size();
  if (n < 1) return error("wrong usage of TB");

  close_cluster_if_opened();

  traverse_points_.clear();

  auto ind = index_;
  do {
      const auto& rec = records_[ind];
      const auto& tag = rec.tag();
      if (tag == "TB" || tag == "T" || tag == "TE")
        {
          std::istringstream istr(rec.code());
          std::string id;
          istr >> id;
          traverse_points_.push_back(id);
        }
      if (rec.tag() == "TE") break;
    }
  while(++ind < records_.size());

  out_ << "\n<obs>\n";
}

void Text2xml::write_record_TE()
{
  cluster_.clear();
  traverse_points_.clear();
  out_ << "</obs>\n";
}

void Text2xml::write_record_T()
{
  auto n = words_.size();
  if (n != 3) return error("wrong usage of T");

  auto bs = traverse_points_.begin();
  auto at = bs; at++;
  auto fs = at; fs++;

  out_ << "<angle bs=\"" << u_(*bs) << "\" from=\"" << u_(*at) << "\" fs=\"" << u_(*fs) << "\" "
       << "val=\"" << words_[1] << "\" />\n";
  out_ << "<distance from=\"" << u_(*at) << "\" to=\"" << u_(*fs) << "\" "
       << "val=\"" << words_[2] << "\" />\n";

  traverse_points_.pop_front();
}

void Text2xml::write_record_M()
{
  auto n = words_.size();
  if (n != 3) return error("wrong usage of M");

  std::string from, bs, fs;
  separate_angle_ids(words_[0], from, bs, fs);

  out_ << "<angle from='" << u_(from) << "' "
       << "bs='"  << u_(bs) << "' fs='" << u_(fs) << "' "
       << "val='" << words_[1] << "' />\n";
  out_ << "<distance from='" << u_(from) << "' "
       << "to='"  << u_(fs) << "' "
       << "val='" << words_[2] << "' />\n";
}

void Text2xml::write_record_B()
{
  auto n = words_.size();
  if (n < 2 || n >3) return error("wrong usage of B");

}
