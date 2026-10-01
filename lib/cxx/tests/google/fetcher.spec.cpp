#include <sway/rms.hpp>

#include <gtest/gtest.h>

#include <fstream>
#include <gmock/gmock.h>
#include <memory>
// #include <nlohmann/json.hpp>
#include <string>

using namespace sway;
using namespace sway::rms;

static void *const NO_NULLPTR = reinterpret_cast<void *>(0x12345678);

class FetcherFake : public Fetcher {
public:
  FetcherFake(const std::string &url)
      : Fetcher(url) {}

  ~FetcherFake() override { cancel(); }

  MTHD_OVERRIDE(void fetch()) {
    thread_ = std::thread([this]() -> void {
#if EMSCRIPTEN_PLATFORM
      fetchHandle_ = RemoteFile::fetch(getUrl().c_str(), [this](const u8_t *data, u32_t num) {
        if (data && num > 0) {
          response_ = std::make_unique<FetchResponse>(data, num);
        }

        fetching_.store(false, std::memory_order_release);
      });
#else
      RemoteFile::fetch(getUrl().c_str(), [this](const u8_t *data, u32_t num) {
        if (data && num > 0) {
          response_ = std::make_unique<FetchResponse>(data, num);
        }

        fetching_.store(false, std::memory_order_release);
      });
#endif
    });
  }

protected:
  void onCancel() override {
#if EMSCRIPTEN_PLATFORM
    if (fetchHandle_) {
      emscripten_fetch_close(fetchHandle_);
      fetchHandle_ = nullptr;
    }
#endif
  }

private:
#if EMSCRIPTEN_PLATFORM
  emscripten_fetch_t *fetchHandle_ = nullptr;
#endif
};

TEST(FetcherQueueTest, fetch) {
  auto fetcherQueue = std::make_unique<FetcherQueue>();
  auto fetcher = std::make_shared<FetcherFake>("test.json");
  auto called = false;

  fetcher->setCallback([&]([[maybe_unused]] FetchResponse *response) { called = true; });
  fetcherQueue->add(fetcher);

  while (fetcherQueue->active()) {
    fetcherQueue->perform();
  }

  EXPECT_TRUE(called);
}
