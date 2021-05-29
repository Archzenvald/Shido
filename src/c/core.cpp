// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

#include "core.hpp"

namespace shido{

thread_local std::string _error;
void error(const std::string& err){ _error = err; }
const std::string& getError(){ return _error; }

void warning(const std::string& warn)
{
  std::cerr << "[shido] " << warn << std::endl;
}

Core::Core()
{
  ok = (SDL_Init(0) == 0);
  if(!ok)
    err = std::string("SDL: ")+SDL_GetError();
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

} // namespace shido

void shido_core_error(const char* err){ shido::error(err); }
const char* shido_core_getError(){ return shido::getError().c_str(); }
void shido_core_warning(const char* warn){ shido::warning(warn); }

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
  shido::Core &state = shido::Core::get();
  if(!state.ok)
    shido::error(state.err);
  return state.ok;
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
