/**
*** This is a set of wrapper classes providing binary input/output in the same way that std::iostream does.
*** The unions are proof of concept, but the classes itself are useful if you want to simplify (un)serialization.
**/

#pragma once
/** STL **/
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

/***************
*** bistream ***
***************/

class bistream
{
public:
  bistream(std::istream& s) : input(s), file(nullptr) {}
  bistream(std::string f) : input(openFile(f)) {}
  bistream(const bistream&) = delete;
  ~bistream() {closeFile();}

  bistream& operator=(const bistream&) = delete;

  template<typename T>
  T get() // read any aggregate or basic type
  {
    static constexpr size_t len = sizeof(T); // length of the array
    union // easy type converting
    {
      T val;
      char str[len];
    };

    input.read(str, len); // read characters
    return val; // convert
  }

  void closeFile();
  size_t size();

protected:
  std::istream& input; // the stream to read
  std::ifstream* file; // file pointer

  std::ifstream& openFile(std::string);
};

/***************
*** bostream ***
***************/

class bostream
{
public:
  bostream(std::ostream& s) : output(s), file(nullptr) {}
  bostream(std::string f) : output(openFile(f)) {}
  bostream(const bostream&) = delete;
  ~bostream() {closeFile();}

  bostream& operator=(const bostream&) = delete;

  template<typename T>
  void put(T w) // write any aggregate or basic type
  {
    static constexpr size_t len = sizeof(T); // length of the array
    union // easy type converting
    {
      T val;
      char str[len];
    };

    val = w; // assign value
    output.write(str, len); // write converted characters
  }

  template<typename T>
  void put(std::vector<T>& v)
  {
    put<size_t>(v.size());
    for(T x : v)
      put(x);
  }

  template<typename T, typename U>
  void put(std::map<T, U>& m)
  {
    put<size_t>(m.size());
    for(auto it = m.begin(); it != m.end(); ++it)
    {
      put(it->first);
      put(it->second);
    }
  }

  void closeFile();
  size_t size();

protected:
  std::ostream& output; // the stream to write
  std::ofstream* file; // file pointer

  std::ofstream& openFile(std::string); // create file
};

/*******************************
********* bistream::get ********
*** Template specializations ***
*******************************/

template<>
std::string bistream::get<std::string>()
{
  std::string ret;
  std::getline(input, ret, '\0');
  return ret;
}

template<>
char* bistream::get<char*>()
{
  size_t pos = input.tellg(); // keep current position
  while(input.get() != '\0'); // find delimiter
  size_t after = input.tellg(); // position after the loop

  size_t len = after - pos; // count string length
  char* ret = new char[len]; // create returned string
  ret[len - 1] = '\0'; // null-terminate

  input.seekg(pos, input.beg); // go back to previous position
  input.getline(ret, len, '\0'); // read string
  return ret;
}

template<>
const char* bistream::get<const char*>()
{
  return get<char*>();
}

template<typename T>
bistream& operator>>(bistream& r, T& v)
{
  v = r.get<T>();
  return r;
}

template<typename T>
bistream& operator>>(bistream& r, std::vector<T>& v)
{
  size_t len = r.get<size_t>();
  v.resize(len);
  for(T& x : v)
    r >> x;
  return r;
}

template<typename T, typename U>
bistream& operator>>(bistream& r, std::map<T, U>& m)
{
  size_t len = r.get<size_t>();
  for(size_t i = 0; i < len; ++i)
  {
    T k;
    U v;
    r >> k >> v;
    m[k] = v;
  }
  return r;
}

/*******************************
********* bostream::put ********
*** Template specializations ***
*******************************/

template<>
void bostream::put<std::string>(std::string str)
{
  std::string tmp = str + '\0';
  output.write(tmp.c_str(), tmp.size());
}

template<>
void bostream::put<const char*>(const char* str)
{
  size_t len = 0;
  while(str[len++] != '\0'); // count string length
  output.write(str, len);
}

template<>
void bostream::put<char*>(char* str)
{
  put<const char*>(str);
}

template<typename T>
bostream& operator<<(bostream& o, T v)
{
  o.put(v);
  return o;
}

/***********************
*** Member functions ***
***********************/

void bistream::closeFile()
{
  if(!file) return; // no file? nothing to do

  file->close();
  delete file;
  file = nullptr; // prevent segfaults
}

size_t bistream::size()
{
  size_t pos = input.tellg(); // keep current position
  input.seekg(input.beg, input.end); // go to the end of stream
  size_t ret = input.tellg(); // get stream length
  input.seekg(pos, input.beg); // go back to previous position

  return ret;
}

std::ifstream& bistream::openFile(std::string filename)
{
  file = new std::ifstream(filename.c_str(), std::ios::binary);
  return *file;
}

void bostream::closeFile()
{
  if(!file) return; // no file? nothing to do

  file->close();
  delete file;
  file = nullptr; // prevent segfaults
}

size_t bostream::size()
{
  size_t pos = output.tellp(); // keep current position
  output.seekp(output.beg, output.end); // go to the end of stream
  size_t ret = output.tellp(); // get stream length
  output.seekp(pos, output.beg); // go back to the kept position

  return ret;
}

std::ofstream& bostream::openFile(std::string filename) // create file
{
  file = new std::ofstream(filename.c_str(), std::ios::binary);
  return *file;
}
