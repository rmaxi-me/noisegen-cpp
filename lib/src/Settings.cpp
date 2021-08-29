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

#include <sstream>

#include "Settings.hpp"

std::ostream &pengen::operator<<(std::ostream &os, const pengen::Settings &settings)
{
    os << "width: " << settings.width << " height: " << settings.height << " octaves: " << settings.octaves
       << " persistence: " << settings.persistence << " count: " << settings.count << " jobs: " << settings.jobs
       << " bUseKenPerlinPermutations: " << settings.bUseKenPerlinPermutations
       << " outputFile: " << settings.outputFile;
    return os;
}

std::string pengen::Settings::toString() const
{
    std::ostringstream oss{};

    oss << *this;
    return oss.str();
}
