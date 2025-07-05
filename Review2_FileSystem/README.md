# Session 2:  LINUX FILE SYSTEM

##  A. Tổng quan về File trên Linux
Một trong những triết lý cốt lõi của **Linux (và UNIX)** là: **"Everything is a file" - Mọi thứ đều là một file.** 	            			
### I. Các loại file trên Linux. 					
Trong hệ điều hành Linux, **mọi thứ được coi là file** và hệ thống phân loại các loại File chính như sau:   
 1. **Regular File (File thông thường)**        
        Là loại file phổ biến nhất.            
		Chứa dữ liệu: văn bản, mã nguồn, hình ảnh, nhạc, video,...         
		Ví dụ: text.txt, code.cpp, image.png,...       
 2. **Directory (Thư Mục)**             
		Là file đặc biệt chứa danh sách các file và thư mục khác.					
		Ví dụ: /home, /usr/bin, /etc,...
 3. **Symbolic Link (Liên kết tượng trưng)**        
		Là "đường dẫn" trỏ đến file hoặc thư mục khác.         
		Tương tự như Shortcut trên Windows.        
		Ví dụ: ln -s /original/file.text link.text
 4. **Block Device File**           
		Đại diện cho các thiết bị lưu trữ hoạt động theo từng khối dữ liệu (block I/O) như: ổ cứng, USB, SSD,...        
		Thường nằm trong /dev/      
		Ví dụ: /dev/sda, /dev/nvmeOn1,...       
 5. **Character Device File**               
		Đại diện cho thiết bị truyền dữ liệu theo từng byte (character I/O) như: bàn phím, chuột, cổng serial,...      
		Ví dụ: /dev/ttys0, /dev/random,...             
 6. **FIFO (Named Pipe)**       
		Cho phép 2 tiến trình giao tiếp được với nhau (Interprocess Communication - IPC).      
 7. **Socket File**	    
		Dùng cho giao tiếp qua mạng hoặc giao tiếp giữa các tiến trình (IPC).
		 
### II. Thông tin về File. 		
![](https://i.ibb.co/nMFVx3fG/490065215-3056116057890276-7042270545055739780-n.jpg)     

**Ví dụ: `-rwxrwxr-x 1 haidoan2098 haidoan2098 15960 Thg 6  29 21:48 text`**
- **Loại file & Quyền truy cập.**  
	 **Cấu trúc**: `-rwxrwxr-x`
	 -> Giải thích: 
	|  Ký hiệu        | Ý nghĩa                          						|
	|---------------	|-------------------------------------------|
	|   `-`           	| **Loại file**: `-` file thường   			|
	|  `rwx`         	| **Quyền của user (owner)**     			|
	|  `rwx`         	| **Quyền của group (nhóm)**        	|
	|  `r-x`         	| **Quyền của others (người khác)** |		

- **Các kí hiệu về loại file.**
	| Ký hiệu | Loại File                   	 |
	|----------|-------------------------|
	| `-`     	| Regular file               | 
	| `d`     	| Directory                   | 
	| `l`     	| Symbolic link            | 
	| `c`     	| Character device      | 
	| `b`     	| Block device             |
	| `s`     	| Socket                      	| 
	| `p`     	| FIFO (named pipe)   |

- **Các kí hiệu về quyền.**
	| Ký hiệu | Nghĩa       |
	|--------|--------------|
	| `r`     | Read         |
	| `w`     | Write        |
	| `x`     | Execute      |
	| `-`     | Không có quyền |
	
- **Cấp quyền cho file.** 	        
	Quyền dưới dạng số (như cách đổi nhị phân -> thập phân).        
	Ví dụ: Quyền hiện tại `rwxrwxr-x`	
	```bash
		r	w	x				r	w	x				r	-   x	
		|	|	|				|	|	|				|	|	|
		1	1	1	=> 7			1	1	1	=> 7			1	0	1	=> 5
	```
	Hiện tại, Others không thể Write vào file được, để Others ghi được thì User phải cấp quyền:         
	**Dùng lệnh:** `chmod XYZ filename`      
	Ví dụ: `chmod 777 filename`		        

## B. Read/Write File trên Linux		
Trong Linux, việc đọc ghi file thường sử dụng các **hàm hệ thống (system calls)** từ thư viện `unistd.h` hoặc `fcntl.h`. Đây là các hàm cấp thấp, tương tác trực tiếp với **Kernel** hệ điều hành. 			

### Các Systemcall đọc ghi file phổ biến. 	
Hầu hết việc đọc ghi file trên Linux được thực hiện bằng 5 functions: `open`, `read`, `write`, `lseek`, `close`. 	
 #### 1. **`open()` - Mở File.** 	
- **Cú pháp:** 	
	```cpp		
	#include <fcntl.h>    // cho open()
	
	// function prototype
	int open(const char *pathname, int flags);
	int open(const char *pathname, int flags, mode_t mode); // dùng mode khi tạo file mới
	```		
	| 	Tham số              | Ý nghĩa                                                          
	|------------------------|---------------------------------------------------------------|
	| 	`pathname`           | Tên file hoặc đường dẫn đến file cần mở.                     |
	|	 `flags`             | Xác định cách mở.                                      						|		
	| 	`mode`               | Quyền cấp khi tạo file mới.       							 		 |

	**Trả về:**	        
	+ Một **file descriptor (fd)** là số nguyên nếu thành công (thường bắt đầu từ 3), có thể hiểu fd như số đại diện cho file.	
	+ Trả về `-1` nếu lỗi.	        
    
- **Các Flags phổ biến:** 					
	| 	Flags                    | Mô tả                                                             
	|--------------------------|---------------------------------------------------------------|
	| 	`O_RDONLY`               | Mở file chỉ để **đọc**                                        |
	| 	`O_WRONLY`               | Mở file chỉ để **ghi**                                        |
	| 	`O_RDWR`                 | Mở file để **đọc và ghi**                                     |
	| 	`O_CREAT`                | Tạo file nếu **chưa tồn tại** (cần truyền thêm `mode`)        |
	| 	`O_TRUNC`                | **Xóa nội dung** file nếu đã tồn tại                          |
	| 	`O_APPEND`               | Ghi thêm vào **cuối file**, không ghi đè nội dung cũ          |
	| 	`O_EXCL`                 | Dùng với `O_CREAT`, báo lỗi nếu **file đã tồn tại**           |							

- **Lưu ý:** Khi cấp quyền cho file mới tạo, **umask** sẽ thực hiện giới hạn quyền lại để tránh rủi ro (Thường thì umask để giới hạn quyền của group và others lại tùy thuộc vào umask của máy).          		    
    **Cách hoạt động:** `quyền_thực_tế = mode_truyền_vao & ~umask`	

#### 2. **`write()` - Ghi File.**		
- **Được ghi từ vị trí con trỏ file hiện tại.**			
	 			
- **Cú pháp:**			
	```cpp		
	#include <unistd.h>	// cho write()
	
	// function prototype
	ssize_t write(int fd, const void *buf, size_t count);
	```
	| 	Tham số                    | Ý nghĩa                                                          
	|--------------------------|---------------------------------------------------------------|
	| 	`fd`               				| File descriptor (mã số đại diện cho file)                   |
	| 	`buf`             		   		| Con trỏ trỏ tới vùng nhớ chứa dữ liệu cần ghi                                     						|		
	| 	`count`                	   | Số byte cần ghi từ buffer vào file     							 		 |

    **Trả về:**	
	+ Số byte **thực tế** đã được ghi nếu thành công.
	+ `-1` nếu lỗi (ví dụ: file không mở để ghi, ổ đĩa đầy, lỗi phân quyền...).     
#### 3. **`read()` - Đọc File.**		
- **Được đọc từ vị trí con trỏ file hiện tại.** 
 	
- **Cú pháp:**			
	```cpp		
	#include <unistd.h>	// cho read()
	
	// function prototype
	ssize_t read(int fd, void *buf, size_t count);
	```
	| 	Tham số                    | Ý nghĩa                                                          
	|--------------------------|---------------------------------------------------------------|
	| 	`fd`               				| File descriptor (mã số đại diện cho file)                   |
	| 	`buf`             		   		| Con trỏ trỏ đến vùng nhớ sẽ chứa dữ liệu đã đọc được        |		
	| 	`count`                	   | Số byte tối đa muốn đọc    							 		 |

	**Trả về:**	
	 + Số byte **thực tế đã đọc** nếu thành công (có thể < `count`).
	 + `0` nếu đọc đến **EOF** (kết thúc file).	
	 + `-1` nếu lỗi.
#### 4. **`lseek()` - Di chuyển con trỏ đọc/ghi File.**		
- Trong Linux, khi mở một file, hệ thống sẽ duy trì một con trỏ file gọi là **file offset** — vị trí hiện tại mà `read()` hoặc `write()` sẽ thao tác trên file.
	 
- **Cú pháp:**			
	```cpp		
	#include <unistd.h>	// cho lseek()
	
	// function prototype
	off_t lseek(int fd, off_t offset, int whence);
	```
	| 	Tham số                    | Ý nghĩa                                                          
	|--------------------------|---------------------------------------------------------------|
	| 	`fd`               				| File descriptor (mã số đại diện cho file)                   |
	| 	`offset`             		 | Giá trị dịch chuyển (dương hoặc âm)       |		
	| 	`whence`                	   | Nơi bắt đầu dịch chuyển   							 		 |      

	 **`whence`** có 3 lựa chọn:
	 | 	Tham số                    | Ý nghĩa                                                          
	|--------------------------|---------------------------------------------------------------|
	| 	`SEEK_SET`               				| Di chuyển tới vị trí `offset` tính từ đầu file                 |
	| 	`SEEK_CUR`             		 | Di chuyển tới vị trí `offset` tính từ vị trí hiện tại      |		
	| 	`SEEK_END`                	   | Di chuyển tới vị trí `offset` tính từ cuối file   							 		 |

	**Trả về:**	
	+ 	Vị trí mới của file offset (tính từ đầu file) nếu thành công.
	+ `-1` nếu lỗi.	
#### 5. `close()` - Đóng File.			
- **Cú pháp:**			
	```cpp		
	#include <unistd.h>	// cho close()
	
	// function prototype
	int close(int fd);
	```	
	**Trả về:**	        
	 + `0` nếu thành công.        
	 + `-1` nếu lỗi.	
	
- **Chuyện gì xảy ra nếu mở file mà không đóng ?**	Trong hệ điều hành, số lượng file descriptor mà 1 tiến trình có thể mở là có giới hạn (thường là vài trăm tới vài nghìn). Kiểu như là nó tài nguyên của Process mà Process thì nó cũng có tài nguyên giới hạn của nó.	    
		→ Không `close()` sau khi dùng xong sẽ gây **rò rỉ tài nguyên (file descriptor leak)**.		
	
## C. Page Cache		

### I. Page Cache là gì ?
- Là bộ nhớ **RAM** mà hệ điều hành dùng để **lưu tạm dữ liệu của file** khi đọc hoặc ghi file, nhằm:		
	+ Tăng tốc độ truy xuất file (vì RAM nhanh hơn đĩa rất nhiều (disk/flash)). 
	+ Giảm số lần truy cập ổ đĩa (để tiết kiệm tài nguyên, tăng tuổi thọ SSD).		
	+ Cho phép ghi file nhanh mà không cần đợi dữ liệu được ghi ra đĩa thật. 		
- **Hiểu nôm na**: thay vì mỗi lần `read()` đều phải ra ổ đĩa để lấy dữ liệu (rất chậm), Linux sẽ nhớ dữ liệu đã đọc vào RAM (Page Cache). Lần sau `read()` lại thì nó lấy luôn từ RAM → nhanh hơn gấp hàng trăm lần.
	
### II. Quá trình Read/Write với Page Cache. 
![](https://i.ibb.co/wNgc9tpZ/page-cache.png)			

1. **Read với Page Cache.** 								
	Khi gọi: `read(fd, buf, size);`
	**Kernel làm gì?** 			
	+ **Kiểm tra Page Cache**:      
		+ Dữ liệu ở vị trí đó trong file có nằm sẵn trong RAM không?	
	+ ✅ Nếu **có**:        
		+ Copy trực tiếp Page Cache vào `buf` (bộ nhớ chương trình của mình). 	        
		-> Nhanh, không cần dụng tới Disk/Flash. 		
	+ ❌ Nếu **không có:**      
		+ Kernel mới xuống đĩa (Disk/Flash) để đọc -> Chậm hơn. 
		+ Sau đó copy vào Page Cache và trả cho buf.
		+ Lần sau đọc chỗ đó -> Nhanh hơn vì đã có ở trong Cache. 
2. **Write với Page Cache.**        
	Khi gọi: `write(fd, buf, size);`        
- **Kernel làm gì?**         	                			
	+ Ghi dữ liệu từ `buf` vào Page Cache — **chưa ghi ra đĩa (Disk/Flash) ngay**.
	+ Đánh dấu vùng dữ liệu đó là **Dirty Page (đã thay đổi)**.		
	+ Sau một thời gian (hoặc khi RAM đầy), **kernel** mới ghi dirty page vào ổ đĩa hay **đồng bộ dữ liệu**. 		
- **Ưu điểm:** chương trình `write()` xong rất nhanh, không bị chờ ổ đĩa. 
- **Nhược điểm:** nếu mất điện hoặc máy sập nguồn trước khi ghi thật, dữ liệu có thể **chưa kịp lưu vào đĩa**. 
3. **Cách để đảm bảo dữ liệu được ghi vào đĩa chứ không phải Page Cache.** 		        
	Dùng **System Call**: `fsync(fd)` hoặc `sync()`	 để đồng bộ. 
	```cpp
	#include <unistd.h>
	
	fsync(fd);	// Với fd là file descriptor của file cần đồng bộ 
	sync();
	```
	**Sự khác biệt:**		
		
	| 	System Call         | Chức năng                                                        
	|----------------------|---------------------------------------------------------------|
	| 	 `fsync(fd)`      | Buộc kernel ghi toàn bộ dữ liệu liên quan đến fd từ Page Cache vào đĩa. | 
	|    `sync()`         	|	Ghi mọi dữ liệu từ tất cả Page Cache của hệ thống vào đĩa.  |		

## C. File Locking 			
**Bài toán đặt ra:** Giả sử có 2 Process cùng ghi vào cùng 1 file thì chuyện gì xảy ra ?        
	-> Kết quả là dữ liệu trên file đó sẽ bị ghi đè lẫn nhau, làm mất dữ liệu. 			
- **Mục đích của File Locking:** 
	+ Đảm bảo tính nhất quán dữ liệu khi nhiều tiến trình cùng truy cập vào file. 
	+ Tránh Race Condition: Hai tiến trình cùng ghi vào file -> dữ liệu sẽ bị ghi đè. 
	+ Cho phép tiến trình được phép độc quyền tài nguyên tạm thời. 			

### Các kĩ thuật File Locking 
#### 1. `flock()` - Khóa toàn File	
- Khóa toàn bộ File, đảm bảo tại 1 thời điểm chỉ có 1 tiến trình được sử dụng. 

	**Cú pháp:** 
	```cpp		
	#include <sys/file.h>

	int flock(int fd, int operation);
	```	
	**`operation`** có thể là:			
	| 	Flags       			| Ý nghĩa                                              						       |
	|---------------------|---------------------------------------------------------------|
	| 	 `LOCK_SH`     	| Khóa chia sẻ (shared – đọc) - Cho phép nhiều tiến trình đọc | 
	|    `LOCK_EX`         | Khóa độc quyền (exclusive – ghi) - Cho phép 1 tiến trình ghi |		
	|    `LOCK_UN`         | Gỡ bỏ khóa  |		
	|    `LOCK_NB`         | Không chờ, nếu bị khóa thì trả lỗi ngay |			

	**Trả về:**				
	+ `0` nếu thành công. 
	+ `-1`nếu lỗi. 				
	
	**Dựa vào Flags, có 2 kiểu xin khóa trong `flock()`:**  
	**1. Blocking (chờ đến khi có khóa)**                       				
    - Nếu file **chưa bị khóa** → tiến trình **có được khóa ngay.**	                                  
	- Nếu file **đang bị khóa** → tiến trình **đứng lại, chờ** cho đến khi được cấp khóa.       
    **=>** Rất hữu ích khi bạn muốn đảm bảo thứ tự truy cập tài nguyên, nhưng có thể làm chương trình **bị treo tạm thời** nếu không cẩn thận.                                                    	
       
	**2. Non-blocking (xin không được thì thoát luôn)**	
	- Nếu file **chưa bị khóa** → tiến trình **nhận được khóa như thường**	
	- Nếu file **đang bị khóa** → **trả về lỗi `-1` ngay lập tức**, không chờ.  
	**=>** Khi muốn kiểm tra "có ai đang dùng file không", nếu có thì **bỏ qua hoặc báo lỗi** thay vì chờ.         	        			
    
#### 2. `fcntl()` - Khóa linh hoạt theo vùng						
- Cho phép đặt khóa **trên từng vùng cụ thể của file**			

- **Cú pháp:** 	
	```cpp		
	#include <fcntl.h>

	int fcntl(int fd, int cmd, struct flock *lock);
	```				
	**`cmd`** phổ biến: 	
	| 	cmd       			| Ý nghĩa                                              	|
	|-------------------|-------------------------------------------|
	| 	 `F_SETLK`     | Đặt khóa, **non-blocking** 				| 
	|    `F_SETLKW`   | Đặt khóa, **blocking** 						|		
	|    `F_UNLCK`     | Gỡ khóa  												|		
	|    `F_GETLK`     | Kiểm tra xem vùng đã bị khóa chưa  |							
	
	**Cấu trúc** `struct flock`:	
	```cpp		
	struct flock {
		short l_type;    // F_RDLCK, F_WRLCK, F_UNLCK
	    short l_whence;  // SEEK_SET, SEEK_CUR, SEEK_END
	    off_t l_start;   // vị trí bắt đầu (offset)
	    off_t l_len;     // độ dài vùng cần khóa
	    pid_t l_pid;     // PID của tiến trình đặt khóa (dùng với F_GETLK)
	};
	```		
	| Trường       | Ý nghĩa |
	|--------------|--------|
	| `l_type`     | **Kiểu khóa cần thiết lập**:  <br>• `F_RDLCK`: Khóa đọc (nhiều tiến trình cùng đọc được) 	<br>• `F_WRLCK`: Khóa ghi (độc quyền) <br>• `F_UNLCK`: Gỡ khóa |
	| `l_whence`   | **Điểm bắt đầu tính offset**:  <br>• `SEEK_SET`: từ đầu file <br>• `SEEK_CUR`: từ vị trí 	hiện tại <br>• `SEEK_END`: từ cuối file |
	| `l_start`     | **Offset tính từ `l_whence`** – byte đầu tiên của vùng cần khóa |
	| `l_len`      | **Chiều dài vùng cần khóa (byte)**|	
	| `l_pid`     | PID của tiến trình đang giữ khóa (chỉ có giá trị khi dùng `F_GETLK`) |				
	
	**Trả về:** Tùy thuộc vào `cmd`	(thường thì `0` thành công, `-1` thất bại)		
