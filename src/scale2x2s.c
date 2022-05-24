#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ttxFonts/ttxFonts.h"

//+============================================================================ =======================================
// Scale each pixel to 2x2
// Scale GLYPH to 1.3:1 (cannot stretch pixels in raster)
//
int  scale2x2s (const glyph_t gIn,  int gfx,  uint16_t* gOut)
{
	uint16_t   clr;

	for (int rIn = 0;  rIn < 10;  rIn++) {
		uint16_t*  out1 = &gOut[ rIn<<1   ];
		uint16_t*  out2 = &gOut[(rIn<<1)|1];

		uint16_t   bit  = 0x8000;

		*out1 = (*out2 = 0);

		for (uint8_t mask = 0x20;  mask;  mask >>= 1) {
			int      c   = (gIn[rIn] & mask);  // centre; this pixel

			if (gfx) {  // gfx smoothing
				if (mask == 0x02)  bit <<= 1 ;  // add to left
				if ((mask <= 0x10) && (mask >= 0x01)) {
					if (c) {
						*out1 |= bit;
						*out2 |= bit;
					}
					bit >>= 1;
				}

			} else {  // alpha smoothing
				uint8_t  pad = 0;

				if (mask < 0x10) {
					uint8_t  left  = mask <<1;
					uint8_t  right = mask >>1;

					// look at diagonals
					int  u  = (rIn > 0) ? (gIn[rIn-1] & mask ) : 0 ;
					int  ul = (rIn > 0) ? (gIn[rIn-1] & left ) : 0 ;
					int  d  = (rIn < 9) ? (gIn[rIn+1] & mask ) : 0 ;
					int  dl = (rIn < 9) ? (gIn[rIn+1] & left ) : 0 ;
					int  l  =             (gIn[rIn  ] & left );
					//int  r  =             (gIn[rIn  ] & right);

					pad = 0;
					if (c && l) {
						pad |= 3;
					} else {
						if (!c && l && u && !ul)    pad |= 1 ;
						if (!c && l && d && !dl)    pad |= 2 ;
						if (c && !l && !u && ul)    pad |= 1 ;
						if (c && !l && !d && dl)    pad |= 2 ;
					//	if (!pad && c && !l && !r)  pad |= 3 ;
					}

					if (pad & 1)  *out1 |= bit;
					if (pad & 2)  *out2 |= bit;
					bit >>= 1;
				}
			}

			// plot
			if (c) {
				*out1 |= bit;  *out2 |= bit;  bit >>= 1;
				*out1 |= bit;  *out2 |= bit;  bit >>= 1;
			} else {
				bit >>= 2;
			}
		}
	}
}

//+============================================================================ =======================================

//void  doFont (const glyph_t set[],  const int cnt,  FILE* fOut)
int  doFont2x2s (const gset_t* gp,  FILE* fh)
{
	for (int n = 0;  n < gp->cnt;  n++) {
		uint16_t  gOut[2*10];
		char      asc[32];

		(void)scale2x2s(gp->gly[n], gp->gfx, gOut);

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

		for (int r = 0;  r < 2*10;  r++) {
			uint16_t  w  = 0;
			char*     ap = asc;
			memset(asc, 0, sizeof(asc));

			for (int c = 0x8000;  c;  c >>= 1) {
				if (gOut[r] & c) {
					*ap++ = '#';
					w |= c;
				} else {
					*ap++ = '.';
				}
			}

			fprintf(fh,
				"\t\t0x%04X%c /* %s */\n",
				w, ((r == 19) ? ' ' : ','), asc
			);
		}
		fprintf(fh, "\t}%s\n", ((n == gp->cnt -1) ? "" : ","));

	}
	return 1;
}

//+============================================================================ =======================================
int  main (void)
{
	char*  dir = "ttxFonts2x2s";

	for (const gset_t* gp = gset; gp->gly;  gp++) {
		FILE*      fh      = NULL;
		char       fn[128] = {0};

		printf("# [2x2s] %s\n", gp->name);
		sprintf(fn, "%s/%s_2x2s.c", dir, gp->name);  // yep, I know!
		if (!(fh = fopen(fn, "wb"))) {
			fprintf(fh, "! File create error ¦%s¦\n", fn);
			return 0;
		}

		fprintf(fh,
			"// Teletext Glyph Map: %s_2x2s\n"
			"// Mode: %s,  Base offset: %d (0x%02X)\n"
			"\n"
			"#include \"ttxFonts_2x2s.h\"\n"
			"\n"
			"const glyph2x2s_t  %s_2x2s[%d] = {\n",
			gp->name, 
			gp->gfx?"gfx":"alpha", gp->chr0, gp->chr0, 
			gp->name, gp->cnt
		);

		doFont2x2s(gp, fh);

		fprintf(fh, "};\n");

		fclose(fh);
	}

	return 0;
}
