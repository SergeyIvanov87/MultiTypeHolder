# MultiTypeHolder
Template extendable type holder, object for storing and providing the uniform access for objects of different types. It may be used as Signleton for loading and storing shared resources, for example: textures, sounds, models etc...
Instead of using for several singletons for several object type, or only one signleton for classes inherited from the base interface (which cannot be common for different types offen).

Now, it initializes as variadic templates of Type Wrappers, for example:
```ruby
LoadedResourcesHolder
    <
        SystemInfoObjectLoader,
        ModelFileDescriptionObjectLoader,
        TexturesObjectLoader
        SoundObjectLoader
        /*TODO your type here*/
    > holder;
```

Which defined in 
```
specificImpl/BaseObjectLoaderSpecific.h
```
Wrappers can provide additional operation: load/store resources. For example
```ruby
//Settings
typedef BaseObjectLoader SystemInfoObjectLoader;

//Textures
typedef BaseObjectLoader<Texture, texture_files_path> TexturesObjectLoader;
```
Its contains 'Type' (Texture for example) and appropriate directory path on file system, which contains expected resources. Provided additional operations on resources are 
```ruby
    void freeResources();
    bool loadResources();
```
which are called, when this type holder initializing first time, or destroying finally.


So, typical usage of Multi Type Holder is:
```
    const Sound *s = getResourceObjectCPtr<Sound>("hihi");
    ...
    s = getResourceObjectCPtr<Sound>("haha");
    ...
    const Texture *t = getResourceObjectCPtr<Texture>("texture1");
    ...
```


