// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#include "core.hpp"

Core::Core()
{
  status = SDL_Init(0);
  if(status != 0)
    std::cerr << "[shido] SDL2 core init failed: " << SDL_GetError() << std::endl;
}

Core::~Core()
{
  SDL_Quit();
}

Core& Core::get()
{
  static Core core;
  return core;
}

const char* shido_core_getWorkingDirectory()
{
  const static utils::Path path = utils::Path::getCurrentDirectory();
  return path.c_str();
}

const char* shido_core_getExecutableDirectory()
{
  const static utils::Path path = utils::Path::getCurrentExecutable().getParent();
  return path.c_str();
}

bool shido_core_init()
{
  return Core::get().status;
}

// Time.

void shido_core_sleep(double time)
{
  SDL_Delay((unsigned int)(time*1000));
}

namespace{
#ifdef _WIN32
  LARGE_INTEGER getPerformanceFrequency()
  {
    LARGE_INTEGER v;
    QueryPerformanceFrequency(&v);
    return v;
  }
  LARGE_INTEGER getPerformanceCounter()
  {
    LARGE_INTEGER v;
    QueryPerformanceCounter(&v);
    return v;
  }
#else // Linux/POSIX
  timespec getTime()
  {
    timespec t;
#if _POSIX_TIMERS > 0 && defined(_POSIX_MONOTONIC_CLOCK)
    // monotonic clock type
#ifdef CLOCK_MONOTONIC_RAW
    clockid_t clock = CLOCK_MONOTONIC_RAW;
#else
    clockid_t clock = CLOCK_MONOTONIC;
#endif
    if(clock_gettime(clock, &t) == 0)
      return t;
#endif
    // fallback to to gettimeofday
    timeval tod;
    gettimeofday(&tod, NULL);
    t.tv_sec = tod.tv_sec;
    t.tv_nsec = tod.tv_usec*1000;
    return t;
  }
#endif
}

double shido_core_getTime()
{
#ifdef _WIN32
  static const LARGE_INTEGER freq = getPerformanceFrequency();
  static const LARGE_INTEGER start = getPerformanceCounter();
  LARGE_INTEGER time = getPerformanceCounter();
  time.QuadPart -= start.QuadPart;
  return (double)time.QuadPart/(double)freq.QuadPart;
#else // Linux/POSIX
  static const timespec start = getTime();
  timespec time = getTime();
  time.tv_sec -= start.tv_sec;
  time.tv_nsec -= start.tv_nsec;
  return (double)time.tv_sec+(double)time.tv_nsec*1.0e-9;
#endif
}
