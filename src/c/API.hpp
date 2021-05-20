// https://github.com/Archzenvald/Shido
// MIT license (see LICENSE, src/c/core.h or src/lua/core.lua)

// API helper.
#ifndef HPP_SHIDO_API
#define HPP_SHIDO_API

#include <memory>
#include <unordered_map>

// Generate ref handle implementation.
#define SHIDO_HANDLE_HPP(T) struct shido_ ## T ## Ref{ std::shared_ptr<shido_ ## T> ref; };
#define SHIDO_HANDLE_CPP(T)  \
  shido_ ## T ## Ref* shido_ ## T ## Ref ## _new(shido_ ## T ## Ref *self) \
  { return new shido_ ## T ## Ref{self->ref}; } \
  shido_ ## T* shido_ ## T ## Ref ## _ptr(shido_ ## T ## Ref *self) \
  { return self->ref.get(); } \
  void shido_ ## T ## Ref ## _free(shido_ ## T ## Ref *self) \
  { delete self; }

namespace shido{

// Registry.
// Used to map internal third-party API resources to reference handles (weakly).
template<typename K, typename H>
struct Registry{
  void reg(const K& k, const H *handle){ map[k] = handle->ref; }
  void unreg(const K& k){ map.erase(k); }
  // Get new reference handle (can be NULL).
  H* get(const K& k)
  {
    auto it = map.find(k);
    if(it != map.end()){
      decltype(H::ref) ref = it->second.lock();
      if(ref) return new H{ref};
    }
    return nullptr;
  }

  std::unordered_map<K, std::weak_ptr<typename decltype(H::ref)::element_type> > map;
};

}

#endif
