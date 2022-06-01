#include <stddef.h>

#include "ttxFonts.h"

const gset_t  gset[] = {
	{"m5050_Alpha_UK_Low", false, 32, 32, ttxf_m5050_Alpha_UK_Low},
	{"m5050_Alpha_UK_Med", false, 32, 64, ttxf_m5050_Alpha_UK_Med},
	{"m5050_Alpha_UK_High", false, 32, 96, ttxf_m5050_Alpha_UK_High},
	{"m5051_Alpha_DE_Low", false, 32, 32, ttxf_m5051_Alpha_DE_Low},
	{"m5051_Alpha_DE_Med", false, 32, 64, ttxf_m5051_Alpha_DE_Med},
	{"m5051_Alpha_DE_High", false, 32, 96, ttxf_m5051_Alpha_DE_High},
	{"m5052_Alpha_SW_Low", false, 32, 32, ttxf_m5052_Alpha_SW_Low},
	{"m5052_Alpha_SW_Med", false, 32, 64, ttxf_m5052_Alpha_SW_Med},
	{"m5052_Alpha_SW_High", false, 32, 96, ttxf_m5052_Alpha_SW_High},
	{"m5053_Alpha_IT_Low", false, 32, 32, ttxf_m5053_Alpha_IT_Low},
	{"m5053_Alpha_IT_Med", false, 32, 64, ttxf_m5053_Alpha_IT_Med},
	{"m5053_Alpha_IT_High", false, 32, 96, ttxf_m5053_Alpha_IT_High},
	{"m5054_Alpha_BE_Low", false, 32, 32, ttxf_m5054_Alpha_BE_Low},
	{"m5054_Alpha_BE_Med", false, 32, 64, ttxf_m5054_Alpha_BE_Med},
	{"m5054_Alpha_BE_High", false, 32, 96, ttxf_m5054_Alpha_BE_High},
	{"m5055_Alpha_US_Low", false, 32, 32, ttxf_m5055_Alpha_US_Low},
	{"m5055_Alpha_US_Med", false, 32, 64, ttxf_m5055_Alpha_US_Med},
	{"m5055_Alpha_US_High", false, 32, 96, ttxf_m5055_Alpha_US_High},
	{"m5056_Alpha_HE_Low", false, 32, 32, ttxf_m5056_Alpha_HE_Low},
	{"m5056_Alpha_HE_Med", false, 32, 64, ttxf_m5056_Alpha_HE_Med},
	{"m5056_Alpha_HE_High", false, 32, 96, ttxf_m5056_Alpha_HE_High},
	{"m5057_Alpha_RU_Low", false, 32, 32, ttxf_m5057_Alpha_RU_Low},
	{"m5057_Alpha_RU_Med", false, 32, 64, ttxf_m5057_Alpha_RU_Med},
	{"m5057_Alpha_RU_High", false, 32, 96, ttxf_m5057_Alpha_RU_High},
	{"m505x_Gfx_Ctg_Low", true, 32, 32, ttxf_m505x_Gfx_Ctg_Low},
	{"m505x_Gfx_Ctg_High", true, 32, 96, ttxf_m505x_Gfx_Ctg_High},
	{"m505x_Gfx_Sep_Low", true, 32, 32, ttxf_m505x_Gfx_Sep_Low},
	{"m505x_Gfx_Sep_High", true, 32, 96, ttxf_m505x_Gfx_Sep_High},
	{"m5050_Mode7_Alpha_Low", false, 95, 32, ttxf_m5050_Mode7_Alpha_Low},
	{"m5050_Mode7_Alpha_High", false, 96, 160, ttxf_m5050_Mode7_Alpha_High},
	{"m5050_Mode7_Gfx_Low", true, 95, 32, ttxf_m5050_Mode7_Gfx_Low},
	{"m5050_Mode7_Gfx_High", true, 96, 160, ttxf_m5050_Mode7_Gfx_High},
	{NULL, false, 0, 0, NULL}  // NULL terminated table
};

const int  gsetCnt = 32;  // EXcluding NULL terminator
