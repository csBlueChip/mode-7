all:
	rm -rf ttxFonts/
	./map2c.sh

	rm -rf ttxFonts2x2s scale2x2s
	gcc ttxFonts/*.c scale2x2s.c -o scale2x2s -Werror -g
	mkdir ttxFonts2x2s
	./scale2x2s

	rm -rf ttxFonts3x3s scale3x3s
	gcc ttxFonts/*.c scale3x3s.c -o scale3x3s -Werror -g
	mkdir ttxFonts3x3s
	./scale3x3s
