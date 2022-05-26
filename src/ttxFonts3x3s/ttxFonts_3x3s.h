#ifndef TTXFONTS_3X3S_H
#define TTXFONTS_3X3S_H

#include <stdint.h>
#include <stdbool.h>

typedef  uint16_t  glyph3x3s_t[20];

typedef
	struct gset3x3s {
		const char*         name;  // Textual name
		const bool          gfx;   // true=graphics; false=alpha
		const int           cnt;   // number of CHRs in set
		const int           chr0;  // offset of CHR(0)
		const glyph3x3s_t*  gly;   // Glyph data
	}
gset3x3s_t;

extern  const gset3x3s_t   gset3x3s[];
extern  const int          gset3x3sCnt;

extern  const glyph3x3s_t  5050_Alpha_UK_Low_3x3s[];
extern  const glyph3x3s_t  5050_Alpha_UK_Med_3x3s[];
extern  const glyph3x3s_t  5050_Alpha_UK_High_3x3s[];
extern  const glyph3x3s_t  5051_Alpha_DE_Low_3x3s[];
extern  const glyph3x3s_t  5051_Alpha_DE_Med_3x3s[];
extern  const glyph3x3s_t  5051_Alpha_DE_High_3x3s[];
extern  const glyph3x3s_t  5052_Alpha_SW_Low_3x3s[];
extern  const glyph3x3s_t  5052_Alpha_SW_Med_3x3s[];
extern  const glyph3x3s_t  5052_Alpha_SW_High_3x3s[];
extern  const glyph3x3s_t  5053_Alpha_IT_Low_3x3s[];
extern  const glyph3x3s_t  5053_Alpha_IT_Med_3x3s[];
extern  const glyph3x3s_t  5053_Alpha_IT_High_3x3s[];
extern  const glyph3x3s_t  5054_Alpha_BE_Low_3x3s[];
extern  const glyph3x3s_t  5054_Alpha_BE_Med_3x3s[];
extern  const glyph3x3s_t  5054_Alpha_BE_High_3x3s[];
extern  const glyph3x3s_t  5055_Alpha_US_Low_3x3s[];
extern  const glyph3x3s_t  5055_Alpha_US_Med_3x3s[];
extern  const glyph3x3s_t  5055_Alpha_US_High_3x3s[];
extern  const glyph3x3s_t  5056_Alpha_HE_Low_3x3s[];
extern  const glyph3x3s_t  5056_Alpha_HE_Med_3x3s[];
extern  const glyph3x3s_t  5056_Alpha_HE_High_3x3s[];
extern  const glyph3x3s_t  5057_Alpha_RU_Low_3x3s[];
extern  const glyph3x3s_t  5057_Alpha_RU_Med_3x3s[];
extern  const glyph3x3s_t  5057_Alpha_RU_High_3x3s[];
extern  const glyph3x3s_t  505x_Gfx_Ctg_Low_3x3s[];
extern  const glyph3x3s_t  505x_Gfx_Ctg_High_3x3s[];
extern  const glyph3x3s_t  505x_Gfx_Sep_Low_3x3s[];
extern  const glyph3x3s_t  505x_Gfx_Sep_High_3x3s[];
extern  const glyph3x3s_t  5050_Mode7_Alpha_Low_3x3s[];
extern  const glyph3x3s_t  5050_Mode7_Alpha_High_3x3s[];
extern  const glyph3x3s_t  5050_Mode7_Gfx_Low_3x3s[];
extern  const glyph3x3s_t  5050_Mode7_Gfx_High_3x3s[];

#endif // TTXFONTS_3X3S_H
