---
layout: default
---

Wyatt is designed to be a modular and *testable* framework for developing robot code. It provides structures for unit testing your robot code, as well as a framework for abstracting hardware to make it easy to adapt your code to whichever system you are running on.

You can check out all of the generated [project documentation here](html/index.html). If you're only interested in learning how to set up and use this framework for your own projects, you can jump to the [installation section](#installation).

# [](#header-1)Motivations

The primary motivation behind this project was that there wasn't a decent framework for smaller robots that allowed for easy unit testing. There are projects like [WPILib](https://github.com/wpilibsuite/allwpilib) (used in the FIRST robotics competition) which provide similar communication and command structures to Wyatt's, however WPILib does not at its core provide a way of unit testing your code. 

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

Talk about how to build the code and how the build differs on different platforms.

## [](#header-2)Running

This section will detail how to run your code.

## [](#header-2)Running Tests

This section will detail how to run tests.

## [](#header-2)Code Coverage Reporting

This section will detail how to run code coverage and generate reports.

## [](#header-2)Deploying to CI

This section will detail how to deploy your own code to Travis CI or something similar.

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

