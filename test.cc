#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
  int i1 = 112;
  int i2 = 1200;

  double d1 = 0.00231385;
  double d2 = 12312351.;
  double d3 = 1.234e9;

  cout<<"fixed = "<<ios_base::fixed<<", scientific = "<<ios_base::scientific<<endl
      <<"internal = "<<ios_base::internal<<", left = "<<ios_base::left<<", right = "<<ios_base::right<<endl
      <<"dec = "<<ios_base::dec<<", hex = "<<ios_base::hex<<", oct = "<<ios_base::oct<<endl
      <<"boolalpha = "<<ios_base::boolalpha<<", showbase = "<<ios_base::showbase<<", showpoint = "<<ios_base::showpoint<<", showpos = "<<ios_base::showpos<<", skipws = "<<ios_base::skipws<<", unitbuf = "<<ios_base::unitbuf<<", uppercase = "<<ios_base::uppercase<<endl;
  
  cout<<"normal = "<<cout.flags()<<endl;
  cout<<"prec. "<<cout.precision()<<":\t"<<i1<<" "<<i2<<" "<<d1<<" "<<d2<<" "<<d3<<endl;

  cout<<setprecision(5);
  cout<<"prec. "<<cout.precision()<<":\t"<<i1<<" "<<i2<<" "<<d1<<" "<<d2<<" "<<d3<<endl;

  cout<<setprecision(2);
  cout<<"prec. "<<cout.precision()<<":\t"<<i1<<" "<<i2<<" "<<d1<<" "<<d2<<" "<<d3<<endl;

  cout<<setprecision(-2);
  cout<<"prec. "<<cout.precision()<<":\t"<<i1<<" "<<i2<<" "<<d1<<" "<<d2<<" "<<d3<<endl;

  cout<<fixed;
  cout<<"fixed = "<<cout.flags()<<endl;
  cout<<setprecision(5);
  cout<<"prec. "<<cout.precision()<<":\t"<<i1<<" "<<i2<<" "<<d1<<" "<<d2<<" "<<d3<<endl;

  cout<<setprecision(2);
  cout<<"prec. "<<cout.precision()<<":\t"<<i1<<" "<<i2<<" "<<d1<<" "<<d2<<" "<<d3<<endl;

  cout<<setprecision(-2);
  cout<<"prec. "<<cout.precision()<<":\t"<<i1<<" "<<i2<<" "<<d1<<" "<<d2<<" "<<d3<<endl;

  cout<<scientific;
  cout<<"scientific = "<<cout.flags()<<endl;
  cout<<setprecision(5);
  cout<<"prec. "<<cout.precision()<<":\t"<<i1<<" "<<i2<<" "<<d1<<" "<<d2<<" "<<d3<<endl;

  cout<<setprecision(2);
  cout<<"prec. "<<cout.precision()<<":\t"<<i1<<" "<<i2<<" "<<d1<<" "<<d2<<" "<<d3<<endl;

  cout<<setprecision(-2);
  cout<<"prec. "<<cout.precision()<<":\t"<<i1<<" "<<i2<<" "<<d1<<" "<<d2<<" "<<d3<<endl;

  return 0;
}
//results:
//normal:	112 1200 0.00231385 1.23124e+07 1.234e+09
//prec. 5:	112 1200 0.0023139 1.2312e+07 1.234e+09
//prec. 2:	112 1200 0.0023 1.2e+07 1.2e+09
//fixed
//prec. 5:	112 1200 0.00231 12312351.00000 1234000000.00000
//prec. 2:	112 1200 0.00 12312351.00 1234000000.00
//scientific
//prec. 5:	112 1200 2.31385e-03 1.23124e+07 1.23400e+09
//prec. 2:	112 1200 2.31e-03 1.23e+07 1.23e+09
