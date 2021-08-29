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

#include <limits>
#include <utility>
#include <fstream>
#include <iostream>
#include <execution>

#include "Generator.hpp"
#include "ScopedProfiler.hpp"

/*
 * This implementation is based on Ken Perlin's original implementation.
 * I improved and modified stuff I felt like modifying (such as frequency and octaves modifiers).
 *
 * Original implementation: https://mrl.cs.nyu.edu/~perlin/noise/
 */

pengen::Generator::Generator(Settings settings, const std::optional<PermutationArray> &permutationArrayOverride)
    : m_settings{std::move(settings)}
{
    PENGEN_SCOPED_PROFILER("Generator()");

    if (permutationArrayOverride.has_value())
        m_permutations = permutationArrayOverride.value();
    else if (!settings.bUseKenPerlinPermutations)
        shufflePermutationArray();

    cacheFrequencyAndAmplitude();
}

double pengen::Generator::noise3D(double x, double y, double z) const noexcept
{
    int X = static_cast<int>(std::floor(x)) & 255;
    int Y = static_cast<int>(std::floor(y)) & 255;
    int Z = static_cast<int>(std::floor(z)) & 255;

    x -= std::floor(x);
    y -= std::floor(y);
    z -= std::floor(z);

    const double u = fade(x);
    const double v = fade(y);
    const double w = fade(z);

    const int A = getPermutation(X) + Y;
    const int AA = getPermutation(A) + Z;
    const int AB = getPermutation(A + 1) + Z;
    const int B = getPermutation(X + 1) + Y;
    const int BA = getPermutation(B) + Z;
    const int BB = getPermutation(B + 1) + Z;

    return lerp(
      w,
      lerp(v, lerp(u, grad(getPermutation(AA), x, y, z), grad(getPermutation(BA), x - 1, y, z)),
           lerp(u, grad(getPermutation(AB), x, y - 1, z), grad(getPermutation(BB), x - 1, y - 1, z))),
      lerp(v, lerp(u, grad(getPermutation(AA + 1), x, y, z - 1), grad(getPermutation(BA + 1), x - 1, y, z - 1)),
           lerp(u, grad(getPermutation(AB + 1), x, y - 1, z - 1), grad(getPermutation(BB + 1), x - 1, y - 1, z - 1))));
}

void pengen::Generator::generate()
{
    PENGEN_SCOPED_PROFILER("Generator::generate()");

    // keep track of min and max value for scaling later
    m_minNoiseValue = std::numeric_limits<double>::max();
    m_maxNoiseValue = std::numeric_limits<double>::min();

    const auto invWidth = 1.0 / m_settings.width;
    const auto invHeight = 1.0 / m_settings.height;

    m_result.reserve(m_settings.width * m_settings.height);
    for (uint32_t y = 0; y < m_settings.height; y++)
        for (uint32_t x = 0; x < m_settings.width; x++)
            m_result.emplace_back(x, y);

    std::for_each(std::execution::par_unseq, m_result.begin(), m_result.end(), [&](auto &&pixel) {
        const auto x = pixel.x;
        const auto y = pixel.y;
        double noiseValue = 0.0;

        for (uint32_t octave = 0; octave < m_settings.octaves; ++octave)
        {
            noiseValue +=
              noise3D(x * invWidth * m_frequencyCache[octave], y * invHeight * m_frequencyCache[octave], 0) *
              m_amplitudeCache[octave];
        }

        m_minNoiseValue = std::min(m_minNoiseValue, noiseValue);
        m_maxNoiseValue = std::max(m_maxNoiseValue, noiseValue);

        m_result[y * m_settings.width + x].value = noiseValue;
    });
}

void pengen::Generator::saveToPGM() const
{
    PENGEN_SCOPED_PROFILER("Generator::saveToPGM()");

    std::ofstream file{m_settings.outputFile};

    file << "P2\n"                                                //
         << m_settings.width << ' ' << m_settings.height << '\n'  //
         << "255\n";

    for (const auto &pixel : m_result)
    {
        const auto grayscale =
          static_cast<int>(std::round((pixel.value - m_minNoiseValue) / (m_maxNoiseValue - m_minNoiseValue) * 255.0));

        file << grayscale << '\n';
    }
}

void pengen::Generator::cacheFrequencyAndAmplitude()
{
    m_frequencyCache.resize(m_settings.octaves);
    m_amplitudeCache.resize(m_settings.octaves);

    for (uint32_t octave = 0; octave < m_settings.octaves; octave++)
    {
        m_frequencyCache[octave] = std::pow(2, octave);
        m_amplitudeCache[octave] = std::pow(m_settings.persistence, octave);
    }
}
