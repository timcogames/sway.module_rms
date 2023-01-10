#ifndef SWAY_RMS_RESOURCEPROVIDER_HPP
#define SWAY_RMS_RESOURCEPROVIDER_HPP

#include <sway/core.hpp>
#include <sway/loader.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

using PluginInstance_t = loader::LoaderPluginDescriptor<loader::ImageLoaderPlugin>;
using PluginGetDescriptorFunc_t = core::binding::TFunction<PluginInstance_t()>;

class ResourceProvider {
public:
  ResourceProvider();

  ~ResourceProvider();

  [[nodiscard]] core::PluginInfo getInfo() const { return plug_->getInfo(); }

  [[nodiscard]] loader::ImageLoaderPlugin *getPlug() const { return instance_.plug(); }

private:
  core::Plugin *plug_;
  PluginInstance_t instance_;
};

NAMESPACE_END(rms)
NAMESPACE_END(sway)

#endif  // SWAY_RMS_RESOURCEPROVIDER_HPP
