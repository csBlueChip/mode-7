#ifndef TTXFONTS_H
#define TTXFONTS_H

#include <stdint.h>
#include <stdbool.h>

typedef  uint8_t  glyph_t[10];

typedef
	struct gset {
		const char*     name;  // Textual name
		const bool      gfx;   // true=graphics; false=alpha
		const int       cnt;   // number of CHRs in set
		const int       chr0;  // offset of CHR(0)
		const glyph_t*  gly;   // Glyph data
	}
gset_t;

extern  const gset_t  gset[];
extern  const int     gsetCnt;

extern  const glyph_t  ttxf_m5050_Alpha_UK_Low[];
extern  const glyph_t  ttxf_m5050_Alpha_UK_Med[];
extern  const glyph_t  ttxf_m5050_Alpha_UK_High[];
extern  const glyph_t  ttxf_m5051_Alpha_DE_Low[];
extern  const glyph_t  ttxf_m5051_Alpha_DE_Med[];
extern  const glyph_t  ttxf_m5051_Alpha_DE_High[];
extern  const glyph_t  ttxf_m5052_Alpha_SW_Low[];
extern  const glyph_t  ttxf_m5052_Alpha_SW_Med[];
extern  const glyph_t  ttxf_m5052_Alpha_SW_High[];
extern  const glyph_t  ttxf_m5053_Alpha_IT_Low[];
extern  const glyph_t  ttxf_m5053_Alpha_IT_Med[];
extern  const glyph_t  ttxf_m5053_Alpha_IT_High[];
extern  const glyph_t  ttxf_m5054_Alpha_BE_Low[];
extern  const glyph_t  ttxf_m5054_Alpha_BE_Med[];
extern  const glyph_t  ttxf_m5054_Alpha_BE_High[];
extern  const glyph_t  ttxf_m5055_Alpha_US_Low[];
extern  const glyph_t  ttxf_m5055_Alpha_US_Med[];
extern  const glyph_t  ttxf_m5055_Alpha_US_High[];
extern  const glyph_t  ttxf_m5056_Alpha_HE_Low[];
extern  const glyph_t  ttxf_m5056_Alpha_HE_Med[];
extern  const glyph_t  ttxf_m5056_Alpha_HE_High[];
extern  const glyph_t  ttxf_m5057_Alpha_RU_Low[];
extern  const glyph_t  ttxf_m5057_Alpha_RU_Med[];
extern  const glyph_t  ttxf_m5057_Alpha_RU_High[];
extern  const glyph_t  ttxf_m505x_Gfx_Ctg_Low[];
extern  const glyph_t  ttxf_m505x_Gfx_Ctg_High[];
extern  const glyph_t  ttxf_m505x_Gfx_Sep_Low[];
extern  const glyph_t  ttxf_m505x_Gfx_Sep_High[];
extern  const glyph_t  ttxf_m5050_Mode7_Alpha_Low[];
extern  const glyph_t  ttxf_m5050_Mode7_Alpha_High[];
extern  const glyph_t  ttxf_m5050_Mode7_Gfx_Low[];
extern  const glyph_t  ttxf_m5050_Mode7_Gfx_High[];

#endif // TTXFONTS_H
