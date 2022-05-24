#!/bin/bash

##+============================================================================
doit () {
	local file hdr 
	local tag mode cnt chr0 last 
	local idx n l gly chr chrx val bit row asc
	local bits0 bits1 bits2 bits3 bits4 bits5 bits6 bits7 bits8 bits9

	file=$1
	hdr=$2

	## Grab the "XML Tags"
	tag="`grep "^<glyphMap id=$hdr " $file`"
	mode=`echo "$tag" | sed 's/.* mode=\([^ ]*\)[ \>].*/\1/'`
	cnt=`echo "$tag" | sed 's/.* cnt=\([^ ]*\)[ \>].*/\1/'`
	chr0=`echo "$tag" | sed 's/.* chr0=\([^ ]*\)[ \>].*/\1/'`

	## We need to know this so we don't put a comma at the end of the array
	((last = cnt -1))

	## Start the array for this Glyph Set
#	echo -e "#ifndef ${hdr^^}_H"
#	echo -e "#define ${hdr^^}_H\n"

	echo -e "// Teletext Glyph Map: $hdr"
	printf -v chrx "%02X" $chr0
	echo -e "// Mode: $mode,  Base offset: $chr0 (0x$chrx)\n"
#	echo -e "#include <stdint.h>\n"
	echo -e "#include \"ttxFonts.h\"\n"
#	echo "const uint8_t  ttxf_$hdr[$cnt][10] = {"
	echo "const glyph_t  ttxf_$hdr[$cnt] = {"

	## Parse the glyphs
	idx=0                                                  ## Array index
	n=0                                                    ## Rows counter

	while read -r l ; do                                   ## Read a line
		[[ -z $l ]] && continue                            ##   Ignore empty lines

		eval "bits${n}=(\$l)"                              ##   Get a full line of 16 rows - to an array
		((++n < 10)) && continue                           ##   ...until we have 10 lines

		for ((gly = 0;  gly < 16;  gly++)) ; do            ##   for 16 glyphs per line

			printf -v chrx "%02X" $((chr = idx + chr0))    ##     Find chr$() values
			eval "asc=\x$chrx"                             ##     Find ASCII character for value

			## Start array for this Glyph
			echo -en "\t{ // [$idx] CHR\$($chr) '\\\\x$chrx'"
			if ((chr >= 32 && chr < 127)) ; then
				echo -en " '\\$asc' ----------------------------------------\n\t"
			else
				echo -en " --------------------------------------------\n\t"
			fi

			## Generate the Glyph array element data
			for ((row = 0;  row < 10;  row++)) ; do        ##     for 10 rows
				eval "x=\${bits$row[$gly]}"                ##       Get a single row of bits

				val=0                                      ##       Calculate value
				for ((bit = 0;  bit < 6;  bit++)); do      ##       6 bits per row
					((val <<= 1))                          ##         Make way for new bit
					[[ ${x:bit:1} != . ]] && ((val |= 1))  ##         Add bit in (if present)
				done                                       ##       .
				printf -v valx "0x%02X" $val               ##       Convert to hex

				if ((row == 10-1)); then                   ##       Last row of glyph?
					echo -en "  $valx  /* $x */\n\t}"      ##         No comma after value; close array
					if ((idx != $last)); then              ##         NOT the last glyph?
						echo -e ","                        ##           Append a comma
					else                                   ##         LAST glyph
						gly=16                             ##           Terminate glyph loop
					fi                                     ##       .
				else                                       ##       Glyph row 0..8
					echo -en "  $valx, /* $x */\n\t"       ##         Comma after value; leave array open
				fi                                         ##       .
			done                                           ##     /next row

			((idx++))                                      ##     Next glyph index
		done                                               ##   /next gly

		n=0
	done < <(sed -n "/^<glyphMap id=$hdr /,/^<\/glyphMap>/p" $file | sed '1d;$d')

	echo -e "\n};"
#	echo -e "\n#endif // ${hdr^^}_H"
}

##+============================================================================
## ENTRY POINT
##

src=../505xMaps.txt
dir=ttxFonts

rm -rf $dir
mkdir -p $dir

##-----------------------------------------------------------------------------

## Parse chosen maps
# doit $src 5054_Alpha_BE_Med
# doit $src 5054_Alpha_BE_High

## Parse all maps
list=`grep "^<glyphMap " $src | sed 's/.* id=\([^ ]*\)[ \>].*/\1/'`

for g in $list ; do
	echo "# $g"
	doit $src $g > $dir/$g.c
done

##-----------------------------------------------------------------------------
## .h
h=ttxFonts.h
H=${h^^}

echo "# $h"
cat <<EOF >$dir/$h
#ifndef ${H//./_}
#define ${H//./_}

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

EOF

for g in $list ; do
	echo "extern  const glyph_t  ttxf_$g[];" >>$dir/$h
done

cat <<EOF >>$dir/$h

#endif // ${H//./_}
EOF

##---------------------------------------------------------
## .c

c=${h//.h/.c}

echo "# $c"
cat <<EOF >$dir/$c
#include <stddef.h>

#include "$h"

const gset_t  gset[] = {
EOF

n=0
for g in $list ; do
	## get tag and extact fields
	tag="`grep "^<glyphMap id=$g " $src`"
	mode=`echo "$tag" | sed 's/.* mode=\([^ ]*\)[ \>].*/\1/'`
	cnt=`echo "$tag" | sed 's/.* cnt=\([^ ]*\)[ \>].*/\1/'`
	chr0=`echo "$tag" | sed 's/.* chr0=\([^ ]*\)[ \>].*/\1/'`

	## find graphics mode
	case "$mode" in
		gfx)   gfx=true  ;;
		alpha) gfx=false ;;
		*)     gfx=ERROR ;;
	esac

	## create array entry
	echo -e "\t{\"$g\", $gfx, $cnt, $chr0, ttxf_$g}," >>$dir/$c
	((n++))
done

## array footer
cat <<EOF >>$dir/$c
	{NULL, false, 0, 0, NULL}  // NULL terminated table
};

const int  gsetCnt = $n;  // EXcluding NULL terminator
EOF

exit 0
