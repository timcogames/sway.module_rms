#include <sway/rms/imageresource.hpp>
#include <sway/rms/imageresourcemanager.hpp>

#include <iostream>  // std::cout

NS_BEGIN_SWAY()
NS_BEGIN(rms)

void ImageResourceManager::registerImageProvider(const std::string &plugname) {
  auto provider = std::make_shared<ImageResourceProvider>(plugname);
  auto info = provider->getInfo();

  providers_.insert(std::make_pair(info.name, provider));
}

void ImageResourceManager::fetchData(const std::string &name, const std::string &filename) {
  auto resource = std::make_shared<ImageResource>(this);
  resource->setUid(name);
  resource->fetchAsyncDataFromFile(filename);

  ResourceManager<ImageResource>::registerResource(resource->getUid().value(), resource);
}

NS_END()  // namespace rms
NS_END()  // namespace sway
