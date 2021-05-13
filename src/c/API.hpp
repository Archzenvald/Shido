// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

// API helper.
#ifndef HPP_SHIDO_API
#define HPP_SHIDO_API

#include <memory>

// Generate ref handle implementation.
#define SHIDO_HANDLE_HPP(T) struct shido_ ## T ## Ref{ std::shared_ptr<shido_ ## T> ref; };
#define SHIDO_HANDLE_CPP(T)  \
  shido_ ## T ## Ref* shido_ ## T ## Ref ## _new(shido_ ## T ## Ref *self) \
  { return new shido_ ## T ## Ref{self->ref}; } \
  shido_ ## T* shido_ ## T ## Ref ## _ptr(shido_ ## T ## Ref *self) \
  { return self->ref.get(); } \
  void shido_ ## T ## Ref ## _free(shido_ ## T ## Ref *self) \
  { delete self; }

#endif
