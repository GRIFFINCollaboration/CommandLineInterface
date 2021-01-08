#include <iostream>

#include "CommandLineInterface.hh"

int main(int argc, char** argv) {
  bool myBool = false;
  char* myCharP = new char;
  std::string myString;
  std::vector<std::string> myStringVector;
  short myShort = 0;
  int myInt = 0;
  long long myLongLong = 0;
  uint8_t myUint8 = 0;
  uint16_t myUint16 = 0;
  uint32_t myUint32 = 0;
  uint64_t myUint64 = 0;

  CommandLineInterface interface;

  interface.Add("pure comment");
  interface.Add("-f1",  "comment  1", &myBool);
  interface.Add("-f2",  "comment  2", &myCharP);
  interface.Add("-f3",  "comment  3", &myString);
  interface.Add("-f4",  "comment  4", &myShort);
  interface.Add("-f5",  "comment  5", &myInt);
  interface.Add("-f6",  "comment  6", &myLongLong);
  interface.Add("-f7",  "comment  7", &myUint8);
  interface.Add("-f8",  "comment  8", &myUint16);
  interface.Add("-f9",  "comment  9", &myUint32);
  interface.Add("-f10", "comment 10", &myUint64);
  interface.Add("-f11", "comment 11", &myStringVector);

  //void Add(const char*, const char*, double*, double factor = 1.);
  //void Add(const char*, const char*, vector<char*>*);
  //void Add(const char*, const char*, vector<string>*);
  //void Add(const char*, const char*, vector<short>*);
  //void Add(const char*, const char*, vector<int>*);
  //void Add(const char*, const char*, vector<long long>*);
  //void Add(const char*, const char*, vector<uint8_t>*);
  //void Add(const char*, const char*, vector<uint16_t>*);
  //void Add(const char*, const char*, vector<uint32_t>*);
  //void Add(const char*, const char*, vector<uint64_t>*);
  ////void Add(const char*, const char*, vector<size_t>*);
  //void Add(const char*, const char*, vector<double>*, double factor = 1.);

  interface.CheckFlags(argc,argv);

  std::cout<<std::endl
			  <<"----------------------------------------"<<std::endl
           <<interface<<std::endl;

  return 0;
}
