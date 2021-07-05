#include "text2xml.h"
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
  std::ifstream ifstr;
  if (argc > 1) {
      ifstr.open(argv[1]);
      // error handling ...
    }
  std::istream istr(argc > 1 ? ifstr.rdbuf() : std::cin.rdbuf());

  std::ofstream ofstr;
  if (argc == 3) {
      ofstr.open(argv[2]);
      // error handling ...
    }
  std::ostream ostr(argc == 3 ? ofstr.rdbuf() : std::cout.rdbuf());

  Text2xml grid2gkf(istr, ostr);
  grid2gkf.exec();

  return grid2gkf.status();
}
