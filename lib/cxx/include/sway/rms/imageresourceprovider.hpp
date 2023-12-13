#ifndef SWAY_RMS_IMAGERESOURCEPROVIDER_HPP
#define SWAY_RMS_IMAGERESOURCEPROVIDER_HPP

#include <sway/core.hpp>
#include <sway/loader.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

using PluginInstance_t = loader::LoaderPluginDescriptor<loader::ImageLoaderPlugin>;
using PluginGetDescriptorFunc_t = core::binding::TFunction<PluginInstance_t()>;

class ImageResourceProvider {
public:
  ImageResourceProvider(const std::string &plugname);

  ~ImageResourceProvider();

  [[nodiscard]] auto getInfo() const -> core::PluginInfo { return plug_->getInfo(); }

  [[nodiscard]] auto getPlug() const -> loader::ImageLoaderPlugin * { return instance_.plug(); }

private:
  core::Plugin *plug_;
  PluginInstance_t instance_;
};

NAMESPACE_END(rms)
NAMESPACE_END(sway)

#endif  // SWAY_RMS_IMAGERESOURCEPROVIDER_HPP
