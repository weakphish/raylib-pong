PKG_FLAGS=`pkg-config --libs --cflags raylib`

main: main.c
	cc main.c $(PKG_FLAGS) -o main
