#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Item {
    int d, e, l;
};

bool compare(const Item &a, const Item &b) {
    return a.d < b.d;
}

int n, m, k;
vector<Item> v; 

int main() {
    cin >> n >> m >> k;
    for (int i = 0 ;i < k; i++) {
        int d, e, l;
        cin >> d >> e >> l;
        v.push_back({d, e, l});
    }

    sort(v.begin(), v.end(), compare);

    queue<Item> stock;
    queue<Item> order;
    for (int i = 0; i < k; i++) {
        Item curr = v[i];
        if (curr.e == 0) {
            if (order.empty()) {
                stock.push(curr);
                cout << 0 << endl;
            }
            else {
                Item currOrder = order.front();
                order.pop();
                cout << currOrder.l << endl;
            }
        }
        if (curr.e == 1) {
            if (stock.empty()) {
                order.push(curr);
                cout << 0 << endl;
            }
            else {
                Item currItem = stock.front();
                stock.pop();
                cout << currItem.l << endl;
            }
        }
    }

    return 0;
}