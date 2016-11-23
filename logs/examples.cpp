/** local **/
#include "logger.hpp"

int main()
{
  Logger log;
  std::map<std::string, std::string> testMap {{"Hello", "Dumps"}, {"Just", "Testing"}, {"Some longer name", "Longer value"}};

  log("Hello");
  log.error("Test error");
  log.info("Info test");
  log.success("Success test");
  log("Normal event");

  log.separator();
  log.dump(testMap, "Testing a map dump", true);
  log.separator();

  log("Pi", 3.1415);
  log("Test", true);

  return 0;
}
