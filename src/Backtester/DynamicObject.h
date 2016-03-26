#ifndef CXXMODULE_DYNMOD_HEADER
#define CXXMODULE_DYNMOD_HEADER

#include "SharedLibrary.h"


namespace DynamicLoading{

// default creator/destructor function name
inline std::string& create_function_name()
{
    static std::string create = "create_object";
    return create;
}

inline std::string& destroy_function_name()
{
    static std::string destroy = "destroy_object";
    return destroy;
}


/*!
 *  Represent an Object loaded from a Shared Library (dll).
 *  The underlying object is accessed as if DynamicObject<> was
 *  a pointer.
 *
 * Constraint
 * ----------
 *
 *  You have to have implemented a create and destroy function
 *  that allocate and desallocate the underlying object.
 *
 *  The create and destroy function default name are:
 *      - create_object
 *      - destroy_object
 *
 *  Those names can be overriden by calling
 *      create_functio_name() = "my_create_function_name";
 *      destroy_function_name() = "my_destroy_function_name";
 *
 *  You can also specify them during the DynamicObject creation
 *
 *      DynamicObject<BaseObject> dyn_object("./libSharedLib.so", "my_create", "my_destroy");
 *
 *  The assignment operatation is no allowed
 *
 * Usage
 * -----
 *
 *  -*- Example 1 -*-
 *
 *  DynamicObject<BaseObject> dyn_object("./libSharedLib.so");
 *
 *  dyn_object->what_ever_function();
 *
 * -*- Example 2 -*-
 *
 *  SharedLibrary sl("./libSharedLib.so");
 *
 *  DynamicObject<BaseObject1> dyn_object1(sl);
 *
 *  DynamicObject<BaseObject2> dyn_object2(sl, "create2", "destroy2");
 *
 */
//#include <functional>

template<typename T>
class DynamicObject
{
public:

//    typedef std::function<T*()> create;
//    typedef std::function<void(T*)> destroy;

    typedef T* (*create)();
    typedef void (*destroy)(T*);

    // load the dynamic library
    DynamicObject(const std::string& path, const std::string& create_name = create_function_name(),
                                           const std::string& destroy_name = destroy_function_name()):
        _dynlib_ref(path), _internal_dyn_object(nullptr), _create(nullptr), _destroy(nullptr)
    {
        // Make Sure both function are defined
        get_create_object(create_name);
        get_destroy_object(destroy_name);

        create_object();
    }

    // Create a DynamicObject based on an existing SharedLibrary
    DynamicObject(const SharedLibrary& sl, const std::string& create_name = create_function_name(),
                                           const std::string& destroy_name = destroy_function_name()):
        _dynlib_ref(sl), _internal_dyn_object(nullptr), _create(nullptr), _destroy(nullptr)
    {
        // Make Sure both function are defined
        get_create_object(create_name);
        get_destroy_object(destroy_name);

        create_object();
    }

    // Create a new Object || SharedLibray is kept unique
    DynamicObject(const DynamicObject& obj):
        _dynlib_ref(obj._dynlib_ref), _internal_dyn_object(nullptr), _create(nullptr), _destroy(nullptr)
    {
        _create = obj._create;      // We don't need to seek the function in the shared lib again
        _destroy = obj._destroy;

        // create a new object
        create_object();
    }

    DynamicObject& operator=(const DynamicObject& rhs) = delete;

    // The object had to be loaded by the ctor : no check needed
    inline T& operator* ()  {   return *_internal_dyn_object;   }
    inline T* operator->()  {   return _internal_dyn_object;    }

    // return a new object instance
    inline DynamicObject new_object()   {   return DynamicObject(*this);    }

    ~DynamicObject()
    {
        if (_internal_dyn_object)
            _destroy(_internal_dyn_object);
    }

    inline SharedLibrary& shared_library() {   return _dynlib_ref; }
    inline operator bool() const {   return _internal_dyn_object;    }

private:

    void get_create_object(const std::string& fname)
    {
        _create = _dynlib_ref.get_function_nocheck<create>(fname);
        THROW(_create == 0, std::runtime_error, "create method is undefined");
    }

    void get_destroy_object(const std::string& fname)
    {
        _destroy = _dynlib_ref.get_function_nocheck<destroy>(fname);
        THROW(_destroy == 0, std::runtime_error, "destroy method is undefined");
    }

    void create_object()
    {
        _internal_dyn_object = _create();
        THROW(_internal_dyn_object == 0, std::runtime_error, "create method call failure");
    }

private:
    SharedLibrary _dynlib_ref;
    T* _internal_dyn_object;

    create _create;
    destroy _destroy;
};
}

#endif
