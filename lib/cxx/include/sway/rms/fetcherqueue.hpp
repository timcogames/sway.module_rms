#ifndef SWAY_RMS_FETCHERQUEUE_HPP
#define SWAY_RMS_FETCHERQUEUE_HPP

#include <sway/core.hpp>
#include <sway/rms/_stdafx.hpp>
#include <sway/rms/fetcher.hpp>

namespace sway::rms {

class FetcherQueue {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  FetcherQueue();

  ~FetcherQueue() = default;

  /** @} */
#pragma endregion

  void add(std::shared_ptr<Fetcher> fetcher);

  void perform();

  auto active() -> bool;

  void terminate();

private:
  std::mutex mutex_;
  std::queue<std::shared_ptr<Fetcher>> queue_;
  std::shared_ptr<Fetcher> current_;
};

}  // namespace sway::rms

#endif  // SWAY_RMS_FETCHERQUEUE_HPP
