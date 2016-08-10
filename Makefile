CC=gcc
CFLAGS=-Wall -I. -std=gnu99 -pedantic -march=native -O2 -Wno-pointer-arith -Wno-address
LDFLAGS=-lmysqlclient -lcurl


all: sdevs

sdevs: main.o tcpclient.o configs.o utils.o log.o state.o devlist.o database.o telegram.o
	$(CC) main.o tcpclient.o configs.o utils.o log.o state.o devlist.o database.o telegram.o -o sdevs $(CFLAGS) $(LDFLAGS)

main.o: main.c
	$(CC) -c main.c $(CFLAGS)

configs.o: configs.c
	$(CC) -c configs.c $(CFLAGS) $(LDFLAGS)

tcpclient.o: tcpclient.c
	$(CC) -c tcpclient.c $(CFLAGS)

log.o: log.c
	$(CC) -c log.c $(CFLAGS)

utils.o: utils.c
	$(CC) -c utils.c $(CFLAGS)

state.o: state.c
	$(CC) -c state.c $(CFLAGS)

devlist.o: devlist.c
	$(CC) -c devlist.c $(CFLAGS)

database.o: database.c
	$(CC) -c database.c $(CFLAGS)

telegram.o: telegram.c
	$(CC) -c telegram.c $(CFLAGS)


install:
	mkdir /usr/share/state-devs
	cp sdevs.cfg /etc/
	cp sdevs /usr/share/state-devs/

remove:
	rm -rf /usr/share/state-devs/
	rm /etc/sdevs.cfg

clean:
	-rm sdevs
	-rm *.o
