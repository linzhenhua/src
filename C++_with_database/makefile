##############################
# Makefile
##############################

#target
TARGET=DatabaseOp               #目标可执行文件

#compile and lib parameter
CXX=g++       					#编译器
CXXFLAGS=-g -std=c++11 -Wall    #编译器参数
LIBS=-lmysqlclient              #动态链接库名称
LDFLAGS=-L/usr/lib/mysql/       #动态库路径
INCLUDE=-I/usr/include/mysql/   #头文件路径

SRC=$(wildcard *.cc)            #wildcard一般和*搭配使用，wildcard表示*通配符展开时，仍然有效
OBJ=$(SRC:%.cc=%.o)             #%.cc=%.o 表示所有.o文件替换为.cc文件，这样就可以得到在当前目录可生成的.o文件列表

#link
#$(TARGET):$(OBJ)
	#$(CXX) -o $@ $^ $(LDFLAGS) $(LIBS)

#compile
#%.o: %.cc
	#$(CXX) $(CXXFLAGS) $(INCLUDE) -c $^

#link
$(TARGET):DatabaseOp.o main.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LIBS)
DatabaseOp.o:DatabaseOp.cc DatabaseOp.h
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $<
main.o:main.cc DatabaseOp.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o
	rm -f $(TARGET) 
