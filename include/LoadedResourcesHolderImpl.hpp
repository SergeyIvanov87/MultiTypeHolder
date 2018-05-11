#ifndef LOADEDRESOURCESHOLDERIMPL_HPP
#define LOADEDRESOURCESHOLDERIMPL_HPP

//use specific instantiaion
#include "../specificImpl/LoadedResourcesHolderSpecific.h"

extern ResourceHolderPtr resourceHolderPtr;
template <class ...Resources>
void createResourceHolder(Resources ...args)
{
    resourceHolderPtr = std::make_shared<ResourceHolder>(args...);
}


template <class Type>
typename BaseResource<Type>::ResourceClassTypeCPtr getResourceObjectCPtr(const std::string &resourceName)
{
    typename BaseResource<Type>::ResourceClassTypeCPtr ret =
        getResourceHolderPtr()->getResourceById <BaseResource<Type>::ResourceClassType::getResourceType()>(resourceName);
    return ret;
}

template <class Type>
bool setResourceObject(
    const std::string &resourceName,
    const typename BaseResource<Type>::ResourceClassTypeSharedPtr &sharedPtr)
{
    return getResourceHolderPtr()->setResourceById <BaseResource<Type>::ResourceClassType::getResourceType()>(resourceName, sharedPtr);
}

#endif /* LOADEDRESOURCESHOLDERIMPL_HPP */
