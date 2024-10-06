#include <sway/rms/imageresourceprovider.hpp>

#include <iostream>

NS_BEGIN_SWAY()
NS_BEGIN(rms)

ImageResourceProvider::ImageResourceProvider(const std::string &plugname) {
  try {
    plug_ = new core::Plugin(core::generic::io::Path(plugname), RTLD_NOW);
    auto callbackFunc = plug_->getMethod<PluginGetDescriptorFunc_t>("pluginGetLoader");
    instance_ = callbackFunc.call();
  } catch (const std::exception &err) {
    std::cout << err.what() << std::endl;
  }
}

ImageResourceProvider::~ImageResourceProvider() { SAFE_DELETE_OBJECT(plug_); };

NS_END()  // namespace rms
NS_END()  // namespace sway
