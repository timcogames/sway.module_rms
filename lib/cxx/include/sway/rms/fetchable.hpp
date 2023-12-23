#ifndef SWAY_RMS_FETCHABLE_HPP
#define SWAY_RMS_FETCHABLE_HPP

#include <sway/core.hpp>

#if EMSCRIPTEN_PLATFORM
#  include <emscripten/wget.h>  // emscripten_async_wget_data
#endif

#include <string>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

struct FetcherJob {
  void *ctx;
};

typedef void (*LOAD_CALLBACK)(void *, int);
typedef void (*FAIL_CALLBACK)(void *);

struct FileAccessDataPack {
  LOAD_CALLBACK load;
  FAIL_CALLBACK fail;
  void *args;
};

struct AsyncLoader {
  // LOAD_CALLBACK load;
  // FAIL_CALLBACK fail;

  static void onDataRead(void *arg, void *data, int nbytes) {
    auto *dataPack = static_cast<FileAccessDataPack *>(arg);
    dataPack->load(data, nbytes);
    SAFE_DELETE_OBJECT(dataPack)
  }

  static void onReadFail(void *arg) {
    auto *dataPack = static_cast<FileAccessDataPack *>(arg);
    dataPack->fail(arg);
    SAFE_DELETE_OBJECT(dataPack)
  }
};

class Fetchable {
public:
  Fetchable() = default;

  DFLT_DTOR_VIRTUAL(Fetchable);

  PURE_VIRTUAL(void onLoadAsync(void *arg, void *data, int size));

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
