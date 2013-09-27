all:
	g++ -c -m64 -pipe -fopenmp -g -Wall -W -D_REENTRANT -fPIE -DQT_QML_DEBUG -DQT_DECLARATIVE_DEBUG -DQT_CORE_LIB -I/home/shybovycha/Qt5.0.1/5.0.1/gcc_64/mkspecs/linux-g++-64 -I/home/shybovycha/Qt5.0.1/5.0.1/gcc_64/include -I/home/shybovycha/Qt5.0.1/5.0.1/gcc_64/include/QtCore -I. -I. -o main.o main.cpp
	
	g++ -m64 -fopenmp -Wl,-rpath,/home/shybovycha/Qt5.0.1/5.0.1/gcc_64 -Wl,-rpath,/home/shybovycha/Qt5.0.1/5.0.1/gcc_64/lib -o main main.o  -L/home/shybovycha/Qt5.0.1/5.0.1/gcc_64/lib -lQt5Core -lpthread	

	rm main.o
