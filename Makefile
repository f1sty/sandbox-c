all: find_urls find_urls_old fn_ptr threads

find_urls: find_urls.o

find_urls_old: find_urls_old.o

fn_ptr: fn_ptr.o

threads: threads.o

find_urls.o: find_urls.c

find_urls_old.o: find_urls_old.c

fn_ptr.o: fn_ptr.c

threads.o: threads.c

clean:
	find . -maxdepth 1 -type f -perm 755 -delete
	rm -rf *.o

.PHONY: all clean
