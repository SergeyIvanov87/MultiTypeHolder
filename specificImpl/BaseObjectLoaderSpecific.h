#ifndef SPECOBJECTLOADER_H_
#define SPECOBJECTLOADER_H_
#include "../include/BaseObjectLoader.h"
#include "../include/resources/Texture.h"
#include "../include/resources/SystemInfo.h"
#include "../include/resources/ModelFileDescription.h"
#include "../include/resources/Sound.h"

//TODO Add your NEW type HERE

//Model from file descriptions
typedef BaseObjectLoader<ModelFileDescription, model_description_path> ModelFileDescriptionObjectLoader;

//Settings
typedef BaseObjectLoader<SystemInfo> SystemInfoObjectLoader;

//Textures
typedef BaseObjectLoader<Texture, texture_files_path> TexturesObjectLoader;

//Sound
typedef BaseObjectLoader<Sound, sound_files_path> SoundObjectLoader;

#endif /* SPECOBJECTLOADER_H_ */
