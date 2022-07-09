
<!-- README.md is generated from README.Rmd. Please edit that file -->

# {rvfc}

<!-- badges: start -->

[![experimental](http://badges.github.io/stability-badges/dist/experimental.svg)](http://github.com/badges/stability-badges)
<!-- badges: end -->

The goal of {rvfc} is to provide bindings for ‘Vector Field Consensus’
based on code provided in Ma et al. (2014).

> Jiayi Ma, Ji Zhao, Jinwen Tian, Alan Yuille, and Zhuowen Tu. (2014)
> “Robust Point Matching via Vector Field Consensus”, IEEE Transactions
> on Image Processing, 23(4), pp. 1706-1721. doi:
> 10.1109/TIP.2014.2307478.

For additional details on the algorithm, see:
<https://www.cs.jhu.edu/~ayuille/Pubs10_12/TIP2014.pdf>

## Installation

> NOTE: this is an experimental package that is allowing me to tinker
> with Rcpp and OpenCV. Feel free to use it but it is presently just one
> of many projects that I do as a proof of concept, mostly for myself.

You can install the development version of {rvfc} by first installing
{opencv}.

Follow the {opencv} instructions to install:
<https://docs.ropensci.org/opencv/>. At present this package does not
depend on {opencv}, it “Enhances,” it. To support independence of the
two packages, and as part of the proofi of concept, a limited amount of
glue code has been used from {opencv}, so special thanks to authors of
that package (Jeroen Ooms and Jan Wijffels).

You will need to install the relevant binaries (e.g. *libopencv-dev* on
Ubuntu) for your platform, and then install the R bindings. On
Windows/Mac you can use CRAN or r-universe to get appropriate, recent
binaries.

For instance (on Ubuntu):

``` sh
sudo apt install libopencv-dev
```

Then install from source, linking to your shared OpenCV libraries:

``` r
install.packages("opencv", type = "source")
```

Then, you can install the development version of {rvfc} from GitHub:

``` r
if (!requireNamespace("remotes")) 
  install.packages("remotes")
  
remotes::install_github("brownag/rvfc")
```

## Example

This is an experimental example of using the {opencv} `"opencv-image"`
class as input to a method. Currently (v0.0.0.9001) `compare()` is just
a demonstration function. It is hard-coded to use `cv:ORB` feature
detection/descriptor extraction, with `n=500` keypoints initially. These
`cv::KeyPoints` are reduced to a smaller set (mismatches removed) using
the VFC algorithm. This information (indices of matches, between 1 and
500) is not presently “useful,” as the keypoint coordinates are not made
available in this demo function, nor are they an input (yet).

Future interfaces will integrate more with functionality available in
{opencv}.

``` r
library(rvfc)

c1 <- system.file("extdata", "image", "church1.jpg", package="rvfc")
c2 <- system.file("extdata", "image", "church2.jpg", package="rvfc")

a <- opencv::ocv_read(c1)
a
#> <pointer: 0x5635cd5d1d30>
#> attr(,"class")
#> [1] "opencv-image"

b <- opencv::ocv_read(c2)
b
#> <pointer: 0x5635cd58c170>
#> attr(,"class")
#> [1] "opencv-image"

x <- compare(a, b)
x
#>  [1]   2   4  18  27  36  37  38  49  56  74  75  92  93  98 113 119 121 124 127
#> [20] 130 132 136 150 164 173 174 180 184 200 206 213 218 219 222 223 225 226 231
#> [39] 240 241 242 243 250 260 283 289 295 298 300 303 309 312 316 318 319 323 327
#> [58] 331 340 343 355 358 359 366 369 375 380 381 387 392 396 416 417 424
```
