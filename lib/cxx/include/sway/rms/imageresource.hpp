#ifndef SWAY_RMS_IMAGERESOURCE_HPP
#define SWAY_RMS_IMAGERESOURCE_HPP

#include <sway/core.hpp>
#include <sway/loader.hpp>
#include <sway/rms/fetchable.hpp>
#include <sway/rms/imageresourceprovider.hpp>
#include <sway/rms/prereqs.hpp>
#include <sway/rms/resource.hpp>

namespace sway::rms {

struct ImageResourceData : public FetcherJob {};

class ImageResourceManager;

class ImageResource : public Resource, public Fetchable {
public:
  ImageResource(ImageResourceManager *mngr);

  virtual ~ImageResource() = default;

  MTHD_OVERRIDE(void onLoadAsync(void *args, void *data, int size));

  MTHD_OVERRIDE(void onLoadAsyncFailed(void *arg));

  void fetchAsyncDataFromFile(const std::string &filename);

  auto getDescriptor() -> loader::ImageDescriptor { return descriptor_; }

public:
  ImageResourceManager *mngr_;
  std::shared_ptr<ImageResourceProvider> provider_;
  loader::ImageDescriptor descriptor_;
};

}  // namespace sway::rms

#endif  // SWAY_RMS_IMAGERESOURCE_HPP
