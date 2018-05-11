#include "../include/LoadedResourcesHolderImpl.hpp"

int main(int argc, char **argv)
{
    //create & get singleton
    auto *rhp = getResourceHolderPtr();
    //load resources
    rhp->initResourceLoader();

    //use loaded resources
    std::cout << "Loaded resources test:" << std::endl;
    const Sound * s = getResourceObjectCPtr<Sound>("haha");
    if(s)
    {
        std::cout << getResourceTypeString(s->getResourceType()) << " by name: " << s->getName() << " loaded" << std::endl;
    }
    s = getResourceObjectCPtr<Sound>("hihi");
    if(s)
    {
        std::cout << getResourceTypeString(s->getResourceType()) << " by name: " <<  s->getName() << " loaded" << std::endl;
    }

    s = getResourceObjectCPtr<Sound>("NotExist");
    if(!s)
    {
        std::cout << "Sound: NotExist Not found" << std::endl;
    }
//////////////////////////////////////////////////////////////
    const Texture *t = getResourceObjectCPtr<Texture>("text1");
    if(t)
    {
        std::cout << getResourceTypeString(t->getResourceType()) << " by name: " << t->getName() << " loaded" << std::endl;
    }

    return 0;
}
