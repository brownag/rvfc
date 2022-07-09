library(rvfc)
library(opencv)
c1 <- system.file("extdata", "image", "church1.jpg", package="rvfc")
c2 <- system.file("extdata", "image", "church2.jpg", package="rvfc")
a <- opencv::ocv_read(c1)
a

b <- opencv::ocv_read(c2)
b

x <- compare(a, b)
x
