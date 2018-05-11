#ifndef TEXTURE_H_
#define TEXTURE_H_
#include "../BaseResource.h"
#include <vector>
#include <map>
#include <string>

class Texture : public BaseResource<Texture>
{
public:
    Texture(const std::string &name, uint16_t w, uint16_t h);
    Texture(const Texture& src) = delete;

    //just Type Id
    static constexpr ResourceType getResourceType()
    {
        return TEXTURE;
    }

    //static constructor from file
    static ResourcesMap loadResourcesFromFile(const std::string &resourcePath);

    //Resource specific methods
    uint16_t getWidth() const {return width; }
    uint16_t getHeigth() const {return height; }
    const std::string &getName() const {return textureName; };

private:
    uint16_t width;
    uint16_t height;
    std::string textureName;
};
#endif /* TEXTURE_H_ */
