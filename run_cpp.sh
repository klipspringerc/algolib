exename=$1
g++ -std=c++11 -I/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/asio-1.18.2/include -Wno-deprecated-declarations $exename.cpp -o $exename && ./$exename && rm $exename