#pragma once
#include <core/watchdog.hpp>

namespace aena
{
    namespace _0_0_1
    {
        std::string global_project_name("project"), global_project_version("0.0.1"), global_project_author("unknown");

        class compilation_unit
        {
        public:
            std::string name, local_project_name, local_project_version, local_project_author;

            inline void operator()() noexcept
            {
                local_project_name = global_project_name;
                local_project_version = global_project_version;
                local_project_author = global_project_author;
            }
        };
    }
}