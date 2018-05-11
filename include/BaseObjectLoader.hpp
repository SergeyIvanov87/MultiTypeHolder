//Get/Set
template <class ResourceHolder,  const char *treeLeafPath>
typename BaseObjectLoader<ResourceHolder, treeLeafPath>::ResourceClassTypeCPtr BaseObjectLoader<ResourceHolder, treeLeafPath>::getResourceByName(const std::string &name) const
{
    ResourcesMapCIt it = loadedObjectResources.find(name);
    if(it != loadedObjectResources.end())
    {
        return it->second.get();    //dereferenced shared ptr
    }
    return NULL;
}

template <class ResourceHolder,  const char *treeLeafPath>
bool BaseObjectLoader<ResourceHolder, treeLeafPath>::setResourceByName(
        const typename BaseObjectLoader<ResourceHolder, treeLeafPath>::ResourcesMap::key_type &name,
        const typename BaseObjectLoader<ResourceHolder, treeLeafPath>::ResourceClassTypeSharedPtr &resource)
{
    ResourcesMapIt it = loadedObjectResources.find(name);
    if(it == loadedObjectResources.end())
    {
        loadedObjectResources.insert(std::make_pair(name, resource));
        return true;
    }
    return false;
}

//Free tree
template <class ResourceHolder,  const char *treeLeafPath>
void BaseObjectLoader<ResourceHolder, treeLeafPath>::freeResources()
{
    loadedObjectResources.clear();
}

//Load Resources from associated tree node
template <class ResourceHolder, const char *treeLeafPath>
bool BaseObjectLoader<ResourceHolder, treeLeafPath>::loadResources()
{
   std::cout << "Loading resources starting: " << getResourceTypeString(ResourceHolder::getResourceType()) << std::endl;
    //free resources
    //freeResources();

    //get directory
    char *curDir = get_current_dir_name();
    chdir(getResourceTreePath());

    DIR *objDir = opendir("./");
    if(!objDir)
    {
        std::cout << "Cannot open directory:" << getResourceTreePath() <<
                               (". Error: ") << strerror(errno) << std::endl;
        return false;
    }
    //iterate over directory and load resoures
    struct dirent *entry = NULL;
    while((entry = readdir(objDir)) != NULL)
    {
        if(!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
        {
            //skip it
            continue;
        }
        //make files filter

        std::string filePath(entry->d_name);
        std::cout << "Load resource from file: " << filePath << std::endl;
        ResourcesMap res;
        try
        {
            //use static resource constructor
            res = ResourceClassType::loadResourcesFromFile(filePath);
            if(res.empty())
            {
                std::cout << "No resources loaded" << std::endl;
                continue;
            }
            std::cout << "Loading resources finished: " << res.size() << std::endl;

            /*if(ResourceClassType::isSerializable())
            {
                //TODO
            }*/
        }
        catch( const std::exception &exception)
        {
            std::cout << "Exception error: " << exception.what()<< std::endl;
            continue;
        }
        //add to map
        loadedObjectResources.insert(res.begin(), res.end());
    }

    //close dir
    closedir(objDir);

    chdir(curDir);
    free(curDir);
    std::cout << "Total loaded resources:" << loadedObjectResources.size() << std::endl;
    return !loadedObjectResources.empty();
}


/////////////////////////DUMMY_PATH SPECIALIZATION///////////////////////////////////////////////////////
template <class ResourceHolder>
typename BaseObjectLoader<ResourceHolder, system_info_dummy_path>::ResourceClassTypeCPtr BaseObjectLoader<ResourceHolder, system_info_dummy_path>::getResourceByName(const std::string &name) const
{
    ResourcesMapCIt it = loadedObjectResources.find(name);
    if(it != loadedObjectResources.end())
    {
        std::cout << "Get resource: " << name << std::endl;
        return it->second.get();    //dereferenced shared ptr
    }
    std::cout << "Cannot get resource: " << name << std::endl;
    return NULL;
}

template <class ResourceHolder>
bool BaseObjectLoader<ResourceHolder, system_info_dummy_path>::setResourceByName(
        const typename BaseObjectLoader<ResourceHolder, system_info_dummy_path>::ResourcesMap::key_type &name,
        const typename BaseObjectLoader<ResourceHolder, system_info_dummy_path>::ResourceClassTypeSharedPtr &resource)
{
    ResourcesMapIt it = loadedObjectResources.find(name);
    if(it == loadedObjectResources.end())
    {
        loadedObjectResources.insert(std::make_pair(name, resource));
        std::cout << "Insert resource: " << name << std::endl;
        return true;
    }
    return false;
}

template <class ResourceHolder>
void BaseObjectLoader<ResourceHolder, system_info_dummy_path>::freeResources()
{
    std::cout << "Free resources" << std::endl;
    loadedObjectResources.clear();
}

template <class ResourceHolder>
bool BaseObjectLoader<ResourceHolder, system_info_dummy_path>::loadResources()
{
    //just resource doesn't need in path
    std::cout << "Loading resources starting: " << getResourceTypeString(ResourceHolder::getResourceType()) << std::endl;
    ResourcesMap res;
    try
    {
        res = ResourceClassType::loadResourcesFromFile();
        loadedObjectResources.insert(res.begin(), res.end());
    }
    catch( const std::exception &exception)
    {
        std::cout << "Exception error: " << exception.what() << std::endl;
        return false;
    }
    std::cout << "Loading resources finished: " << res.size() << std::endl;
    return !res.empty();
}
