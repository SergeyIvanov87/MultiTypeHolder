#include "SystemInfo.h"
#include <sstream>
#include <iostream>

SystemInfo::SystemInfo()
{
}

SystemInfo::SystemInfo(const SystemInfo& orig)
{
}

SystemInfo::ResourcesMap SystemInfo::loadResourcesFromFile(/*const std::string &resourcePath*/)
{
    SystemInfo::ResourcesMap ret;
    SystemInfo::SharedPtr sys(new SystemInfo());
    //TODO
    static bool isExist = false;
    if(!isExist)
    {
        ret["SystemInfo"] = sys;
        isExist = true;
    }
    return ret;
}
