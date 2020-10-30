# Monotonic
[![CodeFactor](https://www.codefactor.io/repository/github/cschladetsch/monotonic/badge)](https://www.codefactor.io/repository/github/cschladetsch/monotonic)
[![License](https://img.shields.io/github/license/cschladetsch/monotonic.svg?label=License&maxAge=86400)](./LICENSE.txt)
[![Release](https://img.shields.io/github/release/cschladetsch/monotonic.svg?label=Release&maxAge=60)](https://github.com/cschladetsch/monotonic/releases/latest)

A boost library propsal: **Fastest C++ Allocator**. Original [code with documentation here](https://svn.boost.org/svn/boost/sandbox/monotonic/libs/monotonic/doc/html/index.html).

This library provides the fastest way to manage memory in a C++ application. Yes, that is a bold claim. See the [exhaustive results]( http://github.com/cschladetsch/Monotonic/tree/master/libs/monotonic/test/results/). 

There are no source files - to add Monotonic functionality to your project, simply get latest and add the root folder to your include path.

## Building

```$ mkdir -p build && cmake .. && make```

## Running

```$ bin/monotonic_test```

## Testing

Tried and tested on Win7, Win8, Win10, Ubuntu and macOS.
