#include <sway/loader.hpp>
#include <sway/rms/resourceprovider.hpp>

#include <iostream>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

using PluginGetDescriptorFunc_t = core::binding::TFunction<loader::LoaderPluginDescriptor<loader::ImageLoaderPlugin>()>;

ResourceProvider::ResourceProvider() {
  try {
    plug_ = new core::Plugin(core::generic::io::Path(
        "/Users/apriori85/Documents/Projects/sway.module_rms/bin/module_loader_png.dylib.0.1.0"));
    core::PluginInfo const info = plug_->getInfo();
    auto instance = plug_->getMethod<PluginGetDescriptorFunc_t>("pluginGetLoader");

    std::cout << "Plugin: " << info.name << " " << instance().plug()->getText() << std::endl;
  } catch (const std::exception &err) {
    std::cout << err.what() << std::endl;
  }
}

ResourceProvider::~ResourceProvider() { SAFE_DELETE_OBJECT(plug_); };

NAMESPACE_END(rms)
NAMESPACE_END(sway)
