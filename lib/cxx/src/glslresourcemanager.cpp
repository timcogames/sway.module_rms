#include <sway/rms/glslresource.hpp>
#include <sway/rms/glslresourcemanager.hpp>

namespace sway::rms {

void GLSLResourceManager::fetchData(const std::string &name, const std::string &filename) {
  auto resource = std::make_shared<GLSLResource>(this);
  resource->setUniqueId(name);
  resource->fetchAsyncDataFromFile(filename);

  ResourceManager<GLSLResource>::registerResource(resource->getUniqueId().value(), resource);
}

}  // namespace sway::rms
