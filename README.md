# Monotonic

A boost library propsal: Fastest C++ Allocator. Original code here http://ci.boost.org/svn-trac/browser/sandbox/monotonic?rev=86799.

This library provides the fastest way to manage memory in a C++ application. Yes, that is a bold claim. See the exhaustive results http://github.com/cschladetsch/Monotonic/tree/master/libs/monotonic/test/results/ 

There are no source files - to add Monotonic functionality to your project, simply get latest and add the root folder to your include path.

## Building

$ mkdir -p build && cmake .. && make

## Running

$ bin/monotonic_test

## Testing



Tried and tested on Win7, Win8, Ubuntu and macOS.


