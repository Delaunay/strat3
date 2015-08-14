#ifndef STRAT3_BACKTESTER_COMPONENTS_HEADER
#define STRAT3_BACKTESTER_COMPONENTS_HEADER

#include "DLLoader.h"
#include "Pointer.h"

namespace strat3{

//
//  Represent an Object Dynamically loaded from a dll
//  can be used as a pointer
//
//  When the copy constructor is used a new underlying object is created
//  the new underlying object WILL NOT be copied using its copy constructor
//  defined by the user.
//
template<typename T>
class DynamicObject
{
public:
    typedef T* (*create)();
    typedef void (*destroy)(T*);

    // Create a new Object keep DLLoader unique
    DynamicObject(const DynamicObject& obj)
    {
        this->_dynlib_ref = obj._dynlib_ref;

        // create a new object
        create fn = _dynlib_ref->get_function<create>("create_object");
        STHROW(fn == 0, std::runtime_error, "'create_object' undefined");

        _internal_dyn_object = fn();
        STHROW(_internal_dyn_object == 0, std::runtime_error, "'create_object' call failure");
    }

    // I am not sure I am going to need this one
    DynamicObject& operator=(const DynamicObject& rhs) = delete;

    // load the dynamic library
    DynamicObject(const std::string& path):
        _dynlib_ref(new DLLoader(path)), _internal_dyn_object(0)
    {
        create fn = _dynlib_ref->get_function<create>("create_object");
        STHROW(fn == 0, std::runtime_error, "'create_object' undefined");

        _internal_dyn_object = fn();
        STHROW(_internal_dyn_object == 0, std::runtime_error, "'create_object' call failure");
    }

    // The object had to be loaded by the ctor
    // no check needed
    inline T& operator* ()  {   return *_internal_dyn_object;   }
    inline T* operator->()  {   return _internal_dyn_object;    }

    ~DynamicObject()
    {
        if (_internal_dyn_object)
        {
            destroy fn = _dynlib_ref->get_function<destroy>("destroy_object");
            STHROW(fn == 0, std::runtime_error, "'destroy_object' undefined");
            fn(_internal_dyn_object);
        }
    }

    operator bool() const
    {
        return _internal_dyn_object;
    }

private:
    Pointer<DLLoader> _dynlib_ref;
    T* _internal_dyn_object;
};

}
#endif
