CC=gcc
CFLAGS=-Wall -I. -std=gnu99 -pedantic -march=native -O2 -Wno-pointer-arith -Wno-address


all: sdevs

sdevs: main.o tcpclient.o configs.o utils.o log.o state.o devlist.o
	$(CC) main.o tcpclient.o configs.o utils.o log.o state.o devlist.o -o sdevs $(CFLAGS)

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
