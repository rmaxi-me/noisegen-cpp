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

#include <CImg.h>
#include <argparse/argparse.hpp>

#include <noisegen/Generator.hpp>
#include <noisegen/Settings.hpp>
#include <noisegen/ScopedProfiler.hpp>
#include <noisegen/Exception.hpp>

static noisegen::Settings parseArguments(int argc, const char *const *const argv)
{
    NOISEGEN_SCOPED_PROFILER("parseArguments()");

    noisegen::Settings settings{};

    // constexpr auto strToInt = [](const std::string &value) { return std::stoi(value); };
    constexpr auto strToUInt32 = [](const std::string &value) { return static_cast<uint32_t>(std::stoul(value)); };
    constexpr auto strToDouble = [](const std::string &value) { return std::stod(value); };

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
      .default_value(settings.outputFile);
    program
      .add_argument("-O", "--octaves")  //
      .help("octaves")                  //
      .default_value(settings.octaves)  //
      .action(strToUInt32);
    program
      .add_argument("-p", "--persistence")  //
      .help("noise persistence")            //
      .default_value(settings.persistence)  //
      .action(strToDouble);
    program
      .add_argument("-n", "--count")  //
      .help("generate N images")      //
      .default_value(settings.count)  //
      .action(strToUInt32);
    program
      .add_argument("-k", "--kenperlin")                                     //
      .help("use Ken Perlin's permutation array instead of a shuffled one")  //
      .default_value(settings.bUseKenPerlinPermutations)                     //
      .implicit_value(true);
    program
      .add_argument("-d", "--dry-run")       //
      .help("don't write anything to disk")  //
      .default_value(settings.bDryRun)       //
      .implicit_value(true);

    try
    {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error &e)
    {
        std::cerr << program;
        std::cerr << "\nerror: " << e.what() << '\n';
        throw noisegen::ArgumentParseException{};
    } catch (const std::invalid_argument &e)
    {
        std::cerr << program;
        std::cerr << "\nerror: invalid argument: " << e.what() << '\n';
        throw noisegen::ArgumentParseException{};
    }

    settings.width = program.get<uint32_t>("width");
    settings.height = program.get<uint32_t>("height");
    settings.octaves = program.get<uint32_t>("--octaves");
    settings.persistence = program.get<double>("--persistence");
    settings.outputFile = program.get<std::string>("--output");
    settings.count = program.get<uint32_t>("--count");
    settings.bDryRun = program.get<bool>("--dry-run");
    settings.bUseKenPerlinPermutations = program.get<bool>("--kenperlin");

    return settings;
}

int main(int argc, const char *const *const argv)
{
    NOISEGEN_SCOPED_PROFILER("main()");

    noisegen::Settings settings;

    try
    {
        settings = parseArguments(argc, argv);
    } catch (const noisegen::ArgumentParseException &)
    {
        return 1;
    }

    noisegen::Generator generator{settings};

    generator.generate();
    generator.saveToPGM();

    // TODO: remove
    cimg_library::CImg<int> img{};

    return 0;
}
