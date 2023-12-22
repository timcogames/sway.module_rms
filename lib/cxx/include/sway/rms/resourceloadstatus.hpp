#ifndef SWAY_RMS_RESOURCELOADSTATUS_HPP
#define SWAY_RMS_RESOURCELOADSTATUS_HPP

#include <sway/core.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

// clang-format off
enum class ResourceLoadStatus : u32_t {
  PENDING,
  IN_PROGRESS,
  COMPLETED,
  FAILED
};
// clang-format on

NAMESPACE_END(rms)
NAMESPACE_END(sway)

#endif  // SWAY_RMS_RESOURCELOADSTATUS_HPP
