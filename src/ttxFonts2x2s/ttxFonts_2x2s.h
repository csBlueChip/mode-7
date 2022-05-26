#ifndef TTXFONTS_2X2S_H
#define TTXFONTS_2X2S_H

#include <stdint.h>
#include <stdbool.h>

typedef  uint16_t  glyph2x2s_t[20];

typedef
	struct gset2x2s {
		const char*         name;  // Textual name
		const bool          gfx;   // true=graphics; false=alpha
		const int           cnt;   // number of CHRs in set
		const int           chr0;  // offset of CHR(0)
		const glyph2x2s_t*  gly;   // Glyph data
	}
gset2x2s_t;

extern  const gset2x2s_t   gset2x2s[];
extern  const int          gset2x2sCnt;

extern  const glyph2x2s_t  5050_Alpha_UK_Low_2x2s[];
extern  const glyph2x2s_t  5050_Alpha_UK_Med_2x2s[];
extern  const glyph2x2s_t  5050_Alpha_UK_High_2x2s[];
extern  const glyph2x2s_t  5051_Alpha_DE_Low_2x2s[];
extern  const glyph2x2s_t  5051_Alpha_DE_Med_2x2s[];
extern  const glyph2x2s_t  5051_Alpha_DE_High_2x2s[];
extern  const glyph2x2s_t  5052_Alpha_SW_Low_2x2s[];
extern  const glyph2x2s_t  5052_Alpha_SW_Med_2x2s[];
extern  const glyph2x2s_t  5052_Alpha_SW_High_2x2s[];
extern  const glyph2x2s_t  5053_Alpha_IT_Low_2x2s[];
extern  const glyph2x2s_t  5053_Alpha_IT_Med_2x2s[];
extern  const glyph2x2s_t  5053_Alpha_IT_High_2x2s[];
extern  const glyph2x2s_t  5054_Alpha_BE_Low_2x2s[];
extern  const glyph2x2s_t  5054_Alpha_BE_Med_2x2s[];
extern  const glyph2x2s_t  5054_Alpha_BE_High_2x2s[];
extern  const glyph2x2s_t  5055_Alpha_US_Low_2x2s[];
extern  const glyph2x2s_t  5055_Alpha_US_Med_2x2s[];
extern  const glyph2x2s_t  5055_Alpha_US_High_2x2s[];
extern  const glyph2x2s_t  5056_Alpha_HE_Low_2x2s[];
extern  const glyph2x2s_t  5056_Alpha_HE_Med_2x2s[];
extern  const glyph2x2s_t  5056_Alpha_HE_High_2x2s[];
extern  const glyph2x2s_t  5057_Alpha_RU_Low_2x2s[];
extern  const glyph2x2s_t  5057_Alpha_RU_Med_2x2s[];
extern  const glyph2x2s_t  5057_Alpha_RU_High_2x2s[];
extern  const glyph2x2s_t  505x_Gfx_Ctg_Low_2x2s[];
extern  const glyph2x2s_t  505x_Gfx_Ctg_High_2x2s[];
extern  const glyph2x2s_t  505x_Gfx_Sep_Low_2x2s[];
extern  const glyph2x2s_t  505x_Gfx_Sep_High_2x2s[];
extern  const glyph2x2s_t  5050_Mode7_Alpha_Low_2x2s[];
extern  const glyph2x2s_t  5050_Mode7_Alpha_High_2x2s[];
extern  const glyph2x2s_t  5050_Mode7_Gfx_Low_2x2s[];
extern  const glyph2x2s_t  5050_Mode7_Gfx_High_2x2s[];

#endif // TTXFONTS_2X2S_H
