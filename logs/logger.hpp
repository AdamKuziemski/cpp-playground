#pragma once

/** STL **/
#include <fstream>
#include <string>
#include <map>

class LogEvent
{
protected:
  std::string prefix = "";
  int color = 0x000000;

  std::string content;

public:
  LogEvent(std::string content) : content(content) {}
  LogEvent(std::string prefix, int color, std::string content) : prefix(prefix), color(color), content(content) {}

  std::string getPrefix() {return prefix;}
  int getColor() {return color;}
  std::string getContent() {return content;}
};

/*************
*** Logger ***
*************/

class Logger
{
  std::string filename;
  std::ofstream file;

  std::string adjustColor(int);
  std::string timestamp();

public:
  Logger();
  ~Logger() {close();}

  void operator()(LogEvent e) {addEvent(e);}
  void operator()(std::string s) {addEvent(s);}
  void operator()(std::string s, int i) {variable(s, i);}
  void operator()(std::string s, double d) {variable(s, d);}
  void operator()(std::string s, bool b) {variable(s, b);}

  void addEvent(LogEvent);
  void addEvent(std::string s) {addEvent(LogEvent(s));}

  void variable(std::string s, int i) {addEvent("[VARIABLE] " + s + " = " + std::to_string(i));}
  void variable(std::string s, double d) {addEvent("[VARIABLE] " + s + " = " + std::to_string(d));}
  void variable(std::string s, bool b) {addEvent("[VARIABLE] " + s + " is " + (b ? "true" : "false"));}
  void error(std::string content) {addEvent(LogEvent("[ERROR] ", 0xD6280D, content));}
  void info(std::string content) {addEvent(LogEvent("[INFO] ", 0x1C77ED, content));}
  void success(std::string content) {addEvent(LogEvent("[SUCCESS] ", 0x08A124, content));}
  void dump(const std::map<std::string, std::string>& data, std::string title = "", bool quotes = false);

  void separator() {file <<"\n  <hr>";}
  void close();

  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;
};
