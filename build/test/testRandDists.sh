#! /bin/sh
# test/testRandDists.sh.  Generated from testRandDists.sh.in by configure.


./testRandDists < ../../Random/test/testRandDists.input \
  | sed 's/e-00\([0-9]\)/e-0\1/g' | diff -q -b - ../../Random/test/testRandDists.output > /dev/null
