#pragma once

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
#include "suffix_automaton_recheck.hpp"

/// &TRD_BEGIN
inline bool example_suffix_automaton() {
    sufauto sam;
    int last = 0;
    for (char c : std::string("ababa")) last = sam.add(last, c);
    sam.buildCnt();  // один раз после построения
    int v = sam.next[0].at('a');
    return sam.cnt[sam.next[v].at('b')] == 2;  // вхождения "ab"
}
/// &TRD_END
