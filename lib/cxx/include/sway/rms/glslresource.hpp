#ifndef SWAY_RMS_GLSLRESOURCE_HPP
#define SWAY_RMS_GLSLRESOURCE_HPP

#include <sway/core.hpp>
#include <sway/loader.hpp>
#include <sway/rms/fetchable.hpp>
#include <sway/rms/resource.hpp>

NS_BEGIN_SWAY()
NS_BEGIN(rms)

class GLSLResourceManager;

class GLSLResource : public Resource, public Fetchable {
public:
  GLSLResource(GLSLResourceManager *mngr);

  virtual ~GLSLResource() = default;

  MTHD_OVERRIDE(void onLoadAsync(void *args, void *data, int size));

  MTHD_OVERRIDE(void onLoadAsyncFailed(void *arg));

  void fetchAsyncDataFromFile(const std::string &filename);

public:
  GLSLResourceManager *mngr_;
  std::string content_;
};

NS_END()  // namespace rms
NS_END()  // namespace sway

#endif  // SWAY_RMS_GLSLRESOURCE_HPP
