#pragma once

#ifndef DUSK_BENCHMARK_H
#define DUSK_BENCHMARK_H

#include <Logging/Logging.h>

#include <chrono>

#define DuskBenchStart() \
auto duskBenchClockStart = std::chrono::high_resolution_clock::now();

#define DuskBenchEnd(funcName) \
auto duskBenchClockEnd = std::chrono::high_resolution_clock::now(); \
double duskBenchMillis = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(duskBenchClockEnd - duskBenchClockStart).count(); \
DuskExtLog("perf", "Function: %s took %.3f millis", funcName, duskBenchMillis);

#endif // DUSK_BENCHMARK_H