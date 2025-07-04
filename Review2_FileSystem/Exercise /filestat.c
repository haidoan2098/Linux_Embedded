// argc: argument count là số lượng tham số dòng lệnh nghĩa là có bao nhiêu lệnh được truyền vào kể cả phần chạy chương trình.
// argv: argument values là là mảng chứa từng phần của dòng lệnh. (là lưu lại mấy lệnh đó)

// stat() và lsat() cả 2 đều là lấy thông tin của file trong inode (thông tin đó là metadata),
// Ví dụ ta có simbolic link 
// Nếu cho stat(simbolic_link) -> Thông tin của file gốc. 
// Nếu cho lsat(simbolic_link) -> Thông tin của file simbolic_link   

#include <stdio.h>
#include <sys/stat.h>       // lstat()
#include <sys/types.h>      // struct stat
#include <time.h> 

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    const char *file_part = argv[1];    
    struct stat infoFile; 
    
    if (lstat(file_part, &infoFile) == -1) {
        printf("Error\n");
        return 1;
    }

    printf("*** FILE INFORMATION ***\n");           
    
    printf("File Part       : %s\n", file_part);     

    printf("File Type       : ");
    if (S_ISREG(infoFile.st_mode)) {
        printf("Regular File\n");
    } else if (S_ISDIR(infoFile.st_mode)) {
        printf("Directory File\n");
    } else if (S_ISLNK(infoFile.st_mode)) {
        printf("Symbolic Link\n");
    } else {
        printf("Other File\n");
    }

    printf("Size            : %ld\n", infoFile.st_size);            

    char lastModifiedTimeBuf[100]; 
    struct tm *timeinfo = localtime(&infoFile.st_mtime);
    strftime(lastModifiedTimeBuf, sizeof(lastModifiedTimeBuf), "%Y-%m-%d %H:%M:%S", timeinfo);
    printf("Last Modified   : %s\n", lastModifiedTimeBuf);            

    return 0;
}
