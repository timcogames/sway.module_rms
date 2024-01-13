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
  FetcherQueue();

  ~FetcherQueue() = default;

  void add(std::shared_ptr<Fetcher> fetcher);

  void perform();

  auto isActive() -> bool;

  void terminate();

private:
  std::mutex mutex_;
  std::queue<std::shared_ptr<Fetcher>> queue_;
  std::shared_ptr<Fetcher> current_;
};

NAMESPACE_END(rms)
NAMESPACE_END(sway)

#endif  // SWAY_RMS_FETCHERQUEUE_HPP
