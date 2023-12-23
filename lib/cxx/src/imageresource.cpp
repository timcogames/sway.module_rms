#include <sway/loader.hpp>
#include <sway/rms/imageresource.hpp>
#include <sway/rms/imageresourcemanager.hpp>

#include <functional>  // std::ref
#include <future>  // std::async
#include <iostream>

#if EMSCRIPTEN_PLATFORM
#  include <emscripten/wget.h>  // emscripten_async_wget_data
#endif

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

class InputReader {
public:
  InputReader(std::ifstream &stream)
      : stream_(stream) {}

  auto onDataRead(loader::ImageLoaderPlugin *plug) -> loader::ImageDescriptor {
    auto descriptor = plug->loadFromStream(stream_);
    return descriptor;
  }

private:
  std::ifstream &stream_;
};

ImageResource::ImageResource(ImageResourceManager *mngr)
    : mngr_(mngr) {}

void ImageResource::onLoadAsync(void *arg, void *data, int size) {
  provider_ = mngr_->getImageProvider("png");
  descriptor_ = provider_->getPlug()->loadFrom(data, size);
}

void ImageResource::onLoadAsyncFailed(void *arg) {
  // emscripten_log(EM_LOG_ERROR, "Failed to load file");
  // emscripten_cancel_main_loop();
}

void ImageResource::load(const std::string &filename, FileAccessDataPack *dataPack) {
  provider_ = mngr_->getImageProvider("png");

#if EMSCRIPTEN_PLATFORM

  fetchAsyncData(filename.c_str(), dataPack);

#else

  std::ifstream stream(filename);
  if (stream.is_open()) {
    auto reader = std::make_unique<InputReader>(stream);
    auto future = std::async(std::launch::async, &InputReader::onDataRead, reader.get(), provider_->getPlug());

    if (future.valid()) {
      descriptor_ = future.get();
    }
  }

#endif
}

NAMESPACE_END(rms)
NAMESPACE_END(sway)
