#include <sway/rms.hpp>

#include <gtest/gtest.h>

using namespace sway;

TEST(ResourceManagerTest, Loaded) {
  auto manager = std::make_shared<rms::ResourceManager>();
  manager->registerProvider();

  auto provider = manager->getProvider("png");

  // const std::filesystem::path &path
  std::ifstream myfile("/Users/apriori85/Documents/Projects/sway.module_rms/bin/img.png");
  if (myfile.is_open()) {
    auto imageDescriptor = provider->getPlug()->loadFromStream(myfile);

    std::cout << "img width: " << imageDescriptor.width << "\theight: " << imageDescriptor.height << std::endl;
  }
}
