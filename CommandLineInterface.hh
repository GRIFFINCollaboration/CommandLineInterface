#ifndef __COMMAND_LINE_INTERFACE
#define __COMMAND_LINE_INTERFACE

#include <stdint.h> //for uint* types
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <vector>

class CommandLineInterface {
public:
  CommandLineInterface();
  ~CommandLineInterface(){};

  //main functions to check all flags from command line
  bool CheckFlags(int, char**, const bool& Debug = false);

  //functions to add flags
  void Add(const char*);
  void Add(const char*, const char*, bool*);
  void Add(const char*, const char*, char**);
  void Add(const char*, const char*, std::string*);
  void Add(const char*, const char*, short*);
  void Add(const char*, const char*, int*);
  void Add(const char*, const char*, long long*);
  void Add(const char*, const char*, uint8_t*);
  void Add(const char*, const char*, uint16_t*);
  void Add(const char*, const char*, uint32_t*);
  void Add(const char*, const char*, uint64_t*);
  //void Add(const char*, const char*, size_t*);
  void Add(const char*, const char*, double*, double factor = 1.);
  void Add(const char*, const char*, std::vector<char*>*);
  void Add(const char*, const char*, std::vector<std::string>*);
  void Add(const char*, const char*, std::vector<short>*);
  void Add(const char*, const char*, std::vector<int>*);
  void Add(const char*, const char*, std::vector<long long>*);
  void Add(const char*, const char*, std::vector<uint8_t>*);
  void Add(const char*, const char*, std::vector<uint16_t>*);
  void Add(const char*, const char*, std::vector<uint32_t>*);
  void Add(const char*, const char*, std::vector<uint64_t>*);
  //void Add(const char*, const char*, std::vector<size_t>*);
  void Add(const char*, const char*, std::vector<double>*, double factor = 1.);

  friend std::ostream& operator <<(std::ostream &,const CommandLineInterface &);

private:
  bool FlagExists(const char*);

  size_t fMaximumFlagLength;
  std::vector<std::string> fFlags;
  std::vector<void*>  fValues;
  size_t fMaximumTypeLength;
  std::vector<std::string> fTypes;
  size_t fMaximumCommentLength;
  std::vector<std::string> fComments;
  std::vector<double> fFactors;
};

#endif
