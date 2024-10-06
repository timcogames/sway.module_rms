#ifndef SWAY_RMS_GLSLRESOURCEMANAGER_HPP
#define SWAY_RMS_GLSLRESOURCEMANAGER_HPP

#include <sway/core.hpp>
#include <sway/rms/imageresourceprovider.hpp>
#include <sway/rms/resourcemanager.hpp>

#include <map>
#include <memory>
#include <string>

NS_BEGIN_SWAY()
NS_BEGIN(rms)

class GLSLResourceManager : public ResourceManager<GLSLResource> {
public:
  GLSLResourceManager() = default;

  ~GLSLResourceManager() = default;

  void fetchData(const std::string &name, const std::string &filename);

  auto getResourceByName(const std::string &name) -> std::shared_ptr<GLSLResource> {
    return ResourceManager<GLSLResource>::findLoadedResource(name);
  }
};

NS_END()  // namespace rms
NS_END()  // namespace sway

#endif  // SWAY_RMS_GLSLRESOURCEMANAGER_HPP
