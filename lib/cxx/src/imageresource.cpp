#include <sway/rms/imageresource.hpp>
#include <sway/rms/imageresourcemanager.hpp>

#include <iostream>

#if EMSCRIPTEN_PLATFORM
#  include <emscripten/wget.h>  // emscripten_async_wget_data
#endif

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

ImageResource::ImageResource(ImageResourceManager *mngr)
    : mngr_(mngr) {
  resourceData_ = new ImageResourceData();
  resourceData_->ctx = (void *)this;
}

void ImageResource::onLoadAsync(void *arg, void *data, int size) {
  provider_ = mngr_->getImageProvider("png");
  descriptor_ = provider_->getPlug()->loadFrom(data, size);
}

void ImageResource::onLoadAsyncFailed(void *arg) {
  // emscripten_log(EM_LOG_ERROR, "Failed to load file");
  // emscripten_cancel_main_loop();
}

void ImageResource::load(const std::string &filename) {
  provider_ = mngr_->getImageProvider("png");

#if EMSCRIPTEN_PLATFORM

  // clang-format off
  emscripten_async_wget_data(filename.c_str(), this, [](void *arg, void *buffer, int size) -> void {
    auto *resourcePtr = (ImageResource *)arg;
    resourcePtr->descriptor_ = resourcePtr->provider_->getPlug()->loadFrom(buffer, size);
  }, [](void *arg) -> void {});
  // clang-format on

#else

  std::ifstream stream(filename);
  if (stream.is_open()) {
    auto *plug = provider_->getPlug();
    assert(plug);

    descriptor_ = plug->loadFromStream(stream);
  }

#endif
}

NAMESPACE_END(rms)
NAMESPACE_END(sway)
