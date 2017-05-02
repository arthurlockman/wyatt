---
layout: default
title: Wyatt - A Modular Robot Framework
---

Wyatt is designed to be a modular and *testable* framework for developing robot code. It provides structures for unit testing your robot code, as well as a framework for abstracting hardware to make it easy to adapt your code to whichever system you are running on.

You can check out all of the generated [project documentation here](html/index.html). If you're only interested in learning how to set up and use this framework for your own projects, you can jump to the [installation section](#installation).

# [](#header-1)Motivations

The primary motivation behind this project was to create a framework for small robotic systems that allowed for easy unit testing and proper test-driven development. We also wanted to provide a command-based framework similar to the one in [WPILib](https://github.com/wpilibsuite/allwpilib) (used in the FIRST robotics competition), but in a lighter-weight fashion. The framework needed to be able to run on a small computer like the Raspberry Pi, and provide excellent performance so that it can be used in a robot to solve a challenge that requires pseudo-realtime response to sensors.

We were so driven to make robots testable due in part to [WPI's Robotics Engineering](https://www.wpi.edu/academics/departments/robotics-engineering) core courses. Students in the robotics program are required to take a software engineering course as part of their studies, but due to the limited time afforded to them in the robotics courses and the lack of a good framework, robot code is often not functionally tested except for on the field. Students have no guarantee or even a good idea of whether or not their robot will reliably perform on the field, because they have no way of testing portions of their robot at a time. They can only test the whole thing together. We wanted to help with that by building this framework that allows students to build their robot code using the test-driven development techniques that they learn in software engineering. Our hope is that students will use this framework to build more reliable robots and put their software engineering skills to good use.

# [](#header-1)Takeaways

What we learned from the project

# [](#header-1)<a name="install"></a>Installation

Wyatt will run on Linux or Mac. Unfortunately we don't support Windows, though you can set up the project with Bash for Windows in the latest versions of Windows 10. It may also be possible to configure the project using [CLion](https://www.jetbrains.com/clion/) on Windows, but that has not been tested. For each of the supported platforms, installation instructions are provided below. If you are working on a Raspberry Pi, do not follow the Linux directions. Skip to the Raspberry Pi directions, as it requires different setup steps. 

## [](#header-2)Linux

This guide is written assuming you are using a Debian-based platform, with the apt package manager. You will need to first install a few dependencies, namely cmake, clang, doxygen, and lcov. You will then need to clone the git repository from the official GitHub repository. You can build this project using either clang or gcc, but we developed it using clang. If you don't want to use clang, omit the `export` lines from the bash snippet below.

```bash
sudo apt-get install cmake build-essential clang doxygen lcov git
git clone https://github.com/arthurlockman/wyatt.git
export CC=/usr/bin/clang
export CXX=/usr/bin/clang++
cd wyatt
mkdir build
cd build
cmake ..
make -j8
```

### [](#header-3)Raspberry Pi

The Raspberry Pi is a Linux platform, but it requires a few extra steps to make it work properly with the Wyatt framework. The main difference is that you will need to jump through a few extra hoops to get it to build with cmake and clang. First, install cmake, clang, and the other dependencies.

```bash
sudo apt-get install cmake build-essential clang-3.9 doxygen lcov git
ln -s /usr/bin/clang-3.9 /usr/bin/clang
ln -s /usr/bin/clang++-3.9 /usr/bin/clang++
```

Next, you will need to create a file so that cmake can find the WiringPi and WiringSerial libraries on the Raspberry Pi. Copy the following into your cmake module folder, which usually looks something like `/usr/share/cmake-3.x/Modules`:

```
find_library(WIRINGPI_LIBRARIES NAMES wiringPi)
find_path(WIRINGPI_INCLUDE_DIRS NAMES wiringPi.h)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(wiringPi DEFAULT_MSG WIRINGPI_LIBRARIES WIRINGPI_INCLUDE_DIRS)
```

Now, you can clone the project and complete the first build.

```bash
git clone https://github.com/arthurlockman/wyatt.git
export CC=/usr/bin/clang
export CXX=/usr/bin/clang++
cd wyatt
mkdir build
cd build
cmake ..
make -j8
```

## [](#header-2)macOS Sierra and Newer

This guide is written assuming you are using macOS Sierra or newer. If you are on an older platform you may need to modify these instructions. In order to start the installation, you will need to install [Homebrew from the official website](https://brew.sh). Once that is done, you need to install some dependencies, clone the git repository, and complete the initial build. If you have Xcode installed already, then you likely can skip installing clang using homebrew.

```bash
brew install cmake clang doxygen lcov git
git clone https://github.com/arthurlockman/wyatt.git
export CC=/usr/bin/clang
export CXX=/usr/bin/clang++
cd wyatt
mkdir build
cd build
cmake ..
make -j8
```

Assuming you have no errors in any of the install steps above, you are now ready to go! Skip down to the [getting started](#gettingstarted) guide to learn how to set up your own project, and how to build and run the provided example project.

# [](#header-1)<a name="gettingstarted"></a>Getting Started

Incoming!

## [](#header-2)Building

The project is built through cmake. We have provided an easy script to allow you to build and run your code. In the project root, simply run the `./deploy.sh` script to build and run your code. If you need to clean the build directory and do a complete rebuild, run `./deploy.sh -c`. This will delete the build directory, rebuild complete, and run your project.

## [](#header-2)Running

If you wish to simply run your code without building you need to run the build wyatt executable in the build directory. If you are using the standard `build` folder for building, you can run your project with this command:

```bash
./build/src/wyatt
```

## [](#header-2)Running Tests

To run your suite of unit tests built with Catch, you need to build your project and then run the testing executable in the project build directory.

```bash
cd build
cmake ..
make
cd ..
./build/test/wyatt_test
```

Alternatively, you can run tests with ctest (cmake's built-in testing library):

```bash
cd build
cmake ..
make
ctest -V
```

## [](#header-2)Code Coverage Reporting

Code coverage reporting is handled with ctest and lcov. Lcov handles generating the coverage report, and compiles the report in a format that can be understood by online code coverage reporting systems. We used [codecov.io](https://codecov.io/) for this project, but you can use any service that can accept output from lcov. To build your own HTML version of the code coverage report:

```bash
cd build
cmake ..
make
make Wyatt_coverage
```

Assuming no errors, your code coverage report can be found by opening `./build/coverage/index.html` in your project root.

## [](#header-2)Deploying to CI

This project is already successfully deployed to [Travis CI](https://travis-ci.org/arthurlockman/wyatt) for continuous integration testing and deployment. To deploy your own copy of this project to Travis or a similar CI provider, you will need to modify the [.travis.yml](https://github.com/arthurlockman/wyatt/blob/master/.travis.yml) file in the project root to suit your own project. This file handles building the project on Travis, and pushing the code coverage reports to Codecov. If you use Travis and Codecov to build your project, then you likely do not need to make any modifications to the [.travis.yml](https://github.com/arthurlockman/wyatt/blob/master/.travis.yml) file at all, and can use it as-is for your CI builds. There is also a [config file for codecov.io](https://github.com/arthurlockman/wyatt/blob/master/codecov.yml) in the project root, but if you don't need any modifications past what we've already customized then you can likely leave that file alone.

# [](#header-1)Creating Projects 

This overall section will show you how to make your own projects.

## [](#header-2)CMake

This will detail how to add your own files and structures to CMake.

## [](#header-2)Robot Structure

This will detail the Robot.h and Robot.cpp files, and how to set up a basic robot.

### [](#header-3)Command Framework

This section will detail how to write and run commands

# [](#header-1)Testing

This section will detail how to write your own unit tests in the framework (and how to deal with mock objects). Make sure to give some examples of unit tests.

```c++
SECTION("Test throws duplicate hardware exception when hardware with the same address is registered more than once.") {
    Hardware mockHardware1 = {255, sizeof(int)};
    Hardware mockHardware2 = {255, sizeof(int)};
    MockHardwareInterface* mockHardwareInterface = new MockHardwareInterface();

    /* Register hardware */
    comm->registerHardware(mockHardware1, mockHardwareInterface);

    REQUIRE_THROWS_AS(
            comm->registerHardware(mockHardware2, mockHardwareInterface),
            DuplicateHardwareException
    );
}
```

