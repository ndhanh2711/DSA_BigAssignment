# Bài toán Người Bán Hàng Du Lịch sử dụng Branch and Bound

## Giới thiệu

**Bài toán Người bán hàng du lịch** (Traveling Salesman Problem - TSP) là một bài toán tối ưu quan trọng trong nhiều lĩnh vực như quy hoạch tuyến đường, lập lịch trình và tối ưu hóa. Mục tiêu chính của bài toán này là tìm ra một đường đi ngắn nhất (hoặc chi phí tối thiểu) để đi qua tất cả các đỉnh (hoặc điểm đến) trong một đồ thị và quay trở về điểm xuất phát.

### Phương pháp giải

Một trong những phương pháp hiệu quả để giải bài toán TSP là sử dụng phương pháp **Branch and Bound**. Đây là một kỹ thuật phân tách và bó ràng buộc không gian tìm kiếm nhằm giảm thiểu số lượng các giải pháp không cần thiết.

## Nội dung chính

1. **Mô hình bài toán**  
   - Các đỉnh là các thành phố hoặc điểm cần ghé thăm.
   - Ma trận chi phí hoặc khoảng cách giữa các đỉnh thể hiện chi phí hoặc quãng đường di chuyển.

2. **Thuật toán Branch and Bound**  
   - **Khởi tạo**: Tạo một trạng thái ban đầu với đỉnh xuất phát.
   - **Tối ưu hóa**: Tính toán chi phí tối thiểu từ trạng thái hiện tại đến từng đỉnh khác.
   - **Phân tách (Branching)**: Tạo các trạng thái mới bằng cách thêm đỉnh chưa được ghé thăm.
   - **Ràng buộc (Bounding)**: Tính toán cận trên và cận dưới để xác định nhánh nào cần loại bỏ.

3. **Quy trình thực hiện**  
   - Tạo ma trận chi phí giữa các đỉnh.
   - Bắt đầu từ đỉnh xuất phát và phân tách không gian tìm kiếm.
   - Duyệt từng nhánh cho đến khi tất cả các đỉnh đều được ghé thăm đúng thứ tự.

4. **Kết quả**  
   - Đường đi ngắn nhất với chi phí nhỏ nhất sẽ được xác định thông qua việc xử lý tất cả các nhánh của không gian tìm kiếm.

---

## Example

### Ma trận chi phí giữa các thành phố:

```c++
int costMatrix[N][N] = {
    { INF, 10, 8, 9, 7 },
    { 10, INF, 10, 5, 6 },
    { 8, 10, INF, 8, 9 },
    { 9, 5, 8, INF, 6 },
    { 7, 6, 9, 6, INF }
};
INF là giá trị đặc biệt đại diện cho chi phí không thể ghé thăm giữa hai thành phố.

Giải thích ma trận chi phí:

|         | City 1 | City 2 | City 3 | City 4 | City 5 |
|---------|--------|--------|--------|--------|--------|
| **City 1**  | INF    | 10     | 8      | 9      | 7      |
| **City 2**  | 10     | INF    | 10     | 5      | 6      |
| **City 3**  | 8      | 10     | INF    | 8      | 9      |
| **City 4**  | 9      | 5      | 8      | INF    | 6      |
| **City 5**  | 7      | 6      | 9      | 6      | INF    |

---

## Output Format

### Đầu ra:

- **Total cost** là chi phí tối ưu của đường đi.

- Danh sách đường đi (1-based index) theo thứ tự ghé thăm thành phố:

| From     | To       |
|----------|----------|
| 1        | 3        |
| 3        | 4        |
| 4        | 2        |
| 2        | 5        |
| 5        | 1        |

**Total cost** là 34.

---

## Tài liệu tham khảo

- [Techie Delight - Traveling Salesman Problem using Branch and Bound](https://www.techiedelight.com/travelling-salesman-problem-using-branch-and-bound/)
