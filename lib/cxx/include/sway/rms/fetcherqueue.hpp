#ifndef SWAY_RMS_FETCHERQUEUE_HPP
#define SWAY_RMS_FETCHERQUEUE_HPP

#include <sway/core.hpp>
#include <sway/rms/fetcher.hpp>

#include <memory>
#include <mutex>
#include <queue>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

class FetcherQueue {
public:
  void add(std::shared_ptr<Fetcher> fetcher) {
    mutex_.lock();

    queue_.push(fetcher);

    mutex_.unlock();
  }

  void tryDequeue() {
    mutex_.lock();

    if (current_ != nullptr && current_->isFinished()) {
      current_->runCallback();
      current_->join();
      current_ = nullptr;
    } else if (current_ == nullptr && queue_.size() > 0) {
      current_ = queue_.front();
      queue_.pop();

      current_->fetch();
    }

    mutex_.unlock();
  }

  auto isActive() -> bool {
    mutex_.lock();

    auto isActive = !queue_.empty() || current_ != nullptr;

    mutex_.unlock();

    return isActive;
  }

  void terminate() {
    if (current_ != nullptr) {
      current_->detach();
    }

    std::queue<std::shared_ptr<Fetcher>>().swap(queue_);
  }

private:
  std::mutex mutex_;
  std::queue<std::shared_ptr<Fetcher>> queue_;
  std::shared_ptr<Fetcher> current_ = nullptr;
};

NAMESPACE_END(rms)
NAMESPACE_END(sway)

#endif  // SWAY_RMS_FETCHERQUEUE_HPP
