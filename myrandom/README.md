## myRandom ##

This class is my implementation of the java equivalent, StdRandom, by Robert Sedgewick and Kevin Wayne.

StdRandom can be found here: [StdRandom](http://introcs.cs.princeton.edu/java/22library/StdRandom.java.html)

It implements things like `uniform()` and `discrete` to help generate random numbers easier. It uses a `<random>` implementation of the `mt19937` generation engine from a non-deterministic `random_device` seed.