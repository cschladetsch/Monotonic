# Monotonic
[![CodeFactor](https://www.codefactor.io/repository/github/cschladetsch/monotonic/badge)](https://www.codefactor.io/repository/github/cschladetsch/monotonic)
[![License](https://img.shields.io/github/license/cschladetsch/monotonic.svg?label=License&maxAge=86400)](./LICENSE.txt)
[![Release](https://img.shields.io/github/release/cschladetsch/monotonic.svg?label=Release&maxAge=60)](https://github.com/cschladetsch/monotonic/releases/latest)

A boost library propsal: **Fastest C++ Allocator**. See original [boost documentation](libs/monotonic/doc/html/index.html) and original [code with documentation here](https://svn.boost.org/svn/boost/sandbox/monotonic/libs/monotonic/doc/html/index.html).

This library provides the fastest way to manage memory in a C++ application. Yes, that is a bold claim. See the [exhaustive results]( http://github.com/cschladetsch/Monotonic/tree/master/libs/monotonic/test/results/). 

There are no source files - to add Monotonic functionality to your project, simply get latest and add the root folder to your include path.

## Building

*Note* There have been some changes to boost/std that I am working on fixing in the `develop` branch.

Current `master` branch will not build on 2021 machines.

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

These are the latest results as of November 2020.

All numbers are normalised by the time taken for Monotonic, so a number < 0 means faster, a number > 0 means slower by that factor.

```
*******************************************************
                FINAL SUMMARY
*******************************************************
    scheme      mean   std-dev       min       max
      fast   14.0359   49.7442         0   357.667
      pool   36.5891   22687.1         1      1225
       std   4.56216   4.24972       0.5         9
```

See the [comparison code](/libs/monotonic/test/compare_memory_pool.cpp) and the latest [results](/libs/monotonic/test/results/2020).

