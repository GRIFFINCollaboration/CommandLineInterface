#include "CommandLineInterface.hh"

CommandLineInterface::CommandLineInterface() {
  fMaximumFlagLength = 0;
  fFlags.clear();
  fValues.clear();
  fMaximumTypeLength = 0;
  fTypes.clear();
  fMaximumCommentLength = 0;
  fComments.clear();
}

void CommandLineInterface::Help(char* programName) {
  size_t i;
  for(i = 0; i < fFlags.size(); ++i) {
    if(fTypes[i].empty())
      std::cout<<fComments[i]<<std::endl<<std::endl;
  }
  std::cout<<"use "<<programName<<" with following flags:"<<std::endl;
  for(i = 0; i < fFlags.size(); ++i) {
    if(fTypes[i] == "bool")
      std::cout<<"        ["<<std::setw(fMaximumFlagLength+fMaximumTypeLength)<<std::left<<fFlags[i]<<"   : "<<fComments[i]<<"]"<<std::endl;
    else if(!fTypes[i].empty())
      std::cout<<"        ["<<std::setw(fMaximumFlagLength)<<std::left<<fFlags[i]<<" <"<<std::setw(fMaximumTypeLength)<<std::left<<fTypes[i]<<">: "<<fComments[i]<<"]"<<std::endl;
  }
}

bool CommandLineInterface::CheckFlags(int argc, char* argv[], const bool& Debug) {
  int i,j;
  
  if(argc == 1) {
    Help(argv[0]);
    return true;
  }

  for(i = 1; i < argc; i++) {
    for(j = 0; j < (int) fFlags.size(); j++) {
      if(argv[i] == fFlags[j]) {
	//bool doesn't need any value to be read
	if(fTypes[j] == "bool") {
	  *((bool*) fValues[j]) = true;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(i+1 >= argc) {
	  //if not bool check whether there are more arguments (with values) coming
	  std::cerr<<"Error in CheckFlags, flag "<<fFlags[j]<<" needs additional arguments"<<std::endl;
	  return false;
	} else if(fTypes[j] == "char*") {
	  *((char**) fValues[j]) = argv[i+1];
	  i++;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >") {
	  //set the string to the first following argument (these are split by whitespace)
	  *((std::string*) fValues[j]) = argv[i+1];
	  i+=2;
	  //as long as there are arguments left and no new flag is found (flags start with -) => add another value (with whitespace inbetween)
	  while(i < argc) {
	    if(argv[i][0] != '-') {
	      (*((std::string*)fValues[j])).append(" ");
	      (*((std::string*)fValues[j])).append(argv[i]);
	      i++;
	    } else {
	      break;
	    }
	  }
	  
	  i--;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "short") {
	  *((short*) fValues[j]) = atoi(argv[i+1]);
	  i++;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "int") {
	  *((int*) fValues[j]) = atoi(argv[i+1]);
	  i++;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "long long") {
	  *((long long*) fValues[j]) = atoi(argv[i+1]);
	  i++;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "unsigned char") {
	  *((unsigned char*) fValues[j]) = atoi(argv[i+1]);
	  i++;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "unsigned short") {
	  *((unsigned short*) fValues[j]) = atoi(argv[i+1]);
	  i++;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "unsigned int") {
	  *((unsigned int*) fValues[j]) = atoi(argv[i+1]);
	  i++;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "unsigned long") {
	  *((unsigned long*) fValues[j]) = atoi(argv[i+1]);
	  i++;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "size_t") {
	  *((size_t*) fValues[j]) = atoi(argv[i+1]);
	  i++;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "double") {
	  *((double*) fValues[j]) = atof(argv[i+1])*fFactors[j];
	  i++;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "std::vector<char*>") {
	  i++;
	  //reset the std::vector
	  (*((std::vector<char*>*)fValues[j])).clear();
	  //as long as there are arguments left and no new flag is found (flags start with -) => read another value
	  while(i < argc) {
	    if(argv[i][0] != '-') {
	      (*((std::vector<char*>*)fValues[j])).push_back(argv[i]);
	      i++;
	    } else {
	      break;
	    }
	  }
	  
	  i--;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "std::vector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >>") {
	  i++;
	  //as long as there are arguments left and no new flag is found (flags start with -) => read another value
	  //reset the std::vector
	  (*((std::vector<std::string>*)fValues[j])).clear();
	  while(i < argc) {
	    if(argv[i][0] != '-') {
	      (*((std::vector<std::string>*)fValues[j])).push_back(argv[i]);
	      i++;
	    } else {
	      break;
	    }
	  }

	  i--;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "std::vector<short>") {
	  i++;
	  //reset the std::vector
	  (*((std::vector<short>*)fValues[j])).clear();
	  //as long as there are arguments left and no new flag is found (flags start with -, but so do negative numbers!) => read another value
	  while(i < argc) {
	    if(argv[i][0] != '-' || isdigit(argv[i][1])) {
	      (*((std::vector<short>*)fValues[j])).push_back(atoi(argv[i]));
	      i++;
	    } else {
	      break;
	    }
	  }

	  i--;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "std::vector<int>") {
	  i++;
	  //reset the std::vector
	  (*((std::vector<int>*)fValues[j])).clear();
	  //as long as there are arguments left and no new flag is found (flags start with -, but so do negative numbers!) => read another value
	  while(i < argc) {
	    if(argv[i][0] != '-' || isdigit(argv[i][1])) {
	      (*((std::vector<int>*)fValues[j])).push_back(atoi(argv[i]));
	      i++;
	    } else {
	      break;
	    }
	  }

	  i--;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "std::vector<long long>") {
	  i++;
	  //reset the std::vector
	  (*((std::vector<long long>*)fValues[j])).clear();
	  //as long as there are arguments left and no new flag is found (flags start with -, but so do negative numbers!) => read another value
	  while(i < argc) {
	    if(argv[i][0] != '-' || isdigit(argv[i][1])) {
	      (*((std::vector<long long>*)fValues[j])).push_back(atoi(argv[i]));
	      i++;
	    } else {
	      break;
	    }
	  }

	  i--;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "std::vector<uint8_t>") {
	  i++;
	  //reset the std::vector
	  (*((std::vector<uint8_t>*)fValues[j])).clear();
	  //as long as there are arguments left and no new flag is found (flags start with -, but so do negative numbers!) => read another value
	  while(i < argc) {
	    if(argv[i][0] != '-' || isdigit(argv[i][1])) {
	      (*((std::vector<uint8_t>*)fValues[j])).push_back(atoi(argv[i]));
	      i++;
	    } else {
	      break;
	    }
	  }

	  i--;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "std::vector<uint16_t>") {
	  i++;
	  //reset the std::vector
	  (*((std::vector<uint16_t>*)fValues[j])).clear();
	  //as long as there are arguments left and no new flag is found (flags start with -, but so do negative numbers!) => read another value
	  while(i < argc) {
	    if(argv[i][0] != '-' || isdigit(argv[i][1])) {
	      (*((std::vector<uint16_t>*)fValues[j])).push_back(atoi(argv[i]));
	      i++;
	    } else {
	      break;
	    }
	  }

	  i--;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "std::vector<uint32_t>") {
	  i++;
	  //reset the std::vector
	  (*((std::vector<uint32_t>*)fValues[j])).clear();
	  //as long as there are arguments left and no new flag is found (flags start with -, but so do negative numbers!) => read another value
	  while(i < argc) {
	    if(argv[i][0] != '-' || isdigit(argv[i][1])) {
	      (*((std::vector<uint32_t>*)fValues[j])).push_back(atoi(argv[i]));
	      i++;
	    } else {
	      break;
	    }
	  }

	  i--;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "std::vector<uint64_t>") {
	  i++;
	  //reset the std::vector
	  (*((std::vector<uint64_t>*)fValues[j])).clear();
	  //as long as there are arguments left and no new flag is found (flags start with -, but so do negative numbers!) => read another value
	  while(i < argc) {
	    if(argv[i][0] != '-' || isdigit(argv[i][1])) {
	      (*((std::vector<uint64_t>*)fValues[j])).push_back(atoi(argv[i]));
	      i++;
	    } else {
	      break;
	    }
	  }

	  i--;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "std::vector<size_t>") {
	  i++;
	  //reset the std::vector
	  (*((std::vector<size_t>*)fValues[j])).clear();
	  //as long as there are arguments left and no new flag is found (flags start with -) => read another value
	  while(i < argc) {
	    if(argv[i][0] != '-') {
	      (*((std::vector<size_t>*)fValues[j])).push_back(atoi(argv[i]));
	      i++;
	    } else {
	      break;
	    }
	  }

	  i--;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "std::vector<double>") {
	  i++;
	  //reset the std::vector
	  (*((std::vector<double>*)fValues[j])).clear();
	  //as long as there are arguments left and no new flag is found (flags start with -, but so do negative numbers!) => read another value
	  while(i < argc) {
	    if(argv[i][0] != '-' || isdigit(argv[i][1])) {
	      (*((std::vector<double>*)fValues[j])).push_back(atof(argv[i])*fFactors[j]);
	      i++;
	    } else {
	      break;
	    }
	  }

	  i--;
	  break;//found the right flag for this argument so the flag loop can be stopped
	}
      }//if(argv[i] == flags[j])
    }//for(j = 0; j < (int) flags.size(); j++)

    if(j == (int) fFlags.size()) {
      //this means no matching flag was found
      std::cerr<<"flag "<<argv[i]<<" unknown"<<std::endl;
      if(Debug) {
	Help(argv[0]);
      }
    } else if(Debug) {
      std::cout<<"found flag "<<i<<" = "<<argv[i]<<std::endl;
    }
  }//for(i = 1; i < argc; i++)

  if(Debug) {
    std::cout<<*this<<std::endl;
  }
  
  return true;
}

std::ostream& operator <<(std::ostream &os,const CommandLineInterface &obj) {
  os<<"command line flags are:"<<std::endl;
  for(size_t i = 0; i < obj.fValues.size(); i++) {
    if(obj.fTypes[i].empty()) {
      continue;
    } else if(obj.fTypes[i] == "bool") {
      std::cout<<obj.fFlags[i]<<": "<<*((bool*) obj.fValues[i])<<std::endl;
    } else if(obj.fTypes[i] == "char*") {
      std::cout<<obj.fFlags[i]<<": '"<<*((char**) obj.fValues[i])<<"'"<<std::endl;
    } else if(obj.fTypes[i] == "std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >") {
      std::cout<<obj.fFlags[i]<<": '"<<*((std::string*) obj.fValues[i])<<"'"<<std::endl;
    } else if(obj.fTypes[i] == "short") {
      std::cout<<obj.fFlags[i]<<": "<<*((short*) obj.fValues[i])<<std::endl;
    } else if(obj.fTypes[i] == "int") {
      std::cout<<obj.fFlags[i]<<": "<<*((int*) obj.fValues[i])<<std::endl;
    } else if(obj.fTypes[i] == "long long") {
      std::cout<<obj.fFlags[i]<<": "<<*((long*) obj.fValues[i])<<std::endl;
    } else if(obj.fTypes[i] == "unsigned char") {
      std::cout<<obj.fFlags[i]<<": "<<static_cast<int>(*((unsigned char*) obj.fValues[i]))<<std::endl;
    } else if(obj.fTypes[i] == "unsigned short") {
      std::cout<<obj.fFlags[i]<<": "<<*((unsigned short*) obj.fValues[i])<<std::endl;
    } else if(obj.fTypes[i] == "unsigned int") {
      std::cout<<obj.fFlags[i]<<": "<<*((unsigned int*) obj.fValues[i])<<std::endl;
    } else if(obj.fTypes[i] == "unsigned long") {
      std::cout<<obj.fFlags[i]<<": "<<*((unsigned long*) obj.fValues[i])<<std::endl;
    } else if(obj.fTypes[i] == "double") {
      std::cout<<obj.fFlags[i]<<": "<<*((double*) obj.fValues[i])<<std::endl;
    } else if(obj.fTypes[i] == "std::vector<char*>") {
      std::cout<<obj.fFlags[i]<<": ";
      for(size_t j = 0; j < ((std::vector<char*>*) obj.fValues[i])->size(); j++)
	{
	  std::cout<<"'"<<(*((std::vector<char*>*) obj.fValues[i]))[j]<<"' ";
	}
      std::cout<<std::endl;
    } else if(obj.fTypes[i] == "std::vector<std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >>") {
      std::cout<<obj.fFlags[i]<<": ";
      for(size_t j = 0; j < ((std::vector<std::string>*) obj.fValues[i])->size(); j++)
	{
	  std::cout<<"'"<<(*((std::vector<std::string>*) obj.fValues[i]))[j]<<"' ";
	}
      std::cout<<std::endl;
    } else if(obj.fTypes[i] == "std::vector<short>") {
      std::cout<<obj.fFlags[i]<<": ";
      for(size_t j = 0; j < ((std::vector<short>*) obj.fValues[i])->size(); j++)
	{
	  std::cout<<(*((std::vector<short>*) obj.fValues[i]))[j]<<" ";
	}
      std::cout<<std::endl;
    } else if(obj.fTypes[i] == "std::vector<int>") {
      std::cout<<obj.fFlags[i]<<": ";
      for(size_t j = 0; j < ((std::vector<int>*) obj.fValues[i])->size(); j++)
	{
	  std::cout<<(*((std::vector<int>*) obj.fValues[i]))[j]<<" ";
	}
      std::cout<<std::endl;
    } else if(obj.fTypes[i] == "std::vector<long long>") {
      std::cout<<obj.fFlags[i]<<": ";
      for(size_t j = 0; j < ((std::vector<long long>*) obj.fValues[i])->size(); j++)
	{
	  std::cout<<(*((std::vector<long long>*) obj.fValues[i]))[j]<<" ";
	}
      std::cout<<std::endl;
    } else if(obj.fTypes[i] == "std::vector<uint8_t>") {
      std::cout<<obj.fFlags[i]<<": ";
      for(size_t j = 0; j < ((std::vector<uint8_t>*) obj.fValues[i])->size(); j++)
	{
	  std::cout<<(*((std::vector<uint8_t>*) obj.fValues[i]))[j]<<" ";
	}
      std::cout<<std::endl;
    } else if(obj.fTypes[i] == "std::vector<uint16_t>") {
      std::cout<<obj.fFlags[i]<<": ";
      for(size_t j = 0; j < ((std::vector<uint16_t>*) obj.fValues[i])->size(); j++)
	{
	  std::cout<<(*((std::vector<uint16_t>*) obj.fValues[i]))[j]<<" ";
	}
      std::cout<<std::endl;
    } else if(obj.fTypes[i] == "std::vector<uint32_t>") {
      std::cout<<obj.fFlags[i]<<": ";
      for(size_t j = 0; j < ((std::vector<uint32_t>*) obj.fValues[i])->size(); j++)
	{
	  std::cout<<(*((std::vector<uint32_t>*) obj.fValues[i]))[j]<<" ";
	}
      std::cout<<std::endl;
    } else if(obj.fTypes[i] == "std::vector<uint64_t>") {
      std::cout<<obj.fFlags[i]<<": ";
      for(size_t j = 0; j < ((std::vector<uint64_t>*) obj.fValues[i])->size(); j++)
	{
	  std::cout<<(*((std::vector<uint64_t>*) obj.fValues[i]))[j]<<" ";
	}
      std::cout<<std::endl;
    } else if(obj.fTypes[i] == "std::vector<size_t>") {
      std::cout<<obj.fFlags[i]<<": ";
      for(size_t j = 0; j < ((std::vector<size_t>*) obj.fValues[i])->size(); j++)
	{
	  std::cout<<(*((std::vector<size_t>*) obj.fValues[i]))[j]<<" ";
	}
      std::cout<<std::endl;
    } else if(obj.fTypes[i] == "std::vector<double>") {
      std::cout<<obj.fFlags[i]<<": ";
      for(size_t j = 0; j < ((std::vector<double>*) obj.fValues[i])->size(); j++)
	{
	  std::cout<<(*((std::vector<double>*) obj.fValues[i]))[j]<<" ";
	}
      std::cout<<std::endl;
    } else {
      std::cout<<obj.fFlags[i]<<": unknown data type '"<<obj.fTypes[i]<<"'"<<std::endl;
    }
  }

  return os;
}

bool CommandLineInterface::FlagExists(const char* flag) {
  //check if this flag already exists
  for(size_t i = 0; i < fFlags.size(); i++) {
    if(flag == fFlags[i]) {
      std::cerr<<"Error, flag "<<flag<<" exists already as flag number "<<i<<" (from zero)"<<std::endl;
      return true;
    }
  }
  return false;
}

void CommandLineInterface::Add(const char* comment) {
  fFlags.push_back(std::string());
  fValues.push_back((void*) NULL);
  fTypes.push_back(std::string());
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(std::string(comment));
  fFactors.push_back(1.);
}

void CommandLineInterface::Add(const char* flag, const char* comment, double* value, double factor) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(std::string(flag));
  fValues.push_back((void*) value);
  if(strlen("double") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("double");
  fTypes.push_back(std::string("double"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(std::string(comment));
  fFactors.push_back(factor);
}

void CommandLineInterface::Add(const char* flag, const char* comment, std::vector<char*>* value) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(std::string(flag));
  fValues.push_back((void*) value);
  if(strlen("std::vector<char*>") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("std::vector<char*>");
  fTypes.push_back(std::string("std::vector<char*>"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(std::string(comment));
  fFactors.push_back(1.);
}

void CommandLineInterface::Add(const char* flag, const char* comment, std::vector<std::string>* value) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(std::string(flag));
  fValues.push_back((void*) value);
  if(strlen("std::vector<std::string>") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("std::vector<std::string>");
  fTypes.push_back(std::string("std::vector<std::string>"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(std::string(comment));
  fFactors.push_back(1.);
}

void CommandLineInterface::Add(const char* flag, const char* comment, std::vector<short>* value) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(std::string(flag));
  fValues.push_back((void*) value);
  if(strlen("std::vector<short>") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("std::vector<short>");
  fTypes.push_back(std::string("std::vector<short>"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(std::string(comment));
  fFactors.push_back(1.);
}

void CommandLineInterface::Add(const char* flag, const char* comment, std::vector<int>* value) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(std::string(flag));
  fValues.push_back((void*) value);
  if(strlen("std::vector<int>") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("std::vector<int>");
  fTypes.push_back(std::string("std::vector<int>"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(std::string(comment));
  fFactors.push_back(1.);
}

void CommandLineInterface::Add(const char* flag, const char* comment, std::vector<long long>* value) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(std::string(flag));
  fValues.push_back((void*) value);
  if(strlen("std::vector<long long>") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("std::vector<long long>");
  fTypes.push_back(std::string("std::vector<long long>"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(std::string(comment));
  fFactors.push_back(1.);
}

void CommandLineInterface::Add(const char* flag, const char* comment, std::vector<uint8_t>* value) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(std::string(flag));
  fValues.push_back((void*) value);
  if(strlen("std::vector<uint8_t>") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("std::vector<uint8_t>");
  fTypes.push_back(std::string("std::vector<uint8_t>"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(std::string(comment));
  fFactors.push_back(1.);
}

void CommandLineInterface::Add(const char* flag, const char* comment, std::vector<uint16_t>* value) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(std::string(flag));
  fValues.push_back((void*) value);
  if(strlen("std::vector<uint16_t>") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("std::vector<uint16_t>");
  fTypes.push_back(std::string("std::vector<uint16_t>"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(std::string(comment));
  fFactors.push_back(1.);
}

void CommandLineInterface::Add(const char* flag, const char* comment, std::vector<uint32_t>* value) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(std::string(flag));
  fValues.push_back((void*) value);
  if(strlen("std::vector<uint32_t>") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("std::vector<uint32_t>");
  fTypes.push_back(std::string("std::vector<uint32_t>"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(std::string(comment));
  fFactors.push_back(1.);
}

void CommandLineInterface::Add(const char* flag, const char* comment, std::vector<uint64_t>* value) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(std::string(flag));
  fValues.push_back((void*) value);
  if(strlen("std::vector<uint64_t>") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("std::vector<uint64_t>");
  fTypes.push_back(std::string("std::vector<uint64_t>"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(std::string(comment));
  fFactors.push_back(1.);
}

//void CommandLineInterface::Add(const char* flag, const char* comment, std::vector<size_t>* value) {
//  if(FlagExists(flag))
//    return;
//  if(strlen(flag) > fMaximumFlagLength)
//    fMaximumFlagLength = strlen(flag);
//  fFlags.push_back(std::string(flag));
//  fValues.push_back((void*) value);
//  if(strlen("std::vector<size_t>") > fMaximumTypeLength)
//    fMaximumTypeLength = strlen("std::vector<size_t>");
//  fTypes.push_back(std::string("std::vector<size_t>"));
//  if(strlen(comment) > fMaximumCommentLength)
//    fMaximumCommentLength = strlen(comment);
//  fComments.push_back(std::string(comment));
//  fFactors.push_back(1.);
//}

void CommandLineInterface::Add(const char* flag, const char* comment, std::vector<double>* value, double factor) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(std::string(flag));
  fValues.push_back((void*) value);
  if(strlen("std::vector<double>") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("std::vector<double>");
  fTypes.push_back(std::string("std::vector<double>"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(std::string(comment));
  fFactors.push_back(factor);
}
