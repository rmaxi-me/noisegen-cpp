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

#pragma once

#include <exception>
#include <string>
#include <string_view>

namespace pengen {
class Exception : public std::exception
{
public:
    Exception() = default;
    explicit Exception(const char *what);
    explicit Exception(std::string_view what);
    explicit Exception(std::string what);

    ~Exception() override = default;

    [[nodiscard]] const char *what() const noexcept override;
protected:
    std::string m_what{"pengen exception"};
};

class ArgumentParseException : public Exception
{
public:
    ArgumentParseException() = default;
    explicit ArgumentParseException(const char *what);
    explicit ArgumentParseException(std::string_view what);
    explicit ArgumentParseException(std::string what);
};
}  // namespace pengen
