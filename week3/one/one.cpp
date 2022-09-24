#include <vector>
#include <iostream>
#include <math.h>
#include <functional>

using namespace std;

int main() {
    int n; cin >> n;
    // Find the cheapest nodes. Then build the more expensive nodes using the cheaper ones.
    // The cheapest node is 1 (requires one 1)
    // Next are all the nodes which require 2 ones.
    // (1 + 1), (1 * 1), (1 @ 1)
    // One thing that's kind of tricky is the all permutations of composites must be attempted for concactenation.
    // We also have to use more then two operations. For the rest, it's sufficient to use only existing numbers.
    // For concactenation, we need to actually try all permuations.
}