#ifndef SWAY_RMS_FETCHABLE_HPP
#define SWAY_RMS_FETCHABLE_HPP

#include <sway/core.hpp>

#if EMSCRIPTEN_PLATFORM
#  include <emscripten/wget.h>  // emscripten_async_wget_data
#endif

#include <functional>
#include <string>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

struct FetcherJob {
  void *ctx;
};

struct FileAccessDataPack {
  std::function<void(void *, void *, int)> load;
  std::function<void(void *)> fail;
  void *args;
};

struct AsyncLoader {
  static void onDataRead(void *arg, void *data, int nbytes) {
    auto *dataPack = static_cast<FileAccessDataPack *>(arg);
    if (dataPack->load) {
      dataPack->load(dataPack->args, data, nbytes);
    }

    SAFE_DELETE_OBJECT(dataPack)
  }

  static void onReadFail(void *arg) {
    auto *dataPack = static_cast<FileAccessDataPack *>(arg);
    if (dataPack->fail) {
      dataPack->fail(arg);
    }

    SAFE_DELETE_OBJECT(dataPack)
  }
};

class Fetchable {
public:
  Fetchable() = default;

  virtual ~Fetchable() = default;

  PURE_VIRTUAL(void onLoadAsync(void *args, void *data, int size));

  PURE_VIRTUAL(void onLoadAsyncFailed(void *arg));

  void fetchAsyncData(const std::string &url, FileAccessDataPack *arg) {
#if EMSCRIPTEN_PLATFORM

    emscripten_async_wget_data(url.c_str(), arg, AsyncLoader::onDataRead, AsyncLoader::onReadFail);

#endif
  }
};

NAMESPACE_END(rms)
NAMESPACE_END(sway)

#endif  // SWAY_RMS_FETCHABLE_HPP
