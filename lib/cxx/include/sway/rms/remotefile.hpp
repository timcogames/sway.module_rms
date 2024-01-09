#ifndef SWAY_RMS_REMOTEFILE_HPP
#define SWAY_RMS_REMOTEFILE_HPP

#include <sway/core.hpp>

#if EMSCRIPTEN_PLATFORM
#  include <emscripten/fetch.h>
#  include <functional>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

class RemoteFile {
public:
  static void fetchFail(emscripten_fetch_t *fetch) {
    printf("Downloading %s failed, HTTP failure status code: %d.\n", fetch->url, fetch->status);
    emscripten_fetch_close(fetch);
  }

  static void fetchSuccess(emscripten_fetch_t *fetch) {
    auto callbackFn = reinterpret_cast<std::function<void(emscripten_fetch_t *)> *>(fetch->userData);
    (*callbackFn)(fetch);

    SAFE_DELETE_OBJECT(callbackFn);
    emscripten_fetch_close(fetch);
  }

  static void fetch(lpcstr_t url, std::function<void(emscripten_fetch_t *)> onSuccess) {
    auto userdata = new std::function(onSuccess);

    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "GET");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = fetchSuccess;
    attr.onerror = fetchFail;
    attr.userData = userdata;

    emscripten_fetch(&attr, url);
  }
};

NAMESPACE_END(rms)
NAMESPACE_END(sway)

#endif  // EMSCRIPTEN_PLATFORM

#endif  // SWAY_RMS_REMOTEFILE_HPP
