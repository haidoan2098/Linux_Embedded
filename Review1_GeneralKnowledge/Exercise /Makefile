# Mục tiêu mặc định: build cả static và shared
all:
	make static
	make shared

# Tạo thư viện static và file main_static
static:
	gcc -c bstrutils.c -o bstrutils.o
	ar rcs libstrutils.a bstrutils.o
	gcc main.c -L. -lstrutils -o main_static

# Tạo thư viện shared và file main_shared
shared:
	gcc -fPIC -c bstrutils.c -o bstrutils.o
	gcc -shared -o libstrutils.so bstrutils.o
	gcc main.c -L. -lstrutils -Wl,-rpath=. -o main_shared

# Xoá các file đã build
clean:
	rm -f *.o libstrutils.a libstrutils.so main_static main_shared
