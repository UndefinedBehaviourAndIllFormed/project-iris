//Copyright 2022 Project Aura, All Rights Reserved
#pragma once
#include <vector>
#include <string>
#include <core/version.hpp>
#include <core/watchdog.hpp>

namespace aena
{
    std::vector<std::string> compiler_versions({"0.0.1"});

    const std::string compiler_actual_version("0.0.1");

    std::string compiler_version, eye, source, document, library, output;

    std::chrono::steady_clock::time_point start;

    u64 indentation = 3ull;

    measurement measure = measurement::microseconds;

    version project_compiler_version = version::_0_0_1;

    //EDIT FROM HERE

    std::string msg;

    
}