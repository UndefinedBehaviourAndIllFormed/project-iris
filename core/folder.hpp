//Copyright 2022 Project Aura, All Rights Reserved
#pragma once
#include <string>
#include <filesystem>

namespace aena
{
    [[nodiscard]] inline bool exists(const std::string& p) noexcept
    {
        return std::filesystem::is_directory(p);
    }

    [[nodiscard]] inline bool create(const std::string& b) noexcept
    {
        if(b.size() < 2ull)
            return false;
        else
        {
            std::string lel(1ull, b[0ull]);
            for(u64 x = 0ull; x < b.size(); ++x)
                if(x)
                {
                    const char& cc = b[x];
                    if(cc == '\\' || cc == '/')
                        if(!exists(lel))
                            if(!std::filesystem::create_directory(lel))
                                return false;
                    lel.append(1ull, cc);
                    if(x == (b.size() - 1ull))
                        if(!exists(lel))
                            if(!std::filesystem::create_directory(lel))
                                return false;
                }
            return true;
        }
    }

    [[nodiscard]] inline std::string get(const std::string& s) noexcept
    {
        return s.substr(0, s.find_last_of("\\/")) + '/';
    }
}