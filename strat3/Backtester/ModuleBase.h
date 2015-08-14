

// for checks
extern "C" const int* module_version();
extern "C" const int* strat3_version();
extern "C" const char* module_name();

// how to create your object
extern "C" void* create_object();
extern "C" void destroy_obbject(void *);

