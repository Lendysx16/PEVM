#include <iostream>
#include <string>

int main ()
{
  int arr[] = { 1, 4, 5, 9, 10, 40, 50, 90, 100, 400, 500, 900, 1000 };
  std::string bukv[] =
  {"I", "IV", "V", "IX", "X", "XL", "L", "XC", "C", "CD", "D", "CM", "M"};
  int N = -1;
  do{
  std::cout<<"Enter positive number: ";
  std::cin >> N;} while(N < 1);
  int largest_base = 12;
  while (N > 0)
    {
      int delitel = N / arr[largest_base];
      N = N % arr[largest_base];
      while (delitel--)
	{
	  std::cout << bukv[largest_base];
	}
      largest_base--;
    }
}
