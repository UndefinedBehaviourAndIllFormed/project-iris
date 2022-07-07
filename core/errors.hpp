//Copyright 2022 Project Aura, All Rights Reserved
#pragma once
#include <core/database.hpp>

namespace aena
{
    const std::string error("\u001b[31m"), no_error("\u001b[37m"), file("\u001b[34m"), location("\u001b[32m"), sequence("\u001b[35m");

    //1
    template<class t> [[nodiscard]] inline bool unrecognized_cver_keyword(const sentence<t>& s)
    {
        msg += "\n\n" + error + "error(C1)" + no_error + " at " + file + compiler_version + no_error + ", " + location + s.end() + no_error + " -> unrecognized " + sequence + s.h.content() + no_error + " starting at " + location + s.start() + no_error + ", expected " + sequence + "compiler_version" + no_error + ", " + sequence + "measure" + no_error + " or " + sequence + "indentation" + no_error;
        return false;
    }
    
    //2
    template<class t> [[nodiscard]] inline bool unrecognized_cver_assignment_token(const sentence<t>& s)
    {
        msg += "\n\n" + error + "error(C2)" + no_error + " at " + file + compiler_version + no_error + ", " + location + s.end() + no_error + " -> unrecognized " + sequence + s.h.content() + no_error + " starting at " + location + s.start() + no_error + ", expected " + sequence + "=" + no_error + " to assign the compiler version";
        return false;
    }

    //3
    template<class t> [[nodiscard]] inline bool unrecognized_cver_repeated_numerical(const sentence<t>& s) noexcept
    {
        msg += "\n\n" + error + "error(C3)" + no_error + " at " + file + compiler_version + no_error + ", " + location + s.end() + no_error + " -> unexpected sub-version " + sequence + s.h.content() + no_error + " starting at " + location + s.start() + no_error + ", expected " + sequence + "." + no_error + " acting as a separator";
        return false;
    }

    //4
    template<class t> [[nodiscard]] inline bool unrecognized_cver(const sentence<t>& s) noexcept
    {
        std::string v;
        for(const std::string& vv : compiler_versions)
        {
            v.append(1ull, '\n');
            v += vv;
        }
        msg += "\n\n" + error + "error(C4)" + no_error + " at " + file + compiler_version + no_error + ", " + location + s.end() + no_error + " -> unrecognized compiler version " + sequence + s.h.content() + no_error + " starting at " + location + s.start() + no_error + ", specify one of these known versions:\n" + sequence + v + no_error;
        return false;
    }

    //5
    template<class t> [[nodiscard]] inline bool unrecognized_cver_token(const sentence<t>& s)
    {
        msg += "\n\n" + error + "error(C5)" + no_error + " at " + file + compiler_version + no_error + ", " + location + s.end() + no_error + " -> unrecognized " + sequence + s.h.content() + no_error + " starting at " + location + s.start() + no_error + ", expected a " + sequence + "numeric" + no_error + " value, " + sequence + "." + no_error + " or " + sequence + ";" + no_error;
        return false;
    }

    //6
    template<class t> [[nodiscard]] inline bool unrecognized_measure_assignment_token(const sentence<t>& s)
    {
        msg += "\n\n" + error + "error(C6)" + no_error + " at " + file + compiler_version + no_error + ", " + location + s.end() + no_error + " -> unrecognized " + sequence + s.h.content() + no_error + " starting at " + location + s.start() + no_error + ", expected " + sequence + "=" + no_error + " to assign the measurement unit";
        return false;
    }

    //7
    template<class t> [[nodiscard]] inline bool unrecognized_measure_unit(const sentence<t>& s)
    {
        msg += "\n\n" + error + "error(C7)" + no_error + " at " + file + compiler_version + no_error + ", " + location + s.end() + no_error + " -> unrecognized " + sequence + s.h.content() + no_error + " starting at " + location + s.start() + no_error + ", expected " + sequence + "microseconds" + no_error + ", " + sequence + "milliseconds" + no_error + " or " + sequence + "nanoseconds" + no_error + " to assign the measurement unit";
        return false;
    }

    //8
    template<class t> [[nodiscard]] inline bool unrecognized_measure_end_token(const sentence<t>& s)
    {
        msg += "\n\n" + error + "error(C8)" + no_error + " at " + file + compiler_version + no_error + ", " + location + s.end() + no_error + " -> unrecognized " + sequence + s.h.content() + no_error + " starting at " + location + s.start() + no_error + ", expected " + sequence + ";" + no_error + " to end the assignment of the measurement unit";
        return false;
    }

    //9
    template<class t> [[nodiscard]] inline bool unrecognized_indentation_assignment_token(const sentence<t>& s)
    {
        msg += "\n\n" + error + "error(C9)" + no_error + " at " + file + compiler_version + no_error + ", " + location + s.end() + no_error + " -> unrecognized " + sequence + s.h.content() + no_error + " starting at " + location + s.start() + no_error + ", expected " + sequence + "=" + no_error + " to assign the indentation space";
        return false;
    }

    //10
    template<class t> [[nodiscard]] inline bool unrecognized_indentation_numeric_token(const sentence<t>& s)
    {
        msg += "\n\n" + error + "error(C10)" + no_error + " at " + file + compiler_version + no_error + ", " + location + s.end() + no_error + " -> unrecognized " + sequence + s.h.content() + no_error + " starting at " + location + s.start() + no_error + ", expected a " + sequence + "numeric" + no_error + " value to assign the indentation space";
        return false;
    }

    //11
    template<class t> [[nodiscard]] inline bool unrecognized_indentation_end_token(const sentence<t>& s)
    {
        msg += "\n\n" + error + "error(C11)" + no_error + " at " + file + compiler_version + no_error + ", " + location + s.end() + no_error + " -> unrecognized " + sequence + s.h.content() + no_error + " starting at " + location + s.start() + no_error + ", expected " + sequence + ";" + no_error + " to end the assignment of the indentation space";
        return false;
    }

    //12
    [[nodiscard]] inline bool unexpected_ending_cver() noexcept
    {
        msg += "\n\n" + error + "error(C12)" + no_error + " at the end of " + file + compiler_version + no_error + " -> expected the assignment of the compiler version";
        return false;
    }

    //13
    [[nodiscard]] inline bool unexpected_ending_measure() noexcept
    {
        msg += "\n\n" + error + "error(C13)" + no_error + " at the end of " + file + compiler_version + no_error + " -> expected the assignment of the measurement unit";
        return false;
    }
    
    //14
    [[nodiscard]] inline bool unexpected_ending_indentation() noexcept
    {
        msg += "\n\n" + error + "error(C14)" + no_error + " at the end of " + file + compiler_version + no_error + " -> expected the assignment of the indentation space";
        return false;
    }

    //15
    [[nodiscard]] inline bool unrecognized_character(const std::string& f, const u64 ln, const u64 ch, const char c) noexcept
    {
        msg += "\n\n" + error + "error(C15)" + no_error + " at " + file + f + no_error + ", " + location + std::to_string(ln) + " : " + std::to_string(ch) + no_error + " -> unrecognized character " + sequence + std::string(1ull, c) + no_error;
        return false;
    }

    //16
    [[nodiscard]] inline bool unexpected_bar_character(const u64 ln, const u64 ch, const char c) noexcept
    {
        msg += "\n\n" + error + "error(C16)" + no_error + " at " + file + eye + no_error + ", " + location + std::to_string(ln) + " : " + std::to_string(ch) + no_error + " -> unexpected character " + sequence + std::string(1ull, c) + no_error + " after the bar literal string character " + sequence + "\\" + no_error + ", expected " + sequence + "\"" + no_error + " or another " + sequence + "\\" + no_error;
        return false;
    }

    //17
    [[nodiscard]] inline bool unexpected_precomment_character(const std::string& f, const u64 ln, const u64 ch, const char c) noexcept
    {
        msg += "\n\n" + error + "error(C17)" + no_error + " at " + file + f + no_error + ", " + location + std::to_string(ln) + " : " + std::to_string(ch) + no_error + " -> unexpected character " + sequence + std::string(1ull, c) + no_error + " after the pre-comment character " + sequence + "`" + no_error + ", expected " + sequence + "*" + no_error + " or another " + sequence + "`" + no_error;
        return false;
    }

    //18
    template<class t> [[nodiscard]] inline bool unexpected_numerical_value(const sentence<t>& s) noexcept
    {
        msg += "\n\n" + error + "error(C18)" + no_error + " at " + file + eye + no_error + ", " + location + s.end() + no_error + " -> unexpected " + sequence + s.h.content() + no_error + " starting at " + location + s.start() + no_error + ", the compilation unit name cannot be only-numeric";
        return false;
    }

    //19
    template<class t> [[nodiscard]] inline bool unknown_general_eye_token(const sentence<t>& s) noexcept
    {
        msg += "\n\n" + error + "error(C19)" + no_error + " at " + file + eye + no_error + ", " + location + s.end() + no_error + " -> unrecognized " + sequence + s.h.content() + no_error + " starting at " + location + s.start() + no_error + ", please use an alpha-numeric identifier to declare a compilation unit, or one of the following sentences:" + sequence + "\n\nname\nauthor" + no_error;
        return false;
    }

    //20
    template<class t> [[nodiscard]] inline bool unexpected_token_start_compilation_unit(const sentence<t>& s) noexcept
    {
        msg += "\n\n" + error + "error(C20)" + no_error + " at " + file + eye + no_error + ", " + location + s.end() + no_error + " -> found " + sequence + s.h.content() + no_error + " starting at " + location + s.start() + no_error + " without starting the compilation unit, use " + sequence + "{" + no_error + " instead";
        return false;
    }

    //21
    template<class t> [[nodiscard]] inline bool unexpected_token_compilation_unit(const std::string& name, const sentence<t>& s) noexcept
    {
        msg += "\n\n" + error + "error(C21)" + no_error + " at " + file + eye + no_error + ", " + location + s.end() + no_error + " -> found unrecognized command " + sequence + s.h.content() + no_error + " starting at " + location + s.start() + no_error + " for the compilation unit " + sequence + name + no_error + ", use one of the following commands:" + sequence + "\n\nname\nauthor\n" + no_error;
        return false;
    }

    //22
    template<class t> [[nodiscard]] inline bool unexpected_local_name_token_assignment(const std::string& name, const sentence<t>& s) noexcept
    {
        msg += "\n\n" + error + "error(C22)" + no_error + " at " + file + eye + no_error + ", " + location + s.end() + no_error + " -> found " + sequence + s.h.content() + no_error + " starting at " + location + s.start() + no_error + ", expected " + sequence + "=" + no_error + " to assign the literal string to the " + sequence + name + no_error + " project name";
        return false;
    }

    //23
    template<class t> [[nodiscard]] inline bool unexpected_global_name_token_assignment(const sentence<t>& s) noexcept
    {
        msg += "\n\n" + error + "error(C23)" + no_error + " at " + file + eye + no_error + ", " + location + s.end() + no_error + " -> found " + sequence + s.h.content() + no_error + " starting at " + location + s.start() + no_error + ", expected " + sequence + "=" + no_error + " to assign the literal string to the global project name";
        return false;
    }

    //24
    template<class t> [[nodiscard]] inline bool unexpected_local_name_empty_string(const std::string& name, const sentence<t>& s) noexcept
    {
        msg += "\n\n" + error + "error(C24)" + no_error + " at " + file + eye + no_error + ", " + location + s.end() + no_error + " -> empty " + sequence + name + no_error + " project name";
        return false;
    }

    //25
    template<class t> [[nodiscard]] inline bool unexpected_global_name_empty_string(const sentence<t>& s) noexcept
    {
        msg += "\n\n" + error + "error(C25)" + no_error + " at " + file + eye + no_error + ", " + location + s.end() + no_error + " -> empty global project name";
        return false;
    }

    //26
    template<class t> [[nodiscard]] inline bool unexpected_local_name(const std::string& name, const sentence<t>& s) noexcept
    {
        msg += "\n\n" + error + "error(C26)" + no_error + " at " + file + eye + no_error + ", " + location + s.end() + no_error + " -> unrecognized " + sequence + s.h.content() + no_error + " starting at " + location + s.start() + no_error + ", expected a non-empty literal string to specify the " + sequence + name + no_error + " project name";
        return false;
    }

    //27
    template<class t> [[nodiscard]] inline bool unexpected_global_name(const sentence<t>& s) noexcept
    {
        msg += "\n\n" + error + "error(C27)" + no_error + " at " + file + eye + no_error + ", " + location + s.end() + no_error + " -> unrecognized " + sequence + s.h.content() + no_error + " starting at " + location + s.start() + no_error + ", expected a non-empty literal string to specify the global project name";
        return false;
    }

    //28
    template<class t> [[nodiscard]] inline bool unexpected_local_name_end_sentence(const std::string& name, const sentence<t>& s) noexcept
    {
        msg += "\n\n" + error + "error(C28)" + no_error + " at " + file + eye + no_error + ", " + location + s.end() + no_error + " -> unrecognized " + sequence + s.h.content() + no_error + " starting at " + location + s.start() + no_error + ", expected " + sequence + ";" + no_error + " to end the specification of the " + sequence + name + no_error + " project name";
        return false;
    }

    //29
    template<class t> [[nodiscard]] inline bool unexpected_global_name_end_sentence(const sentence<t>& s) noexcept
    {
        msg += "\n\n" + error + "error(C29)" + no_error + " at " + file + eye + no_error + ", " + location + s.end() + no_error + " -> unrecognized " + sequence + s.h.content() + no_error + " starting at " + location + s.start() + no_error + ", expected " + sequence + ";" + no_error + " to end the specification of the global project name";
        return false;
    }

    //30
    template<class t> [[nodiscard]] inline bool unexpected_local_version_assignment(const std::string& name, const sentence<t>& s) noexcept
    {
        msg += "\n\n" + error + "error(C30)" + no_error + " at " + file + eye + no_error + ", " + location + s.end() + no_error + " -> found " + sequence + s.h.content() + no_error + " starting at " + location + s.start() + no_error + ", expected " + sequence + "=" + no_error + " to assign the version to the " + sequence + name + no_error + " project version";
        return false;
    }

    //31
    template<class t> [[nodiscard]] inline bool unrecognized_version_repeated_numerical(const sentence<t>& s) noexcept
    {
        msg += "\n\n" + error + "error(C31)" + no_error + " at " + file + compiler_version + no_error + ", " + location + s.end() + no_error + " -> unexpected sub-version " + sequence + s.h.content() + no_error + " starting at " + location + s.start() + no_error + ", expected " + sequence + "." + no_error + " acting as a separator";
        return false;
    }

    //32
    template<class t> [[nodiscard]] inline bool unrecognized_version_token(const sentence<t>& s)
    {
        msg += "\n\n" + error + "error(C32)" + no_error + " at " + file + compiler_version + no_error + ", " + location + s.end() + no_error + " -> unrecognized " + sequence + s.h.content() + no_error + " starting at " + location + s.start() + no_error + ", expected a " + sequence + "numeric" + no_error + " value, " + sequence + "." + no_error + " or " + sequence + ";" + no_error;
        return false;
    }

    //33
    template<class t> [[nodiscard]] inline bool unexpected_global_version_assignment(const sentence<t>& s) noexcept
    {
        msg += "\n\n" + error + "error(C33)" + no_error + " at " + file + eye + no_error + ", " + location + s.end() + no_error + " -> found " + sequence + s.h.content() + no_error + " starting at " + location + s.start() + no_error + ", expected " + sequence + "=" + no_error + " to assign the version to the global project version";
        return false;
    }

    //34
    template<class t> [[nodiscard]] inline bool unexpected_local_author_assignment(const std::string& name, const sentence<t>& s) noexcept
    {
        msg += "\n\n" + error + "error(C34)" + no_error + " at " + file + eye + no_error + ", " + location + s.end() + no_error + " -> found " + sequence + s.h.content() + no_error + " starting at " + location + s.start() + no_error + ", expected " + sequence + "=" + no_error + " to assign the author to the " + sequence + name + no_error + " project author";
        return false;
    }

    //35
    template<class t> [[nodiscard]] inline bool unexpected_local_author_token(const std::string& name, const sentence<t>& s) noexcept
    {
        msg += "\n\n" + error + "error(C35)" + no_error + " at " + file + eye + no_error + ", " + location + s.end() + no_error + " -> found " + sequence + s.h.content() + no_error + " starting at " + location + s.start() + no_error + ", expected a " + sequence + "literal string" + no_error + " to assign the author to the " + sequence + name + no_error + " project author";
        return false;
    }

    //36
    template<class t> [[nodiscard]] inline bool unexpected_empty_author(const sentence<t>& s) noexcept
    {
        msg += "\n\n" + error + "error(C36)" + no_error + " at " + file + eye + no_error + ", " + location + s.end() + no_error + " -> the author " + sequence + "literal string" + no_error + " must not be empty";
        return false;
    }

    //37
    template<class t> [[nodiscard]] inline bool unexpected_local_author_end(const std::string& name, const sentence<t>& s) noexcept
    {
        msg += "\n\n" + error + "error(C37)" + no_error + " at " + file + eye + no_error + ", " + location + s.end() + no_error + " -> found " + sequence + s.h.content() + no_error + " starting at " + location + s.start() + no_error + ", expected " + sequence + ";" + no_error + " to end the assignment of the author to the " + sequence + name + no_error + " project author";
        return false;
    }

    //38
    template<class t> [[nodiscard]] inline bool unexpected_global_author_assignment(const sentence<t>& s) noexcept
    {
        msg += "\n\n" + error + "error(C38)" + no_error + " at " + file + eye + no_error + ", " + location + s.end() + no_error + " -> found " + sequence + s.h.content() + no_error + " starting at " + location + s.start() + no_error + ", expected " + sequence + "=" + no_error + " to assign the author to the global project author";
        return false;
    }

    //39
    template<class t> [[nodiscard]] inline bool unexpected_global_author_token(const sentence<t>& s) noexcept
    {
        msg += "\n\n" + error + "error(C39)" + no_error + " at " + file + eye + no_error + ", " + location + s.end() + no_error + " -> found " + sequence + s.h.content() + no_error + " starting at " + location + s.start() + no_error + ", expected a " + sequence + "literal string" + no_error + " to assign the author to the global project author";
        return false;
    }

    //40
    template<class t> [[nodiscard]] inline bool unexpected_global_author_end(const sentence<t>& s) noexcept
    {
        msg += "\n\n" + error + "error(C40)" + no_error + " at " + file + eye + no_error + ", " + location + s.end() + no_error + " -> found " + sequence + s.h.content() + no_error + " starting at " + location + s.start() + no_error + ", expected " + sequence + ";" + no_error + " to end the assignment of the author to the global project author";
        return false;
    }

    //41
    inline void unexpected_no_files() noexcept
    {
        msg += "\n\n" + error + "error(C41)" + no_error + " at " + file + source + no_error + " -> no files with " + sequence + ".iris" + no_error + " extension were found";
    }

    //42

}