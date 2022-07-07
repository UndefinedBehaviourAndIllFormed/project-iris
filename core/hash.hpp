#pragma once
#include <core/types.hpp>
#include <core/database.hpp>

namespace aena
{
    class [[nodiscard]] pair
    {
    public:
        u64 first = 0ull, second = 0ull;

        inline constexpr pair(const u64 f, const u64 s) noexcept : first(f), second(s){}
    };

    class [[nodiscard]] hash
    {
        std::string _content;

        u64 first = 14695981039346656037ull, second = 14695981039346656037ull;
    public:
        inline hash() noexcept{}

        inline hash(const std::string& s) noexcept
        {
            for(const char& c : s)
            {
                _content.append(1ull, c);
                first = first * 1099511628211ull;
                first = first ^ c;
                second = second ^ c;
                second = second * 1099511628211ull;
            }
        }

        [[nodiscard]] inline bool operator==(const pair& p) const noexcept
        {
            return first == p.first && second == p.second;
        }

        [[nodiscard]] inline bool operator!=(const pair& p) const noexcept
        {
            return first != p.first || second != p.second;
        }

        inline void operator()() noexcept
        {
            _content.clear();
            first = 14695981039346656037ull;
            second = 14695981039346656037ull;
        }

        inline void operator=(const char& c) noexcept
        {
            _content = c;
            first = 14695981039346656037ull * 1099511628211ull;
            first = first ^ c;
            second = 14695981039346656037ull ^ c;
            second = second * 1099511628211ull;
        }

        inline void operator+=(const char& c) noexcept
        {
            _content.append(1ull, c);
            first = first * 1099511628211ull;
            first = first ^ c;
            second = second ^ c;
            second = second * 1099511628211ull;
        }

        [[nodiscard]] inline std::string content() const noexcept
        {
            return _content;
        }

        [[nodiscard]] inline u64 size_string() const noexcept
        {
            return _content.size();
        }

        inline void print() const noexcept
        {
            msg += "\n\ncontent: " + _content + " -> first: " + std::to_string(first) + ", second: " + std::to_string(second);
        }
    };

    template<class t> class [[nodiscard]] sentence
    {
    public:
        hash h;

        u64 ln, ch;

        t token;

        [[nodiscard]] inline std::string start() const noexcept
        {
            return std::to_string(ln) + " : " + std::to_string(ch);
        }

        [[nodiscard]] inline std::string end() const noexcept
        {
            return std::to_string(ln) + " : " + std::to_string(ch + h.size_string());
        }
    };

    namespace _0_0_1
    {
        namespace hashes
        {
            //name
            constexpr pair name(13709268971822177140ull, 14176396743819860870ull);

            //version
            constexpr pair version(14792314564648254299ull, 13502572527641750071ull);

            //author
            constexpr pair author(10674446015911650224ull, 7815024061042257814ull);

            //extern
            constexpr pair _extern(17192341199092675163ull, 417800907370030071ull);
        }
    }
}