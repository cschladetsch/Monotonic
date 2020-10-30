# Results 2020

Standard lib beats monotonic for the first time. All numbers are normalised by the time taken for Monotonic, so a number < 0 means faster, a number > 0 means slower by that factor.

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

And by a good measure too. This was running in a virtual machine, so I will update after running natively.
