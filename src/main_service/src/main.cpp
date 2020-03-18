/*
 * This is the source code of SpecNet project
 *
 * Copyright (c) Dmitriy Bondarenko
 * feel free to contact me: specnet.messenger@gmail.com
 */

#include <iostream>
#if defined(Linux)
  #include "linuxsystem.h"  
  #include "service/linux/linuxservice.h"
#elif defined(Windows)

#endif

#include "file/fileadapter.h"
#include "config/json/configjson.h"
#include "log/speclog/speclog.h"

int  main(int  argc,  char  **argv)
{    
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

  return  0;
}  //  main
