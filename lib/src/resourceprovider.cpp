#include <sway/rms/resourceprovider.hpp>

#include <iostream>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

ResourceProvider::ResourceProvider() {
  try {
    plug_ = new core::Plugin(core::generic::io::Path(
        "/Users/apriori85/Documents/Projects/sway.module_rms/bin/module_loader_png.dylib.0.1.0"));
    core::PluginInfo const info = plug_->getInfo();
    std::cout << "Plugin name: " << info.name << std::endl;
  } catch (const std::exception &err) {
    std::cout << err.what() << std::endl;
  }
}

ResourceProvider::~ResourceProvider() { SAFE_DELETE_OBJECT(plug_); };

NAMESPACE_END(rms)
NAMESPACE_END(sway)
