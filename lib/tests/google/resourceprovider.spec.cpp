#include <sway/rms.hpp>

#include <gtest/gtest.h>

using namespace sway;

TEST(ResourceProviderTest, Loaded) { auto provider = new rms::ResourceProvider(); }
