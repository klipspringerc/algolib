cmake_minimum_required(VERSION 3.8)
project(algolib)

include_directories(/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/asio-1.28.0/include)

SET (CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_STANDARD 11)

add_executable(algolib main.cpp ufds.cpp bt.cpp prime.cpp AVL.cpp algo.cpp bit_man.cpp suffix_array_lcp.cpp kmp.cpp LIS.cpp bi_tree.cpp dfs.cpp bfs.cpp rmq.cpp segment_tree.cpp lowest_common_ancestor.cpp UVa/uva_750.cpp UVa/uva_11195.cpp UVa/uva_261.cpp UVa/uva_00261_ac.cpp UVa/uva_11536.cpp UVa/uva_10909.cpp UVa/uva_11151.cpp UVa/uva_00469.cpp UVa/uva_01103.cpp UVa/uva_11080.cpp UVa/uva_11504.cpp UVa/uva_10600.cpp UVa/uva_11228.cpp UVa/uva_01013.cpp UVa/uva_01265.cpp UVa/uva_10943.cpp UVa/uva_10003.cpp UVa/uva_00259.cpp dinics.cpp UVa/uva_11380.cpp UVa/uva_00787.cpp UVa/uva_10755.cpp UVa/uva_12640.cpp UVa/uva_01105.cpp UVa/uva_01105_ac.cpp UVa/uva_10827.cpp UVa/uva_11951.cpp UVa/uva_01196.cpp UVa/uva_11456.cpp UVa/uva_11790.cpp contest15SG/p1.cpp contest15SG/p3.cpp contest15SG/p9.cpp contest15SG/p4.cpp contest15SG/p7.cpp segment_tree_mss.cpp UVa/uva_01213.cpp contest15JK/p4.cpp contest15JK/p9.cpp contest15JK/p12.cpp contest15JK/p7_d.cpp UVa/uva_11566.cpp UVa/uva_11832.cpp UVa/uva_00242.cpp UVa/uva_10448.cpp contest17Latin/p90.cpp contest17Latin/95.cpp contest17Latin/00.cpp contest17Latin/p3.cpp contest17Latin/p9.cpp whiteboard.cpp contest17Tsu/p1.cpp contest17Tsu/p1a.cpp contest17Tsu/p9.cpp practice7/pF.cpp lt/median_of_two_sorted_arrays.cpp practice8/pH.cpp practice8/pC.cpp practice8/pL.cpp permutation.cpp lt/28_find_string.cpp)