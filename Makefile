all : pcap_test

pcap_test: main.o func.o
	g++ -o pcap_test main.o func.o -lpcap

main.o: func.h main.cpp
	g++ -std=c++11 -c -o main.o main.cpp

func.o: func.cpp func.h struct.h
	g++ -c func.cpp

clean:
	rm -f pcap_test
	rm -f *.o