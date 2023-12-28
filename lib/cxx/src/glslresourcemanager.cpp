#include <sway/rms/glslresource.hpp>
#include <sway/rms/glslresourcemanager.hpp>

#include <iostream>  // std::cout

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

void GLSLResourceManager::fetchData(const std::string &name, const std::string &filename) {
  auto resource = std::make_shared<GLSLResource>(this);
  resource->setUid(name);
  resource->fetchAsyncDataFromFile(filename);

  ResourceManager<GLSLResource>::registerResource(resource->getUid().value(), resource);
}

NAMESPACE_END(rms)
NAMESPACE_END(sway)
