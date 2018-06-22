CFLAGS	:= -Wall
OBJ	:= color_compile out_color_info

SH_PATH	:= $(shell env | grep SHELL)	# /bin/bash
SH_NAME	:= $(notdir $(SH_PATH))		# bash
# if SH_CONFIG file error, please change it manually
SH_CONFIG	:= $(addsuffix rc, $(addprefix ~/., $(SH_NAME)))	# ~/.bashrc

all: $(OBJ)

color_compile: color_compile.o
	gcc -o $@ $^

out_color_info: out_color_info.o
	gcc -o $@ $^

%.o: %.c
	gcc -c -o $@ $< $(CFLAGS)

clean:
	rm -f *.o $(OBJ)

install:
	cp -f color_compile ~/.bin/bin
	cp -f out_color_info ~/.bin/bin

	#echo 'alias gcc="color_compile gcc"' >> $(SH_CONFIG)
	#echo 'alias g++="color_compile g++"' >> $(SH_CONFIG)
	#echo 'alias make="color_compile make"' >> $(SH_CONFIG)
	#echo 'alias arm-openwrt-linux-uclibcgnueabi-gcc="color_compile make"' >> $(SH_CONFIG)

TEST:
	gcc test.c -Wall
