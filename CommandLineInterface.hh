#ifndef __COMMAND_LINE_INTERFACE
#define __COMMAND_LINE_INTERFACE

#include <stdint.h> //for uint* types
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <typeinfo>
#include <cxxabi.h>

class CommandLineInterface {
public:
  CommandLineInterface();
  ~CommandLineInterface(){};

  //main functions to check all flags from command line
  bool CheckFlags(int,char*[],const bool& Debug = false);

  void Help(char*);

  //functions to add flags
  void Add(const char*);
  template<typename T>
  void Add(const char*, const char*, T*);
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

template<typename T>
void CommandLineInterface::Add(const char* flag, const char* comment, T* value) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(std::string(flag));
  fValues.push_back((void*) value);
  int status;
  char* type = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
  if(strlen(type) > fMaximumTypeLength)
    fMaximumTypeLength = strlen(type);
  fTypes.push_back(std::string(type));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(std::string(comment));
  fFactors.push_back(1.);
  free(type);
}

#endif
