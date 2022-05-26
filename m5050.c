
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

//-----------------------------------------------------------------------------
// 505x Control Codes  [qv. CONTROL CODE TABLES]
//
typedef
	enum m7CC {
		M7CC_x = 0;  //! todo
	}
m7CC_t;

//-----------------------------------------------------------------------------
// 505x Control Codes  [qv. CONTROL CODE TABLES]
//
typedef
	enum ttCC {
		TTCC_NUL      = 0x00,
		TTCC_A_BLK    = TTCC_NUL | TTC_BLK,
		TTCC_A_RED    = TTCC_NUL | TTC_RED,
		TTCC_A_GRN    = TTCC_NUL | TTC_GRN,
		TTCC_A_YEL    = TTCC_NUL | TTC_YEL,
		TTCC_A_BLU    = TTCC_NUL | TTC_BLU,
		TTCC_A_MAG    = TTCC_NUL | TTC_MAG,
		TTCC_A_CYN    = TTCC_NUL | TTC_CYN,
		TTCC_A_WHT    = TTCC_NUL | TTC_WHT,

		TTCC_FLASH    = 0x08,
		TTCC_STEADY   = 0x09,
		TTCC_BOX_ST   = 0x0A,
		TTCC_BOX_ND   = 0x0B,
		TTCC_HT_NRM   = 0x0C,
		TTCC_HT_DBL   = 0x0D,
		TTCC_S0       = 0x0E,
		TTCC_S1       = 0x0F,

		TTCC_DLE      = 0x10,
		TTCC_G_BLK    = TTCC_DLE | TTC_BLK,
		TTCC_G_RED    = TTCC_DLE | TTC_RED,
		TTCC_G_GRN    = TTCC_DLE | TTC_GRN,
		TTCC_G_YEL    = TTCC_DLE | TTC_YEL,
		TTCC_G_BLU    = TTCC_DLE | TTC_BLU,
		TTCC_G_MAG    = TTCC_DLE | TTC_MAG,
		TTCC_G_CYN    = TTCC_DLE | TTC_CYN,
		TTCC_G_WHT    = TTCC_DLE | TTC_WHT,

		TTCC_CONCEAL  = 0x18,
		TTCC_CONTIG   = 0x19,
		TTCC_SPACED   = 0x1A,
		TTCC_ESC      = 0x1B,
		TTCC_BG_BLK   = 0x1C,
		TTCC_BG_NEW   = 0x1D,
		TTCC_GR_HOLD  = 0x1E,
		TTCC_GR_REL   = 0x1F,

		TTCC_MASK_FN  = 0x08,
		TTCC_MASK_CLR = 0x07,
		TTCC_MASK_GFX = 0x10,
	}
ttCC_t;

//-----------------------------------------------------------------------------
// Box state
// Box requires TWO ON|OFF Control Codes to affect change
//
typedef
	enum ttBox {
		TTB_OFF,
		TTB_ST1,
		TTB_ON,
		TTB_ND1,
	}
ttBox_t;

//-----------------------------------------------------------------------------
// Fastext options
//
typedef
	struct fastext {
		char     title[10];
		ttClr_t  clr;
		int      page;
	}
fastext_t;

//-----------------------------------------------------------------------------
// Mullard 505x variants
//
typedef
	enum lang505x {
		LANG505X_UK    =  0,  // 5050 - English (UK)
		LANG505X_DE    =  1,  // 5051 - German
		LANG505X_SW    =  2,  // 5052 - Swedish
		LANG505X_IT    =  3,  // 5053 - Italian
		LANG505X_BE    =  4,  // 5054 - Belgian
		LANG505X_US    =  5,  // 5055 - US ASCII
		LANG505X_HE    =  6,  // 5056 - Hebrew
		LANG505X_RU    =  7,  // 5057 - Cyrillic
		LANG505X_MODE7 = 99,  // Acorn BBC Micro implementation of the 5050
	}
lang505x_t;

//-----------------------------------------------------------------------------
// 505x Emulation Driver details
//
typedef
	struct teletext {
		struct feat {  // Features
			int         w;        // columns
			int         h;        // rows

			bool        blkEn;    // Black Ink Available

			bool        fastext;  // Fastext support
		};
		struct sm {  //  Internal State Machine           **reset value
			int         y;        // Cursor y coord
			int         x;        // Cursor x coord        **0

			ttClr_t     clrFg;    // Foreground colour     **WHITE
			ttClr_t     clrBg;    // Background colour     **BLK
			bool        flash;    // !steady               **OFF
			bool        conceal;  // !reveal               **OFF

			bool        dblH;     // !single height        **OFF

			bool        gfx;      // !alphanumeric mode    **OFF
			bool        spaced;   // !contiguous graphics  **OFF
			struct {
				bool    hold;     // !release              **OFF
				int     holdChr;  // Hold CHR value        **20
				int     holdSpc;  // Hold spaced mode      **contiguous
			}

			ttBox_t     box;      // box status            **OFF
		};
		struct hw {  // Hardware state : ALL reset to OFF
			bool        show;     // !hide    [un-conceal]
			bool        scroll;   // !paged   [Mode-7 only]
			bool        subtit;   // subtitle [render only boxes]
			bool        mix;      // overlay  [background transparent]
			fastext_t   ft[4];    // Fastext buttons (if supported)
		};
		struct cs {  // Character set
			lang505x_t  m505x;       // -1 implies Mode-7
			glyph_t*    gfx_low;
			glyph_t*    gfx_high;
			glyph_t*    alpha_low;
			glyph_t*    alpha_med;
			glyph_t*    alpha_high;
		};
	}
teletext_t;

teletext_t  tt;

//+============================================================================
// Set Language
//
int  505x_setLang (lang505x_t lang)
{
	gfx_low  = @font@;
	gfx_high = @font@;
	switch ((tt.cs.m505x = lang)) {
		case LANG505X_UK:
			alpha_low  = @font@;
			alpha_med  = @font@;
			alpha_high = @font@;
			break;
		case LANG505X_DE:
			alpha_low  = @font@;
			alpha_med  = @font@;
			alpha_high = @font@;
			break;
		case LANG505X_SW:
			alpha_low  = @font@;
			alpha_med  = @font@;
			alpha_high = @font@;
			break;
		case LANG505X_IT:
			alpha_low  = @font@;
			alpha_med  = @font@;
			alpha_high = @font@;
			break;
		case LANG505X_BE:
			alpha_low  = @font@;
			alpha_med  = @font@;
			alpha_high = @font@;
			break;
		case LANG505X_US:
			alpha_low  = @font@;
			alpha_med  = @font@;
			alpha_high = @font@;
			break;
		case LANG505X_HE:
			alpha_low  = @font@;
			alpha_med  = @font@;
			alpha_high = @font@;
			break;
		case LANG505X_RU:
			alpha_low  = @font@;
			alpha_med  = @font@;
			alpha_high = @font@;
			break;
		case LANG505X_MODE7:  // As used by the Acorn BBC Micro
			gfx_low    = @font@;  // 127 Glyphs (0x7F is CC:DEL)
			gfx_high   = @font@;  // 128 Glyphs
			alpha_low  = @font@;  // 127 Glyphs (0x7F is CC:DEL)
			alpha_high = @font@;  // 128 Glyphs
			break;
		default:
			return ERR_BAD_LANG;
	}

	return ERR_OK_LANG;
}

//+============================================================================
// Reset for new character line
//
int  505x_lineRst (void)
{
/*
	int y         = tt.sm.y
	memset(&tt.sm, 0, sizeof(tt.sm));
	tt.sm.y       = y;
	tt.sm.holdChr = 0x20;

*/
	tt.sm.x       = 0;
	tt.sm.clrFg   = TTC_WHT;
	tt.sm.clrBg   = TTC_BLK;
	tt.sm.flash   = false;
	tt.sm.conceal = false;
	tt.sm.dblH    = false;
	tt.sm.gfx     = false;
	tt.sm.spaced  = false;
	tt.sm.hold    = false;
	tt.sm.holdChr = 0x20;
	tt.sm.holdSpc = false;
	tt.sm.box     = TTB_OFF;

	return ERR_OK_LINE;
}

//+============================================================================
// Reset Page
//
int  505x_pageRst (void)
{
	tt.sm.y = 0;
	(void)505x_lineRst();

	return ERR_OK_PAGE;
}

//+============================================================================
// Reset Hardware
//
int  505x_hwRst (void)
{
	memset(&tt.hw, 0, sizeof(tt.hw)):
	(void)pageRst();

	return ERR_OK_HW;
}

//+============================================================================
// Initialise Driver
//
int  505x_init (int w,  int h,  bool blkEn,  bool fastext,  lang505x_t lang)
{
	int  err = ERR_UNKNOWN;

	tt.feat.w       = w;        // VDU columns
	tt.feat.h       = h;        // VDU rows
	tt.feat.blkEn   = blkEn;    // Black Ink Available
	tt.feat.fastext = fastext;  // Fastext support

	(void)505x_hwRst();

	if ((err = 505x_setLang(lang)) != ERR_OK_LANG)  return err ;

	return ERR_OK_INIT;
}

//+============================================================================
// Show CHR in Mode-7 stylee
//
int  505x_showMode7 (uint8_t chr)
{
	return ERR_BAD_LANG;  //! not written yet - return a suitable error
}

//+============================================================================
// Handle Control Codes
//
// [qv. CONTROL CODE TABLES]
//
// ,---------------------------------------------------------------------.
// | 505x  | Function      | Reference (qv.)                  | Sequence |
// |       |               |                                  |          |
// |=======|===============|==================================|==========|
// |  00   | NUL           | Some chips map this to ALPHA_BLK | hg,CC,H- |
// |  01   | ALPHA_RED     | [GLYPH COLOUR SELECTION]         | hg,CC,H- |
// |  02   | ALPHA_GRN     | [GLYPH COLOUR SELECTION]         | hg,CC,H- |
// |  03   | ALPHA_YEL     | [GLYPH COLOUR SELECTION]         | hg,CC,H- |
// |  04   | ALPHA_BLU     | [GLYPH COLOUR SELECTION]         | hg,CC,H- |
// |  05   | ALPHA_MAG     | [GLYPH COLOUR SELECTION]         | hg,CC,H- |
// |  06   | ALPHA_CYN     | [GLYPH COLOUR SELECTION]         | hg,CC,H- |
// |  07   | ALPHA_WHT     | [GLYPH COLOUR SELECTION]         | hg,CC,H- |
// |-------|---------------|----------------------------------|----------|
// |  08   | ATTR_FLASH    | [FLASHING GLYPHS]                | hg,CC *1 |
// |  09   | ATTR_STEADY   | [FLASHING GLYPHS]                | CC,hg *1 |
// |  0A   | BOX_END       | [BOXES]                          | hg,CC    |
// |  0B   | BOX_START     | [BOXES]                          | hg,CC    |
// |  0C   | HEIGHT_NORMAL | [DOUBLE HEIGHT]                  | hg,CC *2 |
// |  0D   | HEIGHT_DOUBLE | [DOUBLE HEIGHT]                  | hg,CC *2 |
// |  0E   | S0            | -                                | -        |
// |  0F   | S1            | -                                | -        |
// |-------|---------------|----------------------------------|----------|
// |  10   | DLE           | Some chips map this to GRAPH_BLK | hg,CC    |
// |  11   | GRAPH_RED     | [GLYPH COLOUR SELECTION]         | hg,CC    |
// |  12   | GRAPH_GRN     | [GLYPH COLOUR SELECTION]         | hg,CC    |
// |  13   | GRAPH_YEL     | [GLYPH COLOUR SELECTION]         | hg,CC    |
// |  14   | GRAPH_BLU     | [GLYPH COLOUR SELECTION]         | hg,CC    |
// |  15   | GRAPH_MAG     | [GLYPH COLOUR SELECTION]         | hg,CC    |
// |  16   | GRAPH_CYN     | [GLYPH COLOUR SELECTION]         | hg,CC    |
// |  17   | GRAPH_WHT     | [GLYPH COLOUR SELECTION]         | hg,CC    |
// |-------|---------------|----------------------------------|----------|
// |  18   | DISP_CONCEAL  | [CONCEAL MODE]                   | hg,CC    |
// |  19   | GRAPH_CONTIG  | [GRAPHICS MODE]                  | CC,hg *3 |
// |  1A   | GRAPH_SPACED  | [GRAPHICS MODE]                  | CC,hg *3 |
// |  1B   | ESC           | -                                | -        |
// |  1C   | PAPER_BLACK   | [BACKGROUND COLOUR SELECTION]    | CC,hg    |
// |  1D   | PAPER_NEW     | [BACKGROUND COLOUR SELECTION]    | CC,hg    |
// |  1E   | GRAPH_HOLD    | [GRAPHICS MODE]                  | CC,hg    |
// |  1F   | GRAPH_RELEASE | [GRAPHICS MODE]                  | hg,CC    |
// `---------------------------------------------------------------------'
//
// The sequence has been inferred from (conflicting) online editors
// ...it may be wrong :(
//
int  505x_showCC (uint8_t chr)
{
	bool  last = true;

	if ((chr == TTCC_S0) || (chr == TTCC_S1) || (chr == TTCC_ESC))  return ERR_CC_BAD ;

	// Held Glyph first (not last)
	if (! ((chr == TTCC_STEADY) || (INRANGE(chr, TTCC_CONTIG, TTCC_GR_HOLD)) ) {
		505x_showHeld();
		last = false;
	}

	// Colour
	if (!(chr & TTCC_MASK_FN)) {
		uint8_t  clr = chr & TTCC_MASK_CLR;

		if ((clr == TTC_BLK) && !tt.feat.blkEn)  return ERR_CC_NOBLK ;
		tt.sm.clrFg = clr;

		if (chr & TTCC_MASK_GFX)   tt.sm.gfx = true ;
		else                       tt.sm.gfx = (tt.sm.hold = false) ;

	} else {
		switch (chr) {
			case TTCC_CONCEAL :  tt.sm.conceal = true;         break ;

			case TTCC_FLASH   :  tt.sm.flash   = true;         break ;
			case TTCC_STEADY  :  tt.sm.flash   = false;        break ;

			case TTCC_CONTIG  :  tt.sm.spaced  = false;        break ;
			case TTCC_SPACED  :  tt.sm.spaced  = true;         break ;

			case TTCC_BG_BLK  :  tt.sm.clrBg   = TTC_BLK;      break ;
			case TTCC_BG_NEW  :  tt.sm.clrBg   = tt.sm.clrFg;  break ;

			case TTCC_GR_HOLD :  tt.sm.hold    = true;         break ;
			case TTCC_GR_REL  :  tt.sm.hold    = false;        break ;

			case TTCC_HT_NRM  :
				if (tt.sm.dblH)   tt.sm.hold = false ;  // Change? Release Hold
				tt.sm.dblH = false;                     // Single
				break;
			case TTCC_HT_DBL  :
				if (!tt.sm.dblH)  tt.sm.hold = false ;  // Change? Release Hold
				tt.sm.dblH = true;                      // Double
				break;

			case TTCC_BOX_ST  :
				if ((tt.sm.box != TTB_ST1) && (tt.sm.box != TTB_ON))
					tt.sm.box = TTB_ST1;
				else
					tt.sm.box = TTB_ON;
				break;
			case TTCC_BOX_ND  :
				if ((tt.sm.box != TTB_ND1) && (tt.sm.box != TTB_OFF))
					tt.sm.box = TTB_ND1;
				else
					tt.sm.box = TTB_OFF;
				break;
		}
	}

	// Held Glyph last
	if (last)  505x_showHeld() ;
}

//+============================================================================
// Show CHR
//
int  505x_showChr (uint8_t chr)
{
	int       err = ERR_UNKNOWN;
	glyph_t*  gl  = NULL;

	// Mode-7 has a separate (8-bit) handler
	if (tt.cs.m505x == LANG505X_MODE7)  return 505x_showMode7() ;

	// 505x is a 7-bit Character Set
	if      (chr >  0x7F)  return ERR_BAD_GLYPH ;

	// {00..1F} are Control Codes
	if      (chr <= 0x1F)  err = 5050x_showCC(chr) ;
	// {20..7F} are Printable Glyphs
	else if (chr <= 0x3F)  gl = (tt.sm.gfx) ? tt.cs.gfx_low  : tt.cs.alpha_low ;
	else if (chr <= 0x5F)  gl =                                tt.cs.alpha_med ;
	else                   gl = (tt.sm.gfx) ? tt.cs.gfx_high : tt.cs.alpha_high ;
	if ((err = 505x_render(gl, (chr & 0x1F))) != ERR_OK

	if (++tt.sm.x >= tt.feat.w) {
		if (++tt.sm.y >= tt.feat.h)  return 505x_pageRst() ;
		else                         return 505x_lineRst() ;
	}

	return ERR_OK_CHR;
}

																	  fedcba9876543210
    ..###.    ....######..    ....'##'##'##'..    ....'##=##=##'..    ....'########'..
    .#...#    ....######..    ....'##'##'##'..    ..../##=##=##\..    ....##########..
    .....#    ..##......##    ..##'..'..'..'##    ..##/..'..'..\##    ..###..'..'..###
    ...##.    ..##......##    ..##'..'..'..'##    ..##'..'..'..'##    ..##'..'..'..'##
    ..#...    ..........##    ....'..'..'..'##    ....'..'..'..'##    ....'..'..'..'##
    .#....    ..........##    ....'..'..'..'##    ....'..'..'../##    ....'..'..'..###
    .#####    ......####..    ....'..'##'##'..    ....'..'##=##/..    ....'..'######..
    ......    ......####..    ....'..'##'##'..    ....'../##=##'..    ....'..######'..
    ......    ....##......    ....'##'..'..'..    ....'##/..'..'..    ....'###..'..'..
    ......    ....##......    ....'##'..'..'..    ..../##'..'..'..    ....###'..'..'..
              ..##........    ..##'..'..'..'..    ..##/..'..'..'..    ..###..'..'..'..
              ..##........    ..##'..'..'..'..    ..##'..'..'..'..    ..##'..'..'..'..
              ..##########    ..##'##'##'##'##    ..##=##=##=##=##    ..##############
              ..##########    ..##'##'##'##'##    ..##=##=##=##=##    ..##############
              ............    ....'..'..'..'..    ....'..'..'..'..    ....'..'..'..'..
              ............    ....'..'..'..'..    ....'..'..'..'..    ....'..'..'..'..
              ............    ....'..'..'..'..    ....'..'..'..'..    ....'..'..'..'..
              ............    ....'..'..'..'..    ....'..'..'..'..    ....'..'..'..'..
              ............    ....'..'..'..'..    ....'..'..'..'..    ....'..'..'..'..
              ............    ....'..'..'..'..    ....'..'..'..'..    ....'..'..'..'..
              ............    ....'..'..'..'..    ....'..'..'..'..    ....'..'..'..'..
              ............    ....'..'..'..'..    ....'..'..'..'..    ....'..'..'..'..

    ###...    ######......    ####'##'..'..'..    ####=##=..'..'..
    ###...    ######......    ####'##'..'..'..    ####=##=..'..'..
    ###...    ######......    ####'##'..'..'..    ####=##=..'..'..
    ...###    ######......    ####'##'..'..'..    ####=##=..'..'..
    ...###    ######......    ####'##'..'..'..    ####=##=..'..'..
    ...###    ######......    ####'##'..'..'..    ####=##=..'..'..
    ...###    ......######    ....'..'##'##'##    ....'..'##=##=##
    ######    ......######    ....'..'##'##'##    ....'..'##=##=##
    ######    ......######    ....'..'##'##'##    ....'..'##=##=##
    ######    ......######    ....'..'##'##'##    ....'..'##=##=##
              ......######    ....'..'##'##'##    ....'..'##=##=##
              ......######    ....'..'##'##'##    ....'..'##=##=##
              ......######    ....'..'##'##'##    ....'..'##=##=##
              ......######    ....'..'##'##'##    ....'..'##=##=##
              ############    ####'##'##'##'##    ####=##=##=##=##
              ############    ####'##'##'##'##    ####=##=##=##=##
              ############    ####'##'##'##'##    ####=##=##=##=##
              ############    ####'##'##'##'##    ####=##=##=##=##
              ############    ####'##'##'##'##    ####=##=##=##=##
              ############    ####'##'##'##'##    ####=##=##=##=##

                                                      <  <  >  >

    .##...    ..####......    ..##'##'..'..'..    ..##=##=..'..'..
    .##...    ..####......    ..##'##'..'..'..    ..##=##=..'..'..
    ......    ..####......    ..##'##'..'..'..    ..##=##=..'..'..
    ....##    ..####......    ..##'##'..'..'..    ..##=##=..'..'..
    ....##    ............    ....'..'..'..'..    ....'..'..'..'..
    ....##    ............    ....'..'..'..'..    ....'..'..'..'..
    ......    ........####    ....'..'..'##'##    ....'..'..=##=##
    .##.##    ........####    ....'..'..'##'##    ....'..'..=##=##
    .##.##    ........####    ....'..'..'##'##    ....'..'..=##=##
    ......    ........####    ....'..'..'##'##    ....'..'..=##=##
              ........####    ....'..'..'##'##    ....'..'..=##=##
              ........####    ....'..'..'##'##    ....'..'..=##=##
              ............    ....'..'..'..'..    ....'..'..'..'..
              ............    ....'..'..'..'..    ....'..'..'..'..
              ..####..####    ..##'##'..'##'##    ..##=##=..=##=##
              ..####..####    ..##'##'..'##'##    ..##=##=..=##=##
              ..####..####    ..##'##'..'##'##    ..##=##=..=##=##
              ..####..####    ..##'##'..'##'##    ..##=##=..=##=##
              ............    ....'..'..'..'..    ....'..'..'..'..
              ............    ....'..'..'..'..    ....'..'..'..'..

int  scale (uint8_t* gIn, uint16_t** gOut,  uint16_t bg,  uint16_t fg)
{
	//uint8_t    gIn [  10];           //  1 bpp
	//uint16_t   gOut[2*10][(2*6)+4];  // 16 bpp
	//uint16_t   fg;                   // foreground colour
	//uint16_t   bg;                   // background colour

	//uint8_t    mask;
	uint16_t   clr;


	for (int rIn = 0;  rIn < 10;  rIn++) {
		uint16_t*  out1 = gOut[ rIn<<1   ];
		uint16_t*  out2 = gOut[(rIn<<1)|1];

		for (uint8_t mask = 0x20;  mask;  mask >>= 1) {
			uint8_t    pad;
			uint8_t    mpad = mask <<1;
			// alpha smoothing
			if (mask < 0x10) {
				if (! (pad =             (!!(gIn[rIn  ] & mpad)) *3) ) {    // 3: left
					pad  = (rIn != 0) ? ((!!(gIn[rIn-1] & mpad))   ) : 0 ;  // 1: up
					pad |= (rIn != 9) ? ((!!(gIn[rIn+1] & mpad)) *2) : 0 ;  // 2: down
				}
				*out1++ = (pad & 1) ? fg : bg ;
				*out2++ = (pad & 2) ? fg : bg ;
			}
			// plot
			clr = (gIn[rIn] & mask) ? fc : bg ;
			*out1++ = clr;
			*out2++ = clr;
			*out1++ = clr;
			*out2++ = clr;
		}
	}
}

void  test (uint8_t** set,  int cnt)
{
	uint16_t   gOut[2*10][(2*6)+4];  // 16 bpp
	uint16_t   fg = 0xFFFF;          // foreground colour
	uint16_t   bg = 0x0000;          // background colour

	for (int n = 0;  n < cnt;  n++) {
		(void)scale(gl[n], gOut, fg, bg);
		for (int r = 0;  r < 20;  r++) {
			for (int c = 15;  c >= 0;  c--)
				printf("%c", (gOut[r][c] == fg) ? '#' : '.');
			printf("\n\n");
		}
	}
}

int  main (void)
{
	test(5050_Alpha_UK_Mid, 32);
	return 1;
}
