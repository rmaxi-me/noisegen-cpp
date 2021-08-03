/*
**   Copyright 2021 Maxime Houis
**
**   Licensed under the Apache License, Version 2.0 (the "License");
**   you may not use this file except in compliance with the License.
**   You may obtain a copy of the License at
**
**       http://www.apache.org/licenses/LICENSE-2.0
**
**   Unless required by applicable law or agreed to in writing, software
**   distributed under the License is distributed on an "AS IS" BASIS,
**   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
**   See the License for the specific language governing permissions and
**   limitations under the License.
*/

#include <fmt/core.h>
#include <random>

#include "Generator.hpp"

pengen::Generator::Generator(const pengen::ImageSize &size, const PermutationArray &permutationArray)
    : m_size{size}, m_permutations{permutationArray}
{
}

pengen::Generator::Generator(size_t x, size_t y, const PermutationArray &permutationArray)
    : Generator(ImageSize{x, y}, permutationArray)
{
}

void pengen::Generator::shufflePermutationArray()
{
    std::shuffle(m_permutations.begin(), m_permutations.end(), m_gen);
}

void pengen::Generator::printHelloWorld() const
{
    (void) this;
    fmt::print("Hello world!\n");
}
