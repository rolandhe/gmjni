#!/bin/sh
echo "enter jnd dir and then build GmJni .................."
cd jni
sh clean.sh
sh build.sh
echo "back to home and build jar ......................"
cd ..
mvn clean package install -Dmaven.test.skip=true

