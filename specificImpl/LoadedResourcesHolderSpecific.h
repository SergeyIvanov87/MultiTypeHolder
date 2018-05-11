/*
 * LoadedResourcesHolderConcrete.h
 *
 *  Created on: Feb 24, 2016
 *      Author: user
 */

#ifndef LOADEDRESOURCESHOLDERCONCRETE_H_
#define LOADEDRESOURCESHOLDERCONCRETE_H_

#include "BaseObjectLoaderSpecific.h"
#include "../include/LoadedResourcesHolder.h"


//TODO add your NEW type HERE
using ResourceHolder = LoadedResourcesHolder<
                                        SystemInfoObjectLoader,
                                        ModelFileDescriptionObjectLoader,
                                        TexturesObjectLoader,
                                        SoundObjectLoader>;
using ResourceHolderPtr = std::shared_ptr<ResourceHolder>;

bool isResourceHolderCreated();

template <class ...Resources>
void createResourceHolder(Resources...args);
ResourceHolder *getResourceHolderFacility();

inline ResourceHolder* getResourceHolderPtr()
{
    if(!isResourceHolderCreated())
    {
        SystemInfoObjectLoader systemInfoLoader;
        ModelFileDescriptionObjectLoader modelDescrLoader;
        TexturesObjectLoader tLoader;
        SoundObjectLoader sLoader;

        createResourceHolder(systemInfoLoader, modelDescrLoader, tLoader, sLoader);
    }
    return getResourceHolderFacility();
}


#endif /* LOADEDRESOURCESHOLDERCONCRETE_H_ */
