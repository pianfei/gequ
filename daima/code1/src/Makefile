
OBJ_DIR = ../Obj
SRC = main.c  algorithm.c link.c agi.c
#CC_SRC = cardiology.cc

# 把.c后缀替换为.o，并加上目录        
OBJ = ${patsubst %.c, ${OBJ_DIR}/%.o, ${SRC}}

CC_OBJ = ${patsubst %.cc, ${OBJ_DIR}/%.o, ${CC_SRC}}

OBJ += ${CC_OBJ}

INC = ${wildcard  *.h}

LIBS = -lpthread -lrt -lreadline

TARGET=../code1
CC = gcc
CCFLAGS=-g -Wall ${LIBS} 


all:${TARGET}

${TARGET}: ${OBJ}  
	${CC} $^ -o $@ ${LIBS} -lwinmm 
	@echo "Compile done."
    

${OBJ_DIR}/%.o:%.c ${INC}
	@echo "Compiling $< ==> $@"
	${CC} ${CCFLAGS} -c $< -o $@
	
${OBJ_DIR}/%.o: %.cc ${INC}
	@echo "Compiling C++ $< ==> $@"
	${CC} ${CCFLAGS} -c $< -o $@

    
clean:
# -r删除目录，-f删除文件
	rm -f ${OBJ_DIR}/*.o
	rm -f ${TARGET}