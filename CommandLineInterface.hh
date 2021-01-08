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
	void Add(const char*); // add a pure comment (no flag)
	template<typename T>
		void Add(const char*, const char*, T*); // add a simple flag
	template<typename T>
		void Add(const char*, const char*, std::vector<T>*); // add a flag using a vector of variables
	void Add(const char*, const char*, double*, double factor = 1.);
	void Add(const char*, const char*, std::vector<double>*, double factor = 1.);

	friend std::ostream& operator <<(std::ostream &,const CommandLineInterface &);

private:
	bool FlagExists(const char*);

	// flags
	size_t fMaximumFlagLength;
	std::vector<std::string> fFlags;

	// values
	std::vector<void*>  fValues;

	// types
	size_t fMaximumTypeLength;
	std::vector<std::string> fTypes;

	// comments
	size_t fMaximumCommentLength;
	std::vector<std::string> fComments;

	// factors
	std::vector<double> fFactors;
};

template<typename T>
void CommandLineInterface::Add(const char* flag, const char* comment, T* value)
{
	// check if the flag already exists, otherwise add the new flag and value
	if(FlagExists(flag)) return;
	if(strlen(flag) > fMaximumFlagLength) fMaximumFlagLength = strlen(flag);
	fFlags.push_back(std::string(flag));
	fValues.push_back((void*) value);
	// demangle the type and add it to the type vector
	int status;
	char* type = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
	if(status != 0) {
		std::cerr<<__PRETTY_FUNCTION__<<": failed to demangle type '"<<typeid(T).name()<<"' status "<<status<<std::endl;
		return;
	}
	// make "std::string" more readable
	if(strcmp(type,"std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >") == 0) {
		if(11 > fMaximumTypeLength) {
			fMaximumTypeLength = 11;
		}
		fTypes.push_back(std::string("std::string"));
	} else {
		if(strlen(type) > fMaximumTypeLength) {
			fMaximumTypeLength = strlen(type);
		}
		fTypes.push_back(std::string(type));
	}
	// update comment length and add comment
	if(strlen(comment) > fMaximumCommentLength) {
		fMaximumCommentLength = strlen(comment);
	}
	fComments.push_back(std::string(comment));
	// not using any factors here (why? could just use default=1?)
	fFactors.push_back(1.);
	free(type);
}

template<typename T>
void CommandLineInterface::Add(const char* flag, const char* comment, std::vector<T>* value)
{
	// check if the flag already exists, otherwise add the new flag and value
	if(FlagExists(flag)) return;
	if(strlen(flag) > fMaximumFlagLength) fMaximumFlagLength = strlen(flag);
	fFlags.push_back(std::string(flag));
	fValues.push_back((void*) value);
	// demangle the type and add it to the type vector
	int status;
	char* type = abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
	if(status != 0) {
		std::cerr<<__PRETTY_FUNCTION__<<": failed to demangle type '"<<typeid(T).name()<<"' status "<<status<<std::endl;
		return;
	}
	// make "std::string" more readable
	if(strcmp(type,"std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >") == 0) {
		if(24 > fMaximumTypeLength) {
			fMaximumTypeLength = 24;
		}
		fTypes.push_back(std::string("std::vector<std::string>"));
	} else {
		if(strlen(type)+13 > fMaximumTypeLength) {
			fMaximumTypeLength = strlen(type)+13;
		}
		fTypes.push_back(std::string("std::vector<")+std::string(type)+std::string(">"));
	}
	// update comment length and add comment
	if(strlen(comment) > fMaximumCommentLength) {
		fMaximumCommentLength = strlen(comment);
	}
	fComments.push_back(std::string(comment));
	// not using any factors here (why? could just use default=1?)
	fFactors.push_back(1.);
	free(type);
}

#endif
