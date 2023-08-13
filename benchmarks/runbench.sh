 exename=$1
 g++ -std=c++11 -lbenchmark -O3 $exename -o bm && ./bm