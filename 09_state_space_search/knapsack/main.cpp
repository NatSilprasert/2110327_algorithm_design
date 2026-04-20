#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;

struct Item {
    double w, v, ratio;
};

int n;
double weight, result = 0;
vector<Item> items;

bool compare(const Item &p, const Item &q) {
    return p.ratio > q.ratio;
}

double getHeuristic(int i, double remainingW) {
    double totalV = 0;
    int j = i;
    while (j < n) {
        if (remainingW >= items[j].w) {
            totalV += items[j].v;
            remainingW -= items[j].w;
        }
        else {
            totalV += (remainingW / items[j].w) * items[j].v;
            break;
        }
        j++;
    }
    return totalV;
}

void knapsack(int i, double sumw, double sumv) {
    if (sumw > weight) return;
    if (i == n) {
        if (sumv > result) result = sumv;
        return;
    }

    if (sumv + getHeuristic(i, weight - sumw) <= result) return;

    // pick current
    knapsack(i + 1, sumw + items[i].w, sumv + items[i].v);
    // skip current
    knapsack(i + 1, sumw, sumv);
}

int main() {
    cin >> weight >> n;
    items.resize(n);
    for (int i = 0; i < n; i++) cin >> items[i].v;
    for (int i = 0; i < n; i++) {
        cin >> items[i].w;
        items[i].ratio = items[i].v / items[i].w;
    }

    sort(items.begin(), items.end(), compare);

    knapsack(0, 0.0, 0.0);

    cout << fixed << setprecision(4) << result << endl;

    return 0;
}