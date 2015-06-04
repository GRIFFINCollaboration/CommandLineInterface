#ifndef UNCERTAINTY_HH
#define UNCERTAINTY_HH

#include <iostream>
#include <iomanip>

template <class T>
class Uncertainty
{
public:
  Uncertainty(T, T, Format);
  ~Uncertainty();

  SetFormat(Format format)
  {
    fFormat = format;
  }

  friend ostream& operator <<(ostream &,const Uncertainty<T> &);

protected:
  enum Format
    {
      PlusMinus,
      Brackets
    };

  T fExactValue;
  T fExactUncertainty;
  T fRoundedValue;
  T fRoundedUncertainty;
  Format fFormat;
  int fFixedPrecision;
  int fScientificValuePrecision;
  int fScientificUncertaintyPrecision;
};

//format of the error should be:
//if the first digit is a one => precision of two
//otherwise => precision of one
//and errors should always be rounded up
//            fixed                                                                               scientific (always only one digit before the period)
//error < 20  simply set precision to abs(floor(log(error))) (+1 if first digit is one)           precision of error is always 0 or 1 (if first digit is 1)
//error >= 2  report all digits up to the dot (precision 0), with everything rounded accordingly  precision of value is the same plus floor(log(value)) - floor(log(error))
//
//first digit can be found by dividing the error by 10^(floor of the log(error)) and taking the floor of the result
template <class T>
Uncertainty::Uncertainty(T value, T uncertainty, Format format = PlusMinus)
  : fExactValue(value), fExactUncertainty(uncertainty), fFormat(format)
{
  int firstDigit = (int) fExactUncertainty/pow(10.,floor(log10(fExactUncertainty)));
  if(fExactUncertainty < (T) 20.)
    {
      fFixedPrecision = abs(floor(log10(fExactUncertainty)));
      if(firstDigit == 1)
	{
	  fFixedPrecision++;
	}
    }
  else
    {
      fFixedPrecision = 0;
    }
  fScientificUncertaintyPrecision = 0;
  if(firstDigit == 1)
    {
      fScientificUncertaintyPrecision++;
    }

  fScientificValuePrecision = fScientificUncertaintyPrecision;
  fScientificValuePrecision += floor(log10(fExactValue)) - floor(log10(fExactUncertainty));

  //if the error is equal to 10^(floor of log(error)) we need no rounding
  //otherwise the error should always be rounded up, so we set the error to (firstDigit plus one)*10^(floor of the log(error))
  if(fExactUncertainty == firstDigit*pow(10.,floor(log10(fExactUncertainty))))
    {
      fRoundedUncertainty = fExactUncertainty;
    }
  else
    {
      fRoundedUncertainty = ;
    }

}

template <class T>
ostream& operator <<(ostream &os, const Uncertainty<T> &obj)
{
  //fixed output format was set
  if((cout.flags() & ios_base::fixed) == ios_base::fixed)
    {
      os<<setprecision(fFixedPrecision);
      if(fFormat == PlusMinus)
	{
	  os<<tmpValue<<" +- "<<tmpUncertainty;
	}
      else if(fFormat == Brackets)
	{
	  os<<tmpValue<<"("<<tmpUncertainty<<")";
	}
    }
  else if((cout.flags() & ios_base::scientific) == ios_base::scientific)
    {
      if(fFormat == PlusMinus)
	{
	  os<<setprecision(fScientificValuePrecision)<<tmpValue<<" +- "<<setprecision(fScientificUncertaintyPrecision)<<tmpUncertainty;
	}
      else if(fFormat == Brackets)
	{
	  os<<setprecision(fScientificValuePrecision)<<tmpValue<<"("<<setprecision(fScientificUncertaintyPrecision)<<tmpUncertainty<<")";
	}
    }
  
  return os;
}
#endif
