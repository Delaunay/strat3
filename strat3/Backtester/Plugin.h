#ifndef PLUGIN_LIBRARY_HEADER
#define PLUGIN_LIBRARY_HEADER

// This header should be (does not have to be) included by people implementing the plugin
// It only makes sure users will be implementing the create and destroy function
// with the correct setup (they must be externed "C" and have the PLUGIN_EXPORT macro)
// they can modify the create/destroy function name by defining:
// - DYN_CREATE_OBJ
// - DYN_DESTROY_OBJ
// before including this file

#ifdef __linux__
#   define PLUGIN_EXPORT __attribute__ ((visibility ("default")))
#else
#   define PLUGIN_EXPORT __declspec(dllexport)
#endif

#ifndef DYN_CREATE_OBJ
#define DYN_CREATE_OBJ create_object
#endif

#ifndef DYN_DESTROY_OBJ
#define DYN_DESTROY_OBJ destroy_object
#endif

extern "C"{
    PLUGIN_EXPORT void* DYN_CREATE_OBJ();
    PLUGIN_EXPORT void DYN_DESTROY_OBJ(void* o);
}

#endif
