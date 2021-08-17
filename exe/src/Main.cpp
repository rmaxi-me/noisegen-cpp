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
#include <argparse.hpp>

#include <perlin-noise-generator/Generator.hpp>
#include <perlin-noise-generator/Settings.hpp>

int main(int argc, const char *const *const argv)
{
    // constexpr auto strToInt = [](const std::string &value) { return std::stoi(value); };
    constexpr auto strToUInt = [](const std::string &value) {
        auto result = std::stoi(value);

        if (result < 0)
            throw std::invalid_argument("expected positive number");
        return result;
    };

    argparse::ArgumentParser program{argv[0]};

    program
      .add_argument("width")                   //
      .help("width of the image to generate")  //
      .action(strToUInt);
    program
      .add_argument("height")                   //
      .help("height of the image to generate")  //
      .action(strToUInt);

    program
      .add_argument("-o", "--output")  //
      .help("output file name")        //
      .default_value(std::string{"output.bmp"});
    program
      .add_argument("-f", "--frequency")  //
      .help("noise frequency")            //
      .default_value(0)                   //
      .action(strToUInt);
    program
      .add_argument("-a", "--octaves")  //
      .help("octaves")                  //
      .default_value(0)                 //
      .action(strToUInt);
    program
      .add_argument("-n", "--count")  //
      .help("generate N images")      //
      .default_value(1)               //
      .action(strToUInt);
    program
      .add_argument("-j", "--jobs")                             //
      .help("(for N > 1) max concurrent jobs, use 0 for auto")  //
      .default_value(1)                                         //
      .action(strToUInt);

    try
    {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error &e)
    {
        std::cerr << program;
        std::cerr << "\nerror: " << e.what() << '\n';
        return 1;
    } catch (const std::invalid_argument &e)
    {
        std::cerr << program;
        std::cerr << "\nerror: invalid argument: " << e.what() << '\n';
        return 1;
    }

    pengen::Settings settings{};
    settings.width = program.get<int>("width");
    settings.height = program.get<int>("height");
    settings.frequency = program.get<int>("--frequency");
    settings.octaves = program.get<int>("--octaves");
    const auto output = program.get<std::string>("--output");
    const auto count = program.get<int>("--count");
    const auto jobs = program.get<int>("--jobs");

    fmt::print("{} {} {} {} {} {} {}\n", settings.width, settings.height, settings.frequency, settings.octaves, output,
               count, jobs);

    return 0;
}
