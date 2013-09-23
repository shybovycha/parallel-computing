TARGET := hello
OBJ := hello.obj
CC := g++
override CFLAGS += -fopenmp -Wall
override LDFLAGS += -lopenmp
