//
// pch.h
//

#pragma once

#include "gtest/gtest.h"

#include <future>

#define GTEST_COUT std::cerr << "[          ] [ INFO ]"

#define ASSERT_DURATION_LE(miliseconds, stmt) { \
  std::promise<bool> completed; \
  auto stmt_future = completed.get_future(); \
  std::thread([&](std::promise<bool>& completed) { \
    stmt; \
    completed.set_value(true); \
  }, std::ref(completed)).detach(); \
  if(stmt_future.wait_for(std::chrono::milliseconds(miliseconds)) == std::future_status::timeout) \
    GTEST_FATAL_FAILURE_("       El limite de tiempo se ha excedido (> " #miliseconds \
    " milisegundos.)."); \
}