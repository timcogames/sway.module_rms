#include <sway/loader/imagedescriptor.hpp>
#include <sway/loader/imageloaderplugin.hpp>
#include <sway/rms.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <fstream>
#include <memory>
#include <string>

using namespace sway;

static void *const NO_NULLPTR = reinterpret_cast<void *>(0x12345678);

class ImageLoaderPluginFake : public loader::ImageLoaderPlugin {
public:
  // clang-format off
  MTHD_OVERRIDE(auto loadFromStream(std::ifstream &source) -> loader::ImageDescriptor) {  // clang-format on
    loader::ImageDescriptor desc;
    desc.buf.data = nullptr;
    desc.buf.len = 0;
    desc.size = math::Size<u32_t>();
    desc.pitch = 0;
    desc.bpp = 0;
    desc.type = 0;
    desc.format = 0;
    return desc;
  }

  // clang-format off
  MTHD_OVERRIDE(auto loadFrom(void *data, int nbytes) -> loader::ImageDescriptor) {  // clang-format on
    loader::ImageDescriptor desc;
    desc.buf.data = nullptr;
    desc.buf.len = 0;
    desc.size = math::Size<u32_t>();
    desc.pitch = 0;
    desc.bpp = 0;
    desc.type = 0;
    desc.format = 0;
    return desc;
  }
};

class ImageLoaderPluginMock : public loader::ImageLoaderPlugin {
public:
  ~ImageLoaderPluginMock() override = default;

  MOCK_METHOD(loader::ImageDescriptor, loadFromStream, (std::ifstream & source), (override));

  MOCK_METHOD(loader::ImageDescriptor, loadFrom, (void *data, int nbytes), (override));

  void delegateToFake() {
    ON_CALL(*this, loadFromStream).WillByDefault([this](std::ifstream &source) {
      return fake_.loadFromStream(source);
    });

    ON_CALL(*this, loadFrom).WillByDefault([this](void *data, int nbytes) { return fake_.loadFrom(data, nbytes); });
  }

private:
  ImageLoaderPluginFake fake_;
};

auto load(void *, int) -> void * { return nullptr; }

auto fail(void *) -> void * { return nullptr; }

TEST(ResourceManagerTest, Loaded) {
  const auto binPath = std::string("/Users/apriori85/Documents/Projects/sway.module_rms/bin");
  auto mngr = std::make_shared<rms::ImageResourceManager>();
  mngr->registerImageProvider(binPath + "/libmodule_loader_png.dylib");

  mngr->fetchData("png", binPath + "/img.png", (rms::LOAD_CALLBACK)&load, (rms::FAIL_CALLBACK)&fail);
  auto imageResource = mngr->findLoadedResource("png");

  EXPECT_EQ(imageResource->getDescriptor().size.getW(), 128);
  EXPECT_EQ(imageResource->getDescriptor().size.getH(), 128);

  std::unique_ptr<ImageLoaderPluginMock> mock = std::make_unique<testing::NiceMock<ImageLoaderPluginMock>>();

  mock->delegateToFake();
  EXPECT_CALL(*mock, loadFrom(testing::_, 0));

  auto desc = mock->loadFrom(nullptr, 0);
  EXPECT_EQ(desc.buf.len, 0);
}
