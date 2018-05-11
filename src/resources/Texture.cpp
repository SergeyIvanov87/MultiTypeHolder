
#include "Texture.h"
#include "../Utils.h"
#include <iostream>
#include <string>

Texture::Texture(const std::string &name, uint16_t w, uint16_t h):
        width(w),
        height(h),
        textureName(name)
{
}


Texture::ResourcesMap Texture::loadResourcesFromFile(const std::string &resourcePath)
{
    std::string textName = Utils::parseFileName(resourcePath);
    Texture::SharedPtr texture;
    ResourcesMap texturesMap;
    texture.reset(new Texture(textName, 10, 20));
    texturesMap.insert(std::make_pair(textName, texture));
    return texturesMap;
}
