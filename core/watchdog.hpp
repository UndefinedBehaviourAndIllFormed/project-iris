#pragma once
#include <string>
#include <chrono>
#include <core/types.hpp>

namespace aena
{
    enum class measurement : u8
    {
        nanoseconds,
        microseconds,
        milliseconds
    };

    //const std::chrono::steady_clock::time_point& a = std::chrono::steady_clock::now();

    [[nodiscard]] inline std::string watchdog(const measurement msr, const std::chrono::steady_clock::time_point& a, const std::chrono::steady_clock::time_point& b) noexcept
    {
        switch(msr)
        {
            case measurement::nanoseconds:
    			return std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(b - a).count()) + " nanoseconds";
		    case measurement::microseconds:
			    return std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(b - a).count()) + " microseconds";
            default:
        		return std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(b - a).count()) + " milliseconds";
        }
    }
}