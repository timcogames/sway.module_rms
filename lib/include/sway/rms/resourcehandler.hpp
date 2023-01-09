#ifndef SWAY_RMS_RESOURCEHANDLER_HPP
#define SWAY_RMS_RESOURCEHANDLER_HPP

#include <sway/core.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

template <typename TDesciption>
class ResourceHandler {
public:
  ResourceHandler() = default;

  virtual ~ResourceHandler() = default;

  // clang-format off
  PURE_VIRTUAL(auto loadFromStream(const std::ifstream& source) -> TDesciption);  // clang-format on
};

NAMESPACE_END(rms)
NAMESPACE_END(sway)

#endif  // SWAY_RMS_RESOURCEHANDLER_HPP
