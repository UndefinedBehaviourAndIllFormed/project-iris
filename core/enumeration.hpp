//Copyright 2022 Project Aura, All Rights Reserved
#pragma once

namespace aena
{
    template<class t> concept enumeration = __is_enum(t);
}