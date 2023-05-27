//
// https://leetcode.com/problems/longest-duplicate-substring/description/
// Solve with Suffix array + the LCP solution
//


#include <string>
#include <vector>
#include <cstdio>
#include <iostream>
using namespace std;


class Solution {
public:
    vector<int>SA;
    vector<int>tempSA;
    vector<int>RA;
    vector<int>tempRA;
    vector<int>count;
    string longestDupSubstring(string s) {
        s+='$';
        int n = s.length();
        count.resize(max(n, 256)+2);
        SA.resize(n);
        tempSA.resize(n);
        // SA[0] = 0 means suffix s[0:], SA[3] = 3 means suffix s[3:]
        // so each integer in [0,n) could represent a unique suffix
        for (int i = 0; i < n; i++)
            SA[i] = i;
        // ranking array, used represent rank order between SAs
        // index of RA is string position (not SA position)
        // so find ranking of certain SA is RA[SA[i]]
        RA.resize(n);
        tempRA.resize(n);

        for (int i = 0; i < n; i++)
            RA[i] = s[i]; // initial ordering based on char order
        int size = 256;
        // radix sort for efficient SA sorting.
        for (int k = 1; k < n; k<<=1) {
            countingSort(k, n, size);
            countingSort(0, n, size);
            int r = 0;
            tempRA[SA[0]] = r;
            // reorder from 0, 1, 2, 3, 4
            for (int i = 1; i < n; i++) {
                // only assign same order when RA[SA[i]] and RA[SA[i]+k] are exactly the same with prior SA[i-1]
                bool same = true;
                if (RA[SA[i]] != RA[SA[i-1]])
                    same = false;
                else if (SA[i]+k < n && SA[i-1]+k >= n || SA[i]+k >= n && SA[i-1]+k < n)
                    same = false;
                if (same && ( SA[i]+k < n && SA[i-1]+k < n && RA[SA[i]+k] != RA[SA[i-1]+k]))
                    same = false;
                tempRA[SA[i]] = same? r : ++r;
            }
            size = r+1;
            for (int i = 0; i < n; i++) {
                RA[i] = tempRA[i];
            }
            if (RA[SA[n-1]] == n-1)
                // this means all SAs are successfully sorted from 1 to ... n-1
                break;
        }
        // print SAs
        for (int i = 0; i < n; i++) {
            if (s[SA[i]] == 'a'&& n-SA[i] > 510) {
                cout << "a substr length " << (n-SA[i]) <<endl;
//                cout << s.substr(SA[i], n-SA[i]) <<endl;
            }

        }
        // the main idea is to use sorted SA to jump start next comparison
        // e.g. consider the SA array
        // a b a b e
        // a b e
        // b a b e
        // b e
        // e
        // phi record the previous SA in this sorted order
        // so after comparing ababe and abe, L = 2, then when moving on to next position babe and be, L could start at 2-1=1

        vector<int> phi (n);
        phi[0]= -1;
        for (int i = 1; i < n; i++)
            phi[SA[i]] = SA[i-1];
//        vector<int> plcp(n);
        int max_lcp = -1;
        int max_pos = -1;
        for (int i = 0, L=0; i < n; i++) {
            if (phi[i] == -1) {
//                plcp[i] = 0;
                continue;
            }
            if (i == 0)
                cout << "phi of 0 is " << phi[0] << " cur n is " << n << endl;
            while(i+L < n && phi[i]+L <n && s[i + L] == s[phi[i]+L]) L++;
//            plcp[i] = L;
            if (i == 0) {
                cout << "idx 0 got L value " << L << endl;
                cout << (s[i + L] == s[phi[i]+L]) << endl;
            }
            if (L > max_lcp) {
                max_lcp = L;
                max_pos = i;
            }
            L = max(L-1, 0);

        }
        printf("max pos %d lcp %d\n", max_pos, max_lcp);
        return s.substr(max_pos, max_lcp);
    }

    // sort based on the k-th char of each suffix
    // size is the max value of ranking value in RA, smaller RA -> faster counting sort
    void countingSort(int k, int n, int size) {
        int sum=0;
        fill(count.begin(), count.end(), 0);
        for (int i =0; i < n; i++) {
            // if offset k exceed n , put first
            count[(i+k < n)? RA[i+k] : 0]++;
        }
//        int max_i = max(size, n);
        for (int i = 0; i <= size; i++) {
            int t = count[i];
            count[i]= sum;
            sum+=t;
        }
        for (int i = 0; i < n; i++) {
            // reorder SA based on counting sum.
            // again, if i+k exceed suffix range, put at front, all SA would be sorted again by k=0 after this sort.
            tempSA[count[(SA[i]+k < n)? RA[SA[i]+k] : 0]++] = SA[i];
        }
        for (int i = 0; i < n; i++) {
            SA[i] = tempSA[i];
        }
    }

};

void test() {
    string t = "ababe";
    t.append("$");
    vector<string> sa;
    for (int i = 0; i < t.length(); i++) {
        sa.push_back(t.substr(i, t.length()-i));
    }
    sort(sa.begin(), sa.end());
    for (auto s : sa)
        printf("%s\n", s.c_str());

    vector<pair<string, int>> sap(t.length());
    for (int i = 0 ; i < t.length(); i++) {
        sap[i] = make_pair(t.substr(i, t.length() - i), i);
    }
    sort(sap.begin(), sap.end(), greater<pair<string, int>>());
//    reverse(sap.begin(), sap.end());
    for (auto p : sap) {
        printf("%s %d\n", p.first.c_str(), p.second);
    }
}

int main() {
    test();
    return 0;
    Solution s;
//    string r = s.longestDupSubstring("GATAGACA");
    string tl  = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
//    string tl = "aaabbbbcccccddddddeeeeeeeffffffffffffffffzzzzzzzzzzzzzzzzzzz";
    string r = s.longestDupSubstring(tl);

    cout << "longest repreating substr: " << r << endl;
}