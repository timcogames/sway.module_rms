#ifndef SWAY_RMS_RESOURCEMANAGER_HPP
#define SWAY_RMS_RESOURCEMANAGER_HPP

#include <sway/core.hpp>
#include <sway/rms/imageresourceprovider.hpp>

#include <map>
#include <memory>
#include <string>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

template <class TResource>
using ResourceMap_t = std::map<std::string, std::shared_ptr<TResource>>;

template <class TResource>
class ResourceManager {
public:
  ResourceManager() = default;

  ~ResourceManager() { resources_.clear(); }

  auto findLoadedResource(const std::string &name) -> std::shared_ptr<TResource> {
    auto iter = resources_.find(name);
    if (iter == resources_.end()) {
      return nullptr;
    }

    return iter->second;
  }

  void registerResource(const std::string &name, std::shared_ptr<TResource> resource) {
    resources_.insert(std::make_pair(name, resource));
  }

  void unregisterResource(std::shared_ptr<TResource> resource) {
    const std::string name = resource->getUid().value();

    auto iter = resources_.find(name);
    if (iter != resources_.end() && iter->second == resource) {
      resources_.erase(iter);
    }
  }

private:
  ResourceMap_t<TResource> resources_;
};

NAMESPACE_END(rms)
NAMESPACE_END(sway)

#endif  // SWAY_RMS_RESOURCEMANAGER_HPP
