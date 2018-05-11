#ifndef SYSTEMSETTINGS_H
#define SYSTEMSETTINGS_H
#include "../BaseResource.h"
#include <map>
#include <string>

class SystemInfo : public BaseResource<SystemInfo>
{
public:
    SystemInfo();
    SystemInfo(const SystemInfo& orig);

    //just typeId
    static constexpr ResourceType getResourceType()
    {
        return SYSTEM_INFO;
    }

    //static constructor
    static ResourcesMap loadResourcesFromFile(/*const std::string &resourcePath*/);
};
#endif /* SYSTEMSETTINGS_H */
