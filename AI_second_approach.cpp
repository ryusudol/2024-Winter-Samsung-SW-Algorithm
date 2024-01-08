// 158/158
#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int main(int argc, char** argv) {
	int T;
	cin>>T;
	for (int test_case = 1; test_case <= T; ++test_case) {
        int n;
        cin >> n;
        
        vector<vector<int>> ability(n, vector<int>(3, 0));
        for (int i = 0; i < n; i++) {
            cin >> ability[i][0] >> ability[i][1] >> ability[i][2];
        }
        
        if (n < 3) {
            cout << "#" << test_case << " " << -1 << endl;
            continue;
        }
        
        vector<vector<int>> total_discard(n, vector<int>(3, INT_MAX));
        vector<pair<int, int>> row_min(n, make_pair(INT_MAX, INT_MAX)); // first: value, second: col
        vector<vector<int>> gap(n, vector<int>(3));
        int first_selected = 0, second_selected = 0, third_selected = 0;
        int first_cnt = 0, second_cnt = 0, third_cnt = 0;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 3; j++) {
				total_discard[i][j] = ability[i][0] + ability[i][1] + ability[i][2] - ability[i][j];
                if (total_discard[i][j] < row_min[i].first) {
                    row_min[i].first = total_discard[i][j];
                    row_min[i].second = j;
                }
            }
            
            for (int j = 0; j < 3; j++)
                gap[i][j] = total_discard[i][j] - row_min[i].first;

            if (row_min[i].second == 0) {
                first_selected = 1;
                first_cnt++;
            } else if (row_min[i].second == 1) {
                second_selected = 1;
                second_cnt++;
            } else {
                third_selected = 1;
                third_cnt++;
            }
        }

        if (first_selected + second_selected + third_selected == 3) {
            int min = 0;
            for (int i = 0; i < n; i++)
                min += row_min[i].first;
            cout << "#" << test_case << " " << min << endl;
        } else if (first_selected + second_selected + third_selected == 2) {
            int not_selected_col;
            if (!first_selected) not_selected_col = 0;
            else if (!second_selected) not_selected_col = 1;
            else not_selected_col = 2;
            // cnt 사용해서 풀 것
            int min = INT_MAX;
            for (int i = 0; i < n; i++) {
                if ((row_min[i].second == 0 && first_cnt - 1 == 0) || (row_min[i].second == 1 && second_cnt - 1 == 0) || (row_min[i].second == 2 && third_cnt - 1 == 0)) {
                    int new_not_selected_col = row_min[i].second;
                    for (int j = 0; j < n; j++) {
                        if (j != i) {
                            int sum = 0;
                            for (int k = 0; k < n; k++)
                                sum += row_min[k].first;
                            sum -= row_min[i].first;
                            sum -= row_min[j].first;
                            sum += total_discard[i][not_selected_col];
                            sum += total_discard[j][new_not_selected_col];
                            if (sum < min)
                                min = sum;
                        }
                    }
                } else {
                    int sum = 0;
                    for (int j = 0; j < n; j++)
                        sum += row_min[j].first;
                    sum -= row_min[i].first;
                    sum += total_discard[i][not_selected_col];
                    if (sum < min)
                        min = sum;
                }
            }
            cout << "#" << test_case << " " << min << endl;
        } else if (first_selected + second_selected + third_selected == 1) {
            vector<int> not_selected_col(2);
            if (first_selected) {
                not_selected_col[0] = 1;
                not_selected_col[1] = 2;
            } else if (second_selected) {
                not_selected_col[0] = 0;
                not_selected_col[1] = 2;
            } else {
                not_selected_col[0] = 0;
                not_selected_col[1] = 1;
            }
            
            int min = INT_MAX;
            // not_selected_col[0]
            for (int i = 0; i < n; i++) {
                // not_selected_col[1]
                for (int j = 0; j < n; j++) {
                    int sum = 0;
                    if (j != i) {
                        for (int k = 0; k < n; k++)
                            sum += row_min[k].first;
                        sum -= row_min[i].first;
                        sum -= row_min[j].first;
                        sum += total_discard[i][not_selected_col[0]];
                        sum += total_discard[j][not_selected_col[1]];
                        if (sum < min)
                            min = sum;
                    }
                }
            }
            cout << "#" << test_case << " " << min << endl;
        }
	}
	return 0;
}
