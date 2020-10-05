/**
 * COPYRIGHT (C) 2020 Leyuan Pan ALL RIGHTS RESERVED.
 *
 * @brief Portable jthread inclusion.
 * @author Leyuan Pan
 * @date Oct 04, 2020
 */

#ifndef JTHREAD_HPP_
#define JTHREAD_HPP_

#if __cplusplus < 201703L
#error "jthread not supported before C++17"
#elif __cplusplus < 201907L
#include "jthread/jthread.hpp"
#include "jthread/stop_token.hpp"
#else
#include <stop_token>
#include <thread>
#endif

#endif  // JTHREAD_HPP_