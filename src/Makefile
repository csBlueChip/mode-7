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

render:
	gcc -o render -Werror -g \
		render.c \
		ttxFonts3x3s/m5050_Alpha_UK_High_3x3s.c ttxFonts3x3s/m5050_Alpha_UK_Low_3x3s.c \
		ttxFonts3x3s/m5050_Alpha_UK_Med_3x3s.c \
		ttxFonts3x3s/m505x_Gfx_Ctg_High_3x3s.c  ttxFonts3x3s/m505x_Gfx_Ctg_Low_3x3s.c \
		ttxFonts3x3s/m505x_Gfx_Sep_High_3x3s.c  ttxFonts3x3s/m505x_Gfx_Sep_Low_3x3s.c \
		
