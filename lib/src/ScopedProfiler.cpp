/*
 * Copyright (c) 2021-2021 [fill name later]
 *
 * This software is provided "as-is", without any express or implied warranty. In no event
 *     will the authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose, including commercial
 *     applications, and to alter it and redistribute it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not claim that you
 *     wrote the original software. If you use this software in a product, an acknowledgment
 *     in the product documentation would be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be misrepresented
 * as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 */

#include <iomanip>
#include <iostream>

#include "ScopedProfiler.hpp"

pengen::utils::ScopedProfiler::ScopedProfiler(const char *name) noexcept : m_start{Clock::now()}, m_name{name}
{
}

pengen::utils::ScopedProfiler::~ScopedProfiler()
{
    const auto end = Clock::now();
    const DurationSeconds durationSeconds = end - m_start;
    const DurationMillis durationMillis = durationSeconds;

    auto stream = std::ostringstream{};

    /*if (durationSeconds.count() >= 1)
        stream << durationSeconds.count() << "s";
    else*/
    stream << durationMillis.count() << "ms";

    std::cerr << m_name << " => " << stream.str() << '\n';
}
