#include <sway/rms/imageresourceprovider.hpp>

namespace sway::rms {

ImageResourceProvider::ImageResourceProvider(const std::string &plugname) {
  try {
    plug_ = new core::Plugin(core::Path(plugname), RTLD_NOW);
    auto callbackFunc = plug_->getMethod<PluginGetDescriptorFunc_t>("pluginGetLoader");
    instance_ = callbackFunc.call();
  } catch (const std::exception &err) {
    std::cout << err.what() << std::endl;
  }
}

ImageResourceProvider::~ImageResourceProvider() { core::safeDelete<core::Plugin>(plug_); };

}  // namespace sway::rms
