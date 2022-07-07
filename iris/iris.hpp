#pragma once
#include <core/file.hpp>
#include <core/hash.hpp>
#include <core/errors.hpp>

namespace aena
{
    namespace _0_0_1
    {
        enum class irise : u8
        {
            general,
            precomment,
            single_line_comment,
            multi_line_end_comment,
            multi_line_comment,
            literal_string,
            literal_string_bar
        };

        enum class irisen : u8
        {
            identifier,
            numerical,
            empty_string,
            literal_string,

            //tokens
            end_sentence,

            //keywords
            _extern,

        };

        [[nodiscard]] inline irisen tokenise(bool& on, const hash& h) noexcept
        {
            return on ? irisen::numerical : [&](){on = true; return h == hashes::_extern ? irisen::_extern : irisen::identifier;}();
        }

        [[nodiscard]] inline bool iris(const std::string& f) noexcept
        {
            const std::chrono::steady_clock::time_point& a = std::chrono::steady_clock::now();
            std::chrono::steady_clock::time_point b;
            {
                const std::string& content = read_file(f);
                b = std::chrono::steady_clock::now();
                u64 ln = 1ull, ch = 0ull, lln = 0ull, lch = 0ull;
                irise m = irise::general;
                bool on = true;
                for(const char c : content)
                {
                    c == '\n' ? ++ln, ch = 0ull : ++ch;
                    switch(m)
                    {
                        case irise::precomment:
                            
                        break;
                    }
                }
            }
            const std::chrono::steady_clock::time_point& c = std::chrono::steady_clock::now();
            msg += "\n\nparsing " + file + f + no_error + " took:\n\n" + sequence + "sys(" + watchdog(measure, a, b) + ")\nuser(" + watchdog(measure, b, c) + ")\ntotal(" + watchdog(measure, a, c) + ")" + no_error;
            return true;
        }
    }
}