#ifndef SWAY_RMS_RESOURCEMANAGERSYSTEM_HPP
#define SWAY_RMS_RESOURCEMANAGERSYSTEM_HPP

#include <sway/core.hpp>
#include <sway/rms/imageresourceprovider.hpp>
#include <sway/rms/resourcemanager.hpp>

#include <map>
#include <memory>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

class ResourceManagerSystem : public ResourceManager<ImageResource> {
public:
  ResourceManagerSystem() = default;

  ~ResourceManagerSystem() = default;

  void registerImageProvider(const std::string &plugname);

  auto getImageProvider(const std::string &name) -> std::shared_ptr<ImageResourceProvider> { return providers_[name]; }

  void loadImage(const std::string &name, const std::string &filename);

  auto getImageResourceByName(const std::string &name) -> std::shared_ptr<ImageResource> {
    return ResourceManager<ImageResource>::findLoadedResource(name);
  }

private:
  std::map<std::string, std::shared_ptr<ImageResourceProvider>> providers_;
};

NAMESPACE_END(rms)
NAMESPACE_END(sway)

#endif  // SWAY_RMS_RESOURCEMANAGERSYSTEM_HPP
