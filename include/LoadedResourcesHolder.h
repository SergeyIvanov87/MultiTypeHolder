#ifndef RESOURCESHOLDER_H_
#define RESOURCESHOLDER_H_
#include <tuple>
#include <array>
#include <utility>
#include <unistd.h>
#include <iostream>
#include <error.h>
#include <string.h>
#include "ResourcesPath.h"
#include "CTimeUtils.h"

//!!!!  DELETE IT #include "BaseObjectLoaderConcrete.h"
//https://habrahabr.ru/post/101430/

//instantiated by Resource Loader template classes
template <class ... Loaders>
class LoadedResourcesHolder
{
public:
    typedef std::tuple<Loaders...> ResourceLoadersTuple;
    LoadedResourcesHolder(Loaders ...args):loadersTuple(args...) {}

    ~LoadedResourcesHolder()
    {
        deinitResourceLoader();
    }

    //function to get specific resource from specific resource loader
    template<ResourceType type>
    typename std::tuple_element<type, ResourceLoadersTuple>::type::ResourceClassTypeCPtr
    getResourceById(const std::string &name) const
    {
        return std::get<type>(loadersTuple).getResourceByName(name);
    }

    //function to set specific resource to specific resource loader
    template<ResourceType type>
    bool setResourceById(const std::string &name,
        const typename std::tuple_element<type, ResourceLoadersTuple>::type::ResourceClassTypeSharedPtr &resource)
    {
        return std::get<type>(loadersTuple).setResourceByName(name, resource);
    }
private:
    //Loaders for all registered resource types
    ResourceLoadersTuple loadersTuple;
public:
    //load resources for all ResourceLoaders
    bool initResourceLoader()
    {
        //Enter to main reources tree directory
        char * curDir = get_current_dir_name();

        do
        {
            if(chdir(main_resources_path) != 0)
            {
                std::cout << "Cannot enter in resource dir: " <<
                        strerror(errno) << ". Current dir: " << curDir<< std::endl;
                return false;
            }

            CTimeUtils::for_each_in_tuple(loadersTuple, [](size_t index, auto &x)
            {
                x.loadResources();
            });
        }
        while(false);

        //Back current directory
        chdir(curDir);
        free(curDir);
        return true;
    }

    //free resources for all ResourceLoaders
    bool deinitResourceLoader()
    {
        CTimeUtils::for_each_in_tuple(loadersTuple, [](size_t index, auto &x)
        {
            x.freeResources();
        });
        return true;
    }
};

#endif /* RESOURCESHOLDER_H_ */
