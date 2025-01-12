#ifndef SWAY_RMS_GLSLRESOURCE_HPP
#define SWAY_RMS_GLSLRESOURCE_HPP

#include <sway/core.hpp>
#include <sway/loader.hpp>
#include <sway/rms/_stdafx.hpp>
#include <sway/rms/fetchable.hpp>
#include <sway/rms/resource.hpp>

namespace sway::rms {

class GLSLResourceManager;

class GLSLResource : public Resource, public Fetchable {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  GLSLResource(GLSLResourceManager *mngr);

  virtual ~GLSLResource() = default;

  /** @} */
#pragma endregion

  MTHD_OVERRIDE(void onLoadAsync(void *args, void *data, int size));

  MTHD_OVERRIDE(void onLoadAsyncFailed(void *arg));

  void fetchAsyncDataFromFile(const std::string &filename);

public:
  GLSLResourceManager *mngr_;
  std::string content_;
};

}  // namespace sway::rms

#endif  // SWAY_RMS_GLSLRESOURCE_HPP
