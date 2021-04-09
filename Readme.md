# Monotonic
[![CodeFactor](https://www.codefactor.io/repository/github/cschladetsch/monotonic/badge)](https://www.codefactor.io/repository/github/cschladetsch/monotonic)
[![License](https://img.shields.io/github/license/cschladetsch/monotonic.svg?label=License&maxAge=86400)](./LICENSE.txt)
[![Release](https://img.shields.io/github/release/cschladetsch/monotonic.svg?label=Release&maxAge=60)](https://github.com/cschladetsch/monotonic/releases/latest)

A boost library propsal: **Fastest C++ Allocator**. See original [boost documentation](https://htmlpreview.github.io/?https://github.com/cschladetsch/Monotonic/blob/develop/libs/monotonic/doc/html/index.html) and original [code with documentation here](https://svn.boost.org/svn/boost/sandbox/monotonic/libs/monotonic/doc/html/index.html).

This library provides the fastest way to manage memory in a C++ application. Yes, that is a bold claim. See the [exhaustive results]( http://github.com/cschladetsch/Monotonic/tree/master/libs/monotonic/test/results/). 

There are no source files - to add Monotonic functionality to your project, simply get latest and add the root folder to your include path.

## Building

### Building Boost Requirements

First, build only the requirements:

From Command line 

##### Windows
```
b2 address-model=64 link=static threading=multi runtime-link=shared build-dir=build\x86 install --prefix="c:\lib\boost\" filesystem chrono regex threading
```

##### Ubuntu
```
# sudo apt-get intall libdev-boost-filesystem libdev-boost-chrono libdev-boost-regex
```

Then build the test and performance harnesses:
```bash
$ mkdir -p build && cmake .. && make
```

## Testing

Tried and tested on Win7, Win8, Win10, Ubuntu and macOS.

## Results

See all comparative results, going back to 2009, [here](/libs/monotonic/test/results).

These are the latest results as of April 2021.

All numbers are normalised by the time taken for Monotonic, so a number < 0 means faster, a number > 0 means slower by that factor.

```
*******************************************************
		FINAL SUMMARY
*******************************************************
    scheme      mean   std-dev       min       max
      fast      30.2       119         0  1.04e+03
      pool        75  6.39e+04         1  2.38e+03
       std       3.6      3.04       0.5        11
```

See the [comparison code](/libs/monotonic/test/compare_memory_pool.cpp) and the latest [results](/libs/monotonic/test/results/2021).

