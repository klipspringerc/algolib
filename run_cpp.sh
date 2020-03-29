exename=$1
g++ -std=c++11 $exename.cpp -o $exename && ./$exename && rm $exename