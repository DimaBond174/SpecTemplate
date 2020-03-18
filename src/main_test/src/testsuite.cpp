#define  BUILDING_TestSuite
#include "testsuite.h"
#include "client/testclient.h"
#include "file/fileadapter.h"
#include "config/json/configjson.h"
#include "log/speclog/speclog.h"
#include <memory>
#if defined(Linux)
  #include "linuxsystem.h"
#elif defined(Windows)

#endif

class  TestSuite
{
public:
  TestSuite();
};

TestSuite::TestSuite()
{

}

TestSuite testSuite;

/*
 * do_Test1
 *  returns 0 on success, or errorcode
 * -----------------------------------
 * Sending big file from client to client
*/
int do_Test1()
{
    int re = 1;
    std::shared_ptr<ConfigJSON> p_config
        = std::make_shared<ConfigJSON>(spec::getExePath(),
  // Implement default config values:
                      [] (const std::string &) { return std::string(); }
    );
    // Load config:
      if (p_config->setPath("./assets/settings.service.json"))
      {
        std::shared_ptr<SpecLog>  p_logger
            = std::make_shared<SpecLog>(false, p_config);

      #if defined(Linux)
        std::shared_ptr<LinuxService>  p_service
            = std::make_shared<LinuxService>();
      #elif defined(Windows)

      #endif

        p_service->setEnvironment(p_config, p_logger, p_service);
        p_service->onCmd(argc,  argv);

      } // if (p_config-
      else {
        std::cout << "Can't load config [./assets/settings.service.json]\n";
      }
    TestClient testClient;
    re = testClient.getResult(a);
    return re;
}
