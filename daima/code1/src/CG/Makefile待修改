
OBJ_DIR = ../Obj
SRC = main.c  algorithm.c link.c agi.c
#CC_SRC = cardiology.cc

#此Makefile要把D:\msys64\mingw64\bin中的，用来做调试gtk源码
#libgdk-3-0.dll改为libgdk-3-0-.dll
#libcairo-2.dll改为libcairo-2-.dll
#libgobject-2.0-0.dll改为libgobject-2.0-0-.dll

GTK_DIR = /d/source/msys2package/source/mingw-w64-gtk3/src/build-x86_64-w64-mingw32/gtk/.libs
GDK_DIR = /d/source/msys2package/source/mingw-w64-gtk3/src/build-x86_64-w64-mingw32/gdk/.libs
CAIRO_DIR = /d/source/msys2package/source/mingw-w64-cairo-1.16.0-1/src/build-x86_64-w64-mingw32/src/.libs

# 把.c后缀替换为.o，并加上目录        
OBJ = ${patsubst %.c, ${OBJ_DIR}/%.o, ${SRC}}

CC_OBJ = ${patsubst %.cc, ${OBJ_DIR}/%.o, ${CC_SRC}}

OBJ += ${CC_OBJ}

INC = ${wildcard  *.h}

LIBS = -L/d/msys64/mingw64/bin -L/d/msys64/mingw64/lib \
 -L${CAIRO_DIR} -L${GTK_DIR} -L${GDK_DIR}  \
-L/d/source/glib2/src/glib-2.48.0/gobject/.libs \
-lgtk-31-0 -lgdk-3-0 -lgdi32 -limm32 -lshell32 -lole32 \
-Wl,-luuid -lwinmm -ldwmapi -lsetupapi -lcfgmgr32 -lz \
-lpangowin32-1.0-0 -lpangocairo-1.0-0 -lpango-1.0-0 \
-lfribidi-0 -latk-1.0-0 -lcairo-gobject-2 -lcairo-2 \
-lgdk_pixbuf-2.0-0 -lgio-2.0-0 -lgobject-2.0-0 -lglib-2.0-0 -lintl-8 \


GTK_INC = -pthread -mms-bitfields -I/mingw64/include/gtk-3.0 \
-I/mingw64/include/cairo -I/mingw64/include -I/mingw64/include/pango-1.0 \
-I/mingw64/include/fribidi -I/mingw64/include -I/mingw64/include/atk-1.0 \
-I/mingw64/include/cairo -I/mingw64/include/pixman-1 -I/mingw64/include \
-I/mingw64/include/freetype2 -I/mingw64/include -I/mingw64/include/harfbuzz \
-I/mingw64/include -I/mingw64/include/libpng16 -I/mingw64/include/gdk-pixbuf-2.0 \
-I/mingw64/include -I/mingw64/include/glib-2.0 -I/mingw64/lib/glib-2.0/include \
-I/mingw64/include

TARGET=../code1
#CC=/d/msys64/mingw64/bin/x86_64-w64-mingw32-gcc.exe
CC = gcc
CCFLAGS=-g -Wall ${LIBS} ${GTK_INC}

#这个命令怪怪的，怎么会在同一个目录下生成两个Obj文件夹
#而且还删不掉，显示“无法删除 该项目不在 请确认该项目的位置，然后重试”
#在msys2的命令行用 rm -fr Obj\ \ / 总算删掉了
#所以还是手工新建一下吧 我也不知道正确的操作应该是怎么样的

#$(shell mkdir -p "$(OBJ_DIR)")

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