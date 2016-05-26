#include "Utilities.hh"

//Indexes an array, i.e., outputs the array index such that array[index[j]] is
//in ascending order for j = 0, 1, . . . ,N-1. The input quantity array is not changed.
//returns the sorted array
TVectorD CreateIndex(TVectorD array, std::vector<size_t>& index) {
  size_t tempIndex;
  size_t lowerIndex;
  size_t upperIndex;
  size_t leftIndex = 0;
  size_t rightIndex = array.GetNoElements() - 1;
  size_t median;
  double temp;
  std::vector<size_t> stack(0);

  index.resize(array.GetNoElements());

  //initialise index to ascending numbers
  for(lowerIndex = 0; lowerIndex < (size_t) array.GetNoElements(); lowerIndex++) {
    index[lowerIndex] = lowerIndex;
  }

  //cout<<"initialised index"<<endl;

  while(true) {
    //for(size_t ind = 0; ind < array.GetNoElements(); ind++)
    //	{
    //	  cout<<setw(8)<<array[ind]<<" "<<setw(8)<<index[ind]<<" "<<setw(8)<<array[index[ind]]<<endl;
    //	}
    //cout<<endl;
    //if the remaining subarray is small enough do insertion sort
    if(rightIndex - leftIndex < MINIMUM_LENGTH) {
      for(lowerIndex = leftIndex + 1; lowerIndex <= rightIndex; lowerIndex++) {
	tempIndex = index[lowerIndex];
	temp = array[tempIndex];
	//upperIndex is unsigned => if it's zero the end (--) makes it very big!
	//so we do an extra check and break the loop if upperIndex get's zero
	for(upperIndex = lowerIndex-1; upperIndex >= leftIndex; upperIndex--) {
	  //cout<<"insertion: "<<leftIndex<<" - "<<rightIndex<<", "<<lowerIndex<<" - "<<upperIndex<<endl;
	  if(array[index[upperIndex]] <= temp) {
	    break;
	  }
	  index[upperIndex+1] = index[upperIndex];

	  if(upperIndex == 0) {
	    upperIndex--;
	    break;
	  }
	}
	index[upperIndex+1] = tempIndex;
	//for(size_t ind = 0; ind < array.GetNoElements(); ind++)
	//	{
	//	  cout<<setw(8)<<array[ind]<<" "<<setw(8)<<index[ind]<<" "<<setw(8)<<array[index[ind]]<<endl;
	//	}
	//cout<<endl;
      }
      if(stack.size() < 1) {
	break;
      }
      //pop stack and continue another round of partioning
      rightIndex = stack.back();
      stack.pop_back();
      leftIndex = stack.back();
      stack.pop_back();
      //for(size_t ind = 0; ind < array.GetNoElements(); ind++)
      //  {
      //    cout<<setw(8)<<array[ind]<<" "<<setw(8)<<index[ind]<<" "<<setw(8)<<array[index[ind]]<<endl;
      //  }
      //cout<<endl;
    } else {
      //choose median of left and right as partitioning element
      median = (leftIndex+rightIndex)/2;
      Swap(index[median],index[leftIndex+1]);
      //cout<<"median = "<<median<<endl;
      //rearrange so that a[l] <= a[l+1] <= a[r]
      if(array[index[leftIndex]] > array[index[rightIndex]]) {
	Swap(index[leftIndex],index[rightIndex]);
      }
      if(array[index[leftIndex+1]] > array[index[rightIndex]]) {
	Swap(index[leftIndex+1],index[rightIndex]);
      }
      if(array[index[leftIndex]] > array[index[leftIndex+1]]) {
	Swap(index[leftIndex],index[leftIndex+1]);
      }
      //initialize partitioning indices
      lowerIndex = leftIndex+1;
      upperIndex = rightIndex;
      tempIndex = index[leftIndex+1];
      //partitioning element
      temp = array[tempIndex];
      while(true) {
	//for(size_t ind = 0; ind < array.GetNoElements(); ind++)
	//	{
	//	  cout<<setw(8)<<array[ind]<<" "<<setw(8)<<index[ind]<<" "<<setw(8)<<array[index[ind]]<<endl;
	//	}
	//cout<<endl;
	//cout<<"1. "<<leftIndex<<" - "<<rightIndex<<", "<<lowerIndex<<" - "<<upperIndex<<endl;
	//scan up to find element >= partitioning element
	do lowerIndex++; while(array[index[lowerIndex]] < temp);
	//cout<<"2. "<<leftIndex<<" - "<<rightIndex<<", "<<lowerIndex<<" - "<<upperIndex<<endl;
	//scan down to find element <= partitioning element
	do upperIndex--; while(array[index[upperIndex]] > temp);
	//cout<<"3. "<<leftIndex<<" - "<<rightIndex<<", "<<lowerIndex<<" - "<<upperIndex<<endl;
	//pointers crossed => partitioning finished after swaping of elements
	if(upperIndex < lowerIndex) {
	  break;
	}
	Swap(index[lowerIndex],index[upperIndex]);
      }
      //for(size_t ind = 0; ind < array.GetNoElements(); ind++)
      //  {
      //    cout<<setw(8)<<array[ind]<<" "<<setw(8)<<index[ind]<<" "<<setw(8)<<array[index[ind]]<<endl;
      //  }
      //cout<<endl;
      //cout<<"4. "<<leftIndex<<" - "<<rightIndex<<", "<<lowerIndex<<" - "<<upperIndex<<endl;
      //insert the partitioning element
      index[leftIndex+1]=index[upperIndex];
      index[upperIndex]=tempIndex;
      //for(size_t ind = 0; ind < array.GetNoElements(); ind++)
      //  {
      //    cout<<setw(8)<<array[ind]<<" "<<setw(8)<<index[ind]<<" "<<setw(8)<<array[index[ind]]<<endl;
      //  }
      //cout<<endl;
      //put the indices of the larger subarray on the stack and process the other one directly
      //one array goes from left to upper index, the other from lower to right index
      if(rightIndex - lowerIndex + 1 >= upperIndex - leftIndex) {
	stack.push_back(lowerIndex);
	stack.push_back(rightIndex);
	rightIndex = upperIndex - 1;
      } else {
	stack.push_back(leftIndex);
	stack.push_back(upperIndex - 1);
	leftIndex = lowerIndex;
      }
    }//else of if(rightIndex - leftIndex < MINIMUM_LENGTH)
  }//while(true)

  TVectorD result(array.GetNoElements());

  for(int i = 0; i < array.GetNoElements(); i++) {
    result[i] = array[index[i]];
  }

  return result;
}

bool FileExists(std::string Filename) { 
  return FileExists(Filename.c_str()); 
}

bool FileExists(const char* Filename) { 
  //copied from techbytes.ca and added check if it's a directory
  struct stat FileInfo; 
  bool Return; 
  int Stat; 

  // Attempt to get the file attributes 
  Stat = stat(Filename,&FileInfo); 
  if(Stat == 0) { 
    // We were able to get the file attributes 
    // so the file obviously exists. 
    // But it might be a directory so check that with st_mode
    Return = !S_ISDIR(FileInfo.st_mode); 
  } else { 
    // We were not able to get the file attributes. 
    // This may mean that we don't have permission to 
    // access the folder which contains this file. If you 
    // need to do that level of checking, lookup the 
    // return values of stat which will give you 
    // more details on why stat failed. 
    Return = false; 
  }
  
  return Return; 
}

bool IsDirectory(std::string name) {
	return IsDirectory(name.c_str());
}

bool IsDirectory(const char* name) {
	struct stat info;
	int stats = stat(name,&info);
	if(stats == 0) {
		return S_ISDIR(info.st_mode);
	} else {
		return false;
	}
}

bool DirectoryExists(std::string directoryName) { 
  return DirectoryExists(directoryName.c_str()); 
}

bool DirectoryExists(const char* directoryName) { 
  //copied from techbytes.ca and added check if it's a directory
  struct stat DirectoryInfo; 
  int Stat; 

  // Attempt to get the file attributes 
  Stat = stat(directoryName,&DirectoryInfo); 
  if(Stat == 0) { 
    // We were able to get the file attributes 
    // so the file obviously exists. 
    // But it might be a directory so check that with st_mode
    return S_ISDIR(DirectoryInfo.st_mode); 
  } else { 
    // We were not able to get the file attributes. 
    // This may mean that we don't have permission to 
    // access the folder which contains this file. If you 
    // need to do that level of checking, lookup the 
    // return values of stat which will give you 
    // more details on why stat failed. 
    return false; 
  }
}

std::vector<std::string> GetFilesInDirectory(std::string name) {
	return GetFilesInDirectory(name.c_str());
}

std::vector<std::string> GetFilesInDirectory(const char* name) {
	std::vector<std::string> files;

	DIR* dir = opendir(name);
	struct dirent* ent;

	if(dir != NULL) {
		while((ent = readdir(dir)) != NULL) {
			if(strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
				continue;
			}
			files.push_back(name);
			files.back().append(ent->d_name);
		}
		closedir(dir);
	} else {
		//could not open directory
		std::cerr<<"Failed to open directory '"<<name<<"'!"<<std::endl;
	}

	return files;
}
