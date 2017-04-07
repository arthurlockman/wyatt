# How To Make Unit Tests

Create a new .cpp file in this directory (`/test/`)

Include catch.cpp:

```
#include "../catch/catch.hpp"
```

Write your test cases:

```
TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}
```

Refer to the [catch docs](https://github.com/philsquared/Catch) for how to write more complex unit tests.