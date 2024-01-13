#include <sway/rms/fetcherqueue.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

FetcherQueue::FetcherQueue()
    : current_(nullptr) {}

void FetcherQueue::add(std::shared_ptr<Fetcher> fetcher) {
  mutex_.lock();
  queue_.push(fetcher);
  mutex_.unlock();
}

void FetcherQueue::perform() {
  mutex_.lock();

  if (current_ != nullptr && current_->isFinished()) {
    current_->invokeCallback();
    current_->join();
    current_ = nullptr;
  } else if (current_ == nullptr && queue_.size() > 0) {
    current_ = queue_.front();
    queue_.pop();

    current_->fetch();
  }

  mutex_.unlock();
}

auto FetcherQueue::isActive() -> bool {
  mutex_.lock();
  auto isActive = !queue_.empty() || current_ != nullptr;
  mutex_.unlock();

  return isActive;
}

void FetcherQueue::terminate() {
  if (current_ != nullptr) {
    current_->detach();
  }

  std::queue<std::shared_ptr<Fetcher>>().swap(queue_);
}

NAMESPACE_END(rms)
NAMESPACE_END(sway)
