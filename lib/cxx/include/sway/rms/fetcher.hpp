#ifndef SWAY_RMS_FETCHER_HPP
#define SWAY_RMS_FETCHER_HPP

#include <sway/core.hpp>
#include <sway/rms/_stdafx.hpp>

namespace sway::rms {

struct FetchResponse {
  std::vector<u8_t> dataVector;
  u32_t numBytes;

  FetchResponse(std::vector<u8_t> data, u32_t num)
      : dataVector(std::move(data))
      , numBytes(num) {}

  FetchResponse(const u8_t *data, u32_t num)
      : dataVector(data, data + num)
      , numBytes(num) {}
};

class Fetcher {
public:
#pragma region "Constructor(s) & Destructor"
  /** \~english @name Constructor(s) & Destructor */ /** \~russian @name Конструктор(ы) и Деструктор */
  /** @{ */

  explicit Fetcher(std::string url)
      : url_(std::move(url)) {}

  virtual ~Fetcher() = default;

  /** @} */
#pragma endregion

#pragma region "Pure virtual methods"
  /** \~english @name Pure virtual methods */ /** \~russian @name Чисто виртуальные методы */
  /** @{ */

  virtual void fetch() = 0;

  /** @} */
#pragma endregion

  void setCallback(std::function<void(FetchResponse *)> func) {
    std::lock_guard<std::mutex> lock(callbackMutex_);
    callback_ = std::move(func);
  }

  void invoke() {
    std::function<void(FetchResponse *)> callback;

    {
      std::lock_guard<std::mutex> lock(callbackMutex_);
      callback = callback_;
    }

    if (callback) {
      callback(response_.get());
    }
  }

  void join() {
    if (thread_.joinable()) {
      thread_.join();
    }
  }

  void detach() {
    if (thread_.joinable()) {
      thread_.detach();
    }
  }

  void cancel() {
    canceled_.store(true);
    onCancel();
  }

  auto finished() -> bool { return !fetching_.load(std::memory_order_acquire); }

  auto getUrl() const -> const std::string & { return url_; }

protected:
  virtual void onCancel() {}

  std::thread thread_;
  std::atomic_bool fetching_{true};
  std::atomic_bool canceled_{false};
  std::unique_ptr<FetchResponse> response_;
  std::function<void(FetchResponse *)> callback_;

private:
  std::mutex callbackMutex_;
  std::string url_;
};

}  // namespace sway::rms

#endif  // SWAY_RMS_FETCHER_HPP
