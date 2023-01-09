#ifndef SWAY_RMS_RESOURCEPROVIDER_HPP
#define SWAY_RMS_RESOURCEPROVIDER_HPP

#include <sway/core.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

class ResourceProvider {
public:
  ResourceProvider();

  ~ResourceProvider();

private:
  core::Plugin *plug_;
};

NAMESPACE_END(rms)
NAMESPACE_END(sway)

#endif  // SWAY_RMS_RESOURCEPROVIDER_HPP
