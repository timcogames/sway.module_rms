#ifndef SWAY_RMS_FETCHER_HPP
#define SWAY_RMS_FETCHER_HPP

#include <sway/core.hpp>

#include <atomic>
#include <functional>
#include <nlohmann/json.hpp>
#include <string>
#include <thread>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(rms)

class Fetcher {
public:
  Fetcher(const std::string &url)
      : url_(url) {}

  ~Fetcher() = default;

  PURE_VIRTUAL(void fetch());

  void setCallback(std::function<void(nlohmann::json)> func) { callback_ = func; }

  void invokeCallback() {
    if (callback_ != nullptr) {
      callback_(response_);
    }
  }

  auto isFinished() -> bool { return !fetching_.load(); }

  void join() { thread_.join(); }

  void detach() {
    if (thread_.joinable()) {
      thread_.detach();
    }
  }

  auto getUrl() -> std::string { return url_; }

protected:
  std::thread thread_;
  std::atomic_bool fetching_{true};

  std::function<void(nlohmann::json)> callback_ = nullptr;
  nlohmann::json response_;

private:
  std::string url_;
};

NAMESPACE_END(rms)
NAMESPACE_END(sway)

#endif  // SWAY_RMS_FETCHER_HPP
