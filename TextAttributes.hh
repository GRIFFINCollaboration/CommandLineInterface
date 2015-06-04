#ifndef __COLORS_HH
#define __COLORS_HH

#include <ostream>

namespace Attribs {
  inline std::string Reset() { 
    std::string s("\033[0m");
    return s;
  }
  inline std::ostream& Reset(std::ostream& s) { 
      s<<Reset();
    return s;
  }
  inline std::string Bold() { 
    std::string s("\033[1m");
    return s;
  }
  inline std::ostream& Bold(std::ostream& s) { 
    s<<"\033[1m";
    return s;
  }
  inline std::string Bright() { 
    std::string s("\033[1m");
    return s;
  }
  inline std::ostream& Bright(std::ostream& s) { 
    s<<"\033[1m";
    return s;
  }
  inline std::string Underline() { 
    std::string s("\033[4m");
    return s;
  }
  inline std::ostream& Underline(std::ostream& s) { 
    s<<"\033[4m";
    return s;
  }
}

namespace Foreground {
  inline std::string Black() { 
    std::string s("\033[30m");
    return s;
  }
  inline std::ostream& Black(std::ostream& s) { 
    s<<"\033[30m";
    return s;
  }
  inline std::string Red() { 
    std::string s("\033[31m");
    return s;
  }
  inline std::ostream& Red(std::ostream& s) { 
    s<<"\033[31m";
    return s;
  }
  inline std::string Green() { 
    std::string s("\033[32m");
    return s;
  }
  inline std::ostream& Green(std::ostream& s) { 
    s<<"\033[32m";
    return s;
  }
  inline std::string Yellow() { 
    std::string s("\033[33m");
    return s;
  }
  inline std::ostream& Yellow(std::ostream& s) { 
    s<<"\033[33m";
    return s;
  }
  inline std::string Blue() { 
    std::string s("\033[34m");
    return s;
  }
  inline std::ostream& Blue(std::ostream& s) { 
    s<<"\033[34m";
    return s;
  }
  inline std::string Magenta() { 
    std::string s("\033[35m");
    return s;
  }
  inline std::ostream& Magenta(std::ostream& s) { 
    s<<"\033[35m";
    return s;
  }
  inline std::string Cyan() { 
    std::string s("\033[36m");
    return s;
  }
  inline std::ostream& Cyan(std::ostream& s) { 
    s<<"\033[36m";
    return s;
  }
  inline std::string White() { 
    std::string s("\033[37m");
    return s;
  }
  inline std::ostream& White(std::ostream& s) { 
    s<<"\033[37m";
    return s;
  }
  inline std::string Default() { 
    std::string s("\033[39m");
    return s;
  }
  inline std::ostream& Default(std::ostream& s) { 
    s<<"\033[39m";
    return s;
  }
}

namespace Background {
  inline std::string Black() { 
    std::string s("\033[40m");
    return s;
  }
  inline std::ostream& Black(std::ostream& s) { 
    s<<"\033[40m";
    return s;
  }
  inline std::string Red() { 
    std::string s("\033[41m");
    return s;
  }
  inline std::ostream& Red(std::ostream& s) { 
    s<<"\033[41m";
    return s;
  }
  inline std::string Green() { 
    std::string s("\033[42m");
    return s;
  }
  inline std::ostream& Green(std::ostream& s) { 
    s<<"\033[42m";
    return s;
  }
  inline std::string Yellow() { 
    std::string s("\033[43m");
    return s;
  }
  inline std::ostream& Yellow(std::ostream& s) { 
    s<<"\033[43m";
    return s;
  }
  inline std::string Blue() { 
    std::string s("\033[44m");
    return s;
  }
  inline std::ostream& Blue(std::ostream& s) { 
    s<<"\033[44m";
    return s;
  }
  inline std::string Magenta() { 
    std::string s("\033[45m");
    return s;
  }
  inline std::ostream& Magenta(std::ostream& s) { 
    s<<"\033[45m";
    return s;
  }
  inline std::string Cyan() { 
    std::string s("\033[46m");
    return s;
  }
  inline std::ostream& Cyan(std::ostream& s) { 
    s<<"\033[46m";
    return s;
  }
  inline std::string White() { 
    std::string s("\033[47m");
    return s;
  }
  inline std::ostream& White(std::ostream& s) { 
    s<<"\033[47m";
    return s;
  }
  inline std::string Default() { 
    std::string s("\033[49m");
    return s;
  }
  inline std::ostream& Default(std::ostream& s) { 
    s<<"\033[49m";
    return s;
  }
}
#endif
