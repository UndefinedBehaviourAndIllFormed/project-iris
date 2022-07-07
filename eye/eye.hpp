#pragma once
#include <thread>
#include <iris/iris.hpp>
#include <eye/compilation_unit.hpp>

namespace aena
{
    namespace _0_0_1
    {
        //eye mode
        enum class eyede : u8
        {
            normal,
            literal_string,
            literal_string_bar,
            precomment,
            single_line_comment,
            multi_line_comment,
            multi_line_end_comment
        };

        //eye token
        enum class eyeken : u8
        {
            identifier,
            numerical,
            empty_string,
            string,

            //tokens
            assignment,
            end_sentence,
            dot,
            start_node,
            end_node,
            
            //keywords
            name,
            version,
            author,
        };

        inline void dispatch_eyeken(sentence<eyeken>& s, bool& on) noexcept
        {
            s.token = on ? eyeken::numerical : [&](){on = true; return s.h == hashes::name ? eyeken::name : s.h == hashes::version ? eyeken::version : s.h == hashes::author ? eyeken::author : eyeken::identifier;}();
        }

        [[nodiscard]] inline bool tokeneye(std::vector<sentence<eyeken>>& tokens, const std::string& content) noexcept
        {
            sentence<eyeken> s;
            const u64 ind = indentation;
            u64 ln = 1ull, ch = 0ull;
            eyede m = eyede::normal;
            bool on = true, fc = false;
            for(const char& c : content)
            {
                c == '\n' ? ++ln, ch = 0ull : ++ch;
                switch(m)
                {
                    case eyede::normal:
                        switch(c)
                        {
                            case alpha:
                                on = false;
                                if(!fc)
                                {
                                    fc = true;
                                    s.ln = ln;
                                    s.ch = ch;
                                    s.h = c;
                                }
                                else
                                    s.h += c;
                            break;
                            case numeric:
                                if(!fc)
                                {
                                    fc = true;
                                    s.ln = ln;
                                    s.ch = ch;
                                    s.h = c;
                                }
                                else
                                    s.h += c;
                            break;
                            case '\n':
                            case ' ':
                                if(fc)
                                {
                                    fc = false;
                                    dispatch_eyeken(s, on);
                                    tokens.push_back(s);
                                }
                            break;
                            case '=':
                                if(fc)
                                {
                                    fc = false;
                                    dispatch_eyeken(s, on);
                                    tokens.push_back(s);
                                }
                                s.token = eyeken::assignment;
                                s.ln = ln;
                                s.ch = ch;
                                s.h = '=';
                                tokens.push_back(s);
                            break;
                            case ';':
                                if(fc)
                                {
                                    fc = false;
                                    dispatch_eyeken(s, on);
                                    tokens.push_back(s);
                                }
                                s.token = eyeken::end_sentence;
                                s.ln = ln;
                                s.ch = ch;
                                s.h = ';';
                                tokens.push_back(s);
                            break;
                            case '.':
                                if(fc)
                                {
                                    fc = false;
                                    dispatch_eyeken(s, on);
                                    tokens.push_back(s);
                                }
                                s.token = eyeken::dot;
                                s.ln = ln;
                                s.ch = ch;
                                s.h = '.';
                                tokens.push_back(s);
                            break;
                            case '{':
                                if(fc)
                                {
                                    fc = false;
                                    dispatch_eyeken(s, on);
                                    tokens.push_back(s);
                                }
                                s.token = eyeken::start_node;
                                s.ln = ln;
                                s.ch = ch;
                                s.h = '{';
                                tokens.push_back(s);
                            break;
                            case '}':
                                if(fc)
                                {
                                    fc = false;
                                    dispatch_eyeken(s, on);
                                    tokens.push_back(s);
                                }
                                s.token = eyeken::end_node;
                                s.ln = ln;
                                s.ch = ch;
                                s.h = '}';
                                tokens.push_back(s);
                            break;
                            case '"':
                                m = eyede::literal_string;
                                if(fc)
                                {
                                    fc = false;
                                    dispatch_eyeken(s, on);
                                    tokens.push_back(s);
                                }
                            break;
                            case '`':
                                m = eyede::precomment;
                                if(fc)
                                {
                                    fc = false;
                                    dispatch_eyeken(s, on);
                                    tokens.push_back(s);
                                }
                            break;
                            case '\t':
                                ch += ind;
                                if(fc)
                                {
                                    fc = false;
                                    dispatch_eyeken(s, on);
                                    tokens.push_back(s);
                                }
                            break;
                            default:
                                return unrecognized_character(eye, ln, ch, c);
                        }
                    break;
                    case eyede::literal_string:
                        switch(c)
                        {
                            default:
                                if(!fc)
                                {
                                    fc = true;
                                    s.ln = ln;
                                    s.ch = ch;
                                    s.h = c;
                                }
                                else
                                    s.h += c;
                            break;
                            case '"':
                                m = eyede::normal;
                                if(!fc)
                                {
                                    s.token = eyeken::empty_string;
                                    s.ln = ln;
                                    s.ch = ch;
                                }
                                else
                                {
                                    fc = false;
                                    s.token = eyeken::string;
                                }
                                tokens.push_back(s);
                            break;
                            case '\\':
                                m = eyede::literal_string_bar;
                            break;
                        }
                    break;
                    case eyede::single_line_comment:
                        if(c == '\n')
                            m = eyede::normal;
                    break;
                    case eyede::multi_line_comment:
                        if(c == '*')
                            m = eyede::multi_line_end_comment;
                    break;
                    case eyede::multi_line_end_comment:
                        switch(c)
                        {
                            case '`':
                                m = eyede::normal;
                            break;
                            case '*':
                            break;
                            default:
                                m = eyede::multi_line_comment;
                            break;
                        }
                    break;
                    case eyede::precomment:
                        switch(c)
                        {
                            case '`':
                                m = eyede::single_line_comment;
                            break;
                            case '*':
                                m = eyede::multi_line_comment;
                            break;
                            default:
                                return unexpected_precomment_character(eye, ln, ch, c);
                            break;
                        }
                    break;
                    case eyede::literal_string_bar:
                        if(c == '\\' || c == '"')
                        {
                            m = eyede::literal_string;
                            if(!fc)
                            {
                                fc = true;
                                s.ln = ln;
                                s.ch = ch;
                                s.h = c;
                            }
                            else
                                s.h += c;
                        }
                        else
                            return unexpected_bar_character(ln, ch, c);
                    break;
                }
            }
            return true;
        }

        enum class eyese : u8
        {
            general,
            compilation_unit_start,
            compilation_unit,
            global_name,
            name,
            global_version,
            version,
            global_author,
            author,

        };

        [[nodiscard]] inline bool parseye(const std::vector<sentence<eyeken>>& tokens, std::vector<compilation_unit>& units) noexcept
        {
            std::string ver;
            u8 mode = 0u;
            compilation_unit cu;
            eyese m = eyese::general;
            for(const sentence<eyeken>& s : tokens)
                switch(m)
                {
                    case eyese::compilation_unit:
                        switch(s.token)
                        {
                            case eyeken::end_node:
                                m = eyese::general;
                                units.push_back(cu);
                            break;
                            case eyeken::name:
                                m = eyese::name;
                            break;
                            case eyeken::version:
                                m = eyese::version;
                            break;
                            case eyeken::author:
                                m = eyese::author;
                            break;
                            default:
                                return unexpected_token_compilation_unit(cu.name, s);
                        }
                    break;
                    case eyese::general:
                        switch(s.token)
                        {
                            case eyeken::name:
                                m = eyese::global_name;
                            break;
                            case eyeken::version:
                                m = eyese::global_version;
                            break;
                            case eyeken::author:
                                m = eyese::global_author;
                            break;
                            case eyeken::identifier:
                                m = eyese::compilation_unit_start;
                                cu.name = s.h.content();
                                cu();
                            break;
                            case eyeken::numerical:
                                return unexpected_numerical_value(s);
                            default:
                                return unknown_general_eye_token(s);
                        }
                    break;
                    case eyese::compilation_unit_start:
                        if(s.token == eyeken::start_node)
                            m = eyese::compilation_unit;
                        else
                            return unexpected_token_start_compilation_unit(s);
                    break;
                    case eyese::name:
                        switch(mode)
                        {
                            case 0u:
                                if(s.token == eyeken::assignment)
                                    mode = 1u;
                                else
                                    return unexpected_local_name_token_assignment(cu.name, s);
                            break;
                            case 1u:
                                switch(s.token)
                                {
                                    case eyeken::string:
                                        mode = 2u;
                                        cu.local_project_name = s.h.content();
                                    break;
                                    case eyeken::empty_string:
                                        return unexpected_local_name_empty_string(cu.name, s);
                                    default:
                                        return unexpected_local_name(cu.name, s);
                                }
                            break;
                            case 2u:
                                if(s.token == eyeken::end_sentence)
                                {
                                    mode = 0u;
                                    m = eyese::compilation_unit;
                                }
                                else
                                    return unexpected_local_name_end_sentence(cu.name, s);
                            break;
                        }
                    break;
                    case eyese::global_name:
                        switch(mode)
                        {
                            case 0u:
                                if(s.token == eyeken::assignment)
                                    mode = 1u;
                                else
                                    return unexpected_global_name_token_assignment(s);
                            break;
                            case 1u:
                                switch(s.token)
                                {
                                    case eyeken::string:
                                        mode = 2u;
                                        global_project_name = s.h.content();
                                    break;
                                    case eyeken::empty_string:
                                        return unexpected_global_name_empty_string(s);
                                    default:
                                        return unexpected_global_name(s);
                                }
                            break;
                            case 2u:
                                if(s.token == eyeken::end_sentence)
                                {
                                    mode = 0u;
                                    m = eyese::general;
                                }
                                else
                                    return unexpected_global_name_end_sentence(s);
                            break;
                        }
                    break;
                    case eyese::version:
                        if(!mode)
                        {
                            if(s.token == eyeken::assignment)
                                mode = 1u;
                            else
                                return unexpected_local_version_assignment(cu.name, s);
                        }
                        else
                            switch(s.token)
                            {
                                case eyeken::dot:
                                    if(mode == 2u)
                                    {
                                        mode = 1u;
                                        ver.append(1ull, '.');
                                    }
                                    else
                                        ver += "0.";
                                break;
                                case eyeken::numerical:
                                    if(mode == 2u)
                                        return unrecognized_version_repeated_numerical(s);
                                    else
                                    {
                                        mode = 2u;
                                        ver += s.h.content();
                                    }
                                break;
                                case eyeken::end_sentence:
                                    if(mode == 1u)
                                        ver.append(1ull, '0');
                                    mode = 0u;
                                    m = eyese::compilation_unit;
                                    cu.local_project_version = ver;
                                    ver.clear();
                                break;
                                default:
                                    return unrecognized_version_token(s);
                            }
                    break;
                    case eyese::global_version:
                        if(!mode)
                        {
                            if(s.token == eyeken::assignment)
                                mode = 1u;
                            else
                                return unexpected_global_version_assignment(s);
                        }
                        else
                            switch(s.token)
                            {
                                case eyeken::dot:
                                    if(mode == 2u)
                                    {
                                        mode = 1u;
                                        ver.append(1ull, '.');
                                    }
                                    else
                                        ver += "0.";
                                break;
                                case eyeken::numerical:
                                    if(mode == 2u)
                                        return unrecognized_version_repeated_numerical(s);
                                    else
                                    {
                                        mode = 2u;
                                        ver += s.h.content();
                                    }
                                break;
                                case eyeken::end_sentence:
                                    if(mode == 1u)
                                        ver.append(1ull, '0');
                                    mode = 0u;
                                    m = eyese::general;
                                    global_project_version = ver;
                                    ver.clear();
                                break;
                                default:
                                    return unrecognized_version_token(s);
                            }
                    break;
                    case eyese::author:
                        switch(mode)
                        {
                            case 0u:
                                if(s.token == eyeken::assignment)
                                    mode = 1u;
                                else
                                    return unexpected_local_author_assignment(cu.name, s);
                            break;
                            case 1u:
                                switch(s.token)
                                {
                                    case eyeken::string:
                                        mode = 2u;
                                        cu.local_project_author = s.h.content();
                                    break;
                                    case eyeken::empty_string:
                                        return unexpected_empty_author(s);
                                    default:
                                        return unexpected_local_author_token(cu.name, s);
                                }
                            break;
                            case 2u:
                                if(s.token == eyeken::end_sentence)
                                {
                                    mode = 0u;
                                    m = eyese::compilation_unit;
                                }
                                else
                                    return unexpected_local_author_end(cu.name, s);
                            break;
                        }
                    break;
                    case eyese::global_author:
                        switch(mode)
                        {
                            case 0u:
                                if(s.token == eyeken::assignment)
                                    mode = 1u;
                                else
                                    return unexpected_global_author_assignment(s);
                            break;
                            case 1u:
                                switch(s.token)
                                {
                                    case eyeken::string:
                                        mode = 2u;
                                        global_project_author = s.h.content();
                                    break;
                                    case eyeken::empty_string:
                                        return unexpected_empty_author(s);
                                    default:
                                        return unexpected_global_author_token(s);
                                }
                            break;
                            case 2u:
                                if(s.token == eyeken::end_sentence)
                                {
                                    mode = 0u;
                                    m = eyese::general;
                                }
                                else
                                    return unexpected_global_author_end(s);
                            break;
                        }
                    break;
                }
            return true;
        }

        inline void eye_() noexcept
        {
            //hash("extern").print();
            const std::chrono::steady_clock::time_point& a = std::chrono::steady_clock::now();
            const std::string& content = read_file(eye);
            std::vector<compilation_unit> units;
            std::vector<sentence<eyeken>> tokens;
            const std::chrono::steady_clock::time_point& b = std::chrono::steady_clock::now();
            if(tokeneye(tokens, content) && parseye(tokens, units))
            {
                const std::chrono::steady_clock::time_point& c = std::chrono::steady_clock::now();
                msg += "\n\nparsing " + file + eye + no_error + " took:\n\n" + sequence + "sys(" + watchdog(measure, a, b) + ")\nuser(" + watchdog(measure, b, c) + ")\ntotal(" + watchdog(measure, a, c) + ")" + no_error;
                bool ok = true;
                for(const compilation_unit& cu : units)
                {
                    const std::chrono::steady_clock::time_point& f = std::chrono::steady_clock::now();
                    std::vector<file_object> files = get_files(source, file_type::iris);
                    if(files.empty())
                        unexpected_no_files();
                    else
                    {
                        {

                        }
                        const u32 mts = std::thread::hardware_concurrency();
                        if(mts == 1ul)
                            for(const file_object& fo : files)
                                switch(fo.ft)
                                {
                                    case file_type::iris:
                                        if(!iris(fo.f))
                                            ok = false;
                                    break;
                                }
                        else
                        {
                            const u64 fs = files.size();
                            std::vector<std::thread> ths;
                            ths.reserve(fs);
                            u64 x = 0ull;
                            u32 xx = 1ull;
                            while(x < fs)
                                while(x < fs and xx < mts)
                                {
                                    ++xx;
                                    const file_object& fo = files[x++];
                                    switch(fo.ft)
                                    {
                                        case file_type::iris:
                                            ths.push_back(std::thread([&]()
                                            {
                                                if(!iris(fo.f))
                                                    ok = false;
                                                --xx;
                                            }));
                                        break;
                                    }
                                }
                            for(std::thread& t : ths)
                                t.join();
                        }
                    }
                    if(ok)
                    {
                        const std::chrono::steady_clock::time_point& g = std::chrono::steady_clock::now();
                        msg += "\n\nthe compilation of " + location + cu.name + no_error + " took " + sequence + watchdog(measure, f, g) + no_error;
                    }
                }
                if(ok)
                {
                    const std::chrono::steady_clock::time_point& e = std::chrono::steady_clock::now();
                    msg += "\n\nthe compilation process took " + sequence + watchdog(measure, start, e) + no_error;

                }
            }
        }
    }
}