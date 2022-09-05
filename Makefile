run:
	gcc src/pong.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o run

clean:
	rm run