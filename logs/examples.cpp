/** local **/
#include "logger.hpp"

int main()
{
  Logger log;
  std::map<std::string, std::string> testMap {{"Hello", "Dumps"}, {"Just", "Testing"}, {"Some longer name", "Longer value"}};

  log(ErrorEvent("Test error"));
  log(InfoEvent("Info test"));
  log(SuccessEvent("Success test"));
  log("Normal event");
  log.separator();
  log(DumpEvent(testMap));

  return 0;
}
