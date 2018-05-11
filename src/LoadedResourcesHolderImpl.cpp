#include "LoadedResourcesHolderImpl.hpp"

ResourceHolderPtr resourceHolderPtr;
bool isResourceHolderCreated()
{
    return resourceHolderPtr != NULL;
}

ResourceHolder *getResourceHolderFacility()
{
    return resourceHolderPtr.get();
}
