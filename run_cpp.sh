exename=$1
g++ -std=c++11 -I. $exename.cpp -o $exename && ./$exename && rm $exename