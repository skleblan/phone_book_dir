all: phone_book

phone_book: smpl_phone_book.o
	gcc -v -o phone_book smpl_phone_book.o >linking.log 2>&1

smpl_phone_book.o: smpl_phone_book.s
	gcc -c -g -v smpl_phone_book.s >assembly.log 2>&1

smpl_phone_book.s: smpl_phone_book.c ct_assert.h util.h
	gcc -S -v smpl_phone_book.c >compilation.log 2>&1

clean:
	rm *.log; rm *.o; rm *.s
