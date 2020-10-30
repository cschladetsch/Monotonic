# Results 2020

All numbers are normalised by the time taken for Monotonic, so a number < 0 means faster, a number > 0 means slower by that factor.

Monotonic is still the fastest allocator, by at least a factor of 4.

The full results are listed [here](results.2020.txt).

## Environment

Fast desktop, VS 2019 Community Release build.

```
*******************************************************
		FINAL SUMMARY
*******************************************************
    scheme      mean   std-dev       min       max
      fast   20.9295   72.6713         0   358.083
      pool    31.434   14902.4         1      1191
       std   4.29316   4.05895       0.5         9
```

