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

class Fetchable {
public:
  Fetchable() {}

  virtual ~Fetchable() = default;

  PURE_VIRTUAL(void onLoadAsync(void *arg, void *data, int size));

  PURE_VIRTUAL(void onLoadAsyncFailed(void *arg));

  template <typename T>
  static void handleLoadAsync(void *arg, void *data, int nbytes) {
    auto *self = static_cast<FetcherJob *>(arg);
    auto *ctx = static_cast<T *>(self->ctx);
    ctx->onLoadAsync(self, data, nbytes);
  }

  template <typename T>
  static void handleLoadAsyncFailed(void *arg) {
    auto *self = static_cast<FetcherJob *>(arg);
    auto *ctx = static_cast<T *>(self->ctx);
    ctx->onLoadAsyncFailed(arg);
  }

  template <typename T>
  void fetchAsyncData(const std::string &url, void *arg) {
#if EMSCRIPTEN_PLATFORM
    emscripten_async_wget_data(url.c_str(), arg, handleLoadAsync<T>, handleLoadAsyncFailed<T>);
#endif
  }
};

NAMESPACE_END(rms)
NAMESPACE_END(sway)

#endif  // SWAY_RMS_FETCHABLE_HPP
