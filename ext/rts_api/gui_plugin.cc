#include "ag_plugin.h"
#include <iostream>

#ifdef WIN32
#   include <windows.h>
#include <ag_debug.h>

AGPlugin::~AGPlugin() throw()
{
  FreeLibrary((HINSTANCE__*)myptr);
}

typedef AGPlugin* CreatePluginType();

typedef int (CALLBACK* LPFNDLLFUNC1)();

AGPlugin *loadPlugin(const std::string &pFile)
{
  std::cout<<"loadPlugin1"<<std::endl;
  TRACE;
  HMODULE hMod = LoadLibrary(pFile.c_str());
  std::cout<<"loadPlugin1"<<std::endl;
  cdebug("1");
  LPFNDLLFUNC1 createPlugin = GetProcAddress(hMod, "create");
  std::cout<<"loadPlugin1"<<std::endl;
  cdebug("2");
  if(!createPlugin)
    {
      std::cout<<"Plugin create() not found!"<<std::endl;
      return 0;
    }


  AGPlugin *p=((CreatePluginType*)createPlugin)();
  std::cout<<"loadPlugin1"<<std::endl;
  cdebug("3");
  p->myptr=hMod;
  std::cout<<"loadPlugin1"<<std::endl;
  cdebug("4");
  return p;
}



#else

#include <dlfcn.h>

AGPlugin::~AGPlugin() throw()
{
  dlclose(myptr);
}

typedef AGPlugin* CreatePluginType();

AGPlugin *loadPlugin(const std::string &pFile)
{
  void* plugin = dlopen(pFile.c_str(), RTLD_LAZY);
  if (!plugin)
    {
      std::cerr << "Cannot load library: " << dlerror() << '\n';
      std::cerr << "File was:" << pFile<< "."<<std::endl;
      return 0;
    }
  CreatePluginType* createPlugin = (CreatePluginType*) dlsym(plugin, "create");
  AGPlugin *p=createPlugin();
  p->myptr=plugin;
  return p;
}

#endif
