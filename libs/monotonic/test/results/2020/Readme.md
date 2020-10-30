# Results 2020

All numbers are normalised by the time taken for Monotonic, so a number < 0 means faster, a number > 0 means slower by that factor.

Monotonic is still the fastest allocator.

## Environment
Fast desktop, VS 2019 Community Release build.

```
*******************************************************
		FINAL SUMMARY
*******************************************************
    scheme      mean   std-dev       min       max
      fast   5.19468   12.1203  0.224707   52.9735
      pool   32.8582   17507.5  0.140893   1097.28
       std  0.617688  0.409162 0.0450729   1.53835
       tbb         0         0         0         0
```

