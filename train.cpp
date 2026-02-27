#include <iostream>   // for input (cin) and output (cout)
#include <vector>     // for using dynamic arrays (vector)
#include <algorithm>  // for max()
using namespace std;

int main() {

    // ----------------------------
    // STEP 1: READ INPUT
    // ----------------------------

    int n;             // number of train cars
    cin >> n;          // read n from input

    // a[i] will store the weight (or value) of the i-th train car
    vector<int> a(n);

    // read the weights of the train cars
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    // ---------------------------------------------------------
    // STEP 2: LONGEST INCREASING SUBSEQUENCE ENDING AT EACH i
    // ---------------------------------------------------------
    // incEnd[i] = length of the longest strictly increasing
    // subsequence that ends exactly at index i
    //
    // Example meaning:
    // If incEnd[i] = 3, we can pick 3 cars in increasing order
    // and the LAST car chosen is a[i].

    vector<int> incEnd(n, 1);

    // initialize all values to 1 because:
    // a single car by itself is an increasing subsequence of length 1

    for (int i = 0; i < n; i++) {
        // we are trying to compute incEnd[i]

        for (int j = 0; j < i; j++) {
            // j represents a position BEFORE i

            // check if we can place a[i] after a[j]
            // in a strictly increasing sequence
            if (a[j] < a[i]) {

                // if so, we can extend the increasing sequence
                // that ends at j by adding a[i]
                //
                // candidate length = incEnd[j] + 1
                incEnd[i] = max(incEnd[i], incEnd[j] + 1);
            }
        }
    }

    // ---------------------------------------------------------
    // STEP 3: LONGEST DECREASING SUBSEQUENCE STARTING AT EACH i
    // ---------------------------------------------------------
    // decStart[i] = length of the longest strictly decreasing
    // subsequence that starts exactly at index i
    //
    // Example meaning:
    // If decStart[i] = 3, we can start at a[i] and pick
    // 2 more cars to the right that strictly decrease.

    vector<int> decStart(n, 1);

    // initialize all values to 1 because:
    // a single car by itself is a decreasing subsequence of length 1

    // loop from right to left because decStart[i]
    // depends on values to the RIGHT of i
    for (int i = n - 1; i >= 0; i--) {

        for (int j = i + 1; j < n; j++) {
            // j represents a position AFTER i

            // check if we can go down from a[i] to a[j]
            if (a[j] < a[i]) {

                // if so, we can extend the decreasing sequence
                // starting at i by going to j
                //
                // candidate length = decStart[j] + 1
                decStart[i] = max(decStart[i], decStart[j] + 1);
            }
        }
    }

    // ---------------------------------------------------------
    // STEP 4: COMBINE INCREASING + DECREASING (BITONIC)
    // ---------------------------------------------------------
    // We now try every index i as the "peak" of the train.
    //
    // Total length if i is the peak:
    // incEnd[i] + decStart[i] - 1
    //
    // We subtract 1 because a[i] is counted in both sequences.

    int ans = 0;   // will store the maximum train length found

    for (int i = 0; i < n; i++) {

        // compute the bitonic length using i as the peak
        int candidate = incEnd[i] + decStart[i] - 1;

        // update the answer if this is better
        ans = max(ans, candidate);
    }

    // ----------------------------
    // STEP 5: OUTPUT RESULT
    // ----------------------------

    cout << ans << "\n";   // print the length of the longest valid train

    return 0;              // end the program
}