---
layout: default
---

Wyatt is designed to be a modular and *testable* framework for developing robot code. It provides structures for unit testing your robot code, as well as a framework for abstracting hardware to make it easy to adapt your code to whichever system you are running on.

You can check out all of the generated [project documentation here](html/index.html). If you're only interested in learning how to set up and use this framework for your own projects, you can jump to the [installation section](#installation).

# [](#header-1)Motivations

The primary motivation behind this project was that there wasn't a decent framework for smaller robots that allowed for easy unit testing. There are projects like [WPILib](https://github.com/wpilibsuite/allwpilib) which is used in the FIRST robotics competition which provide similar communication and command structures to Wyatt's, however WPILib does not at its core provide a way of unit testing your code. 

# [](#header-1)Takeaways

What we learned from the project

# [](#header-1)<a name="install"></a>Installation

Wyatt will run on Linux or Mac (sorry, no Windows support yet). 

Make sure to include info about the [WiringPi.cmake](http://stackoverflow.com/questions/30424236/add-wiringpi-lib-to-cmake-on-raspberrypi) file on the raspberry pi.

# [](#header-1)Getting Started

Incoming!

## [](#header-2)Building

```js
// Javascript code with syntax highlighting.
var fun = function lang(l) {
  dateformat.i18n = require('./lang/' + l)
  return true;
}
```

```ruby
# Ruby code with syntax highlighting
GitHubPages::Dependencies.gems.each do |gem, version|
  s.add_dependency(gem, "= #{version}")
end
```

## [](#header-2)Running

This section will detail how to run your code.

## [](#header-2)Running Tests

This section will detail how to run tests.

### [](#header-3)Deploying to CI

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

This section will detail how to write your own unit tests in the framework (and how to deal with mock objects).