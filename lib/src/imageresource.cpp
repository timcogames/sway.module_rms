#include <sway/rms/imageresource.hpp>
#include <sway/rms/resourcemanagersystem.hpp>

#include <iostream>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

ImageResource::ImageResource(ResourceManagerSystem *system)
    : system_(system) {}

void ImageResource::load(const std::string &filename) {
  auto provider = system_->getImageProvider("png");

  std::ifstream file(filename);
  if (file.is_open()) {
    descriptor_ = provider->getPlug()->loadFromStream(file);
  }
}

NAMESPACE_END(rms)
NAMESPACE_END(sway)
