#ifndef SWAY_RMS_REMOTEFILE_HPP
#define SWAY_RMS_REMOTEFILE_HPP

#include <sway/core.hpp>
#include <sway/rms/_stdafx.hpp>

namespace sway::rms {

#if EMSCRIPTEN_PLATFORM
using fetch_res_t = emscripten_fetch_t *;
#else
struct FetchRes {
  lpcstr_t url;
  u32_t status;
  void *userData;
  lpcstr_t data;
  u32_t numBytes;
  u32_t totalBytes;
};

using fetch_res_t = FetchRes *;
#endif

struct FetchUserData {
  std::function<void(const u8_t *, u32_t)> callback;
  std::vector<u8_t> data;
};

class RemoteFile {
public:
  static void fetchFail(fetch_res_t fetch) {
    printf("Downloading %s failed, HTTP failure status code: %d.\n", fetch->url, fetch->status);

    auto *userData = reinterpret_cast<FetchUserData *>(fetch->userData);
    if (userData) {
      if (userData->callback) {
        userData->callback(nullptr, 0);
      }

      delete userData;
    }

#if EMSCRIPTEN_PLATFORM
    emscripten_fetch_close(fetch);
#endif
  }

  static void fetchSuccess(fetch_res_t fetch) {
    printf(
        "Finished downloading %llu bytes from URL %s.\n", static_cast<unsigned long long>(fetch->numBytes), fetch->url);

    auto *userData = reinterpret_cast<FetchUserData *>(fetch->userData);
    if (userData) {
      const auto numBytes = static_cast<u32_t>(fetch->numBytes);
      userData->data.assign(
          reinterpret_cast<const u8_t *>(fetch->data), reinterpret_cast<const u8_t *>(fetch->data) + numBytes);

      if (userData->callback) {
        userData->callback(userData->data.data(), userData->data.size());
      }

      delete userData;
    }

#if EMSCRIPTEN_PLATFORM
    emscripten_fetch_close(fetch);
#endif
  }

  static fetch_res_t fetch(lpcstr_t url, std::function<void(const u8_t *, u32_t)> onResult) {
    auto userData = std::make_unique<FetchUserData>();
    userData->callback = std::move(onResult);

#if EMSCRIPTEN_PLATFORM

    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    std::strncpy(attr.requestMethod, "GET", sizeof(attr.requestMethod) - 1);
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY | EMSCRIPTEN_FETCH_REPLACE;
    attr.onsuccess = fetchSuccess;
    attr.onerror = fetchFail;
    attr.userData = userData.release();  // Владение переходит в колбэк.
    return emscripten_fetch(&attr, url);

#else

    std::ifstream strm(url, std::ios::binary);
    if (!strm.is_open()) {
      if (userData->callback) {
        userData->callback(nullptr, 0);
      }

      return nullptr;
    }

    std::vector<u8_t> buf((std::istreambuf_iterator<char>(strm)), std::istreambuf_iterator<char>());
    if (userData->callback) {
      userData->callback(buf.data(), static_cast<u32_t>(buf.size()));
    }

    return nullptr;

#endif
  }
};

}  // namespace sway::rms

#endif  // SWAY_RMS_REMOTEFILE_HPP
