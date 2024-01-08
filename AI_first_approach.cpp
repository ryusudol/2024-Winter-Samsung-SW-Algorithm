// 151/158
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
        
        for (int i = 0; i < n; i++) {
            // total_discard 배열, row_min 배열 값 저장
            for (int j = 0; j < 3; j++) {
				total_discard[i][j] = ability[i][0] + ability[i][1] + ability[i][2] - ability[i][j];
                if (total_discard[i][j] < row_min[i].first) {
                    row_min[i].first = total_discard[i][j];
                    row_min[i].second = j;
                }
            }
            
            // gap 배열 값 저장
            for (int j = 0; j < 3; j++)
                gap[i][j] = total_discard[i][j] - row_min[i].first;
            
            // column이 특정 row의 min 값을 포함하는지 저장
            if (row_min[i].second == 0) first_selected = 1;
            else if (row_min[i].second == 1) second_selected = 1;
            else third_selected = 1;
        }
        
		if (first_selected + second_selected + third_selected == 2) {
            int not_selected_col;
            if (!first_selected) not_selected_col = 0;
            else if (!second_selected) not_selected_col = 1;
            else not_selected_col = 2;
            
            int col_min = INT_MAX;
            int col_min_row_idx;
            for (int i = 0; i < n; i++) {
                if (gap[i][not_selected_col] < col_min) {
                    col_min = gap[i][not_selected_col];
                    col_min_row_idx = i;
                }
            }
            
            int original_row_min_value = row_min[col_min_row_idx].first;
            int original_row_min_col_idx = row_min[col_min_row_idx].second;
            row_min[col_min_row_idx].first = total_discard[col_min_row_idx][not_selected_col];
            row_min[col_min_row_idx].second = not_selected_col;
            
            int col_second_min = INT_MAX;
            int col_second_min_row_idx;
            for (int i = 0; i < n; i++) {
                if  (gap[i][not_selected_col] < col_second_min && gap[i][not_selected_col] >= col_min && i != col_min_row_idx) {
                    col_second_min = gap[i][not_selected_col];
                    col_second_min_row_idx = i;
                }
            }
            
            // not_selected_col에서 최솟값을 선택했는데 이제 다른 col이 선택되지는 않았는지 확인
            first_selected = 0; second_selected = 0; third_selected = 0;
            for (int i = 0; i < n; i++) {
                if (row_min[i].second == 0) first_selected = 1;
                else if (row_min[i].second == 1) second_selected = 1;
                else third_selected = 1;
            }

            // row_min을 변경하고 나서도 선택된 col이 2개일 때
            if (first_selected + second_selected + third_selected == 2) {
                int new_not_selected_col;
                if (!first_selected) new_not_selected_col = 0;
                else if (!second_selected) new_not_selected_col = 1;
                else new_not_selected_col = 2;
                
                // 새롭게 선택되지 않은 col에서의 min 값과 그 값의 row index 값
                int new_col_min = INT_MAX;
                int new_col_min_row_idx;
                for (int i = 0; i < n; i++) {
                    if (i != col_min_row_idx && gap[i][new_not_selected_col] < new_col_min) {
                        new_col_min = gap[i][new_not_selected_col];
                        new_col_min_row_idx = i;
                    }
                }
                
                if (gap[new_col_min_row_idx][new_not_selected_col] + gap[col_min_row_idx][not_selected_col] > gap[original_row_min_col_idx][new_not_selected_col] + gap[col_second_min_row_idx][not_selected_col]) {
                    row_min[col_min_row_idx].first = original_row_min_value;
                    row_min[col_min_row_idx].second = original_row_min_col_idx;
                    row_min[col_second_min_row_idx].first = total_discard[col_second_min_row_idx][not_selected_col];
                    row_min[col_second_min_row_idx].second = col_second_min_row_idx;
                } else {
                    row_min[new_col_min_row_idx].first = total_discard[new_col_min_row_idx][new_not_selected_col];
                }
            }
        } else if (first_selected + second_selected + third_selected == 1) {
            // 선택되지 않은 두 col 검색
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
            
            // 선택되지 않은 각 col에서 최솟값 검색
            vector<int> col_min(2, INT_MAX);
            vector<int> col_min_row_idx(2);
            for (int i = 0; i < n; i++) {
                if (gap[i][not_selected_col[0]] < col_min[0]) {
                    col_min[0] = gap[i][not_selected_col[0]];
                    col_min_row_idx[0] = i;
                }
                if (gap[i][not_selected_col[1]] < col_min[1]) {
                    col_min[1] = gap[i][not_selected_col[1]];
                    col_min_row_idx[1] = i;
                }
            }
            
            row_min[col_min_row_idx[0]].first = total_discard[col_min_row_idx[0]][not_selected_col[0]];
            row_min[col_min_row_idx[1]].first = total_discard[col_min_row_idx[1]][not_selected_col[1]];
            if (col_min_row_idx[0] == col_min_row_idx[1]) {
				// 두 번째 최솟값 검색
                vector<int> col_second_min(2, INT_MAX);
                vector<int> col_second_min_row_idx(2);
                for (int i = 0; i < n; i++) {
                    // 안 되면 gap[i][not_selected_col[0]] <= col_second_min[0]으로 변경
                    if (gap[i][not_selected_col[0]] < col_second_min[0] && ((gap[i][not_selected_col[0]] > col_min[0]) || (gap[i][not_selected_col[0]] == col_min[0] && i != col_min_row_idx[0]))) {
                        col_second_min[0] = gap[i][not_selected_col[0]];
                        col_second_min_row_idx[0] = i;
                    }
                    if (gap[i][not_selected_col[1]] < col_second_min[1] && ((gap[i][not_selected_col[1]] > col_min[1]) || (gap[i][not_selected_col[1]] == col_min[1] && i != col_min_row_idx[1]))) {
                        col_second_min[1] = gap[i][not_selected_col[1]];
                        col_second_min_row_idx[1] = i;
                    }
                }

                if (col_min[0] + col_second_min[1] < col_min[1] + col_second_min[0]) {
                    row_min[col_min_row_idx[0]].first = total_discard[col_min_row_idx[0]][not_selected_col[0]];
                    row_min[col_second_min_row_idx[1]].first = total_discard[col_second_min_row_idx[1]][not_selected_col[1]];
                } else {
                    row_min[col_second_min_row_idx[0]].first = total_discard[col_second_min_row_idx[0]][not_selected_col[0]];
                    row_min[col_min_row_idx[1]].first = total_discard[col_min_row_idx[1]][not_selected_col[1]];
                }
            }
        }
        int min = 0;
        for (int i = 0; i < n; i++)
            min += row_min[i].first;
        cout << "#" << test_case << " " << min << endl;
	}
	return 0;
}
