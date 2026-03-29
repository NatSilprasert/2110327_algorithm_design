#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Class {
    int start;
    int stop;
};

bool compare(Class a, Class b) {
    return a.stop < b.stop;
}

int n;
vector<Class> classes;

int main() {
    cin >> n;
    classes.resize(n);
    for (int i = 0; i < n; i++) cin >> classes[i].start;
    for (int i = 0; i < n; i++) cin >> classes[i].stop;

    sort(classes.begin(), classes.end(), compare);

    int count = 1;
    int prev_stop = classes[0].stop;
    for (int i = 1; i < n; i++) {
        if (classes[i].start >=  prev_stop) {
            count++;
            prev_stop = classes[i].stop;
        }
    }

    cout << count;

    return 0;
}