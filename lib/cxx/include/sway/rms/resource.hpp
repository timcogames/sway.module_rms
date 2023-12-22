#ifndef SWAY_RMS_RESOURCE_HPP
#define SWAY_RMS_RESOURCE_HPP

#include <sway/core.hpp>
#include <sway/core/foundation/uniqueable.hpp>
#include <sway/rms/resourceloadstatus.hpp>

#include <atomic>
#include <string>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

class Resource : public core::foundation::Uniqueable<std::string> {
public:
  Resource()
      : core::foundation::Uniqueable<std::string>(std::nullopt) {}

  virtual ~Resource() = default;

  virtual auto getStatus() -> ResourceLoadStatus { return status_.load(); }

private:
  std::atomic<ResourceLoadStatus> status_ = {ResourceLoadStatus::PENDING};
};

NAMESPACE_END(rms)
NAMESPACE_END(sway)

#endif  // SWAY_RMS_RESOURCE_HPP
