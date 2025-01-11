#ifndef SWAY_RMS_GLSLRESOURCEMANAGER_HPP
#define SWAY_RMS_GLSLRESOURCEMANAGER_HPP

#include <sway/core.hpp>
#include <sway/rms/imageresourceprovider.hpp>
#include <sway/rms/prereqs.hpp>
#include <sway/rms/resourcemanager.hpp>

namespace sway::rms {

class GLSLResourceManager : public ResourceManager<GLSLResource> {
public:
  GLSLResourceManager() = default;

  ~GLSLResourceManager() = default;

  void fetchData(const std::string &name, const std::string &filename);

  auto getResourceByName(const std::string &name) -> std::shared_ptr<GLSLResource> {
    return ResourceManager<GLSLResource>::findLoadedResource(name);
  }
};

}  // namespace sway::rms

#endif  // SWAY_RMS_GLSLRESOURCEMANAGER_HPP
