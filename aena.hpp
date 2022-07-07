//Copyright 2022 Project Aena, All Rights Reserved
#pragma once
#include <iostream>
#include <eye/eye.hpp>
#include <core/folder.hpp>

namespace aena
{
    inline void panic_msg() noexcept
    {
        std::cout << "\n\npress any key and 'enter' to exit...\n";
        char c;
        std::cin >> c;
    }

    //clean whole project
    inline void clean() noexcept
    {
        measure = measurement::microseconds;
        project_compiler_version = version::_0_0_1;
        indentation = 3ull;
        _0_0_1::global_project_name = "project";
        _0_0_1::global_project_version = "0.0.1";
        _0_0_1::global_project_author = "unknown";
        msg.clear();
    }

    enum class eyeven : u8
    {
        unknown,
        compiler_version,
        indentation,
        measure,
        ns,
        mcs,
        ms,
        assignment,
        end_sentence,
        dot,
        numerical
    };

    enum class eyeve : u8
    {
        general,
        precomment,
        single_line_comment,
        multi_line_end_comment,
        multi_line_comment
    };

    enum class eyede : u8
    {
        global,
        compiler_version,
        indentation,
        measure
    };

    namespace hashes
    {
        //compiler_version
        constexpr pair compiler_version(2788337614625958691ull, 7360576879880264139ull);

        //indentation
        constexpr pair indentation(1115557258779054154ull, 5247152489884054320ull);

        //measure
        constexpr pair measure(8809352708207431423ull, 13586824709325088415ull);

        //milliseconds
        constexpr pair millisecond(14764342759833537195ull, 16848878135655731003ull);

        //microseconds
        constexpr pair microsecond(8292197474839951502ull, 9963175650068536944ull);

        //nanoseconds
        constexpr pair nanosecond(3217324105945459902ull, 5935205276411397260ull);
    }

    inline void dispatch_eyeven(sentence<eyeven>& s, bool& on) noexcept
    {
        s.token = on ? eyeven::numerical : [&](){on = true; return s.h == hashes::compiler_version ? eyeven::compiler_version : s.h == hashes::indentation ? eyeven::indentation : s.h == hashes::measure ? eyeven::measure : s.h == hashes::nanosecond ? eyeven::ns : s.h == hashes::microsecond ? eyeven::mcs : s.h == hashes::millisecond ? eyeven::ms : eyeven::unknown;}();
    }

    [[nodiscard]] inline bool process_cver_last(const eyede m, const u8 mode) noexcept
    {
        switch(m)
        {
            case eyede::global:
                return true;
            case eyede::compiler_version:
                return unexpected_ending_cver();
            case eyede::measure:
                return unexpected_ending_measure();
            case eyede::indentation:
                return unexpected_ending_indentation();
        }
    }

    [[nodiscard]] inline bool process_cver() noexcept
    {
        std::vector<sentence<eyeven>> sentences;
        const std::chrono::steady_clock::time_point& a = std::chrono::steady_clock::now();
        std::chrono::steady_clock::time_point b;
        {
            const std::string& content = read_file(compiler_version);
            b = std::chrono::steady_clock::now();
            sentence<eyeven> s;
            u64 ln = 1ull, ch = 0ull, lln = 0ull, lch = 0ull;
            eyeve m = eyeve::general;
            bool on = true, fc = false;
            for(const char c : content)
            {
                c == '\n' ? ++ln, ch = 0ull : ++ch;
                switch(m)
                {
                    case eyeve::general:
                        switch(c)
                        {
                            case alpha:
                                on = false;
                                if(!fc)
                                {
                                    fc = true;
                                    lln = ln;
                                    lch = ch;
                                    s.h = c;
                                }
                                else
                                    s.h += c;
                            break;
                            case numeric:
                                if(!fc)
                                {
                                    fc = true;
                                    lln = ln;
                                    lch = ch;
                                    s.h = c;
                                }
                                else
                                    s.h += c;
                            break;
                            case ' ':
                            case '\n':
                                if(fc)
                                {
                                    fc = false;
                                    dispatch_eyeven(s, on);
                                    sentences.push_back(s);
                                }
                            break;
                            case '=':
                                if(fc)
                                {
                                    fc = false;
                                    dispatch_eyeven(s, on);
                                    sentences.push_back(s);
                                }
                                s.token = eyeven::assignment;
                                s.ln = lln;
                                s.ch = lch;
                                s.h = '=';
                                sentences.push_back(s);
                            break;
                            case ';':
                                if(fc)
                                {
                                    fc = false;
                                    dispatch_eyeven(s, on);
                                    sentences.push_back(s);
                                }
                                s.token = eyeven::end_sentence;
                                s.ln = lln;
                                s.ch = lch;
                                s.h = ';';
                                sentences.push_back(s);
                            break;
                            case '.':
                                if(fc)
                                {
                                    fc = false;
                                    dispatch_eyeven(s, on);
                                    sentences.push_back(s);
                                }
                                s.token = eyeven::dot;
                                s.ln = lln;
                                s.ch = lch;
                                s.h = '.';
                                sentences.push_back(s);
                            break;
                            case '`':
                                m = eyeve::precomment;
                                if(fc)
                                {
                                    fc = false;
                                    dispatch_eyeven(s, on);
                                    sentences.push_back(s);
                                }
                            break;
                            default:
                                return unrecognized_character(compiler_version, ln, ch, c);
                        }
                    break;
                    case eyeve::single_line_comment:
                        if(c == '\n')
                            m = eyeve::general;
                    break;
                    case eyeve::multi_line_comment:
                        if(c == '*')
                            m = eyeve::multi_line_end_comment;
                    break;
                    case eyeve::precomment:
                        switch(c)
                        {
                            case '`':
                                m = eyeve::single_line_comment;
                            break;
                            case '*':
                                m = eyeve::multi_line_comment;
                            break;
                            default:
                                return unexpected_precomment_character(compiler_version, ln, ch, c);
                        }
                    break;
                    case eyeve::multi_line_end_comment:
                        switch(c)
                        {
                            case '`':
                                m = eyeve::general;
                            break;
                            case '*':
                            break;
                            default:
                                m = eyeve::multi_line_comment;
                            break;
                        }
                    break;
                }
            }
        }
        std::string cver;
        eyede m = eyede::global;
        u8 mode = 0u;
        for(const sentence<eyeven>& s : sentences)
            switch(m)
            {
                case eyede::global:
                    switch(s.token)
                    {
                        case eyeven::compiler_version:
                            m = eyede::compiler_version;
                        break;
                        case eyeven::measure:
                            m = eyede::measure;
                        break;
                        case eyeven::indentation:
                            m = eyede::indentation;
                        break;
                        default:
                            return unrecognized_cver_keyword(s);
                    }
                break;
                case eyede::compiler_version:
                    if(!mode)
                    {
                        if(s.token == eyeven::assignment)
                            mode = 1u;
                        else
                            return unrecognized_cver_assignment_token(s);
                    }
                    else
                        switch(s.token)
                        {
                            case eyeven::dot:
                                if(mode == 2u)
                                {
                                    mode = 1u;
                                    cver.append(1ull, '.');
                                }
                                else
                                    cver += "0.";
                            break;
                            case eyeven::numerical:
                                if(mode == 2u)
                                    return unrecognized_cver_repeated_numerical(s);
                                else
                                {
                                    mode = 2u;
                                    cver += s.h.content();
                                }
                            break;
                            case eyeven::end_sentence:
                                if(mode == 1u)
                                    cver.append(1ull, '0');
                                mode = 0u;
                                m = eyede::global;
                                if(cver == "0.0.1")
                                    project_compiler_version = version::_0_0_1;
                                else
                                    return unrecognized_cver(s);
                            break;
                            default:
                                return unrecognized_cver_token(s);
                        }
                break;
                case eyede::measure:
                    switch(mode)
                    {
                        case 0u:
                            if(s.token == eyeven::assignment)
                                mode = 1u;
                            else
                                return unrecognized_measure_assignment_token(s);
                        break;
                        case 1u:
                            mode = 2u;
                            switch(s.token)
                            {
                                case eyeven::ms:
                                    measure = measurement::milliseconds;
                                break;
                                case eyeven::mcs:
                                break;
                                case eyeven::ns:
                                    measure = measurement::nanoseconds;
                                break;
                                default:
                                    return unrecognized_measure_unit(s);
                            }
                        break;
                        case 2u:
                            if(s.token == eyeven::end_sentence)
                            {
                                mode = 0u;
                                m = eyede::global;
                            }
                            else
                                return unrecognized_measure_end_token(s);
                        break;
                    }
                break;
                case eyede::indentation:
                    switch(mode)
                    {
                        case 0u:
                            if(s.token == eyeven::assignment)
                                mode = 1u;
                            else
                                return unrecognized_indentation_assignment_token(s);
                        break;
                        case 1u:
                            if(s.token == eyeven::numerical)
                            {
                                mode = 2u;
                                indentation = std::stoull(s.h.content());
                                if(indentation)
                                    --indentation;
                            }
                            else
                                return unrecognized_indentation_numeric_token(s);
                        break;
                        case 2u:
                            if(s.token == eyeven::end_sentence)
                            {
                                mode = 0u;
                                m = eyede::global;
                            }
                            else
                                return unrecognized_indentation_end_token(s);
                        break;
                    }
                break;
            }
        const bool bo = process_cver_last(m, mode);
        if(bo)
        {
            const std::chrono::steady_clock::time_point& c = std::chrono::steady_clock::now();
            msg += "\n\nparsing " + file + compiler_version + no_error + " took:\n\n" + sequence + "sys(" + watchdog(measure, a, b) + ")\nuser(" + watchdog(measure, b, c) + ")\ntotal(" + watchdog(measure, a, c) + ")" + no_error;
        }
        return bo;
    }

    [[nodiscard]] inline bool compile() noexcept
    {
        if(!fiexists(compiler_version))
        {
            std::cout << "the project compiler version file '" << compiler_version << "' doesn't exists";
            return true;
        }
        else if(!fiexists(eye))
        {
            std::cout << "the project file '" << eye << "' doesn't exists";
            return true;
        }
        else if(!exists(source))
        {
            std::cout << "the folder '" << source << "' doesn't exists";
            return true;
        }
        else if(!exists(document))
        {
            std::cout << "the folder '" << document << "' doesn't exists";
            return true;
        }
        else if(!exists(library))
        {
            std::cout << "the folder '" << library << "' doesn't exists";
            return true;
        }
        else if(!exists(output))
        {
            std::cout << "the folder '" << output << "' doesn't exists";
            return true;
        }
        start = std::chrono::steady_clock::now();
        if(process_cver())
            switch(project_compiler_version)
            {
                case version::_0_0_1:
                    _0_0_1::eye_();
                break;
            }
        msg += "\n\npress 'r' to recompile or any other key to exit, and 'enter'...\n";
        std::cout << msg;
        char c;
        std::cin >> c;
        if(c == 'r')
        {
            clean();
            return compile();
        }
        return false;
    }

    inline void process(int argc, char** argv) noexcept
    {
        const std::string s(argv[argc - 1]);
        if(s == "version")
        {
            std::cout << compiler_actual_version;
            panic_msg();
        }
        else if(s.find("create-") != std::string::npos)
        {
            std::string sss("./");
            std::string ss;
            bool record = false, on = true;
            for(const char& c : s)
                switch (c)
                {
                    case '-':
                        record = true;
                    break;
                    case alpha:
                        on = false;
                        if(record)
                            ss.append(1ull, c);
                    break;
                    case numeric:
                        if(record)
                            ss.append(1ull, c);
                    break;
                    default:
                        if(record)
                        {
                            std::cout << "expected an alpha-numeric character, found '" + std::string(1ull, c) + "' at '" + s + '\'';
                            panic_msg();
                            return;
                        }
                    break;
                }
            if(on)
                std::cout << "the project '" << ss << "' is only numeric";
            else
            {
                sss += ss;
                if(exists(sss))
                    std::cout << "the folder '" << sss << "' already exists";
                else if(!create(sss))
                    std::cout << "the folder '" << sss << "' couldn't be created";
                else
                {
                    sss.append(1ull, '/');
                    const std::string src(sss + "src"), docs(sss + "docs"), libs(sss + "libs"), out(sss + "out"), eye(sss + ss + ".eye"), cver(sss + ss + ".cver");
                    if(!write_file(eye, "name = \"" + ss + "\";\nversion = ..1;\nauthor = \"unknown\";\n\nfirst_unit\n{\n    \n}"))
                        std::cout << "the project file '" << eye << "' couldn't be created";
                    else if(!write_file(cver, "compiler_version = " + compiler_actual_version + ';'))
                        std::cout << "the compiler version project file '" << cver << "' couldn't be created";
                    else if(!create(src))
                        std::cout << "the folder '" << src << "' couldn't be created";
                    else if(!create(docs))
                        std::cout << "the folder '" << docs << "' couldn't be created";
                    else if(!create(libs))
                        std::cout << "the folder '" << libs << "' couldn't be created";
                    else if(!create(out))
                        std::cout << "the folder '" << out << "' couldn't be created";
                    else
                        std::cout << "the project was created successfully";
                }
            }
            panic_msg();
        }
        else if(s.find("compile-") != std::string::npos)
        {
            {
                std::string ss;
                bool record = false, on = true;
                for(const char& c : s)
                    switch (c)
                    {
                        case '-':
                            record = true;
                        break;
                        case alpha:
                            on = false;
                            if(record)
                                ss.append(1ull, c);
                        break;
                        case numeric:
                            if(record)
                                ss.append(1ull, c);
                        break;
                        default:
                            if(record)
                            {
                                std::cout << "expected an alpha-numeric character, found '" + std::string(1ull, c) + "' at '" + s + '\'';
                                panic_msg();
                                return;
                            }
                        break;
                    }
                if(on)
                {
                    std::cout << "the project '" << ss << "' is only numeric";
                    panic_msg();
                    return;
                }
                else if(!exists(ss))
                {
                    std::cout << "the project folder '" << ss << "' doesn't exists";
                    panic_msg();
                    return;
                }
                std::string sss(ss + '/');
                compiler_version = sss + ss + ".cver";
                eye = sss + ss + ".eye";
                output = sss + "out";
                document = sss + "docs";
                library = sss + "libs";
                source = sss + "src";
            }
            if(compile())
                panic_msg();
        }
        else
        {
            std::cout << "expected 'version', 'create-proj' or 'compile-proj' at the last console argument, found '" + s + '\'';
            panic_msg();
        }
    }
}