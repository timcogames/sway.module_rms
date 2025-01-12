#ifndef SWAY_RMS_GLSLRESOURCEMANAGER_HPP
#define SWAY_RMS_GLSLRESOURCEMANAGER_HPP

#include <sway/core.hpp>
#include <sway/rms/_stdafx.hpp>
#include <sway/rms/imageresourceprovider.hpp>
#include <sway/rms/resourcemanager.hpp>

namespace sway::rms {

class GLSLResourceManager : public ResourceManager<GLSLResource> {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  GLSLResourceManager() = default;

  ~GLSLResourceManager() = default;

  /** @} */
#pragma endregion

  void fetchData(const std::string &name, const std::string &filename);

  auto getResourceByName(const std::string &name) -> std::shared_ptr<GLSLResource> {
    return ResourceManager<GLSLResource>::findLoadedResource(name);
  }
};

}  // namespace sway::rms

#endif  // SWAY_RMS_GLSLRESOURCEMANAGER_HPP
