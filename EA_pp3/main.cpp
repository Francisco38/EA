#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

map<int, vector<int>> input;
vector<int> weight;
vector<int> times;
vector<int> solution;
vector<int> times_calc;
vector<int> bottle;

int inicial = 0;
int final = 0;
int invalid = 0;
int type = 0;
int n;
void find_solution() {
    int input2[n][n];
    if (type == 3) {
        for (int c = 0; c < n; c++) {
            for (int v = 0; v < n; v++) {
                input2[c][v] = 0;
            }
        }
    }
    priority_queue <int, vector<int>, greater<int>> Q;
    Q.push(inicial);
    if (type == 2) {
        times_calc[inicial - 1] = times[inicial - 1];
    }
    while (!Q.empty()) {
        int current = Q.top();
        Q.pop();
        weight[current - 1] = -1;
        vector<int> connec = input[current];

        if (type == 3 && Q.size() == 0) {
            int s = (int) solution.size();
            for (int i = 0; i < n; i++) {
                if (input2[current - 1][i] == 1) {
                    s--;
                }
            }
            if (s == 0) {
                bottle.push_back(current);
            }
        }
        solution.push_back(current);
        if (connec.size() == 0) {
            if (final != 0) {
                invalid = 1;
                return;
            } else {
                final = current;
            }
        }
        for (int i = 0; i < (int) connec.size(); i++) {
            weight[connec[i] - 1]--;
            if (type == 3) {
                input2[connec[i] - 1][current - 1] = 1;
                for (int t = 0; t < n; t++) {
                    if (input2[current - 1][t] == 1) {
                        input2[connec[i] - 1][t] = 1;
                    }
                }
            }
            if (type == 2) {
                if (times_calc[connec[i] - 1] < (times_calc[current - 1] + times[connec[i] - 1])) {
                    times_calc[connec[i] - 1] = times_calc[current - 1] + times[connec[i] - 1];
                }
            }
            if (weight[connec[i] - 1] == 0) {
                Q.push(connec[i]);
            }
        }
    }
    if((int)solution.size()!=n){
        invalid=1;
        return;
    }
}

int main() {
    cin >> n;
    weight.resize(n, 0);
    times_calc.resize(n, 0);
    times.resize(n, 0);
    vector<int> ini = {};
    for (int i = 1; i <= n; i++) {
        input[i] = ini;
    }
    for (int i = 1; i <= n; i++) {
        int t, d;
        cin >> t >> d;
        weight[i - 1] = d;
        times[i - 1] = t;
        if (d == 0) {
            if (inicial != 0) {
                invalid = 1;
            } else {
                inicial = i;
            }
        }
        for (int v = 0; v < d; v++) {
            int temp;
            cin >> temp;
            input[temp].push_back(i);
        }
    }
    cin >> type;
    if (inicial == 0) {
        invalid = 1;
    }
    if (invalid == 1) {
        cout << "INVALID" << endl;
    } else {
        find_solution();
        if (invalid == 1) {
            cout << "INVALID" << endl;
        } else {
            if (type == 0) {
                cout << "VALID" << endl;
            } else if (type == 1) {
                int sum = 0;
                for (int i = 0; i < (int) times.size(); i++) {
                    sum = sum + times[i];
                }
                cout << sum << endl;
                for (int i = 0; i < (int) solution.size(); i++) {
                    cout << solution[i] << endl;
                }
            } else if (type == 2) {
                cout << times_calc[final - 1] << endl;
            } else if (type == 3) {
                for (int i = 0; i < (int) bottle.size(); i++) {
                    cout << bottle[i] << endl;
                }
            }
        }
    }
    return 0;
}