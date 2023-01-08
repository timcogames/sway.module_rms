#ifndef SWAY_RMS_RESOURCE_HPP
#define SWAY_RMS_RESOURCE_HPP

#include <sway/core.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

class Resource {
public:
  Resource() = default;

  virtual ~Resource() = default;
};

NAMESPACE_END(rms)
NAMESPACE_END(sway)

#endif  // SWAY_RMS_RESOURCE_HPP
