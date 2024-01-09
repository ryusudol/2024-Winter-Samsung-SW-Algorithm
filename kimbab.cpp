// 1000/1000
#include <iostream>
#include <cmath>
using namespace std;

pair<int, int> findPosition(int num) {
    int height = 0;
    int standard = 0;
    while (standard < num) {
        height++;
        standard += height;
    }
    int position = num - (standard - height);
    return {height, position};
}

int calculateCost(int start, int end) {
    if (start == end) return 0;

    pair<int, int> startPosition = findPosition(start);
    pair<int, int> endPosition = findPosition(end);
    
    int x = startPosition.first, y = startPosition.second;
    int a = endPosition.first, b = endPosition.second;

    int vCost = abs(x - a);
    int hCost = abs(y - b);
    
    if ((x < a && y > b) || (x > a && y < b))
        return vCost + hCost;
	else if (vCost >= hCost) return vCost;
    else return vCost + (hCost - vCost);
}

int main(int argc, char** argv) {
	int T;
	cin>>T;
	for (int test_case = 1; test_case <= T; ++test_case) {
	        int start, end;
	        cin >> start >> end;
	        int cost = calculateCost(start, end);
	        cout << "#" << test_case << " " << cost << endl;
	}
	return 0;
}
