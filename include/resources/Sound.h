#ifndef SOUND_H
#define SOUND_H
#include "../BaseResource.h"
#include <vector>
#include <map>
#include <string>

class Sound : public BaseResource<Sound>
{
public:
    Sound(const std::string &name);
    Sound(const Sound& src) = delete;

    //just TypeID
    static constexpr ResourceType getResourceType()
    {
        return SOUND;
    }

    //static constructor from file
    static ResourcesMap loadResourcesFromFile(const std::string &resourcePath);
    const std::string &getName() const {return soundName; };

private:
    std::string soundName;
};

#endif /* SOUND_H */
