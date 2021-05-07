#ifndef H_SHIDO_API
#define H_SHIDO_API

#ifdef _WIN32
  #define API __declspec(dllexport)
#else
  #define API __attribute__((visibility("default")))
#endif

#endif
