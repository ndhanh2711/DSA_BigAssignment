/**
 * Đầu vào: 
 * costMatrix[][] - Ma trận chi phí giữa các thành phố (N x N), với INF là giá trị đặc biệt cho không có chi phí.
 *
 * Đầu ra:
 * Chi phí tối ưu của hành trình, là tổng chi phí ngắn nhất khi thăm tất cả các thành phố một lần và quay trở về điểm xuất phát.
 */

   
# Giải bài toán Người du lịch bằng phương pháp Nhánh và Cận

Chương trình này giải bài toán Người du lịch (Traveling Salesman Problem - TSP) bằng cách sử dụng phương pháp Nhánh và Cận. Mục tiêu là tìm ra lộ trình ngắn nhất có thể, đi qua tất cả các thành phố đúng một lần và quay trở về thành phố xuất phát.

## Mã giả

### Định nghĩa
1. Định nghĩa các hằng số và cấu trúc dữ liệu:
    - `N`: Số lượng thành phố
    - `INF`: Một số lớn đại diện cho vô cực
    - `Path`: Một cấu trúc để lưu trữ đường đi giữa các thành phố, bao gồm hai trường `first` và `second` để lưu trữ các cặp thành phố.
    - `Node`: Một cấu trúc để đại diện cho một nút trong cây không gian trạng thái, bao gồm:
        - `path`: Mảng lưu trữ các cạnh của cây không gian trạng thái
        - `reducedMatrix`: Ma trận giảm
        - `cost`: Chi phí của nút
        - `vertex`: Đỉnh hiện tại
        - `level`: Mức độ của nút trong cây

### Các hàm

2. Triển khai các hàm:

#### `newNode(parentMatrix, path, level, i, j)`
- Mục đích: Tạo một nút mới `(i, j)` tương ứng với việc ghé thăm thành phố `j` từ thành phố `i`
- Các bước thực hiện:
    - Tạo một nút mới và sao chép ma trận cha vào nút mới
    - Cập nhật đường đi và ma trận giảm
    - Trả về nút mới

#### `rowReduction(reducedMatrix, row)`
- Mục đích: Giảm mỗi hàng sao cho mỗi hàng đều có ít nhất một số không
- Các bước thực hiện:
    - Duyệt qua từng hàng và tìm giá trị nhỏ nhất trong mỗi hàng
    - Trừ giá trị nhỏ nhất đó cho tất cả các phần tử trong hàng
    - Cập nhật ma trận giảm và mảng hàng

#### `columnReduction(reducedMatrix, col)`
- Mục đích: Giảm mỗi cột sao cho mỗi cột đều có ít nhất một số không
- Các bước thực hiện:
    - Duyệt qua từng cột và tìm giá trị nhỏ nhất trong mỗi cột
    - Trừ giá trị nhỏ nhất đó cho tất cả các phần tử trong cột
    - Cập nhật ma trận giảm và mảng cột

#### `calculateCost(reducedMatrix)`
- Mục đích: Tính toán chi phí thấp nhất của đường đi bắt đầu từ nút hiện tại
- Các bước thực hiện:
    - Thực hiện giảm hàng và cột
    - Tính tổng chi phí của các giá trị đã giảm
    - Trả về tổng chi phí

#### `printPath(node)`
- Mục đích: In ra đường đi của các thành phố đã ghé thăm với chi phí ít nhất
- Các bước thực hiện:
    - Duyệt qua mảng `path` của nút và in ra các cặp thành phố

#### `solve(costMatrix)`
- Mục đích: Giải bài toán TSP bằng phương pháp Nhánh và Cận
- Các bước thực hiện:
    - Khởi tạo một hàng đợi ưu tiên
    - Tạo một nút gốc và tính toán chi phí của nó
    - Đẩy nút gốc vào hàng đợi ưu tiên
    - Trong khi hàng đợi ưu tiên không rỗng:
        - Lấy nút có chi phí nhỏ nhất ra khỏi hàng đợi
        - Nếu tất cả các thành phố đã được ghé thăm, in ra đường đi và trả về chi phí
        - Đối với mỗi thành phố chưa được ghé thăm, tạo một nút con và tính toán chi phí của nó
        - Đẩy nút con vào hàng đợi ưu tiên
    - Trả về -1 nếu không tìm thấy giải pháp

### Hàm chính

#### `main()`
- Mục đích: Khởi tạo ma trận chi phí và giải bài toán TSP
- Các bước thực hiện:
    - Định nghĩa ma trận chi phí
    - Gọi hàm `solve` với ma trận chi phí
    - In ra tổng chi phí

## Ví dụ

```cpp
int main() {
    int costMatrix[N][N] = {
        { INF, 10, 8, 9, 7 },
        { 10, INF, 10, 5, 6 },
        { 8, 10, INF, 8, 9 },
        { 9, 5, 8, INF, 6 },
        { 7, 6, 9, 6, INF }
    };

    cout << "\n\nTổng chi phí là: " << solve(costMatrix) << endl;

    return 0;
}