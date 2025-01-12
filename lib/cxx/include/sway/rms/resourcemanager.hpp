#ifndef SWAY_RMS_RESOURCEMANAGER_HPP
#define SWAY_RMS_RESOURCEMANAGER_HPP

#include <sway/core.hpp>
#include <sway/rms/_stdafx.hpp>
#include <sway/rms/imageresourceprovider.hpp>

namespace sway::rms {

template <class RESOURCE>
using ResourceMap_t = std::map<std::string, std::shared_ptr<RESOURCE>>;

template <class RESOURCE>
class ResourceManager {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  ResourceManager() = default;

  ~ResourceManager() { resources_.clear(); }

  /** @} */
#pragma endregion

  auto findLoadedResource(const std::string &name) -> std::shared_ptr<RESOURCE> {
    auto iter = resources_.find(name);
    if (iter == resources_.end()) {
      return nullptr;
    }

    return iter->second;
  }

  void registerResource(const std::string &name, std::shared_ptr<RESOURCE> res) {
    resources_.insert(std::make_pair(name, res));
  }

  void unregisterResource(std::shared_ptr<RESOURCE> res) {
    const std::string name = res->getUid().value();

    auto iter = resources_.find(name);
    if (iter != resources_.end() && iter->second == res) {
      resources_.erase(iter);
    }
  }

private:
  ResourceMap_t<RESOURCE> resources_;
};

}  // namespace sway::rms

#endif  // SWAY_RMS_RESOURCEMANAGER_HPP
