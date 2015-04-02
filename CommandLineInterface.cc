#include "CommandLineInterface.hh"

using namespace std;

CommandLineInterface::CommandLineInterface() {
  fMaximumFlagLength = 0;
  fFlags.clear();
  fValues.clear();
  fMaximumTypeLength = 0;
  fTypes.clear();
  fMaximumCommentLength = 0;
  fComments.clear();
}

bool CommandLineInterface::CheckFlags(int argc, char* argv[], const bool& Debug) {
  int i,j;
  
  if(argc == 1) {
    for(i = 0; i < fFlags.size(); i++) {
      if(fTypes[i].empty())
	cout<<fComments[i]<<endl<<endl;
    }
    cout<<"use "<<argv[0]<<" with following flags:"<<endl;
    for(i = 0; i < fFlags.size(); i++) {
      if(fTypes[i] == "bool")
	cout<<"        ["<<setw(fMaximumFlagLength+fMaximumTypeLength)<<left<<fFlags[i]<<"   : "<<fComments[i]<<"]"<<endl;
      else if(!fTypes[i].empty())
	cout<<"        ["<<setw(fMaximumFlagLength)<<left<<fFlags[i]<<" <"<<setw(fMaximumTypeLength)<<left<<fTypes[i]<<">: "<<fComments[i]<<"]"<<endl;
    }
    
    return true;
  }

  for(i = 1; i < argc; i++) {
    for(j = 0; j < fFlags.size(); j++) {
      if(argv[i] == fFlags[j]) {
	//bool doesn't need any value to be read
	if(fTypes[j] == "bool") {
	  *((bool*) fValues[j]) = true;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(i+1 >= argc) {
	  //if not bool check whether there are more arguments (with values) coming
	  cerr<<"Error in CheckFlags, flag "<<fFlags[j]<<" needs additional arguments"<<endl;
	  return false;
	} else if(fTypes[j] == "char*") {
	  *((char**) fValues[j]) = argv[i+1];
	  i++;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "string") {
	  //set the string to the first following argument (these are split by whitespace)
	  *((string*) fValues[j]) = argv[i+1];
	  i+=2;
	  //as long as there are arguments left and no new flag is found (flags start with -) => add another value (with whitespace inbetween)
	  while(i < argc) {
	    if(argv[i][0] != '-') {
	      (*((string*)fValues[j])).append(" ");
	      (*((string*)fValues[j])).append(argv[i]);
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
	} else if(fTypes[j] == "uint8_t") {
	  *((uint8_t*) fValues[j]) = atoi(argv[i+1]);
	  i++;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "uint16_t") {
	  *((uint16_t*) fValues[j]) = atoi(argv[i+1]);
	  i++;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "uint32_t") {
	  *((uint32_t*) fValues[j]) = atoi(argv[i+1]);
	  i++;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "uint64_t") {
	  *((uint64_t*) fValues[j]) = atoi(argv[i+1]);
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
	} else if(fTypes[j] == "vector<char*>") {
	  i++;
	  //reset the vector
	  (*((vector<char*>*)fValues[j])).clear();
	  //as long as there are arguments left and no new flag is found (flags start with -) => read another value
	  while(i < argc) {
	    if(argv[i][0] != '-') {
	      (*((vector<char*>*)fValues[j])).push_back(argv[i]);
	      i++;
	    } else {
	      break;
	    }
	  }
	  
	  i--;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "vector<string>") {
	  i++;
	  //as long as there are arguments left and no new flag is found (flags start with -) => read another value
	  //reset the vector
	  (*((vector<string>*)fValues[j])).clear();
	  while(i < argc) {
	    if(argv[i][0] != '-') {
	      (*((vector<string>*)fValues[j])).push_back(argv[i]);
	      i++;
	    } else {
	      break;
	    }
	  }

	  i--;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "vector<short>") {
	  i++;
	  //reset the vector
	  (*((vector<short>*)fValues[j])).clear();
	  //as long as there are arguments left and no new flag is found (flags start with -, but so do negative numbers!) => read another value
	  while(i < argc) {
	    if(argv[i][0] != '-' || isdigit(argv[i][1])) {
	      (*((vector<short>*)fValues[j])).push_back(atoi(argv[i]));
	      i++;
	    } else {
	      break;
	    }
	  }

	  i--;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "vector<int>") {
	  i++;
	  //reset the vector
	  (*((vector<int>*)fValues[j])).clear();
	  //as long as there are arguments left and no new flag is found (flags start with -, but so do negative numbers!) => read another value
	  while(i < argc) {
	    if(argv[i][0] != '-' || isdigit(argv[i][1])) {
	      (*((vector<int>*)fValues[j])).push_back(atoi(argv[i]));
	      i++;
	    } else {
	      break;
	    }
	  }

	  i--;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "vector<long long>") {
	  i++;
	  //reset the vector
	  (*((vector<long long>*)fValues[j])).clear();
	  //as long as there are arguments left and no new flag is found (flags start with -, but so do negative numbers!) => read another value
	  while(i < argc) {
	    if(argv[i][0] != '-' || isdigit(argv[i][1])) {
	      (*((vector<long long>*)fValues[j])).push_back(atoi(argv[i]));
	      i++;
	    } else {
	      break;
	    }
	  }

	  i--;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "vector<uint8_t>") {
	  i++;
	  //reset the vector
	  (*((vector<uint8_t>*)fValues[j])).clear();
	  //as long as there are arguments left and no new flag is found (flags start with -, but so do negative numbers!) => read another value
	  while(i < argc) {
	    if(argv[i][0] != '-' || isdigit(argv[i][1])) {
	      (*((vector<uint8_t>*)fValues[j])).push_back(atoi(argv[i]));
	      i++;
	    } else {
	      break;
	    }
	  }

	  i--;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "vector<uint16_t>") {
	  i++;
	  //reset the vector
	  (*((vector<uint16_t>*)fValues[j])).clear();
	  //as long as there are arguments left and no new flag is found (flags start with -, but so do negative numbers!) => read another value
	  while(i < argc) {
	    if(argv[i][0] != '-' || isdigit(argv[i][1])) {
	      (*((vector<uint16_t>*)fValues[j])).push_back(atoi(argv[i]));
	      i++;
	    } else {
	      break;
	    }
	  }

	  i--;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "vector<uint32_t>") {
	  i++;
	  //reset the vector
	  (*((vector<uint32_t>*)fValues[j])).clear();
	  //as long as there are arguments left and no new flag is found (flags start with -, but so do negative numbers!) => read another value
	  while(i < argc) {
	    if(argv[i][0] != '-' || isdigit(argv[i][1])) {
	      (*((vector<uint32_t>*)fValues[j])).push_back(atoi(argv[i]));
	      i++;
	    } else {
	      break;
	    }
	  }

	  i--;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "vector<uint64_t>") {
	  i++;
	  //reset the vector
	  (*((vector<uint64_t>*)fValues[j])).clear();
	  //as long as there are arguments left and no new flag is found (flags start with -, but so do negative numbers!) => read another value
	  while(i < argc) {
	    if(argv[i][0] != '-' || isdigit(argv[i][1])) {
	      (*((vector<uint64_t>*)fValues[j])).push_back(atoi(argv[i]));
	      i++;
	    } else {
	      break;
	    }
	  }

	  i--;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "vector<size_t>") {
	  i++;
	  //reset the vector
	  (*((vector<size_t>*)fValues[j])).clear();
	  //as long as there are arguments left and no new flag is found (flags start with -) => read another value
	  while(i < argc) {
	    if(argv[i][0] != '-') {
	      (*((vector<size_t>*)fValues[j])).push_back(atoi(argv[i]));
	      i++;
	    } else {
	      break;
	    }
	  }

	  i--;
	  break;//found the right flag for this argument so the flag loop can be stopped
	} else if(fTypes[j] == "vector<double>") {
	  i++;
	  //reset the vector
	  (*((vector<double>*)fValues[j])).clear();
	  //as long as there are arguments left and no new flag is found (flags start with -, but so do negative numbers!) => read another value
	  while(i < argc) {
	    if(argv[i][0] != '-' || isdigit(argv[i][1])) {
	      (*((vector<double>*)fValues[j])).push_back(atof(argv[i])*fFactors[j]);
	      i++;
	    } else {
	      break;
	    }
	  }

	  i--;
	  break;//found the right flag for this argument so the flag loop can be stopped
	}
      }//if(argv[i] == flags[j])
    }//for(j = 0; j < flags.size(); j++)

    if(j == fFlags.size()) {
      //this means no matching flag was found
      cerr<<"flag "<<argv[i]<<" unknown"<<endl;
    } else if(Debug) {
      cout<<"found flag "<<i<<" = "<<argv[i]<<endl;
    }
  }//for(i = 1; i < argc; i++)

  if(Debug) {
    cout<<*this<<endl;
  }
  
  return true;
}

ostream& operator <<(ostream &os,const CommandLineInterface &obj) {
  os<<"command line flags are:"<<endl;
  for(int i = 0; i < obj.fValues.size(); i++) {
    if(obj.fTypes[i] == "bool") {
      cout<<obj.fFlags[i]<<": "<<*((bool*) obj.fValues[i])<<endl;
    } else if(obj.fTypes[i] == "char*") {
      cout<<obj.fFlags[i]<<": "<<*((char**) obj.fValues[i])<<endl;
    } else if(obj.fTypes[i] == "string") {
      cout<<obj.fFlags[i]<<": "<<*((string*) obj.fValues[i])<<endl;
    } else if(obj.fTypes[i] == "short") {
      cout<<obj.fFlags[i]<<": "<<*((short*) obj.fValues[i])<<endl;
    } else if(obj.fTypes[i] == "int") {
      cout<<obj.fFlags[i]<<": "<<*((int*) obj.fValues[i])<<endl;
    } else if(obj.fTypes[i] == "long long") {
      cout<<obj.fFlags[i]<<": "<<*((long*) obj.fValues[i])<<endl;
    } else if(obj.fTypes[i] == "uint8_t") {
      cout<<obj.fFlags[i]<<": "<<*((uint8_t*) obj.fValues[i])<<endl;
    } else if(obj.fTypes[i] == "uint16_t") {
      cout<<obj.fFlags[i]<<": "<<*((uint16_t*) obj.fValues[i])<<endl;
    } else if(obj.fTypes[i] == "uint32_t") {
      cout<<obj.fFlags[i]<<": "<<*((uint32_t*) obj.fValues[i])<<endl;
    } else if(obj.fTypes[i] == "uint64_t") {
      cout<<obj.fFlags[i]<<": "<<*((uint64_t*) obj.fValues[i])<<endl;
    } else if(obj.fTypes[i] == "double") {
      cout<<obj.fFlags[i]<<": "<<*((double*) obj.fValues[i])<<endl;
    } else if(obj.fTypes[i] == "vector<char*>") {
      cout<<obj.fFlags[i]<<": ";
      for(size_t j = 0; j < ((vector<char*>*) obj.fValues[i])->size(); j++)
	{
	  cout<<(*((vector<char*>*) obj.fValues[i]))[j]<<" ";
	}
      cout<<endl;
    } else if(obj.fTypes[i] == "vector<string>") {
      cout<<obj.fFlags[i]<<": ";
      for(size_t j = 0; j < ((vector<string>*) obj.fValues[i])->size(); j++)
	{
	  cout<<(*((vector<string>*) obj.fValues[i]))[j]<<" ";
	}
      cout<<endl;
    } else if(obj.fTypes[i] == "vector<short>") {
      cout<<obj.fFlags[i]<<": ";
      for(size_t j = 0; j < ((vector<short>*) obj.fValues[i])->size(); j++)
	{
	  cout<<(*((vector<short>*) obj.fValues[i]))[j]<<" ";
	}
      cout<<endl;
    } else if(obj.fTypes[i] == "vector<int>") {
      cout<<obj.fFlags[i]<<": ";
      for(size_t j = 0; j < ((vector<int>*) obj.fValues[i])->size(); j++)
	{
	  cout<<(*((vector<int>*) obj.fValues[i]))[j]<<" ";
	}
      cout<<endl;
    } else if(obj.fTypes[i] == "vector<long long>") {
      cout<<obj.fFlags[i]<<": ";
      for(size_t j = 0; j < ((vector<long long>*) obj.fValues[i])->size(); j++)
	{
	  cout<<(*((vector<long long>*) obj.fValues[i]))[j]<<" ";
	}
      cout<<endl;
    } else if(obj.fTypes[i] == "vector<uint8_t>") {
      cout<<obj.fFlags[i]<<": ";
      for(size_t j = 0; j < ((vector<uint8_t>*) obj.fValues[i])->size(); j++)
	{
	  cout<<(*((vector<uint8_t>*) obj.fValues[i]))[j]<<" ";
	}
      cout<<endl;
    } else if(obj.fTypes[i] == "vector<uint16_t>") {
      cout<<obj.fFlags[i]<<": ";
      for(size_t j = 0; j < ((vector<uint16_t>*) obj.fValues[i])->size(); j++)
	{
	  cout<<(*((vector<uint16_t>*) obj.fValues[i]))[j]<<" ";
	}
      cout<<endl;
    } else if(obj.fTypes[i] == "vector<uint32_t>") {
      cout<<obj.fFlags[i]<<": ";
      for(size_t j = 0; j < ((vector<uint32_t>*) obj.fValues[i])->size(); j++)
	{
	  cout<<(*((vector<uint32_t>*) obj.fValues[i]))[j]<<" ";
	}
      cout<<endl;
    } else if(obj.fTypes[i] == "vector<uint64_t>") {
      cout<<obj.fFlags[i]<<": ";
      for(size_t j = 0; j < ((vector<uint64_t>*) obj.fValues[i])->size(); j++)
	{
	  cout<<(*((vector<uint64_t>*) obj.fValues[i]))[j]<<" ";
	}
      cout<<endl;
    } else if(obj.fTypes[i] == "vector<size_t>") {
      cout<<obj.fFlags[i]<<": ";
      for(size_t j = 0; j < ((vector<size_t>*) obj.fValues[i])->size(); j++)
	{
	  cout<<(*((vector<size_t>*) obj.fValues[i]))[j]<<" ";
	}
      cout<<endl;
    } else if(obj.fTypes[i] == "vector<double>") {
      cout<<obj.fFlags[i]<<": ";
      for(size_t j = 0; j < ((vector<double>*) obj.fValues[i])->size(); j++)
	{
	  cout<<(*((vector<double>*) obj.fValues[i]))[j]<<" ";
	}
      cout<<endl;
    }
  }

  return os;
}

bool CommandLineInterface::FlagExists(const char* flag) {
  //check if this flag already exists
  for(size_t i = 0; i < fFlags.size(); i++) {
    if(flag == fFlags[i]) {
      cerr<<"Error, flag "<<flag<<" exists already as flag number "<<i<<" (from zero)"<<endl;
      return true;
    }
  }
  return false;
}

void CommandLineInterface::Add(const char* comment) {
  fFlags.push_back(string());
  fValues.push_back((void*) NULL);
  fTypes.push_back(string());
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(string(comment));
  fFactors.push_back(1.);
}

void CommandLineInterface::Add(const char* flag, const char* comment, bool* value) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(string(flag));
  fValues.push_back((void*) value);
  if(strlen("bool") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("bool");
  fTypes.push_back(string("bool"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(string(comment));
  fFactors.push_back(1.);
}

void CommandLineInterface::Add(const char* flag, const char* comment, char** value) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(string(flag));
  fValues.push_back((void*) value);
  if(strlen("char*") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("char*");
  fTypes.push_back(string("char*"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(string(comment));
  fFactors.push_back(1.);
}

void CommandLineInterface::Add(const char* flag, const char* comment, string* value) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(string(flag));
  fValues.push_back((void*) value);
  if(strlen("string") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("string");
  fTypes.push_back(string("string"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(string(comment));
  fFactors.push_back(1.);
}

void CommandLineInterface::Add(const char* flag, const char* comment, short* value) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(string(flag));
  fValues.push_back((void*) value);
  if(strlen("short") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("short");
  fTypes.push_back(string("short"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(string(comment));
  fFactors.push_back(1.);
}

void CommandLineInterface::Add(const char* flag, const char* comment, int* value) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(string(flag));
  fValues.push_back((void*) value);
  if(strlen("int") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("int");
  fTypes.push_back(string("int"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(string(comment));
  fFactors.push_back(1.);
}

void CommandLineInterface::Add(const char* flag, const char* comment, long long* value) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(string(flag));
  fValues.push_back((void*) value);
  if(strlen("long long") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("long long");
  fTypes.push_back(string("long long"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(string(comment));
  fFactors.push_back(1.);
}

void CommandLineInterface::Add(const char* flag, const char* comment, uint8_t* value) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(string(flag));
  fValues.push_back((void*) value);
  if(strlen("uint8_t") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("uint8_t");
  fTypes.push_back(string("uint8_t"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(string(comment));
  fFactors.push_back(1.);
}

void CommandLineInterface::Add(const char* flag, const char* comment, uint16_t* value) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(string(flag));
  fValues.push_back((void*) value);
  if(strlen("uint16_t") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("uint16_t");
  fTypes.push_back(string("uint16_t"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(string(comment));
  fFactors.push_back(1.);
}

void CommandLineInterface::Add(const char* flag, const char* comment, uint32_t* value) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(string(flag));
  fValues.push_back((void*) value);
  if(strlen("uint32_t") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("uint32_t");
  fTypes.push_back(string("uint32_t"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(string(comment));
  fFactors.push_back(1.);
}

void CommandLineInterface::Add(const char* flag, const char* comment, uint64_t* value) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(string(flag));
  fValues.push_back((void*) value);
  if(strlen("uint64_t") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("uint64_t");
  fTypes.push_back(string("uint64_t"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(string(comment));
  fFactors.push_back(1.);
}

//void CommandLineInterface::Add(const char* flag, const char* comment, size_t* value) {
//  if(FlagExists(flag))
//    return;
//  if(strlen(flag) > fMaximumFlagLength)
//    fMaximumFlagLength = strlen(flag);
//  fFlags.push_back(string(flag));
//  fValues.push_back((void*) value);
//  if(strlen("int") > fMaximumTypeLength)
//    fMaximumTypeLength = strlen("size_t");
//  fTypes.push_back(string("size_t"));
//  if(strlen(comment) > fMaximumCommentLength)
//    fMaximumCommentLength = strlen(comment);
//  fComments.push_back(string(comment));
//  fFactors.push_back(1.);
//}

void CommandLineInterface::Add(const char* flag, const char* comment, double* value, double factor) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(string(flag));
  fValues.push_back((void*) value);
  if(strlen("double") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("double");
  fTypes.push_back(string("double"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(string(comment));
  fFactors.push_back(factor);
}

void CommandLineInterface::Add(const char* flag, const char* comment, vector<char*>* value) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(string(flag));
  fValues.push_back((void*) value);
  if(strlen("vector<char*>") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("vector<char*>");
  fTypes.push_back(string("vector<char*>"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(string(comment));
  fFactors.push_back(1.);
}

void CommandLineInterface::Add(const char* flag, const char* comment, vector<string>* value) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(string(flag));
  fValues.push_back((void*) value);
  if(strlen("vector<string>") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("vector<string>");
  fTypes.push_back(string("vector<string>"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(string(comment));
  fFactors.push_back(1.);
}

void CommandLineInterface::Add(const char* flag, const char* comment, vector<short>* value) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(string(flag));
  fValues.push_back((void*) value);
  if(strlen("vector<short>") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("vector<short>");
  fTypes.push_back(string("vector<short>"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(string(comment));
  fFactors.push_back(1.);
}

void CommandLineInterface::Add(const char* flag, const char* comment, vector<int>* value) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(string(flag));
  fValues.push_back((void*) value);
  if(strlen("vector<int>") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("vector<int>");
  fTypes.push_back(string("vector<int>"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(string(comment));
  fFactors.push_back(1.);
}

void CommandLineInterface::Add(const char* flag, const char* comment, vector<long long>* value) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(string(flag));
  fValues.push_back((void*) value);
  if(strlen("vector<long long>") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("vector<long long>");
  fTypes.push_back(string("vector<long long>"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(string(comment));
  fFactors.push_back(1.);
}

void CommandLineInterface::Add(const char* flag, const char* comment, vector<uint8_t>* value) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(string(flag));
  fValues.push_back((void*) value);
  if(strlen("vector<uint8_t>") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("vector<uint8_t>");
  fTypes.push_back(string("vector<uint8_t>"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(string(comment));
  fFactors.push_back(1.);
}

void CommandLineInterface::Add(const char* flag, const char* comment, vector<uint16_t>* value) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(string(flag));
  fValues.push_back((void*) value);
  if(strlen("vector<uint16_t>") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("vector<uint16_t>");
  fTypes.push_back(string("vector<uint16_t>"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(string(comment));
  fFactors.push_back(1.);
}

void CommandLineInterface::Add(const char* flag, const char* comment, vector<uint32_t>* value) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(string(flag));
  fValues.push_back((void*) value);
  if(strlen("vector<uint32_t>") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("vector<uint32_t>");
  fTypes.push_back(string("vector<uint32_t>"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(string(comment));
  fFactors.push_back(1.);
}

void CommandLineInterface::Add(const char* flag, const char* comment, vector<uint64_t>* value) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(string(flag));
  fValues.push_back((void*) value);
  if(strlen("vector<uint64_t>") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("vector<uint64_t>");
  fTypes.push_back(string("vector<uint64_t>"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(string(comment));
  fFactors.push_back(1.);
}

//void CommandLineInterface::Add(const char* flag, const char* comment, vector<size_t>* value) {
//  if(FlagExists(flag))
//    return;
//  if(strlen(flag) > fMaximumFlagLength)
//    fMaximumFlagLength = strlen(flag);
//  fFlags.push_back(string(flag));
//  fValues.push_back((void*) value);
//  if(strlen("vector<size_t>") > fMaximumTypeLength)
//    fMaximumTypeLength = strlen("vector<size_t>");
//  fTypes.push_back(string("vector<size_t>"));
//  if(strlen(comment) > fMaximumCommentLength)
//    fMaximumCommentLength = strlen(comment);
//  fComments.push_back(string(comment));
//  fFactors.push_back(1.);
//}

void CommandLineInterface::Add(const char* flag, const char* comment, vector<double>* value, double factor) {
  if(FlagExists(flag))
    return;
  if(strlen(flag) > fMaximumFlagLength)
    fMaximumFlagLength = strlen(flag);
  fFlags.push_back(string(flag));
  fValues.push_back((void*) value);
  if(strlen("vector<double>") > fMaximumTypeLength)
    fMaximumTypeLength = strlen("vector<double>");
  fTypes.push_back(string("vector<double>"));
  if(strlen(comment) > fMaximumCommentLength)
    fMaximumCommentLength = strlen(comment);
  fComments.push_back(string(comment));
  fFactors.push_back(factor);
}
