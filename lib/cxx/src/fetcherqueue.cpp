#include <sway/rms/fetcherqueue.hpp>

namespace sway::rms {

FetcherQueue::FetcherQueue()
    : current_(nullptr) {}

void FetcherQueue::add(std::shared_ptr<Fetcher> fetcher) {
  std::lock_guard<std::mutex> lock(mutex_);

  if (terminated_) {
    return;
  }

  queue_.push(std::move(fetcher));
}

void FetcherQueue::perform() {
  std::shared_ptr<Fetcher> finished;
  std::shared_ptr<Fetcher> toStart;

  {
    std::lock_guard<std::mutex> lock(mutex_);
    if (current_ && current_->finished()) {
      finished = std::move(current_);
      current_ = nullptr;
    } else if (!current_ && !queue_.empty()) {
      toStart = queue_.front();
      queue_.pop();
      current_ = toStart;
    }
  }

  if (finished) {
    finished->invoke();
    finished->join();
  }

  if (toStart) {
    toStart->fetch();
  }
}

auto FetcherQueue::active() -> bool {
  std::lock_guard<std::mutex> lock(mutex_);
  return !queue_.empty() || current_ != nullptr;
}

void FetcherQueue::terminate() {
  std::shared_ptr<Fetcher> fetcher;

  {
    std::lock_guard<std::mutex> lock(mutex_);
    fetcher = std::move(current_);
    std::queue<std::shared_ptr<Fetcher>>().swap(queue_);
    terminated_ = true;
  }

  if (fetcher) {
    fetcher->cancel();
    fetcher->join();
  }
}

}  // namespace sway::rms
