
#ifndef BASEOBJECTLOADER_H_
#define BASEOBJECTLOADER_H_

#include "BaseResource.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include "Utils.h"

//Loader for ResouceType, associated with file system tree path
template<class ResourceHolder, const char *treeLeafPath = system_info_dummy_path>
class BaseObjectLoader
{
public:
    ~BaseObjectLoader() = default;
    BaseObjectLoader() = default;
public:
    //Aliases
    typedef typename ResourceHolder::ResourceClassType ResourceClassType;
    typedef typename ResourceHolder::ResourceClassTypeSharedPtr ResourceClassTypeSharedPtr;
    typedef typename ResourceHolder::ResourceClassTypeCPtr ResourceClassTypeCPtr;
    typedef typename ResourceHolder::ResourcesMap ResourcesMap;
    typedef typename ResourceHolder::ResourcesMapValueType ResourcesMapValueType;
    typedef typename ResourceHolder::ResourcesMapIt ResourcesMapIt;
    typedef typename ResourceHolder::ResourcesMapCIt ResourcesMapCIt;
    constexpr static const char* ResourceTreePath = treeLeafPath;

    //Interface methods:
    // get pointer on loaded resource
    ResourceClassTypeCPtr getResourceByName(const std::string &name) const;
    ResourceType getResourceType() const    //just TypeID
    {
        return ResourceHolder::getResourceType();
    };
    //get FS resource root path:  /texture, /sound, etc
    const char *getResourceTreePath() const
    {
        return treeLeafPath;
    };

    //insert new resource
    bool setResourceByName(const typename ResourcesMap::key_type &name,
            const ResourceClassTypeSharedPtr &resource);

    //RAII
    void freeResources();
    bool loadResources();

private:
    ResourcesMap loadedObjectResources;
};

////////////////////////////////////////////////////////////////////////////////
//partial specialization for dummy file path (not associate with path)
template<class ResourceHolder>
class BaseObjectLoader<ResourceHolder, system_info_dummy_path> {
public:
    ~BaseObjectLoader() = default;
    BaseObjectLoader() = default;

public:
    //Aliases
    typedef typename ResourceHolder::ResourceClassType ResourceClassType;
    typedef typename ResourceHolder::ResourceClassTypeSharedPtr ResourceClassTypeSharedPtr;
    typedef typename ResourceHolder::ResourceClassTypeCPtr ResourceClassTypeCPtr;
    typedef typename ResourceHolder::ResourcesMap ResourcesMap;
    typedef typename ResourceHolder::ResourcesMapValueType ResourcesMapValueType;
    typedef typename ResourceHolder::ResourcesMapIt ResourcesMapIt;
    typedef typename ResourceHolder::ResourcesMapCIt ResourcesMapCIt;

    //Interface oublic methods
    ResourceClassTypeCPtr getResourceByName(const std::string &name) const;
    ResourceType getResourceType() const
    {
        return ResourceHolder::getResourceType();
    };

    bool setResourceByName(const typename ResourcesMap::key_type &name,
            const ResourceClassTypeSharedPtr &resource);
    void freeResources();
    bool loadResources();
private:
    ResourcesMap loadedObjectResources;
};
////////////////////////////////////////////////////////////////////////////////

#include "BaseObjectLoader.hpp"
#endif /* BASEOBJECTLOADER_H_ */
