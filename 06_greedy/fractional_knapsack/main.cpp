#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Item {
    double value;
    double weight;
    double ratio;
};

bool compare(Item a, Item b) {
    return a.ratio > b.ratio;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    double w;
    int n;
    cin >> w >> n;

    vector<Item> items(n);
    for (int i = 0; i < n; i++) cin >> items[i].value;
    for (int i = 0; i < n; i++) cin >> items[i].weight;
    for (int i = 0; i < n; i++) items[i].ratio = items[i].value / items[i].weight;

    sort(items.begin(), items.end(), compare);

    double curr_weight = 0;
    double curr_value = 0;
    for (int i = 0; i < n; i++) {
        if (curr_weight + items[i].weight <= w) {
            curr_weight += items[i].weight;
            curr_value  += items[i].value;
        } 
        else {
            double remaining_weight = w - curr_weight;
            curr_value += items[i].ratio * remaining_weight;
            break;
        }
    }

    cout << fixed << setprecision(4) << curr_value << endl;

    return 0;
}
