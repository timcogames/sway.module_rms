#include <sway/rms.hpp>

#include <gtest/gtest.h>

using namespace sway;

TEST(ResourceManagerTest, Loaded) {
  auto system = std::make_shared<rms::ResourceManagerSystem>();
  system->registerImageProvider(
      "/Users/apriori85/Documents/Projects/sway.module_rms/bin/module_loader_png.dylib.0.1.0");

  // const std::filesystem::path &path
  system->loadImage("png", "/Users/apriori85/Documents/Projects/sway.module_rms/bin/img.png");
  auto image = system->findLoadedResource("png");
  std::cout << "img width: " << image->getDescriptor().size.getW() << "\theight: " << image->getDescriptor().size.getH()
            << std::endl;
}
