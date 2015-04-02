#ifndef __COMMAND_LINE_INTERFACE
#define __COMMAND_LINE_INTERFACE

#include <stdint.h> //for uint* types
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <vector>

using namespace std;

class CommandLineInterface {
public:
  CommandLineInterface();
  ~CommandLineInterface(){};

  //main functions to check all flags from command line
  bool CheckFlags(int,char*[],const bool& Debug = false);

  //functions to add flags
  void Add(const char*);
  void Add(const char*, const char*, bool*);
  void Add(const char*, const char*, char**);
  void Add(const char*, const char*, string*);
  void Add(const char*, const char*, short*);
  void Add(const char*, const char*, int*);
  void Add(const char*, const char*, long long*);
  void Add(const char*, const char*, uint8_t*);
  void Add(const char*, const char*, uint16_t*);
  void Add(const char*, const char*, uint32_t*);
  void Add(const char*, const char*, uint64_t*);
  //void Add(const char*, const char*, size_t*);
  void Add(const char*, const char*, double*, double factor = 1.);
  void Add(const char*, const char*, vector<char*>*);
  void Add(const char*, const char*, vector<string>*);
  void Add(const char*, const char*, vector<short>*);
  void Add(const char*, const char*, vector<int>*);
  void Add(const char*, const char*, vector<long long>*);
  void Add(const char*, const char*, vector<uint8_t>*);
  void Add(const char*, const char*, vector<uint16_t>*);
  void Add(const char*, const char*, vector<uint32_t>*);
  void Add(const char*, const char*, vector<uint64_t>*);
  //void Add(const char*, const char*, vector<size_t>*);
  void Add(const char*, const char*, vector<double>*, double factor = 1.);

  friend ostream& operator <<(ostream &,const CommandLineInterface &);

private:
  bool FlagExists(const char*);

  int fMaximumFlagLength;
  vector<string> fFlags;
  vector<void*>  fValues;
  int fMaximumTypeLength;
  vector<string> fTypes;
  int fMaximumCommentLength;
  vector<string> fComments;
  vector<double> fFactors;
};

#endif
