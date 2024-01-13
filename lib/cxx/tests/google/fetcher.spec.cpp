#include <sway/rms.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fstream>
#include <memory>
#include <string>

using namespace sway;
using namespace sway::rms;

static void *const NO_NULLPTR = reinterpret_cast<void *>(0x12345678);

class FetcherFake : public Fetcher {
public:
  FetcherFake(const std::string &url)
      : Fetcher(url) {}

  ~FetcherFake() {}

  MTHD_OVERRIDE(void fetch()) {
    thread_ = std::thread([this]() -> void {
      // if emsc

      RemoteFile::fetch(getUrl().c_str(), [this](fetch_res_t fetch) {
        // auto *self = static_cast<FetcherFake *>(fetch->userData);
        response_ = nlohmann::json::parse(std::string(fetch->data, fetch->numBytes));
        if (response_.empty()) {
          // TODO
        }

        fetching_.store(false);
      });

      // else

      //   std::ifstream strm(filename);
      //   if (!strm.is_open()) {
      //     std::cout << "failed to open " << filename << std::endl;
      //     return nullptr;
      //   }

      //   response_ = nlohmann::json::parse(strm);
    });
  }
};

TEST(FetcherQueueTest, fetch) {}
