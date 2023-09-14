#include <sway/rms/imageresource.hpp>
#include <sway/rms/imageresourcemanager.hpp>

#include <iostream>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

ImageResource::ImageResource(ImageResourceManager *mngr)
    : mngr_(mngr) {}

void ImageResource::load(const std::string &filename) {
  auto provider = mngr_->getImageProvider("png");

  std::ifstream file(filename);
  if (file.is_open()) {
    descriptor_ = provider->getPlug()->loadFromStream(file);
  }
}

NAMESPACE_END(rms)
NAMESPACE_END(sway)
