CC=gcc
CXX=g++
target=test
inc=./
src=$(wildcard ./*.cpp)

obj=$(patsubst %.c, %.o, $(src))
CLAGS =  -lpthread


$(target):$(obj)
	$(CXX) $^ -o $@ $(CLAGS)

%.o:%.c
	$(CXX) -c $< -I $(inc) -o $@ $(CLAGS)

.PHONY:clean
clean:
	-rm -rf logs/ $(target)





