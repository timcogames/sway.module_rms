#include <sway/rms/fetchable.hpp>
#include <sway/rms/glslresource.hpp>
#include <sway/rms/glslresourcemanager.hpp>

#include <functional>  // std::ref
#include <future>  // std::async
#include <iostream>

#if EMSCRIPTEN_PLATFORM
#  include <emscripten/wget.h>  // emscripten_async_wget_data
#endif

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

auto dataToChar(void *data, int size) -> char * {
  char *tmp = new char[size + 1];
  memcpy(tmp, data, size * sizeof(char));
  tmp[size] = '\0';

  return tmp;
}

GLSLResource::GLSLResource(GLSLResourceManager *mngr)
    : mngr_(mngr) {}

void GLSLResource::onLoadAsync(void *args, void *data, int size) {
  content_ = std::string(dataToChar(data, size));
  loadingDone_.store(true, std::memory_order_relaxed);
}

void GLSLResource::onLoadAsyncFailed(void *arg) {
  // emscripten_log(EM_LOG_ERROR, "Failed to load file");
  // emscripten_cancel_main_loop();
}

void GLSLResource::fetchAsyncDataFromFile(const std::string &filename) {

#if EMSCRIPTEN_PLATFORM

  auto *dataPack = new FileAccessDataPack();
  dataPack->load =
      std::bind(&GLSLResource::onLoadAsync, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
  dataPack->fail = std::bind(&GLSLResource::onLoadAsyncFailed, this, std::placeholders::_1);
  dataPack->args = nullptr;
  fetchAsyncData(filename.c_str(), dataPack);

#else

  std::ifstream stream(filename, std::ios::binary);
  if (!stream.is_open()) {
    return;
  }

  std::string source((std::istreambuf_iterator<s8_t>(stream)), std::istreambuf_iterator<s8_t>());
  stream.close();

  if (source.length() == 0) {
    return;
  }

  content_ = source;

#endif
}

NAMESPACE_END(rms)
NAMESPACE_END(sway)
