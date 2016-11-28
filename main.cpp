#include "biostream.hpp"
#include <iostream>
#include <bitset>
using namespace std;

ifstream fin("board.txt");
bostream bout("board.dat");

inline uint8_t conv(ifstream& in)
{
  int tmp;
  in >> tmp;

  return (tmp <= 255 ? static_cast<uint8_t>(tmp) : 0);
}

void dreams();
void jobs();
void stocks();

int main()
{
  bout << "ECA5#";

  dreams();
  jobs();
  stocks();

  bout.closeFile();

  return 0;
}

void dreams()
{
  size_t dcnt;

  fin >> dcnt;
  bout << dcnt;
  cout <<"Loading "<< dcnt <<" dreams\n";

  while(dcnt--)
  {
    long value;
    fin >> value;
    bout << value;
  }
}

void jobs()
{
  size_t jcnt;
  fin >> jcnt;
  bout << jcnt;
  cout << "Loading "<< jcnt << " jobs\n";

  while(jcnt--)
  {
    for(size_t i = 0; i < 13; ++i)
    {
      uint32_t value;
      fin >> value;
      bout << value;
    }
  }
}

void stocks()
{
  size_t scnt;
  fin >> scnt;
  bout << scnt;
  cout << "Loading "<< scnt << " stocks\n";

  while(scnt--)
  {
    uint8_t type = conv(fin);
    bout << type;

    int16_t price;
    size_t index;

    if(type == 0)
    {
      fin >> price;
      bout << price;
    }
    if(type == 1)
    {
      int16_t income;
      fin >> price >> income;
      bout << price << income;
    }
    if(type == 2)
    {
      uint8_t secondary = conv(fin);
      bout << secondary;
    }

    fin >> index;
    bout << index;
  }
}
