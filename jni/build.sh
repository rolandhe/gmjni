#!bin/sh

echo "try to compile camke file and build GmJni lib .................."

cmake .
make clean
make

echo "copy lib to java resource................"
cp libGmJni.* ../src/main/resources/lib
rm libGmJni.*
