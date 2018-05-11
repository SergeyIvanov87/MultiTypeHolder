#ifndef IRESOURCELOADER_H
#define IRESOURCELOADER_H
#include <memory>
#include <string>
#include <map>
#include <memory>
#include "ResourcesPath.h"
template<class Resource>
class BaseResource
{
public:
    //Export Defines
    typedef Resource ResourceClassType;
    typedef std::shared_ptr<ResourceClassType> SharedPtr;
    typedef std::map<std::string, SharedPtr> ResourcesMap;
    typedef typename ResourcesMap::value_type ResourcesMapValueType;
    typedef typename ResourcesMap::iterator ResourcesMapIt;

    typedef SharedPtr ResourceClassTypeSharedPtr;
    typedef const Resource * ResourceClassTypeCPtr;
    typedef typename ResourcesMap::const_iterator ResourcesMapCIt;
    constexpr static ResourceType resourceType = ResourceClassType::getResourceType();

    BaseResource() = default;

    //TODO
    //Add ISerializable interface
};
#endif //IRESOURCELOADER_H
