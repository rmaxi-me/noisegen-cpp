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

    constexpr auto strToUInt32 = [](const std::string &value) { return static_cast<uint32_t>(std::stoul(value)); };
    constexpr auto strToDouble = [](const std::string &value) { return std::stod(value); };

    pengen::Settings settings{};
    argparse::ArgumentParser program{argv[0]};

    program
      .add_argument("width")                   //
      .help("width of the image to generate")  //
      .action(strToUInt32);
    program
      .add_argument("height")                   //
      .help("height of the image to generate")  //
      .action(strToUInt32);

    program
      .add_argument("-o", "--output")  //
      .help("output file name")        //
      .default_value(std::string{"output.pgm"});
    program
      .add_argument("-f", "--frequency")  //
      .help("noise frequency")            //
      .default_value(settings.frequency)  //
      .action(strToDouble);
    program
      .add_argument("-a", "--amplitude")  //
      .help("noise amplitude")            //
      .default_value(1.0)                 //
      .action(strToDouble);
    program
      .add_argument("-O", "--octaves")  //
      .help("octaves")                  //
      .default_value(1u)                //
      .action(strToUInt32);
    program
      .add_argument("-p", "--persistence")  //
      .help("persistence")                  //
      .default_value(0.5)                   //
      .action(strToDouble);
    program
      .add_argument("-n", "--count")  //
      .help("generate N images")      //
      .default_value(1u)              //
      .action(strToUInt32);
    program
      .add_argument("-j", "--jobs")                             //
      .help("(for N > 1) max concurrent jobs, use 0 for auto")  //
      .default_value(1u)                                        //
      .action(strToUInt32);
    program
      .add_argument("-k", "--kenperlin")                                     //
      .help("use Ken Perlin's permutation array instead of a shuffled one")  //
      .default_value(false)                                                  //
      .implicit_value(true);

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

    settings.width = program.get<uint32_t>("width");
    settings.height = program.get<uint32_t>("height");
    settings.octaves = program.get<uint32_t>("--octaves");
    settings.frequency = program.get<double>("--frequency");
    settings.amplitude = program.get<double>("--amplitude");
    settings.persistence = program.get<double>("--persistence");

    const auto output = program.get<std::string>("--output");
    [[maybe_unused]] const auto count = program.get<uint32_t>("--count");
    [[maybe_unused]] const auto jobs = program.get<uint32_t>("--jobs");

    fmt::print("{}\n", settings.toString());

    pengen::Generator generator{settings};

    generator.generate();
    generator.saveToPGM(output.c_str());

    return 0;
}
