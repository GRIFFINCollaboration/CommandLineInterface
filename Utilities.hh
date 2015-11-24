#ifndef UTILITIES_HH
#define UTILITIES_HH

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <sys/stat.h> 
#include <limits>
#include <dirent.h>

#include "TVectorT.h"

//-------------------- three function templates that print all arguments into a string
//last template uses existing stream and appends the last argument to it
template <typename T>
void Append(std::stringstream& stream, const T& tail) {
  //append last argument
  stream<<tail;
}

//first template uses existing stream and appends to it
template <typename T, typename... U>
void Append(std::stringstream& stream, const T& head, const U&... tail) {
  //append first argument
  stream<<head;

  //reversely call this template (or the third)
  Append(stream,tail...);
}

//this function typically gets called by user
template <typename T, typename... U>
std::string Show(const T& head, const U&... tail) {
  //print first arguments to string
  std::stringstream stream;
  stream<<head;

  //call the second template (or the third if tail is just one argument)
  Append(stream,tail...);
  return stream.str();
}

//quick sort from numerical recipes in c, adapted to c++
#define MINIMUM_LENGTH 7

template <class T>
void Swap(T& a, T& b) {
  T temp = a;
  a = b;
  b = temp;
}

TVectorD CreateIndex(TVectorD, std::vector<size_t>&);

bool FileExists(std::string);
bool FileExists(const char*);
bool DirectoryExists(std::string);
bool DirectoryExists(const char*);
bool IsDirectory(std::string);
bool IsDirectory(const char*);
std::vector<std::string> GetFilesInDirectory(std::string);
std::vector<std::string> GetFilesInDirectory(const char*);

template <typename T>
inline bool IsNan(T value) {
  return value != value;
}

template <typename T>
inline bool IsInfinite(T value) {
  return std::numeric_limits<T>::has_infinity &&
    value == std::numeric_limits<T>::infinity();
}

template <typename T>
inline bool IsPowerOfTwo (T x) {
  return ((x != 0) && ((x & (~x + 1)) == x));
}

//template <class T>
//std::string FormatNumber(T value, T error) {
//  //if the value and the error are zero we use precision 1
//  int precision = 1;
//
//  if(error < (T) 0) {
//      error = Abs(error);
//    }
//  //error < 1: get the precision as negative logarithm, divide by two to get two digits for numbers starting with 1
//  if(error < (T) 1) {
//      precision = ceil(-1.*log10(error/2));
//    } else {
//      precision = ???;
//    }
//
//  std::stringstream Stream;
//  Stream.precision(precision);
//  Stream<<value<<" +- "<<error;
//
//  return Stream.str();
//}

//Indexes an array, i.e., outputs the array index such that array[index[j]] is
//in ascending order for j = 0, 1, . . . ,N-1. The input quantity array is not changed.
//returns the sorted array
//template has to be defined in the header (or use the export feature)
template <class T>
std::vector<T> CreateIndex(std::vector<T> array, std::vector<size_t>& index) {
  size_t tempIndex;
  size_t lowerIndex;
  size_t upperIndex;
  size_t leftIndex = 0;
  size_t rightIndex = array.size() - 1;
  size_t median;
  T temp;
  std::vector<size_t> stack(0);

  index.resize(array.size());

  //initialise index to ascending numbers
  for(lowerIndex = 0; lowerIndex < array.size(); lowerIndex++) {
    index[lowerIndex] = lowerIndex;
  }

  //cout<<"initialised index"<<endl;

  while(true) {
    //for(size_t ind = 0; ind < array.size(); ind++)
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
	//for(size_t ind = 0; ind < array.size(); ind++)
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
      //for(size_t ind = 0; ind < array.size(); ind++)
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
	//for(size_t ind = 0; ind < array.size(); ind++)
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
      //for(size_t ind = 0; ind < array.size(); ind++)
      //  {
      //    cout<<setw(8)<<array[ind]<<" "<<setw(8)<<index[ind]<<" "<<setw(8)<<array[index[ind]]<<endl;
      //  }
      //cout<<endl;
      //cout<<"4. "<<leftIndex<<" - "<<rightIndex<<", "<<lowerIndex<<" - "<<upperIndex<<endl;
      //insert the partitioning element
      index[leftIndex+1]=index[upperIndex];
      index[upperIndex]=tempIndex;
      //for(size_t ind = 0; ind < array.size(); ind++)
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

  std::vector<T> result(array.size());

  for(size_t i = 0; i < array.size(); i++) {
    result[i] = array[index[i]];
  }

  return result;
}

//Indexes an array, i.e., outputs the array index such that array[index[j]] is
//in ascending order for j = 0, 1, . . . ,N-1. The input quantity array is not changed.
//returns the inverse index array (InverseIndexArray[IndexArray[i]] = i)
//template has to be defined in the header (or use the export feature)
template <class T>
std::vector<size_t> CreateInverseIndex(std::vector<T> array, std::vector<size_t>& index) {
  size_t tempIndex;
  size_t lowerIndex;
  size_t upperIndex;
  size_t leftIndex = 0;
  size_t rightIndex = array.size() - 1;
  size_t median;
  T temp;
  std::vector<size_t> stack(0);

  index.resize(array.size());

  //initialise index to ascending numbers
  for(lowerIndex = 0; lowerIndex < array.size(); lowerIndex++) {
    index[lowerIndex] = lowerIndex;
  }

  //cout<<"initialised index"<<endl;

  while(true) {
    //for(size_t ind = 0; ind < array.size(); ind++)
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
	//for(size_t ind = 0; ind < array.size(); ind++)
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
      //for(size_t ind = 0; ind < array.size(); ind++)
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
	//for(size_t ind = 0; ind < array.size(); ind++)
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
      //for(size_t ind = 0; ind < array.size(); ind++)
      //  {
      //    cout<<setw(8)<<array[ind]<<" "<<setw(8)<<index[ind]<<" "<<setw(8)<<array[index[ind]]<<endl;
      //  }
      //cout<<endl;
      //cout<<"4. "<<leftIndex<<" - "<<rightIndex<<", "<<lowerIndex<<" - "<<upperIndex<<endl;
      //insert the partitioning element
      index[leftIndex+1]=index[upperIndex];
      index[upperIndex]=tempIndex;
      //for(size_t ind = 0; ind < array.size(); ind++)
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

  std::vector<size_t> result(array.size());

  for(size_t i = 0; i < array.size(); i++) {
    result[index[i]] = i;
  }

  return result;
}

//create a vector of unique indexes, each giving the first instance of a value of class T in the given array
template <class T>
std::vector<size_t> UniqueIndexes(std::vector<T> array) {
  std::vector<size_t> result;

  if(array.size() == 0) {
    return result;
  }

  //since we always use the first instance, 0 is always used
  result.push_back(0);

  size_t i,j;

  //loop over all other members of the array
  for(i = 1; i < array.size(); ++i) {
    //loop over all existing indexes and check whether the current array object matches any of them
    for(j = 0; j < result.size(); ++j) {
      if(array[i] == array[result[j]]) {
	break;
      }
    }
    //if we didn't manage to find the object the loop finished normally and we need to add this index
    if(j == result.size()) {
      result.push_back(i);
    }
  }
   
  return result;
}

#endif
