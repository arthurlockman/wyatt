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

One of the major goals of this project was to create a framework for a robot that was testable and verifiable. The majority of code written by WPI RBE students is spaghetti code: it works well enough to get the lab report done but is not extendable, maintainable, or even correct in some cases. Furthermore, students must always be the in RBE lab to test their code. The code is typically tied to the hardware in such a way that they can't build and execute it on their own machines. As a result, development bottlenecked by a single robot and by the time it takes to upload, setup, and deploy the robot.  

## [](#header-2)Unit Test
In software engineering, unit tests are used to verify 'units' of code, prove that they work the first time, and check that a 'unit' of code still works after changes to the system. Moreover, good unit tests should check standard behavior as well as corner cases and exceptions.
 
A unit is a scoped section of code that has a defined input and output. In object-oriented programming, a unit is typically a class. 

To unit test a piece of code, one creates and gives as input some mock data to a unit and requires that a specific output is created.

### [](#header-3)Examples
Consider a java class that performs various algebraic functions.

```Java
class Algebra {
    int add(int a, int b);
    int subtract(int a, int b);
    int multiply(int a, int b);
    double divide(int num, int den);
}
```

Unit tests check expected behavior but should also check corner cases and exceptions.

```Java
// Check standard division
@Test
public void testSumLargeNumbers() {
    Algebra alg = new Algebra();
    assert(alg.divide(1, 2) == 0.5);
}
```

```Java
// Check dividing zero by an integer results in zero
@Test
public void testSumLargeNumbers() {
    Algebra alg = new Algebra();
    assert(alg.divide(0, 2) == 0.0);
}
```

```Java
// Check dividing by zero results in DivideByZeroException
@Test
public void testSumLargeNumbers() {
    Algebra alg = new Algebra();
    try{
        alg.divide(1, 0);
        fail(); // Fail if no exception thrown
    } catch(DivideByZeroException) {
        pass(); // Pass if expected exception
    } catch(Exception) {
        fail(); // Fail otherwise
    }
    
}
```

```Java
// Check dividing zero by zero results in DivideByZeroException
@Test
public void testSumLargeNumbers() {
    Algebra alg = new Algebra();
    try{
        alg.divide(0, 0);
        fail(); // Fail if no exception thrown
    } catch(DivideByZeroException) {
        pass(); // Pass if expected exception
    } catch(Exception) {
        fail(); // Fail otherwise
    }
    
}
```

## [](#header-2)Dependency Injection
Dependency injection is a software engineering principle used to create loosely-coupled and easily testable code. Dependency injection is the process of injecting dependencies into units of code through their constructors. This is best demonstrated with an example. Consider this command class below.

```C++
class DriveMotorSpeedCommand: public Command {

public:
    DriveMotorSpeedCommand(Motor* motor, Encoder* encoder, int speed);
}
```

The dependencies for this class are the encoder and the motor objects. The command is dependent on the encoder to get the most current speed reading and dependent on the motor object to control the motor.

With dependency injection, unit testing becomes a breeze. In the unit test, one can create mock objects for the motor and encoder that have specific behaviors. One can use this specific behavior to generate a specified set of input (in this case the current motor speed from the encoder) and check that a specific output is generated (the motor is driven in a particular direction).

```C++
TEST_CASE("DriveMotorSpeedCommand") {

    Motor* mockMotor = new MockMotor();     // MockMotor extends Motor
    Encoder* encoder = new MockEncoder();   // MockEncoder extends Encoder
    
    // Have the encoder read a speed of zero
    encoder.setValue(0);
    
    // Drive the wheel at 1 cm/s
    DriveMotorSpeedCommand(mockMotor, mockEncoder, 1);
    
    // Check that the motor is now being driven forwards
    REQUIRE(mockMotor.power() > 0);
    
}
```

Dependency injection is critical for creating testable code, even on a hardware-integrated system. Notice how the hardware is abstracted away in the unit test. **Now the code can be written and tested without a robot present!**

## [](#header-2)Test Driven Development


