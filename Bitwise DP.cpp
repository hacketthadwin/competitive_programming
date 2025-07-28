    int countSubsetsWithValue(vector<int>& arr,
                              int target,
                              function<int(int,int)> op,
                              int maxState,
                              bool iterateHighToLow)
    {
        // dp[x] = # of subsets seen so far whose op‐value is exactly x
        vector<long long> dp(maxState + 1, 0);
        dp[0] = 1;   // the empty subset has “neutral” value:
                                     //   0 for OR, 0 for XOR, all‐1’s for AND
        for (int num : arr) {
            if (iterateHighToLow) {
                // for OR and AND: update from maxState→0
                for (int s = maxState; s >= 0; --s) {
                    dp[ op(s, num) ] += dp[s];
                }
            } else {
                // for XOR (and any operator where op(s,num) can be < s or > s
                // without a simple total order), you must snapshot:
                auto old = dp;
                for (int s = 0; s <= maxState; ++s) {
                    int t = op(s, num);
                    old[t] += dp[s];
                }
                dp.swap(old);
            }
        }
        return dp[target];
    }

    int countMaxOrSubsets(vector<int>& arr) {
        // your original code:
        int max_or = 0;
        for (int v : arr) max_or |= v;
        return countSubsetsWithValue(
            arr,
            max_or,
            [](int a,int b){return a|b;},
            max_or,
            true        // for OR, op(s,num) >= s so we go high→low
        );
    }

    int countTargetXorSubsets(vector<int>& arr, int target) {
        // XOR values range from 0 up to (next power‑of‑two minus one).
        // Find the maximum possible XOR‐mask:
        int mx = 0;
        for (int v : arr) mx |= v; 
        // round mx up to all 1’s: e.g. if mx=5 (101b) → mask=7 (111b)
        int mask = 1; while (mask <= mx) mask <<= 1; mask -= 1;

        return countSubsetsWithValue(
            arr,
            target,
            [](int a,int b){return a^b;},
            mask,
            false       // for XOR, op(s,num) can go up or down → snapshot
        );
    }

    int countTargetAndSubsets(vector<int>& arr, int target) {
        // AND values fall between 0 and min(all bits)—the largest possible
        // “all‐ones” base is determined similarly to OR:
        int allOnes = ~0;
        for (int v : arr) allOnes &= v;
        // but we really only need to consider up to the OR‐mask of arr:
        int max_or = 0; 
        for (int v: arr) max_or |= v;

        return countSubsetsWithValue(
            arr,
            target,
            [](int a,int b){return a&b;},
            max_or,
            true        // for AND, op(s,num) ≤ s so we go high→low
        );
    }
