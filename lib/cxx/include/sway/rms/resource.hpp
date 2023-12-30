#ifndef SWAY_RMS_RESOURCE_HPP
#define SWAY_RMS_RESOURCE_HPP

#include <sway/core.hpp>
#include <sway/core/foundation/uniqueable.hpp>
#include <sway/rms/resourcedatastatus.hpp>

#include <atomic>
#include <string>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

class Resource : public core::foundation::Uniqueable<std::string> {
public:
  Resource()
      : core::foundation::Uniqueable<std::string>(std::nullopt) {}

  virtual ~Resource() = default;

  void postStatus(ResourceDataStatus status) {
    // std::lock_guard lock(mutex_);
    status_.store(core::detail::toUnderlying(status), std::memory_order_seq_cst);
  }

  [[nodiscard]] auto getStatus() const -> ResourceDataStatus {
    return core::detail::toEnum<ResourceDataStatus>(status_.load(std::memory_order_seq_cst));
  }

  void wait(std::chrono::milliseconds timeout) {
    // std::unique_lock<std::mutex> lock(mutex_);
    while (ResourceDataStatusHelper::isPending(getStatus())) {
      // condition_.wait_for(lock, timeout);
    }
  }

protected:
  std::mutex mutex_;
  std::atomic_uint status_ = ATOMIC_VAR_INIT(core::detail::toUnderlying(ResourceDataStatus::WAITING));
  std::condition_variable condition_;

public:
  std::atomic_bool loadingDone_{false};
};

NAMESPACE_END(rms)
NAMESPACE_END(sway)

#endif  // SWAY_RMS_RESOURCE_HPP
