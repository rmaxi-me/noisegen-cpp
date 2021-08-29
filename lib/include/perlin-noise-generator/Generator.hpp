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

#pragma once

#include <cmath>
#include <array>
#include <random>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <algorithm>

#include "Random.hpp"
#include "Settings.hpp"
#include "ScopedProfiler.hpp"

/*
 * This implementation is based on Ken Perlin's original implementation.
 * I improved and modified stuff I felt like modifying (such as frequency and octaves modifiers).
 *
 * Original implementation: https://mrl.cs.nyu.edu/~perlin/noise/
 */

namespace pengen {
class Generator
{
public:
    using PermutationArray = std::array<uint8_t, 256>;

    /**
     * Default Ken Perlin's permutation array
     */
    static constexpr PermutationArray s_KenPerlinPermutations{
      151, 160, 137, 91,  90,  15,  131, 13,  201, 95,  96,  53,  194, 233, 7,   225, 140, 36,  103, 30,  69,  142,
      8,   99,  37,  240, 21,  10,  23,  190, 6,   148, 247, 120, 234, 75,  0,   26,  197, 62,  94,  252, 219, 203,
      117, 35,  11,  32,  57,  177, 33,  88,  237, 149, 56,  87,  174, 20,  125, 136, 171, 168, 68,  175, 74,  165,
      71,  134, 139, 48,  27,  166, 77,  146, 158, 231, 83,  111, 229, 122, 60,  211, 133, 230, 220, 105, 92,  41,
      55,  46,  245, 40,  244, 102, 143, 54,  65,  25,  63,  161, 1,   216, 80,  73,  209, 76,  132, 187, 208, 89,
      18,  169, 200, 196, 135, 130, 116, 188, 159, 86,  164, 100, 109, 198, 173, 186, 3,   64,  52,  217, 226, 250,
      124, 123, 5,   202, 38,  147, 118, 126, 255, 82,  85,  212, 207, 206, 59,  227, 47,  16,  58,  17,  182, 189,
      28,  42,  223, 183, 170, 213, 119, 248, 152, 2,   44,  154, 163, 70,  221, 153, 101, 155, 167, 43,  172, 9,
      129, 22,  39,  253, 19,  98,  108, 110, 79,  113, 224, 232, 178, 185, 112, 104, 218, 246, 97,  228, 251, 34,
      242, 193, 238, 210, 144, 12,  191, 179, 162, 241, 81,  51,  145, 235, 249, 14,  239, 107, 49,  192, 214, 31,
      181, 199, 106, 157, 184, 84,  204, 176, 115, 121, 50,  45,  127, 4,   150, 254, 138, 236, 205, 93,  222, 114,
      67,  29,  24,  72,  243, 141, 128, 195, 78,  66,  215, 61,  156, 180};

    explicit Generator(Settings settings,
                       const std::optional<PermutationArray> &permutationArrayOverride = std::nullopt);

    void generate();
    void saveToPGM() const;
    [[nodiscard]] double noise3D(double x, double y, double z) const noexcept;

    template<typename Gen>
    void shufflePermutationArray(Gen &&generator)
    {
        PENGEN_SCOPED_PROFILER("Generator::shufflePermutationArray()");

        std::shuffle(m_permutations.begin(), m_permutations.end(), std::forward<Gen>(generator));
    }
    inline void shufflePermutationArray() { shufflePermutationArray(Random::s_generator); }

    [[nodiscard]] inline const Settings &getSettings() const noexcept { return m_settings; }
    [[nodiscard]] inline const PermutationArray &getPermutationArray() const noexcept { return m_permutations; }

private:
    Settings m_settings;
    PermutationArray m_permutations = s_KenPerlinPermutations;

    std::vector<double> m_frequencyCache{};
    std::vector<double> m_amplitudeCache{};

    std::vector<std::vector<double>> m_result{};
    double m_minNoiseValue{};
    double m_maxNoiseValue{};

    void cacheFrequencyAndAmplitude();

    /**
     * Get a permutation value from the array.
     * Allows index overflow for simpler operations with the array.
     * @param index for the array, allows overflow
     * @return m_permutations array value, modulo m_permutations.size()
     */
    [[nodiscard]] inline uint8_t getPermutation(size_t index) const
    {
        return m_permutations[index % m_permutations.size()];
    }

    static inline constexpr double fade(double t) noexcept { return t * t * t * (t * (t * 6 - 15) + 10); }
    static inline constexpr double lerp(double t, double a, double b) noexcept { return a + t * (b - a); }
    static inline constexpr double grad(int hash, double x, double y, double z) noexcept
    {
        const int h = hash & 15;
        const double u = h < 8 ? x : y, v = h < 4 ? y : h == 12 || h == 14 ? x : z;
        return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
    }
};
}  // namespace pengen
