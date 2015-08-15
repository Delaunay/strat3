#ifndef PLUGIN_LIBRARY_HEADER
#define PLUGIN_LIBRARY_HEADER

#ifdef __linux__
#   define DLLEXP
#else
#   define DLLEXP __declspec(dllexport)
#endif

extern "C"{
    DLLEXP void* create_object();
    DLLEXP void destroy_object(void* o);
}

#endif

