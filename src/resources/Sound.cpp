
#include "Sound.h"
#include "../Utils.h"
#include <iostream>
#include <string>

Sound::Sound(const std::string &name):
        soundName(name)
{
}


Sound::ResourcesMap Sound::loadResourcesFromFile(const std::string &resourcePath)
{
    std::string textName = Utils::parseFileName(resourcePath);
    Sound::SharedPtr s;
    ResourcesMap sMap;
    s.reset(new Sound(textName));
    sMap.insert(std::make_pair(textName, s));
    return sMap;
}
