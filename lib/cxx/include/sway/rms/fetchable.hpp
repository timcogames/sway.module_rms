#ifndef SWAY_RMS_FETCHABLE_HPP
#define SWAY_RMS_FETCHABLE_HPP

#include <sway/core.hpp>
#include <sway/rms/_stdafx.hpp>

namespace sway::rms {

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
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  Fetchable() = default;

  virtual ~Fetchable() = default;

  /** @} */
#pragma endregion

#pragma region "Pure virtual methods"
  /** \~english @name Pure virtual methods */ /** \~russian @name Чисто виртуальные методы */
  /** @{ */

  virtual void onLoadAsync(void *args, void *data, int size) = 0;

  virtual void onLoadAsyncFailed(void *arg) = 0;

  /** @} */
#pragma endregion

  void fetchAsyncData(const std::string &url, FileAccessDataPack *arg) {
#if EMSCRIPTEN_PLATFORM

    emscripten_async_wget_data(url.c_str(), arg, AsyncLoader::onDataRead, AsyncLoader::onReadFail);

#endif
  }
};

}  // namespace sway::rms

#endif  // SWAY_RMS_FETCHABLE_HPP
