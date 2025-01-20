#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <cstring>
#include <climits>
using namespace std;
/** 
 * @brief  TSP (Traveling Salesman Problem) giải quyết bài toán tìm đường đi ngắn nhất giữa các thành phố 
 * sao cho mỗi thành phố chỉ được ghé thăm một lần và quay trở về điểm xuất phát với chi phí thấp nhất.
 * 
 * Thuật toán sử dụng phương pháp Branch and Bound để tìm giải pháp tối ưu. 
 * Các bước cơ bản bao gồm giảm bớt ma trận chi phí (rowReduction, columnReduction), 
 * tạo ra các nút con để tìm giải pháp tối ưu, và sử dụng Priority Queue để chọn nút có chi phí thấp nhất.
 * 
 * @author Hanh Nguyen Duc
 * @ 20/01/2025
 */

// `N` là tổng số nút (hoặc các thành phố trên bản đồ)
#define N 5

// Giá trị đặc biệt cho đại diện `INFINITY`
#define INF INT_MAX
/** 
 * Lớp Node: Dùng để lưu trữ trạng thái hiện tại của cây tìm kiếm 
 * trong thuật toán Branch and Bound, bao gồm đường đi, ma trận đã giảm và chi phí hiện tại.
 */
struct Node {
    vector<pair<int, int>> path;     // Lưu lại đường đi của cây trạng thái
    int reducedMatrix[N][N];         // Ma trận đã giảm bớt
    int cost;                        // Chi phí hiện tại
    int vertex;                      // Thành phố hiện tại
    int level;                       // Số lượng thành phố đã được ghé thăm
};
/** 
 * Hàm tạo một nút mới với trạng thái con từ nút cha. 
 * Nó giảm ma trận bằng cách loại bỏ hàng và cột không cần thiết.
 * 
 * @param parentMatrix Ma trận gốc
 * @param path Đường đi hiện tại
 * @param level Cấp độ của cây trạng thái
 * @param i Thành phố cha
 * @param j Thành phố con
 * @return Node* Trỏ đến nút con mới
 */
Node* newNode(int parentMatrix[N][N], vector<pair<int, int>> const &path, int level, int i, int j) {
    Node* node = new Node;
    node->path = path;

    if (level != 0) {
        node->path.push_back(make_pair(i, j));
    }

    memcpy(node->reducedMatrix, parentMatrix, sizeof(node->reducedMatrix));

    // Xóa hàng và cột liên quan đến đỉnh (i, j)
    for (int k = 0; level != 0 && k < N; k++) {
        node->reducedMatrix[i][k] = INF;
        node->reducedMatrix[k][j] = INF;
    }
    node->reducedMatrix[j][0] = INF;

    node->level = level;
    node->vertex = j;

    return node;
}
/** 
 * Hàm giảm bớt ma trận theo hàng, tìm giá trị nhỏ nhất của từng hàng 
 * và trừ đi các giá trị trong ma trận.
 * 
 * @param reducedMatrix Ma trận đã giảm bớt
 * @param row Mảng lưu các giá trị nhỏ nhất của từng hàng
 * @return int Số lượng đã giảm trừ
 */
int rowReduction(int reducedMatrix[N][N], int row[N]) {
    fill_n(row, N, INF);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (reducedMatrix[i][j] < row[i]) {
                row[i] = reducedMatrix[i][j];
            }
        }
    }

    // Giảm cột dựa trên các số tối thiểu trong từng hàng
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (reducedMatrix[i][j] != INF && row[i] != INF) {
                reducedMatrix[i][j] -= row[i];
            }
        }
    }
}
/** 
 * Hàm giảm bớt ma trận theo cột, tìm giá trị nhỏ nhất của từng cột 
 * và trừ đi các giá trị trong ma trận.
 * 
 * @param reducedMatrix Ma trận đã giảm bớt
 * @param col Mảng lưu các giá trị nhỏ nhất của từng cột
 * @return int Số lượng đã giảm trừ
 */
int columnReduction(int reducedMatrix[N][N], int col[N]) {
    fill_n(col, N, INF);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (reducedMatrix[i][j] < col[j]) {
                col[j] = reducedMatrix[i][j];
            }
        }
    }

    // Giảm hàng dựa trên các số tối thiểu trong từng cột
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (reducedMatrix[i][j] != INF && col[j] != INF) {
                reducedMatrix[i][j] -= col[j];
            }
        }
    }
}

/** 
 * Tính toán chi phí tổng thể của ma trận đã giảm bớt.
 * 
 * @param reducedMatrix Ma trận đã giảm bớt
 * @return int Chi phí tổng thể
 */
int calculateCost(int reducedMatrix[N][N]) {
    int cost = 0;

    int row[N];
    rowReduction(reducedMatrix, row);

    int col[N];
    columnReduction(reducedMatrix, col);

    // Tổng chi phí là tổng các số nhỏ nhất từ giảm hàng và giảm cột
    for (int i = 0; i < N; i++) {
        cost += (row[i] != INT_MAX) ? row[i] : 0;
        cost += (col[i] != INT_MAX) ? col[i] : 0;
    }

    return cost;
}

/** 
 * In ra đường đi từ danh sách các cặp (thành phố bắt đầu, thành phố kết thúc).
 * 
 * @param list Danh sách các cặp (i, j)
 */
void printPath(vector<pair<int, int>> const &list) {
    for (int i = 0; i < list.size(); i++) {
        cout << list[i].first + 1 << " —> " << list[i].second + 1 << endl;
    }
}

/** 
 * So sánh hai nút Node dựa trên chi phí của chúng. 
 * Được sử dụng trong priority_queue để sắp xếp các nút theo chi phí tăng dần.
 */
struct comp {
    bool operator()(const Node* lhs, const Node* rhs) const {
        return lhs->cost > rhs->cost;
    }
};

/** 
 * Giải bài toán TSP bằng thuật toán Branch and Bound.
 * 
 * @param costMatrix Ma trận chi phí giữa các thành phố
 * @return int Chi phí tối ưu tìm được
 */
int solve(int costMatrix[N][N]) {
    priority_queue<Node*, vector<Node*>, comp> pq;

    vector<pair<int, int>> v;
    Node* root = newNode(costMatrix, v, 0, -1, 0);
    root->cost = calculateCost(root->reducedMatrix);
    pq.push(root);

    while (!pq.empty()) {
        Node* min = pq.top();
        pq.pop();

        int i = min->vertex;

        // Nếu tất cả các thành phố đã được ghé thăm, kết thúc thuật toán
        if (min->level == N - 1) {
            min->path.push_back(make_pair(i, 0));
            printPath(min->path);
            return min->cost;
        }

        for (int j = 0; j < N; j++) {
            // Tạo một nút con nếu cột và hàng không phải INF
            if (min->reducedMatrix[i][j] != INF) {
                Node* child = newNode(min->reducedMatrix, min->path, min->level + 1, i, j);
                child->cost = min->cost + min->reducedMatrix[i][j] + calculateCost(child->reducedMatrix);
                pq.push(child);
            }
        }
        delete min;
    }
}

int main() {
    int costMatrix[N][N] = {
        { INF, 10, 8, 9, 7 },
        { 10, INF, 10, 5, 6 },
        { 8, 10, INF, 8, 9 },
        { 9, 5, 8, INF, 6 },
        { 7, 6, 9, 6, INF }
    };

    cout << "\n\nTotal cost is " << endl << solve(costMatrix);
    return 0;
}
