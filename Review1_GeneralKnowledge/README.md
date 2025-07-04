# Lesson 1:  GENERAL KNOWLEDGE     

## A. Quá trình biên dịch chương trình C/C++.    
![](https://i.ibb.co/jsXyMLL/GCC-Compilation-Process.png)
### 1. Giai đoạn tiền xử lý - Preprocessing. (*)    
Đây là **giai đoạn đầu tiên**, đóng vai trò **xử lý trước khi mã nguồn thực sự được biên dịch thành mã máy**.       
- **Các thao tác chính trong tiền xử lý:**
    - **Loại bỏ các Comment (//).**       
    - **Xử lý tất cả các dòng bắt đầu bằng dấu `#`:**      
        + `#include` - Chèn nội dung file `library.h`.  
        + `#define` - Thay thế các Macro.   
        + `#ifdef`, `#ifndef`, `#endif`, `#else` – Biên dịch có điều kiện.  
        + `#undef` – Hủy bỏ định nghĩa. 
        + `#pragma` – Hướng dẫn đặc biệt cho trình biên dịch.       

**=> Kết quả:** File `main.c` -> `main.i` chứa mã **C đã xử lý xong**: không còn `#include`, `#define`,... — tất cả đã được thay thế cụ thể.   

**Lệnh biên dịch:**
```cpp
gcc -E main.c -o main.i
```
### 2. Giai đoạn biên dịch NNBC -> Assembly. 
- Các thao tác chính:       
    + Phân tích cú pháp -> Phát hiện lỗi cú pháp.    
    + Tối ưu hóa code ở mức cao nhất.       

**=> Kết quả:** `File main.i` -> `main.s` thành mã hợp ngữ assembly.     

**Lệnh biên dịch:**
```cpp 
gcc -S main.i -o main.s
```
### 3. Giai đoạn dịch Assembly.         
**=> Kết quả:** Chuyển mã hợp ngữ (main.s) sang mã máy nhị phân dạng object file (main.o).

**Lệnh biên dịch:**
```cpp 
gcc -c main.s -o main.o
```

### 4. Giai đoạn Linking. (*)       
- **Linking** là quá trình kết hợp **các file object (.o)** và các thư viện để tạo ra **file thực thi (chương trình hoàn chỉnh)h**.     
- Nó **liên kết** các hàm, biến, đặc biệt là những **hàm không định nghĩa trong cùng một file**.

    **Nối hàm.**         
    Giả sử viết 2 file như sau:     
    `main.c`        
    ```cpp
    void xin_chao();  // chỉ khai báo, chưa có nội dung

    int main() {
        xin_chao();   // gọi hàm này
        return 0;
    }
    ```
    `xinchao.c`
    ```cpp
    #include <stdio.h>

    void xin_chao() {
        printf("Chào bạn!\n");
    }
    ```
    Sau giai đoạn 3:    
    + `main.o`: Mã máy có hàm xin_chào mà chả biết nó ở đâu.      
    + `xinchao.o`: Mã máy chứa nội dung thật sự xin_chao().

    **=> Vì vậy Linking có vai trò dẫn đường để `main.o` biết nội dung nó cần tìm nằm ở đâu (còn gọi là Linker)**.          

- **Tại sao phải có bước Linking?** Vì: 
    + Chia chương trình thành nhiều file để quản lý.    
    + Một file có thể gọi hàm của file khác.        
    + Máy tính không biết được các hàm đó nằm ở đâu.        
    + Linker giúp nối các đoạn mã lại với nhau thành chương trình hoàn chỉnh.       

## B. Makefile.   
**Makefile là gì?**     
Makefile là một file chứa tập hợp các lệnh để tự động hóa quá trình build, dùng với công cụ make.       
**Tưởng tượng như sau:**   
+ Có 100 `file.c` -> build từng cái ra `file.o` -> rồi link lại thành file thực thi.        
**->** Thay vào đó viết các lệnh vào Makfile, rồi chạy:         
    ```cpp 
    make
    ```          

**I. Cấu trúc và các bước thực hiện Makefile**.   
**1) Cấu trúc của Makefile**.

![](https://i.ibb.co/zhyBrW6P/Screenshot-from-2025-07-03-16-57-20.png)   

- **Taget**: Là tên của một "điều gì đó" mà bạn muốn `Make` thực hiện hoặc tạo ra.      
    + Đó có thể là **một file** mà mình muốn tạo ra. (ví dụ: `file.o`, `file thực thi`).        
    + Hoặc là tên của **một hành động** mà mình muốn thực hiện (như `run`, `clean`,...) -> này gọi là **target ảo (phony target)**.     
- **Dependences (Phụ thuộc)**: là những **file cần có** hay điều kiện cần để tạo ra **Target**.        
- **Action**: Lệnh để thực hiện.    

**2) Các bước thực hiện**.      
- **Bước 1**: `make` xác định Target chính.   
    + Nếu chạy Target mà không có tham số, nó sẽ lấy target đầu tiên trong file.        
- **Bước 2**: Kiểm tra Target có tồn tại không?       
    + **Nếu không tồn tại** -> chắc chắn phải build.   
    + **Nếu đã tồn tại**:
        + **Dependences phải mới hơn Target** -> mới build lại.  
        + Nếu Target mới hơn Dependences thì -> Không chạy lại + Thông báo: 
            ```cpp  
            make: 'file' is up to date.
            ```
**II. Các quy tắc & Thao tác trong Makefile**.                 
**1. Quy tắc đặt tên Makefile**.        
- **Có 3 cách**: **`Makefile`**, **`makefile`**, **`<namefile>.mk`**        
    **Câu hỏi đặt ra**: Nếu trong 1 project có cả 3 file Makefile có cách đặt tên như vậy thì nó chạy file nào?     
    **--> Kết quả**: Nó sẽ ưu tiên thực thi file có tên Makefile.       
    **Vậy làm sao để chạy file Makefile khác?**     
    **--> Dùng lệnh**:          
    ```cpp         
        make -f <file_makefile_chỉ_định>    
    ```
**2. Các loại biến & Kiểu gán**.           
**a) Các loại biến**.         
      
1. **Biến người dùng tự định nghĩa**.     
    + Do người dùng định nghĩa.         
    + Dùng với cú pháp `$(...)`.   
    + Thường dùng để quản lý danh sách file, flags,... 
    ```mk
    SRC = main.c utils.c    # có thể gán 1 biến với nhiều file
    # $(<biến>) nghĩa là tất cả giá trị của biến. 
    OBJ = $(SRC:.c=.o)      # Lấy giá trị của biến SRC đổi đuôi .c -> .o   
    ``` 
2. **Biến mặc định**.       
    + Là biến của Make. 
    + Thường dùng để cấu hình Compiler, Linker, Cờ biên dịch,...
    - **Biến mặc định phổ biến**: 

    | Biến         | Mặc định       | Mô tả                                                                 | Ví dụ sử dụng                      |
    |--------------|----------------|------------------------------------------------------------------------|------------------------------------|
    | `CC`         | `cc` hoặc `gcc`| Trình biên dịch ngôn ngữ C                                             | `$(CC) -c main.c -o main.o`        |
    | `CXX`        | `g++`          | Trình biên dịch ngôn ngữ C++                                           | `$(CXX) -c main.cpp -o main.o`     |
    | `CPP`        | `$(CC) -E`     | Trình tiền xử lý C                                                                                                 | `$(AS) -o main.o main.s`           |
    | `LD`         | `ld`           | Trình liên kết (linker)                                                | `$(LD) $(LDFLAGS) -o app main.o`   |
    | `AR`         | `ar`           | Dùng để tạo thư viện tĩnh `.a`                                        | `$(AR) rcs libmylib.a foo.o bar.o` |

    - **Biến cấu hình cờ biên dịch/liên kết**.      

    | Biến        | Áp dụng cho     | Mô tả                                         | Ví dụ                              |
    |-------------|------------------|-----------------------------------------------|-------------------------------------|
    | `CFLAGS`    | `$(CC)`         | Cờ truyền cho trình biên dịch C               | `-Wall -O2 -g`                      |
    | `CXXFLAGS`  | `$(CXX)`        | Cờ truyền cho trình biên dịch C++             | `-std=c++17 -O3`                    |
    | `CPPFLAGS`  | `$(CPP)`        | Cờ tiền xử lý (thêm thư mục `-I`)             | `-Iinclude/ -DDEBUG`                |
    | `LDFLAGS`   | `$(LD)`         | Cờ truyền khi liên kết (link)                 | `-lm -pthread`                      |         
    
    ```mk
    # rõ ràng và kiểm soát được
    CC = gcc
    CFLAGS = -Wall -O2

    all:
	    $(CC) $(CFLAGS) main.c -o app
    ```         
3. **Biến đặc biệt**.   
    + Là những biến sinh ra trong quá trình thực thi, không cần định nghĩa. 
    + Dùng để: Đại diện cho target, danh sách dependences,...   
    + Các biến đặc biệt phổ biến:  

    | Biến        | Ý nghĩa                                                           | Ví dụ                                |
    |-------------|-------------------------------------------------------------------|----------------------------------------|
    | `$@`        | Tên của **target** hiện tại                                       | Nếu rule là `main.o: main.c`, thì `$@` là `main.o` |
    | `$<`        | **Dependency đầu tiên** (thường là file nguồn `.c`)               | Trong `main.o: main.c`, thì `$<` là `main.c` |
    | `$^`        | **Tất cả dependencies**, cách nhau bởi khoảng trắng               | Nếu `main.o: main.c common.h`, thì `$^` là `main.c common.h` |

    ```mk
    app: main.o utils.o 
	$(CC) $^ -o $@      
    # $^ là main.o utils.o
    # $@ là app
    ```
**b) Các kiểu gán**.        

| Kiểu gán        | Cú pháp  | Thời điểm tính giá trị       | Ghi chú & Ví dụ                                                                 |
|-----------------|----------|-------------------------------|----------------------------------------------------------------------------------|
| Gán đệ quy       | `=`      | Khi sử dụng biến              | ```A = hello```<br>```B = $(A) world```<br>→ `B` sẽ là `hello world` nếu dùng ngay,<br>nhưng nếu sau đó `A = goodbye`,<br>thì `B` thành `goodbye world` |
| Gán ngay         | `:=`     | Khi gán                       | ```A = hello```<br>```B := $(A) world```<br>→ `B` sẽ luôn là `hello world`,<br>kể cả khi `A` thay đổi sau đó |
| Gán nếu chưa có  | `?=`     | Khi gán, nếu biến chưa tồn tại| ```A ?= default```<br>→ Nếu `A` chưa được gán trước đó thì sẽ có giá trị `"default"` |
| Gán thêm         | `+=`     | Khi gán                       | ```A = hello```<br>```A += world```<br>→ `A` sẽ thành `"hello world"` |

**III. Cấu trúc chuẩn của một Makefile**.               

```mk
# -----------------------------
# 1. Biến cấu hình
# -----------------------------
CC      := gcc
CFLAGS  := -Wall -Wextra -O2
SRC     := main.c utils.c io.c
OBJ     := $(SRC:.c=.o)
TARGET  := app

# -----------------------------
# 2. Target mặc định
# -----------------------------
all: $(TARGET)

# -----------------------------
# 3. Rule build file thực thi
# -----------------------------
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

# -----------------------------
# 4. Rule build file .o từ .c
# -----------------------------
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# -----------------------------
# 5. Dọn dẹp file build
# -----------------------------
clean:
	rm -f $(OBJ) $(TARGET)

# -----------------------------
# 6. Rule giả
# -----------------------------
.PHONY: all clean     
#.PHONY giúp đảm bảo các Target không bị nhầm với file thật. 
```
## C. Static Library & Shared Library.      
- **Định nghĩa thư viện:** Thư viện là **tập hợp các đoạn mã đã được biên dịch sẵn** (từ `file.c`), có thể **tái sử dụng trong nhiều chương trình** và **được liên kết (link) vào các chương trình** khi biên dịch hoặc khi chạy chạy.     
- **Mục đích**.        
    - **Tái sử dụng mã:** Thay vì viết đi viết lại cùng một đoạn code (như hàm tính toán, xử lý chuỗi,...), bạn viết một lần, đóng gói thành thư viện rồi dùng lại.       
    - **Tách biệt mã nguồn:** Giúp quản lý dự án dễ dàng, chia nhỏ thành các phần (module).   
    - **Giấu mã nguồn (một phần):** Có thể phát hành lib thay vì file.c.

- ❌ **Nhầm lẫn to lớn:**   
    + Viết thư viện là viết `file.h` và `file.c`.  
    + Gọi: stdio.h, stdlib.h,... => là thư viện. Gọi đúng là Header của thư viện.       

- **Phân loại thư viện:**         

    | 	Loại Library      | Phần mở rộng                            |                                                       
	|---------------------|---------------------------------------------------------------|
	|  Static Library     | `.a` (Linux), `.lib` (Windows)                                |
	|  Dynamic Library (Shared Library) | `.so` (Linux), `.dll` (Windows)                 |	

- **Thư viện đúng nghĩa gồm những gì?**

    | 	Tên               | Ý nghĩa                                                       |                
	|---------------------|---------------------------------------------------------------|
	| `.h` (header file) | Function Prototype để `#include`                              |
	| `.c` (source file) | Định nghĩa hàm – được compile thành `.o`                      |		
	| `.a` hoặc `.so`   | File thư viện chứa mã đã biên dịch sẵn, dùng để link vào chương trình |      
    
### So sánh Static Library và Dynamic Library.           

 ![](https://i.ibb.co/xqj7bXpX/1652102344888.png)    
   

   | **Tiêu chí**          | **Static Library**                                                                 | **Shared Library**                                                                 |
|-----------------------|-------------------------------------------------------------------------------------|------------------------------------------------------------------------------------|
| **Linking time**      | Được liên kết vào chương trình tại **thời điểm build**. Mã thư viện được chép vào file thực thi. | Được liên kết khi **chương trình chạy (runtime)**. Thư viện sẽ **được OS load vào bộ nhớ**. |
| **Kích thước (Size)** | File thực thi **nặng hơn vì chứa luôn mã thư viện**.                                    | File thực thi **nhẹ hơn vì chỉ chứa tham chiếu đến thư viện `.so` load ở RAM**.               |
| **Thay đổi thư viện** | Khi thư viện thay đổi, phải biên dịch lại chương trình để cập nhật.                 | Không cần biên dịch lại. Chỉ cần thay đổi thư viện là đủ.                         |
| **Tốc độ thực thi**   | Có thể chạy **nhanh hơn vì mã đã sẵn trong chương trình**.                              | Có thể **chậm hơn lúc bắt đầu do phải load thư viện**.                                 |
| **Quản lý bộ nhớ**     | Mỗi chương trình giữ riêng bản copy thư viện.                                       | Nhiều chương trình dùng chung một bản thư viện → tiết kiệm bộ nhớ.                |
