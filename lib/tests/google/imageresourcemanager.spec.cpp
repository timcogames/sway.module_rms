#include <sway/rms.hpp>

#include <gtest/gtest.h>

using namespace sway;

TEST(ResourceManagerTest, Loaded) {
  std::string binPath("/Users/apriori85/Documents/Projects/sway.module_rms/bin");
  auto mngr = std::make_shared<rms::ImageResourceManager>();
  mngr->registerImageProvider(binPath + "/loader_png.dylib.0.1.0");

  // const std::filesystem::path &path
  mngr->loadImage("png", binPath + "/img.png");
  auto image = mngr->findLoadedResource("png");
  std::cout << "img width: " << image->getDescriptor().size.getW() << "\theight: " << image->getDescriptor().size.getH()
            << std::endl;
}
