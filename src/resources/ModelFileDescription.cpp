#include "ModelFileDescription.h"
#include <iostream>
#include <fstream>
#include <string.h>
#include "../Utils.h"

ModelFileDescription::ModelFileDescription(const std::string &name)
{
}

ModelFileDescription::ModelFileDescription(const ModelFileDescription& orig)
{
}

ModelFileDescription::~ModelFileDescription()
{
}
ModelFileDescription::ResourcesMap ModelFileDescription::loadResourcesFromFile(const std::string &resourcePath)
{
    ModelFileDescription::ResourcesMap objectsMap;
    std::cout << "Read model description file: " << resourcePath << std::endl;
    std::ifstream file;
    file.open(resourcePath, std::ifstream::in);
    if(!file.good())
    {
        return objectsMap;
    }

    char line[1024];

    ModelFileDescriptionPtr modelPtr;
    while(file.getline(line, 1024))
    {
        //TODO - evry line is resource name
        modelPtr.reset(new ModelFileDescription(line));
        objectsMap[line] = modelPtr;
    }
    return objectsMap;
}
