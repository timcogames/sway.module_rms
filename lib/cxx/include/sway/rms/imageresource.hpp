#ifndef SWAY_RMS_IMAGERESOURCE_HPP
#define SWAY_RMS_IMAGERESOURCE_HPP

#include <sway/core.hpp>
#include <sway/loader.hpp>
#include <sway/rms/fetchable.hpp>
#include <sway/rms/imageresourceprovider.hpp>
#include <sway/rms/resource.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

struct ImageResourceData : public FetcherJob {};

class ImageResourceManager;

class ImageResource : public Resource, public Fetchable {
public:
  ImageResource(ImageResourceManager *mngr);

  virtual ~ImageResource() = default;

  MTHD_OVERRIDE(void onLoadAsync(void *arg, void *data, int size));

  MTHD_OVERRIDE(void onLoadAsyncFailed(void *arg));

  void load(const std::string &filename, FileAccessDataPack *dataPack);

  auto getDescriptor() -> loader::ImageDescriptor { return descriptor_; }

public:
  ImageResourceManager *mngr_;
  std::shared_ptr<ImageResourceProvider> provider_;
  loader::ImageDescriptor descriptor_;
};

NAMESPACE_END(rms)
NAMESPACE_END(sway)

#endif  // SWAY_RMS_IMAGERESOURCE_HPP
