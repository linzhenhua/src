// string::substr
#include <iostream>
#include <string>

int main ()
{
  std::string str="We think in generalities, but we live in details.";

  std::string str2 = str.substr (100,1);
  std::cout << "111"  << std::endl;
  std::cout << "str2: " << str2 << std::endl;

  return 0;
}
