#ifndef SWAY_RMS_RESOURCEMANAGER_HPP
#define SWAY_RMS_RESOURCEMANAGER_HPP

#include <sway/core.hpp>
#include <sway/rms/resourceprovider.hpp>

#include <map>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

class ResourceManager {
public:
  ResourceManager() = default;

  ~ResourceManager() = default;

  void registerProvider() {
    auto provider = std::make_shared<ResourceProvider>();
    auto info = provider->getInfo();

    std::cout << "Plugin Info: "
              << "\n\tname: " << info.name << "\n\tauthor: " << info.author << "\n\tdescription: " << info.description
              << "\n\turl: " << info.url << "\n\tlicense: " << info.license
              << "\n\tversion: " << info.version.getMajor() << std::endl;

    providers_.insert(std::make_pair(info.name, provider));
  }

  auto getProvider(const std::string &name) -> std::shared_ptr<ResourceProvider> { return providers_[name]; }

private:
  std::map<std::string, std::shared_ptr<ResourceProvider>> providers_;
};

NAMESPACE_END(rms)
NAMESPACE_END(sway)

#endif  // SWAY_RMS_RESOURCEMANAGER_HPP
