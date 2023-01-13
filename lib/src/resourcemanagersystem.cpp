#include <sway/rms/imageresource.hpp>
#include <sway/rms/resourcemanagersystem.hpp>

#include <iostream>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

void ResourceManagerSystem::registerImageProvider(const std::string &plugname) {
  auto provider = std::make_shared<ImageResourceProvider>(plugname);
  auto info = provider->getInfo();

  std::cout << "Plugin Info: "
            << "\n\tname: " << info.name << "\n\tauthor: " << info.author << "\n\tdescription: " << info.description
            << "\n\turl: " << info.url << "\n\tlicense: " << info.license << "\n\tversion: " << info.version.getMajor()
            << std::endl;

  providers_.insert(std::make_pair(info.name, provider));
}

void ResourceManagerSystem::loadImage(const std::string &name, const std::string &filename) {
  auto resource = std::make_shared<ImageResource>(this);
  resource->setUid(name);
  resource->load(filename);
  ResourceManager<ImageResource>::registerResource(resource->getUid().value(), resource);
}

NAMESPACE_END(rms)
NAMESPACE_END(sway)
