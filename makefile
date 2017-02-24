all: phone_book

phone_book: smpl_phone_book.o
	gcc -o phone_book smpl_phone_book.o

smpl_phone_book.o: smpl_phone_book.c ct_assert.h util.h
	gcc -c -g smpl_phone_book.c

