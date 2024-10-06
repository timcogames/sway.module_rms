#ifndef SWAY_RMS_RESOURCEDATASTATUS_HPP
#define SWAY_RMS_RESOURCEDATASTATUS_HPP

#include <sway/core.hpp>

#include <atomic>

NS_BEGIN_SWAY()
NS_BEGIN(rms)

// clang-format off
enum class ResourceDataStatus : u32_t {
  WAITING = 0,
  IN_PROGRESS,
  SUCCESS,
  FAIL
};
// clang-format on

struct ResourceDataStatusHelper {
  static auto isPending(ResourceDataStatus status) -> bool {
    return status == ResourceDataStatus::WAITING || status == ResourceDataStatus::IN_PROGRESS;
  }
};

NS_END()  // namespace rms
NS_END()  // namespace sway

#endif  // SWAY_RMS_RESOURCEDATASTATUS_HPP
