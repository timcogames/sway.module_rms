#ifndef SWAY_RMS_IMAGERESOURCEPROVIDER_HPP
#define SWAY_RMS_IMAGERESOURCEPROVIDER_HPP

#include <sway/core.hpp>
#include <sway/loader.hpp>

#include <string>

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

  [[nodiscard]] auto toStr() const -> std::string {
    auto info = plug_->getInfo();
    std::stringstream stream;
    // clang-format off
    stream << "Plugin information:"
           << "\n\tname: " << info.name
           << "\n\tauthor: " << info.author
           << "\n\tdescription: " << info.description
           << "\n\turl: " << info.url
           << "\n\tlicense: " << info.license
           << "\n\tversion: " << info.version.getMajor();
    // clang-format on
    return stream.str();
  }

private:
  core::Plugin *plug_;
  PluginInstance_t instance_;
};

NAMESPACE_END(rms)
NAMESPACE_END(sway)

#endif  // SWAY_RMS_IMAGERESOURCEPROVIDER_HPP
