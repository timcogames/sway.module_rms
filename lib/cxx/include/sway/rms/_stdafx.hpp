#ifndef SWAY_RMS_PREREQS_HPP
#define SWAY_RMS_PREREQS_HPP

#include <sway/core.hpp>

#if EMSCRIPTEN_PLATFORM
#  include <emscripten/fetch.h>
#  include <emscripten/wget.h>  // emscripten_async_wget_data
// #else
// #  include <curl/curl.h>
#endif

#include <atomic>
#include <fstream>  // ifstream
#include <functional>  // ref
#include <future>  // async
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <vector>

#endif  // SWAY_RMS_PREREQS_HPP
