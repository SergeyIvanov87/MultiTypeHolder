#ifndef MODELFILEDESCRIPTION_H
#define MODELFILEDESCRIPTION_H

#include <vector>
#include <unordered_map>
#include "../BaseResource.h"

class ModelFileDescription : public BaseResource<ModelFileDescription> {
public:
    ModelFileDescription(const std::string &name);
    ModelFileDescription(const ModelFileDescription& orig);
    virtual ~ModelFileDescription();

    //Aliases
    typedef std::string Description;
    typedef std::string Value;
    typedef const Value & ValueCRef;
    typedef std::map<Description, Value> DescriptionValueMap;
    typedef DescriptionValueMap::iterator DescriptionValueMapIt;
    typedef DescriptionValueMap::const_iterator DescriptionValueMapCIt;
    typedef DescriptionValueMap::value_type DescriptionValueMapValue;

    //constant just TypeId
    static constexpr ResourceType getResourceType()
    {
        return MODEL_DESCRIPTION;
    }

    //static constructor from file
    static ResourcesMap loadResourcesFromFile(const std::string &resourcePath);

};
typedef std::shared_ptr<ModelFileDescription> ModelFileDescriptionPtr;

#endif /* MODELFILEDESCRIPTION_H */
