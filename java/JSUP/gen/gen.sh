#!/bin/bash

echo "Entering in bin directory";
cd ../bin;
echo "Current in: $(pwd)";

echo "";

echo "Generating .h";
javah -jni br.com.jsup.hardware.JSUPHardwareManager;

echo "";
echo "Moving .h to headers folder";
mv br_com_jsup_hardware_JSUPHardwareManager.h ../gen/headers;

echo ""

cd ../gen/headers
echo "Generated with success in:  $(pwd)";


