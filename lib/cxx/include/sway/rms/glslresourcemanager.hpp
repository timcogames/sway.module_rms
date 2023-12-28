#ifndef SWAY_RMS_GLSLRESOURCEMANAGER_HPP
#define SWAY_RMS_GLSLRESOURCEMANAGER_HPP

#include <sway/core.hpp>
#include <sway/rms/imageresourceprovider.hpp>
#include <sway/rms/resourcemanager.hpp>

#include <map>
#include <memory>
#include <string>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

class GLSLResourceManager : public ResourceManager<GLSLResource> {
public:
  GLSLResourceManager() = default;

  ~GLSLResourceManager() = default;

  void fetchData(const std::string &name, const std::string &filename);

  auto getResourceByName(const std::string &name) -> std::shared_ptr<GLSLResource> {
    return ResourceManager<GLSLResource>::findLoadedResource(name);
  }
};

NAMESPACE_END(rms)
NAMESPACE_END(sway)

#endif  // SWAY_RMS_GLSLRESOURCEMANAGER_HPP
