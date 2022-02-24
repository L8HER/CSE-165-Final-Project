CC = g++

gamefile=main.cpp

ifeq ($(shell uname), Linux)
		exe = Pong.exe

		comp = -Wall -lglfw3 -lrt -lm -ldl -lX11 -lpthread -lxcb -lXau -lXdmcp -lGL -pthread -lXxf86vm -lxcb-dri2 -lXdamage -lXfixes -lXext -xcb -ldrm -lxcb-dri2 -lXdamage -lXfixes -lxcb-glx -lGLU -lm -lglut -lSOIL -lGLEW -o
endif

all:
	$(CC) $(gamefile) $(comp) $(exe)

run: 
	./$(exe)

clean:
	rm -f Pong.exe