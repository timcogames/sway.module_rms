#ifndef SWAY_RMS_GLSLRESOURCE_HPP
#define SWAY_RMS_GLSLRESOURCE_HPP

#include <sway/core.hpp>
#include <sway/loader.hpp>
#include <sway/rms/fetchable.hpp>
#include <sway/rms/resource.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

class GLSLResourceManager;

class GLSLResource : public Resource, public Fetchable {
public:
  GLSLResource(GLSLResourceManager *mngr);

  virtual ~GLSLResource() = default;

  MTHD_OVERRIDE(void onLoadAsync(void *args, void *data, int size));

  MTHD_OVERRIDE(void onLoadAsyncFailed(void *arg));

  void load(const std::string &filename);

public:
  GLSLResourceManager *mngr_;
  std::string content_;
};

NAMESPACE_END(rms)
NAMESPACE_END(sway)

#endif  // SWAY_RMS_GLSLRESOURCE_HPP
