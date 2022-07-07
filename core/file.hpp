#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <core/types.hpp>

namespace aena
{
    enum class file_type : u8
    {
        iris,
        cornea,
        retina,
        pupil,
        system_lib,
        native_lib,
        resource,
        unknown
    };

    class file_object
    {
    public:
        std::string f;

        file_type ft = file_type::iris;
    };

    [[nodiscard]] inline bool fiexists(const std::string& s) noexcept
    {
        return !std::filesystem::is_directory(s) && std::filesystem::exists(s);
    }

    [[nodiscard]] inline bool delete_(const std::string& s) noexcept
    {
        return std::filesystem::remove(s);
    }

    [[nodiscard]] inline std::string get_extension(const std::string& f) noexcept
    {
        u64 s = f.size();
        while(f[--s] != '.');
        std::string r;
        for(; s < f.size(); ++s)
            r.append(1ull, f[s]);
        return r;
    }

    [[nodiscard]] inline std::vector<file_object> get_files(const std::string& dir, const file_type ft) noexcept
    {
        std::vector<file_object> files;
        file_object fo;
        fo.ft = ft;
        const auto& lis = std::filesystem::recursive_directory_iterator(dir);
        for(const auto& File : lis)
		{
			fo.f = File.path().string();
            switch(ft)
            {
                case file_type::iris:
                    if(get_extension(fo.f) == ".iris")
                        files.push_back(fo);
                break;
            }
        }
        return files;
    }

    abool ReadFileLock = false;

    [[nodiscard]] inline std::string read_file(const std::string& s) noexcept
    {
        std::stringstream ss;
        while(ReadFileLock);
        ReadFileLock = true;
        std::ifstream i(s);
        ss << i.rdbuf();
        i.close();
        ReadFileLock = false;
        std::string sss(ss.str());
        sss.erase(std::remove(sss.begin(), sss.end(), '\r'), sss.end());
        sss.append(1ull, '\n');
        return sss;
    }

    [[nodiscard]] inline bool write_file(const std::string& s, const std::string& v) noexcept
    {
        if(fiexists(s))
            if(!delete_(s))
                return false;
        std::ofstream o(s);
        std::copy(v.cbegin(), v.cend(), std::ostream_iterator<char>(o));
        o.close();
        #if defined(aena_windows)
        return std::filesystem::file_size(s) == (v.size() + std::count(v.cbegin(), v.cend(), '\n'));
        #else
        return std::filesystem::file_size(s) == v.size();
        #endif
    }
}