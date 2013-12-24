all:KMeans
hash.o: hash.cpp
	g++ -c hash.cpp
main.o: main.cpp
	g++ -c main.cpp
kmeans.o: kmeans.cpp
	g++ -c kmeans.cpp
KMeans: main.o hash.o kmeans.o
	g++ -o KMeans main.o hash.o kmeans.o
clean:
	rm -rf *.o KMeans
