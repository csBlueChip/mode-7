#include "ttxFonts3x3s/ttxFonts_3x3s.h"
#include <stddef.h>
#include <alloca.h>

const gset3x3s_t  gset[] = {
	{"m5050_Alpha_UK_Low_3s3x", false, 32, 32, m5050_Alpha_UK_Low_3x3s},
	{"m5050_Alpha_UK_Med_3s3x", false, 32, 64, m5050_Alpha_UK_Med_3x3s},
	{"m5050_Alpha_UK_High_3s3x", false, 32, 96, m5050_Alpha_UK_High_3x3s},
	{"m505x_Gfx_Ctg_Low_3s3x", true, 32, 32, m505x_Gfx_Ctg_Low_3x3s},
	{"m505x_Gfx_Ctg_High_3s3x", true, 32, 96, m505x_Gfx_Ctg_High_3x3s},
	{"m505x_Gfx_Sep_Low_3s3x", true, 32, 32, m505x_Gfx_Sep_Low_3x3s},
	{"m505x_Gfx_Sep_High_3s3x", true, 32, 96, m505x_Gfx_Sep_High_3x3s},
};

//-----------------------------------------------------------------------------
// Available Colours
//
typedef
	enum ttClr {
		TTC_BLK = 0,  // Non-standard
		TTC_RED = 1,
		TTC_GRN = 2,
		TTC_YEL = 3,
		TTC_BLU = 4,
		TTC_MAG = 5,
		TTC_CYN = 6,
		TTC_WHT = 7,
	}
ttClr_t;

enum {
	ALF_LO = 0,
	ALF_MD = 1,
	ALF_HI = 2,
	GFX_CTG_LO = 3,
	GFX_CTG_HI = 4,
	GFX_SEP_LO = 5,
	GFX_SEP_HI = 6,
};

typedef
	enum ttxMode {
		TXM_ALF,
		TXM_GFX_CTG,
		TXM_GFX_SEP,
	}
ttxMode_t;

typedef
	enum ttxHt {
		TXH_SGL,
		TXH_DBL_TOP,
		TXH_DBL_BTM,
		TXH_DBL_FULL,
	}
ttxHt_t;

typedef  uint16_t  pixel_t ;

int  render_3x3 (pixel_t* glyph,  const glyph3x3s_t gp,  const ttxHt_t ht,  const ttClr_t fg,  const ttClr_t bg)
{
	switch (ht) {
		case TXH_SGL :
			for (int r = 0;  r < 30;  r++) {
				uint32_t  mask = 0x800000;
				for (int c = 0;  c < 24;  c++, mask >>= 1)
					glyph[(r*24)+c] = (gp[r] & mask) ? fg : bg ;
			}
			break;

		case TXH_DBL_TOP :
			for (int r = 0;  r < 15;  r++) {
				uint32_t  mask = 0x800000;
				for (int c = 0;  c < 24;  c++, mask >>= 1)
					glyph[(r*48)+c] = glyph[(r*48)+c+24]  = (gp[r] & mask) ? fg : bg ;
			}
			break;

		case TXH_DBL_BTM :
			for (int r = 0;  r < 15;  r++) {
				uint32_t  mask = 0x800000;
				for (int c = 0;  c < 24;  c++, mask >>= 1)
					glyph[(r*48)+c] = glyph[(r*48)+c+24]  = (gp[r+15] & mask) ? fg : bg ;
			}
			break;

		case TXH_DBL_FULL :  // requires a double size dest buffer!
			for (int r = 0;  r < 30;  r++) {
				uint32_t  mask = 0x800000;
				for (int c = 0;  c < 24;  c++, mask >>= 1)
					glyph[(r*48)+c] = glyph[(r*48)+c+24]  = (gp[r] & mask) ? fg : bg ;
			}
			break;
	}

	return 1;
}

int  showCh_3x3 (int y, int x, char ch,  ttxMode_t m,  ttxHt_t ht,  ttClr_t fg,  ttClr_t bg)
{
	const  glyph3x3s_t*  set  = NULL;

	pixel_t*     glyph;
	int          goff = 0;
	int          h    = (ht == TXH_DBL_FULL) ? 2*30 : 30 ;

	glyph = alloca(sizeof(*glyph) * 24*h); // 2* 24*30=1,440 ...*2 = 2,880

	if ((ch < 0x20) || (ch > 0x7F))  return 0 ;

	switch (m) {
		case TXM_ALF:
			if        (ch >= gset[ALF_HI].chr0) {
				set  =       gset[ALF_HI].gly;
				goff = ch -  gset[ALF_HI].chr0;

			} else if (ch >= gset[ALF_MD].chr0) {
				set  =       gset[ALF_MD].gly;
				goff = ch -  gset[ALF_MD].chr0;

			} else {
				set  =       gset[ALF_LO].gly;
				goff = ch -  gset[ALF_LO].chr0;
			}
			break;

		case TXM_GFX_CTG:
			if        (ch >= gset[GFX_CTG_HI].chr0) {
				set  =       gset[GFX_CTG_HI].gly;
				goff = ch -  gset[GFX_CTG_HI].chr0;

			} else if (ch >= gset[ALF_MD].chr0) {
				set  =       gset[ALF_MD].gly;
				goff = ch -  gset[ALF_MD].chr0;

			} else {
				set  =       gset[GFX_CTG_LO].gly;
				goff = ch -  gset[GFX_CTG_LO].chr0;
			}
			break;

		case TXM_GFX_SEP:
			if        (ch >= gset[GFX_SEP_HI].chr0) {
				set  =       gset[GFX_SEP_HI].gly;
				goff = ch -  gset[GFX_SEP_HI].chr0;

			} else if (ch >= gset[ALF_MD].chr0) {
				set  =       gset[ALF_MD].gly;
				goff = ch -  gset[ALF_MD].chr0;

			} else {
				set  =       gset[GFX_SEP_LO].gly;
				goff = ch -  gset[GFX_SEP_LO].chr0;
			}
			break;

		default:
			return 0;
	}

	render_3x3(glyph, set[goff], ht, fg, bg);

	if (bg = 0x0001) {  // transparency
		for (int row = 0;  row < h;  row++) {
			uint32_t  mask = 0x800000;
			int       col  = 0;
			while (mask) {
				// Trivial RLE to minimise bus transactions
				int  bit  = !!(glyph[row] & mask);
				int  cnt  = 1;
				while (mask >>= 1) {
					if (!!(glyph[row] & mask) != bit)  break ;
					cnt++;
				}

				bus->beginWrite();
				gfx->writeAddrWindow(4+(x*24)+col, y*30+row, cnt, 1);
				bus->writeBytes(glyph, cnt*sizeof(*glyph));
				bus->endWrite();

				col += cnt;
			}
		}

	} else {
		bus->beginWrite();
		gfx->writeAddrWindow(4+(x*24), y*30, 24, h);  // 13.3 x 8 .. 4=(320%13)/2
		bus->writeBytes(glyph, 24*h*sizeof(*glyph));
		bus->endWrite();
	}

	return 1;
}
