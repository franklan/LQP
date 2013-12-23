INCLUDE_DIR=-I/home/liuss/environment/opencv2.2/include
LIBS = -Wl,--rpath=/home/liuss/environment/opencv2.2/lib,-L/home/liuss/environment/opencv2.2/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_objdetect -lopencv_ml -lopencv_calib3d
all:extractLQP
main.o: main.cpp
	g++ -c main.cpp $(INCLUDE_DIR)
svmscale.o: svmscale.cpp
	g++ -c svmscale.cpp
LQP.o: LQP.cpp
	g++ -c LQP.cpp $(INCLUDE_DIR)
extractLQP: main.o LQP.o svmscale.o
	g++ -o extractLQP main.o LQP.o svmscale.o $(INCLUDE_DIR) $(LIBS)
clean:
	rm -rf extractLQP *.o

