#include <sway/rms/glslresource.hpp>
#include <sway/rms/glslresourcemanager.hpp>

#include <iostream>  // std::cout

NS_BEGIN_SWAY()
NS_BEGIN(rms)

void GLSLResourceManager::fetchData(const std::string &name, const std::string &filename) {
  auto resource = std::make_shared<GLSLResource>(this);
  resource->setUid(name);
  resource->fetchAsyncDataFromFile(filename);

  ResourceManager<GLSLResource>::registerResource(resource->getUid().value(), resource);
}

NS_END()  // namespace rms
NS_END()  // namespace sway
