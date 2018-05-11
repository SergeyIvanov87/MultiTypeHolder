#ifndef RESOURCESPATH_H
#define RESOURCESPATH_H

extern const char main_resources_path[];
extern const char root_files_path[];
extern const char sound_files_path[];
extern const char texture_files_path[];
extern const char system_info_dummy_path[];
extern const char model_description_path[];

enum ResourceType
    {
        EMPTY = -1,//0x0,
        SYSTEM_INFO,
        MODEL_DESCRIPTION,
        TEXTURE,
        SOUND,
        MAX_RESOURCE_TYPE
    };

inline const char *getResourceTypeString(ResourceType type)
{
    static const char *strings[] = {"SYSTEM_INFO", "MODEL_DESCRIPTION",
                                    "TEXTURE",
                                    "SOUND"};
    static_assert(sizeof(strings)/sizeof(strings[0]) == MAX_RESOURCE_TYPE,
            "Invalid ResourceType and ResourceType description count");
    if(type == EMPTY)
    {
        return "INVALID RESOURCE TYPE";
    }
    return type < MAX_RESOURCE_TYPE ? strings[type] : "INVALID RESOURCE TYPE";
}
#endif //RESOURCESPATH_H
