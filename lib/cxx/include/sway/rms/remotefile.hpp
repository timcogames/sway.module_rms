#ifndef SWAY_RMS_REMOTEFILE_HPP
#define SWAY_RMS_REMOTEFILE_HPP

#include <sway/core.hpp>

#if EMSCRIPTEN_PLATFORM
#  include <emscripten/fetch.h>
#endif

#include <functional>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

#if EMSCRIPTEN_PLATFORM
using fetch_res_t = emscripten_fetch_t *;
#else
struct FetchRes {
  lpcstr_t url;
  u32_t status;
  void *userData;
  lpcstr_t data;
  u32_t numBytes;
};

using fetch_res_t = FetchRes *;
#endif

class RemoteFile {
public:
  static void fetchFail(fetch_res_t fetch) {
    printf("Downloading %s failed, HTTP failure status code: %d.\n", fetch->url, fetch->status);

#if EMSCRIPTEN_PLATFORM
    emscripten_fetch_close(fetch);
#endif
  }

  static void fetchSuccess(fetch_res_t fetch) {
    auto callbackFn = reinterpret_cast<std::function<void(fetch_res_t)> *>(fetch->userData);
    (*callbackFn)(fetch);

    SAFE_DELETE_OBJECT(callbackFn);

#if EMSCRIPTEN_PLATFORM
    emscripten_fetch_close(fetch);
#endif
  }

  static void fetch(lpcstr_t url, std::function<void(fetch_res_t)> onSuccess) {
    auto userdata = new std::function(onSuccess);

#if EMSCRIPTEN_PLATFORM

    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "GET");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = fetchSuccess;
    attr.onerror = fetchFail;
    attr.userData = userdata;

    emscripten_fetch(&attr, url);

#endif
  }
};

NAMESPACE_END(rms)
NAMESPACE_END(sway)

#endif  // SWAY_RMS_REMOTEFILE_HPP
