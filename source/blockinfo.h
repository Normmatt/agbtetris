#ifndef BLOCK_HEADER
#define BLOCK_HEADER

#include "block_data.h"

typedef struct {   
    const sTileInfo *tilemap;
    u16 flags; //oam flags?	  
} sBlockInfo;

const sBlockInfo off_2C68 = { .tilemap = &L_Block_Rotated_0, .flags = 0xF0EF };
const sBlockInfo off_2C6C = { .tilemap = &L_Block_Rotated_90, .flags = 0xF0EF };
const sBlockInfo off_2C70 = { .tilemap = &L_Block_Rotated_180, .flags = 0xF0EF };
const sBlockInfo off_2C74 = { .tilemap = &L_Block_Rotated_270, .flags = 0xF0EF };
const sBlockInfo off_2C78 = { .tilemap = &J_Block_Rotated_0, .flags = 0xF0EF };
const sBlockInfo off_2C7C = { .tilemap = &J_Block_Rotated_90, .flags = 0xF0EF };
const sBlockInfo off_2C80 = { .tilemap = &J_Block_Rotated_180, .flags = 0xF0EF };
const sBlockInfo off_2C84 = { .tilemap = &J_Block_Rotated_270, .flags = 0xF0EF };
const sBlockInfo off_2C88 = { .tilemap = &I_Block_Rotated_0, .flags = 0xF0EF };
const sBlockInfo off_2C8C = { .tilemap = &I_Block_Rotated_90, .flags = 0xF0EF };
const sBlockInfo off_2C90 = { .tilemap = &I_Block_Rotated_180, .flags = 0xF0EF };
const sBlockInfo off_2C94 = { .tilemap = &I_Block_Rotated_270, .flags = 0xF0EF };
const sBlockInfo off_2C98 = { .tilemap = &O_Block_Rotated_0, .flags = 0xF0EF };
const sBlockInfo off_2C9C = { .tilemap = &O_Block_Rotated_90, .flags = 0xF0EF };
const sBlockInfo off_2CA0 = { .tilemap = &O_Block_Rotated_180, .flags = 0xF0EF };
const sBlockInfo off_2CA4 = { .tilemap = &O_Block_Rotated_270, .flags = 0xF0EF };
const sBlockInfo off_2CA8 = { .tilemap = &Z_Block_Rotated_0, .flags = 0xF0EF };
const sBlockInfo off_2CAC = { .tilemap = &Z_Block_Rotated_90, .flags = 0xF0EF };
const sBlockInfo off_2CB0 = { .tilemap = &Z_Block_Rotated_180, .flags = 0xF0EF };
const sBlockInfo off_2CB4 = { .tilemap = &Z_Block_Rotated_270, .flags = 0xF0EF };
const sBlockInfo off_2CB8 = { .tilemap = &S_Block_Rotated_0, .flags = 0xF0EF };
const sBlockInfo off_2CBC = { .tilemap = &S_Block_Rotated_90, .flags = 0xF0EF };
const sBlockInfo off_2CC0 = { .tilemap = &S_Block_Rotated_180, .flags = 0xF0EF };
const sBlockInfo off_2CC4 = { .tilemap = &S_Block_Rotated_270, .flags = 0xF0EF };
const sBlockInfo off_2CC8 = { .tilemap = &T_Block_Rotated_0, .flags = 0xF0EF };
const sBlockInfo off_2CCC = { .tilemap = &T_Block_Rotated_90, .flags = 0xF0EF };
const sBlockInfo off_2CD0 = { .tilemap = &T_Block_Rotated_180, .flags = 0xF0EF };
const sBlockInfo off_2CD4 = { .tilemap = &T_Block_Rotated_270, .flags = 0xF0EF };
const sBlockInfo off_2CD8 = { .tilemap = &off_2F75, .flags = 0xE800 };
const sBlockInfo off_2CDC = { .tilemap = &off_2F7E, .flags = 0xE800 };
const sBlockInfo off_2CE0 = { .tilemap = &off_2F87, .flags = 0xE800 };
const sBlockInfo off_2CE4 = { .tilemap = &off_2F90, .flags = 0xE800 };
const sBlockInfo off_2CE8 = { .tilemap = &Number0Block, .flags = 0x0000 };
const sBlockInfo off_2CEC = { .tilemap = &Number1Block, .flags = 0x0000 };
const sBlockInfo off_2CF0 = { .tilemap = &Number2Block, .flags = 0x0000 };
const sBlockInfo off_2CF4 = { .tilemap = &Number3Block, .flags = 0x0000 };
const sBlockInfo off_2CF8 = { .tilemap = &Number4Block, .flags = 0x0000 };
const sBlockInfo off_2CFC = { .tilemap = &Number5Block, .flags = 0x0000 };
const sBlockInfo off_2D00 = { .tilemap = &Number6Block, .flags = 0x0000 };
const sBlockInfo off_2D04 = { .tilemap = &Number7Block, .flags = 0x0000 };
const sBlockInfo off_2D08 = { .tilemap = &Number8Block, .flags = 0x0000 };
const sBlockInfo off_2D0C = { .tilemap = &Number9Block, .flags = 0x0000 };
const sBlockInfo off_2D10 = { .tilemap = &off_2FC1, .flags = 0xF8F0 };
const sBlockInfo off_2D14 = { .tilemap = &off_2FCC, .flags = 0xF8F0 };
const sBlockInfo off_2D18 = { .tilemap = &off_2FD7, .flags = 0xF0F0 };
const sBlockInfo off_2D1C = { .tilemap = &off_2FEB, .flags = 0xF0F0 };
const sBlockInfo off_2D20 = { .tilemap = &off_3000, .flags = 0xF8F8 };
const sBlockInfo off_2D24 = { .tilemap = &off_3009, .flags = 0xF8F8 };
const sBlockInfo off_2D28 = { .tilemap = &off_3012, .flags = 0xF8F8 };
const sBlockInfo off_2D2C = { .tilemap = &off_3019, .flags = 0xF8F8 };
const sBlockInfo off_2D30 = { .tilemap = &off_3020, .flags = 0xF8F0 };
const sBlockInfo off_2D34 = { .tilemap = &off_302B, .flags = 0xF8F0 };
const sBlockInfo off_2D38 = { .tilemap = &off_3036, .flags = 0xF0F0 };
const sBlockInfo off_2D3C = { .tilemap = &off_304B, .flags = 0xF0F0 };
const sBlockInfo off_2D40 = { .tilemap = &off_3061, .flags = 0xF8F8 };
const sBlockInfo off_2D44 = { .tilemap = &off_306A, .flags = 0xF8F8 };
const sBlockInfo off_2D48 = { .tilemap = &off_3073, .flags = 0xF8F8 };
const sBlockInfo off_2D4C = { .tilemap = &off_307A, .flags = 0xF8F8 };
const sBlockInfo off_2D50 = { .tilemap = &off_3081, .flags = 0xF8F8 };
const sBlockInfo off_2D54 = { .tilemap = &off_3088, .flags = 0xF8F8 };
const sBlockInfo off_2D58 = { .tilemap = &off_308F, .flags = 0xF8F8 };
const sBlockInfo off_2D5C = { .tilemap = &off_3096, .flags = 0xF8F8 };
const sBlockInfo off_2D60 = { .tilemap = &off_309D, .flags = 0xF8F8 };
const sBlockInfo off_2D64 = { .tilemap = &off_30A4, .flags = 0xF8F8 };
const sBlockInfo off_2D68 = { .tilemap = &off_30AF, .flags = 0xF8F8 };
const sBlockInfo off_2D6C = { .tilemap = &off_30B6, .flags = 0xF8F8 };
const sBlockInfo off_2D70 = { .tilemap = &off_30BD, .flags = 0xF8F8 };
const sBlockInfo off_2D74 = { .tilemap = &off_30C4, .flags = 0xF8F8 };
const sBlockInfo off_2D78 = { .tilemap = &off_30CB, .flags = 0xF8F8 };
const sBlockInfo off_2D7C = { .tilemap = &off_30D4, .flags = 0xF8F8 };
const sBlockInfo off_2D80 = { .tilemap = &off_30DD, .flags = 0xF8F8 };
const sBlockInfo off_2D84 = { .tilemap = &off_30E6, .flags = 0xF8F8 };
const sBlockInfo off_2D88 = { .tilemap = &off_30EF, .flags = 0xF8F8 };
const sBlockInfo off_2D8C = { .tilemap = &off_30F8, .flags = 0xF8F8 };
const sBlockInfo off_2D90 = { .tilemap = &off_3101, .flags = 0xF8F8 };
const sBlockInfo off_2D94 = { .tilemap = &off_3108, .flags = 0xF8F8 };
const sBlockInfo off_2D98 = { .tilemap = &off_318E, .flags = 0xF0F0 };
const sBlockInfo off_2D9C = { .tilemap = &off_31A5, .flags = 0xF8F8 };

const sBlockInfo off_310F = { .tilemap = &off_3113, .flags = 0xF0E0 };

const sBlockInfo off_3132 = { .tilemap = &off_315E, .flags = 0xE8F8 };
const sBlockInfo off_3136 = { .tilemap = &off_3164, .flags = 0xE8F0 };
const sBlockInfo off_313A = { .tilemap = &off_316D, .flags = 0x0000 };
const sBlockInfo off_313E = { .tilemap = &off_3173, .flags = 0x0000 };
const sBlockInfo off_3142 = { .tilemap = &off_3179, .flags = 0x0000 };
const sBlockInfo off_3146 = { .tilemap = &off_3182, .flags = 0x0000 };
const sBlockInfo off_314A = { .tilemap = &off_31E5, .flags = 0x0000 };
const sBlockInfo off_314E = { .tilemap = &off_31EB, .flags = 0x0000 };
const sBlockInfo off_3152 = { .tilemap = &off_31AC, .flags = 0xF8D8 };
const sBlockInfo off_3156 = { .tilemap = &off_31C4, .flags = 0xF8E8 };
const sBlockInfo off_315A = { .tilemap = &off_31D6, .flags = 0xF8F0 };

const sBlockInfo *BlockInfoList[] = {
    &off_2C68,
    &off_2C6C,
    &off_2C70,
    &off_2C74,
    &off_2C78,
    &off_2C7C,
    &off_2C80,
    &off_2C84,
    &off_2C88,
    &off_2C8C,
    &off_2C90,
    &off_2C94,
    &off_2C98,
    &off_2C9C,
    &off_2CA0,
    &off_2CA4,
    &off_2CA8,
    &off_2CAC,
    &off_2CB0,
    &off_2CB4,
    &off_2CB8,
    &off_2CBC,
    &off_2CC0,
    &off_2CC4,
    &off_2CC8,
    &off_2CCC,
    &off_2CD0,
    &off_2CD4,
    &off_2CD8,
    &off_2CDC,
    &off_2CE0,
    &off_2CE4,
    &off_2CE8,
    &off_2CEC,
    &off_2CF0,
    &off_2CF4,
    &off_2CF8,
    &off_2CFC,
    &off_2D00,
    &off_2D04,
    &off_2D08,
    &off_2D0C,
    &off_2D10,
    &off_2D14,
    &off_310F,
    &off_2D14,
    &off_2D18,
    &off_2D1C,
    &off_2D20,
    &off_2D24,
    &off_2D28,
    &off_2D2C,
    &off_3132,
    &off_3136,
    &off_2D30,
    &off_2D34,
    &off_313A,
    &off_313E,
    &off_2D38,
    &off_2D3C,
    &off_2D40,
    &off_2D44,
    &off_2D48,
    &off_2D4C,
    &off_3142,
    &off_3146,
    &off_2D4C,
    &off_2D50,
    &off_2D50,
    &off_2D54,
    &off_2D58,
    &off_2D5C,
    &off_2D60,
    &off_2D64,
    &off_2D68,
    &off_2D6C,
    &off_2D70,
    &off_2D74,
    &off_2D78,
    &off_2D7C,
    &off_2D80,
    &off_2D84,
    &off_2D88,
    &off_2D8C,
    &off_2D90,
    &off_2D94,
    &off_2D98,
    &off_2D9C,
    &off_3152,
    &off_3156,
    &off_315A,
    &off_315A,
    &off_314A,
    &off_314E,
};

#endif