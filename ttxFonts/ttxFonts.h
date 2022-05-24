#ifndef TTXFONTS_H
#define TTXFONTS_H

#include <stdint.h>
#include <stdbool.h>

typedef
	struct gset {
		const char*      name;  // Textual name
		const bool       gfx;   // true=graphics; false=alpha
		const int        cnt;   // number of CHRs in set
		const int        chr0;  // offset of CHR(0)
		const uint8_t**  set;   // Glyph data
	}
gset_t;

extern  const gset_t  gset[];
extern  const int     gsetCnt;

#endif // TTXFONTS_H
