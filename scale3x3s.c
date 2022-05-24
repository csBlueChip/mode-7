#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ttxFonts/ttxFonts.h"

//+============================================================================ =======================================
// Scale each pixel to 3x3s
// Scale GLYPH to 1.3:1 (cannot stretch pixels in raster)
// NO SMOOTHING
//
int  scale3x3s (const glyph_t gIn,  int gfx,  uint32_t* gOut)
{
	uint16_t   clr;

	for (int rIn = 0;  rIn < 10;  rIn++) {
		uint32_t*  out1 = &gOut[(rIn*3)  ];
		uint32_t*  out2 = &gOut[(rIn*3)+1];
		uint32_t*  out3 = &gOut[(rIn*3)+2];

		uint32_t   bit  = 0x800000;

		*out1 = (*out2 = (*out3 = 0));

		for (uint8_t mask = 0x20;  mask;  mask >>= 1) {
			int      c   = (gIn[rIn] & mask);  // centre; this pixel

			// plot
			if (c) {
				// pixles are plotted as 4x3 to attain 1.33:1 pixel scaling
				*out1 |= bit;  *out2 |= bit;  *out3 |= bit;  bit >>= 1;
				*out1 |= bit;  *out2 |= bit;  *out3 |= bit;  bit >>= 1;
				*out1 |= bit;  *out2 |= bit;  *out3 |= bit;  bit >>= 1;
				*out1 |= bit;  *out2 |= bit;  *out3 |= bit;  bit >>= 1;  // pixel scaling

			} else if (!gfx) {
				// Smooth non-graphical glyphs
				uint8_t  left  = mask <<1;
				uint8_t  right = mask >>1;

				int  u  = (rIn > 0) ? (gIn[rIn-1] & mask ) : 0 ;
				int  d  = (rIn < 9) ? (gIn[rIn+1] & mask ) : 0 ;
				int  l  =             (gIn[rIn  ] & left );
				int  r  =             (gIn[rIn  ] & right);

				if (u && l)  *out1 |= bit ;
				if (d && l)  *out3 |= bit ;
				bit >>= 3;
				if (u && r)  *out1 |= bit ;
				if (d && r)  *out3 |= bit ;
				bit >>= 1;

			} else {
				// do NOT smooth graphical glyphs
				bit >>= 4;
			}
		}
	}
}

//+============================================================================ =======================================
int  doFont3x3s (const gset_t* gp,  FILE* fh)
{
	for (int n = 0;  n < gp->cnt;  n++) {
		uint32_t  gOut[3*10];
		char      asc[32];

		(void)scale3x3s(gp->gly[n], gp->gfx, gOut);

		if ((gp->chr0 +n >= 0x20) && (gp->chr0 +n <= 0x7E))
			fprintf(fh,
				"\t{ // [%d] CHR$(%d) '0x%X' '%c' ----------------------------------------\n",
				n, gp->chr0 +n, gp->chr0 +n, gp->chr0 +n
			);
		else
			fprintf(fh,
				"\t{ // [%d] CHR$(%d) '0x%X' --------------------------------------------\n",
				n, gp->chr0 +n, gp->chr0 +n
			);

		for (int r = 0;  r < 3*10;  r++) {
			uint32_t  d  = 0;
			char*     ap = asc;
			memset(asc, 0, sizeof(asc));

			for (int c = 0x800000;  c;  c >>= 1) {
				if (gOut[r] & c) {
					*ap++ = '#';
					d |= c;
				} else {
					*ap++ = '.';
				}
			}

			fprintf(fh,
				"\t\t0x%06X%c /* %s */\n",
				d, ((r == 19) ? ' ' : ','), asc
			);
		}
		fprintf(fh, "\t}%s\n", ((n == gp->cnt -1) ? "" : ","));

	}
	return 1;
}

//+============================================================================ =======================================
int  main (void)
{
	char*  dir = "ttxFonts3x3s";

	for (const gset_t* gp = gset; gp->gly;  gp++) {
		FILE*      fh      = NULL;
		char       fn[128] = {0};

		printf("# [3x3s] %s\n", gp->name);
		sprintf(fn, "%s/%s_3x3s.c", dir, gp->name);  // yep, I know!
		if (!(fh = fopen(fn, "wb"))) {
			fprintf(fh, "! File create error ¦%s¦\n", fn);
			return 0;
		}

		fprintf(fh,
			"// Teletext Glyph Map: %s_3x3s\n"
			"// Mode: %s,  Base offset: %d (0x%02X)\n"
			"\n"
			"#include \"ttxFonts_3x3s.h\"\n"
			"\n"
			"const glyph3x3s_t  %s_3x3s[%d] = {\n",
			gp->name, 
			gp->gfx?"gfx":"alpha", gp->chr0, gp->chr0, 
			gp->name, gp->cnt
		);

		doFont3x3s(gp, fh);

		fprintf(fh, "};\n");

		fclose(fh);
	}

	return 0;
}
