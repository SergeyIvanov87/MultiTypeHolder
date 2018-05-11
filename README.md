# MultiTypeHolder

Template extendable type holder, object for storing and providing the uniform access for objects of different types.
It may be used as Signleton for loading and storing shared resources, for example: textures, sounds, models and etc

Now, it initializes as variadic templates of Type Wrappers
LoadedResourcesHolder<SystemInfoObjectLoader,ModelFileDescriptionObjectLoader, TexturesObjectLoader, SoundObjectLoader> holder;

Which defined in 'specificImpl/BaseObjectLoaderSpecific.h'. For example

//Settings
typedef BaseObjectLoader<SystemInfo> SystemInfoObjectLoader;

//Textures
typedef BaseObjectLoader<Texture, texture_files_path> TexturesObjectLoader;

Its contains 'Type' (Texture for example) and appropriate directory path on file system
