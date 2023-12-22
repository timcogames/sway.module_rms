#include <sway/rms/imageresource.hpp>
#include <sway/rms/imageresourcemanager.hpp>

#include <iostream>  // std::cout

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

void ImageResourceManager::registerImageProvider(const std::string &plugname) {
  auto provider = std::make_shared<ImageResourceProvider>(plugname);
  auto info = provider->getInfo();

  providers_.insert(std::make_pair(info.name, provider));
}

void ImageResourceManager::loadImage(const std::string &name, const std::string &filename) {
  auto resource = std::make_shared<ImageResource>(this);
  resource->setUid(name);
  // resource->fetchAsyncData<ImageResource>(filename, resource->resourceData_);
  resource->load(filename);
  ResourceManager<ImageResource>::registerResource(resource->getUid().value(), resource);
}

NAMESPACE_END(rms)
NAMESPACE_END(sway)
