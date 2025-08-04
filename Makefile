CC=clang
CFLAGS=-lX11

all: hntrwm

hntrwm: hntrwm.c config.h
	$(CC) $(CFLAGS) hntrwm.c -o hntrwm

clean: 
	rm hntrwm

test: all
	Xephyr -screen 1280x720 :1 & 
	sleep 0.25
	env DISPLAY=:1 ./hntrwm & 
	sleep 0.25
	env DISPLAY=:1 fastcompmgr &
	# env DISPLAY=:1 xwallpaper --zoom /home/hntr/.local/share/wallpapers/dragon-gruvbox.jpg &
	env DISPLAY=:1 kitty & 