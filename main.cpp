#include "grid2gkf.h"
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

  Snd2gkf sndfk2gkf(istr, ostr);
  sndfk2gkf.exec();

  return 0;
}
