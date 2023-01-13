#ifndef SWAY_RMS_IMAGERESOURCE_HPP
#define SWAY_RMS_IMAGERESOURCE_HPP

#include <sway/core.hpp>
#include <sway/loader.hpp>
#include <sway/rms/resource.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

class ResourceManagerSystem;

class ImageResource : public Resource {
public:
  ImageResource(ResourceManagerSystem *system);

  virtual ~ImageResource() = default;

  void load(const std::string &filename);

  auto getDescriptor() -> loader::ImageDescriptor { return descriptor_; }

private:
  ResourceManagerSystem *system_;
  loader::ImageDescriptor descriptor_;
};

NAMESPACE_END(rms)
NAMESPACE_END(sway)

#endif  // SWAY_RMS_IMAGERESOURCE_HPP
