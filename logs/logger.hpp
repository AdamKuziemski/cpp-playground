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

class ErrorEvent : public LogEvent
{
public:
  ErrorEvent(std::string content) : LogEvent("[ERROR] ", 0xD6280D, content) {}
};

class InfoEvent : public LogEvent
{
public:
  InfoEvent(std::string content) : LogEvent("[INFO] ", 0x1C77ED, content) {}
};

class SuccessEvent : public LogEvent
{
public:
  SuccessEvent(std::string content) : LogEvent("[SUCCESS] ", 0x08A124, content) {}
};

class DumpEvent : public LogEvent
{
public:
  DumpEvent(const std::map<std::string, std::string>& dump);
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

  void operator()(LogEvent);
  void operator()(std::string);
  void addEvent(LogEvent);
  void addEvent(std::string);
  void separator();
  void close();

  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;
};
