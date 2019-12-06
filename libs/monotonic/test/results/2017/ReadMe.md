# Test Results

In general, any number you see has been divided by the time that Monotonic Allocator took.

So a Number like "15" means that the given allocator took 15 times longer than Monotonic took.

The summary lays it all out, but doesn't say it explictly: Monotonic is faster than any other allocation system out there. Yes, it has it limitations. You can't free Monotonic allocations. But that's not what it's for. It's for per-frame or per-second throw-away allocations. And it does that *fast*.
