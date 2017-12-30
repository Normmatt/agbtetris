#ifndef BLOCK_DATA
#define BLOCK_DATA

typedef struct {   
    const u8 *rotation_info;
    const u8 data[64]; //have to have a fixed size here :(  
} sTileInfo;

const u8 byte_31F1[] = 
{
  0x00, 0x00, 0x00, 0x08, 
  0x00, 0x10, 0x00, 0x18, 
  0x08, 0x00, 0x08, 0x08, 
  0x08, 0x10, 0x08, 0x18, 
  0x10, 0x00, 0x10, 0x08, 
  0x10, 0x10, 0x10, 0x18, 
  0x18, 0x00, 0x18, 0x08, 
  0x18, 0x10, 0x18, 0x18
};

const u8 byte_3211[] = 
{
  0x00, 0x00, 0x00, 0x08, 
  0x00, 0x10, 0x00, 0x18, 
  0x00, 0x20, 0x00, 0x28, 
  0x00, 0x30, 0x00, 0x38
};

const u8 byte_3221[] = 
{
  0x00, 0x00, 0x00, 0x08, 
  0x08, 0x00, 0x08, 0x08, 
  0x10, 0x00, 0x10, 0x08, 
  0x18, 0x00, 0x18, 0x08, 
  0x20, 0x00, 0x20, 0x08, 
  0x28, 0x00, 0x28, 0x08, 
  0x30, 0x00, 0x30, 0x08
};

const u8 byte_323D[] = 
{
  0x00, 0x08, 0x00, 0x10, 
  0x08, 0x08, 0x08, 0x10, 
  0x10, 0x00, 0x10, 0x08, 
  0x10, 0x10, 0x10, 0x18, 
  0x18, 0x00, 0x18, 0x08, 
  0x18, 0x10, 0x18, 0x18, 
  0x20, 0x00, 0x20, 0x08, 
  0x20, 0x10, 0x20, 0x18, 
  0x28, 0x00, 0x28, 0x08, 
  0x28, 0x10, 0x28, 0x18, 
  0x30, 0x00, 0x30, 0x08, 
  0x30, 0x10, 0x30, 0x18, 
  0x38, 0x00, 0x38, 0x08, 
  0x38, 0x10, 0x38, 0x18
};

const u8 byte_3275[] = 
{
  0x00, 0x00, 0x00, 0x08, 
  0x00, 0x10, 0x08, 0x00, 
  0x08, 0x08, 0x08, 0x10, 
  0x10, 0x00, 0x10, 0x08, 
  0x10, 0x10
};

const sTileInfo L_Block_Rotated_0 =
{
  .rotation_info = byte_31F1,
  .data = {
    0xFE, 0xFE, 0xFE, 0xFE, 
    0xFE, 0xFE, 0xFE, 0xFE, 
    0x84, 0x84, 0x84, 0xFE, 
    0x84, 0xFF
  }
};

const sTileInfo L_Block_Rotated_90 =
{
  .rotation_info = byte_31F1,
  .data = {
    0xFE, 0xFE, 0xFE, 0xFE, 
    0xFE, 0x84, 0xFE, 0xFE, 
    0xFE, 0x84, 0xFE, 0xFE, 
    0xFE, 0x84, 0x84, 0xFF
  }
};

const sTileInfo L_Block_Rotated_180 =
{
  .rotation_info = byte_31F1,
  .data = {
    0xFE, 0xFE, 0xFE, 0xFE, 
    0xFE, 0xFE, 0x84, 0xFE, 
    0x84, 0x84, 0x84, 0xFE, 
    0xFF
  }
};

const sTileInfo L_Block_Rotated_270 =
{
  .rotation_info = byte_31F1,
  .data = {
    0xFE, 0xFE, 0xFE, 0xFE, 
    0x84, 0x84, 0xFE, 0xFE, 
    0xFE, 0x84, 0xFE, 0xFE, 
    0xFE, 0x84, 0xFF
  }
};

const sTileInfo J_Block_Rotated_0 =
{
  .rotation_info = byte_31F1,
  .data = {
    0xFE, 0xFE, 0xFE, 0xFE, 
    0xFE, 0xFE, 0xFE, 0xFE, 
    0x81, 0x81, 0x81, 0xFE, 
    0xFE, 0xFE, 0x81, 0xFF
  }
};

const sTileInfo J_Block_Rotated_90 =
{
  .rotation_info = byte_31F1,
  .data = {
    0xFE, 0xFE, 0xFE, 0xFE, 
    0xFE, 0x81, 0x81, 0xFE, 
    0xFE, 0x81, 0xFE, 0xFE, 
    0xFE, 0x81, 0xFF
  }
};

const sTileInfo J_Block_Rotated_180 =
{
  .rotation_info = byte_31F1,
  .data = {
    0xFE, 0xFE, 0xFE, 0xFE, 
    0x81, 0xFE, 0xFE, 0xFE, 
    0x81, 0x81, 0x81, 0xFF
  }
};

const sTileInfo J_Block_Rotated_270 =
{
  .rotation_info = byte_31F1,
  .data = {
    0xFE, 0xFE, 0xFE, 0xFE, 
    0xFE, 0x81, 0xFE, 0xFE, 
    0xFE, 0x81, 0xFE, 0xFE, 
    0x81, 0x81, 0xFF
  }
};

const sTileInfo I_Block_Rotated_0 =
{
  .rotation_info = byte_31F1,
  .data = {
    0xFE, 0xFE, 0xFE, 0xFE, 
    0xFE, 0xFE, 0xFE, 0xFE, 
    0x8A, 0x8B, 0x8B, 0x8F, 
    0xFF
  }
};

const sTileInfo I_Block_Rotated_90 =
{
  .rotation_info = byte_31F1,
  .data = {
    0xFE, 0x80, 0xFE, 0xFE, 
    0xFE, 0x88, 0xFE, 0xFE, 
    0xFE, 0x88, 0xFE, 0xFE, 
    0xFE, 0x89, 0xFF
  }
};

const sTileInfo I_Block_Rotated_180 =
{
  .rotation_info = byte_31F1,
  .data = {
    0xFE, 0xFE, 0xFE, 0xFE, 
    0xFE, 0xFE, 0xFE, 0xFE, 
    0x8A, 0x8B, 0x8B, 0x8F, 
    0xFF
  }
};

const sTileInfo I_Block_Rotated_270 =
{
  .rotation_info = byte_31F1,
  .data = {
    0xFE, 0x80, 0xFE, 0xFE, 
    0xFE, 0x88, 0xFE, 0xFE, 
    0xFE, 0x88, 0xFE, 0xFE, 
    0xFE, 0x89, 0xFF
  }
};

const sTileInfo O_Block_Rotated_0 =
{
  .rotation_info = byte_31F1,
  .data = {
    0xFE, 0xFE, 0xFE, 0xFE, 
    0xFE, 0xFE, 0xFE, 0xFE, 
    0xFE, 0x83, 0x83, 0xFE, 
    0xFE, 0x83, 0x83, 0xFF
  }
};

const sTileInfo O_Block_Rotated_90 =
{
  .rotation_info = byte_31F1,
  .data = {
    0xFE, 0xFE, 0xFE, 0xFE, 
    0xFE, 0xFE, 0xFE, 0xFE, 
    0xFE, 0x83, 0x83, 0xFE, 
    0xFE, 0x83, 0x83, 0xFF
  }
};

const sTileInfo O_Block_Rotated_180 =
{
  .rotation_info = byte_31F1,
  .data = {
    0xFE, 0xFE, 0xFE, 0xFE, 
    0xFE, 0xFE, 0xFE, 0xFE, 
    0xFE, 0x83, 0x83, 0xFE, 
    0xFE, 0x83, 0x83, 0xFF
  }
};

const sTileInfo O_Block_Rotated_270 =
{
  .rotation_info = byte_31F1,
  .data = {
    0xFE, 0xFE, 0xFE, 0xFE, 
    0xFE, 0xFE, 0xFE, 0xFE, 
    0xFE, 0x83, 0x83, 0xFE, 
    0xFE, 0x83, 0x83, 0xFF
  }
};

const sTileInfo Z_Block_Rotated_0 =
{
  .rotation_info = byte_31F1,
  .data = {
    0xFE, 0xFE, 0xFE, 0xFE, 
    0xFE, 0xFE, 0xFE, 0xFE, 
    0x82, 0x82, 0xFE, 0xFE, 
    0xFE, 0x82, 0x82, 0xFF
  }
};

const sTileInfo Z_Block_Rotated_90 =
{
  .rotation_info = byte_31F1,
  .data = {
    0xFE, 0xFE, 0xFE, 0xFE, 
    0xFE, 0x82, 0xFE, 0xFE, 
    0x82, 0x82, 0xFE, 0xFE, 
    0x82, 0xFF
  }
};

const sTileInfo Z_Block_Rotated_180 =
{
  .rotation_info = byte_31F1,
  .data = {
    0xFE, 0xFE, 0xFE, 0xFE, 
    0xFE, 0xFE, 0xFE, 0xFE, 
    0x82, 0x82, 0xFE, 0xFE, 
    0xFE, 0x82, 0x82, 0xFF
  }
};

const sTileInfo Z_Block_Rotated_270 =
{
  .rotation_info = byte_31F1,
  .data = {
    0xFE, 0xFE, 0xFE, 0xFE, 
    0xFE, 0x82, 0xFE, 0xFE, 
    0x82, 0x82, 0xFE, 0xFE, 
    0x82, 0xFF
  }
};

const sTileInfo S_Block_Rotated_0 =
{
  .rotation_info = byte_31F1,
  .data = {
    0xFE, 0xFE, 0xFE, 0xFE, 
    0xFE, 0xFE, 0xFE, 0xFE, 
    0xFE, 0x86, 0x86, 0xFE, 
    0x86, 0x86, 0xFF
  }
};

const sTileInfo S_Block_Rotated_90 =
{
  .rotation_info = byte_31F1,
  .data = {
    0xFE, 0xFE, 0xFE, 0xFE, 
    0x86, 0xFE, 0xFE, 0xFE, 
    0x86, 0x86, 0xFE, 0xFE, 
    0xFE, 0x86, 0xFF
  }
};

const sTileInfo S_Block_Rotated_180 =
{
  .rotation_info = byte_31F1,
  .data = {
    0xFE, 0xFE, 0xFE, 0xFE, 
    0xFE, 0xFE, 0xFE, 0xFE, 
    0xFE, 0x86, 0x86, 0xFE, 
    0x86, 0x86, 0xFF
  }
};

const sTileInfo S_Block_Rotated_270 =
{
  .rotation_info = byte_31F1,
  .data = {
    0xFE, 0xFE, 0xFE, 0xFE, 
    0x86, 0xFE, 0xFE, 0xFE, 
    0x86, 0x86, 0xFE, 0xFE, 
    0xFE, 0x86, 0xFF
  }
};

const sTileInfo T_Block_Rotated_0 =
{
  .rotation_info = byte_31F1,
  .data = {
    0xFE, 0xFE, 0xFE, 0xFE, 
    0xFE, 0xFE, 0xFE, 0xFE, 
    0x85, 0x85, 0x85, 0xFE, 
    0xFE, 0x85, 0xFF
  }
};

const sTileInfo T_Block_Rotated_90 =
{
  .rotation_info = byte_31F1,
  .data = {
    0xFE, 0xFE, 0xFE, 0xFE, 
    0xFE, 0x85, 0xFE, 0xFE, 
    0xFE, 0x85, 0x85, 0xFE, 
    0xFE, 0x85, 0xFF
  }
};

const sTileInfo T_Block_Rotated_180 =
{
  .rotation_info = byte_31F1,
  .data = {
    0xFE, 0xFE, 0xFE, 0xFE, 
    0xFE, 0x85, 0xFE, 0xFE, 
    0x85, 0x85, 0x85, 0xFF
  }
};

const sTileInfo T_Block_Rotated_270 =
{
  .rotation_info = byte_31F1,
  .data = {
    0xFE, 0xFE, 0xFE, 0xFE, 
    0xFE, 0x85, 0xFE, 0xFE, 
    0x85, 0x85, 0xFE, 0xFE, 
    0xFE, 0x85, 0xFF
  }
};

const sTileInfo off_2F75 =
{
  .rotation_info = byte_3211,
  .data = {
    0x0A, 0x25, 0x1D, 0x22, 
    0x19, 0x0E, 0xFF
  }
};

const sTileInfo off_2F7E =
{
  .rotation_info = byte_3211,
  .data = {
    0x0B, 0x25, 0x1D, 0x22, 
    0x19, 0x0E, 0xFF
  }
};

const sTileInfo off_2F87 =
{
  .rotation_info = byte_3211,
  .data = {
    0x0C, 0x25, 0x1D, 0x22, 
    0x19, 0x0E, 0xFF
  }
};

const sTileInfo off_2F90 =
{
  .rotation_info = byte_3211,
  .data = {
    0x2F, 0x18, 0x0F, 0x0F, 
    0x2F, 0x2F, 0xFF
  }
};

const sTileInfo Number0Block =
{
  .rotation_info = byte_3211,
  .data = {
    0x00, 0xFF
  }
};

const sTileInfo Number1Block =
{
  .rotation_info = byte_3211,
  .data = {
    0x01, 0xFF
  }
};

const sTileInfo Number2Block =
{
  .rotation_info = byte_3211,
  .data = {
    0x02, 0xFF
  }
};

const sTileInfo Number3Block =
{
  .rotation_info = byte_3211,
  .data = {
    0x03, 0xFF
  }
};

const sTileInfo Number4Block =
{
  .rotation_info = byte_3211,
  .data = {
    0x04, 0xFF
  }
};

const sTileInfo Number5Block =
{
  .rotation_info = byte_3211,
  .data = {
    0x05, 0xFF
  }
};

const sTileInfo Number6Block =
{
  .rotation_info = byte_3211,
  .data = {
    0x06, 0xFF
  }
};

const sTileInfo Number7Block =
{
  .rotation_info = byte_3211,
  .data = {
    0x07, 0xFF
  }
};

const sTileInfo Number8Block =
{
  .rotation_info = byte_3211,
  .data = {
    0x08, 0xFF
  }
};

const sTileInfo Number9Block =
{
  .rotation_info = byte_3211,
  .data = {
    0x09, 0xFF
  }
};

const sTileInfo off_2FC1 =
{
  .rotation_info = byte_3221,
  .data = {
    0x2F, 0x01, 0x2F, 0x11, 
    0x20, 0x21, 0x30, 0x31, 
    0xFF
  }
};

const sTileInfo off_2FCC =
{
  .rotation_info = byte_3221,
  .data = {
    0x2F, 0x03, 0x12, 0x13, 
    0x22, 0x23, 0x32, 0x33, 
    0xFF
  }
};

const sTileInfo off_3113 =
{
  .rotation_info = byte_323D,
  .data = {
    0xC0, 0xC1, 0xC5, 0xC6, 
    0xCC, 0xCD, 0x75, 0x76, 
    0xA4, 0xA5, 0xA6, 0xA7, 
    0x54, 0x55, 0x56, 0x57, 
    0x44, 0x45, 0x46, 0x47, 
    0xA0, 0xA1, 0xA2, 0xA3, 
    0x9C, 0x9D, 0x9E, 0x9F, 
    0xFF
  }
};

const sTileInfo off_2FD7 =
{
  .rotation_info = byte_31F1,
  .data = {
    0x2F, 0x05, 0xFD, 0x05, 
    0x2F, 0x2F, 0x15, 0x04, 
    0x17, 0x24, 0x25, 0x26, 
    0x27, 0x34, 0x35, 0x36, 
    0x2F, 0xFF
  }
};

const sTileInfo off_2FEB =
{
  .rotation_info = byte_31F1,
  .data = {
    0x08, 0x37, 0xFD, 0x37, 
    0xFD, 0x08, 0x18, 0x19, 
    0x14, 0x1B, 0x28, 0x29, 
    0x2A, 0x2B, 0x60, 0x70, 
    0x36, 0x2F, 0xFF
  }
};

const sTileInfo off_3000 =
{
  .rotation_info = byte_3221,
  .data = {
    0xB9, 0xFD, 0xB9, 0xBA, 
    0xFD, 0xBA, 0xFF
  }
};

const sTileInfo off_3009 =
{
  .rotation_info = byte_3221,
  .data = {
    0x82, 0xFD, 0x82, 0x83, 
    0xFD, 0x83, 0xFF
  }
};

const sTileInfo off_3012 =
{
  .rotation_info = byte_3221,
  .data = {
    0x09, 0x0A, 0x3A, 0x3B, 
    0xFF
  }
};

const sTileInfo off_3019 =
{
  .rotation_info = byte_3221,
  .data = {
    0x0B, 0x40, 0x7C, 0x6F, 
    0xFF
  }
};

const sTileInfo off_315E =
{
  .rotation_info = byte_3275,
  .data = {
    0x63, 0x64, 0x65, 0xFF
  }
};

const sTileInfo off_3164 =
{
  .rotation_info = byte_3275,
  .data = {
    0x63, 0x64, 0x65, 0x66, 
    0x67, 0x68, 0xFF
  }
};

const sTileInfo off_3020 =
{
  .rotation_info = byte_3221,
  .data = {
    0x2F, 0x0F, 0x2F, 0x1F, 
    0x5F, 0x2C, 0x2F, 0x3F, 
    0xFF
  }
};

const sTileInfo off_302B =
{
  .rotation_info = byte_3221,
  .data = {
    0x6C, 0x3C, 0x4B, 0x4C, 
    0x5B, 0x5C, 0x6B, 0x2F, 
    0xFF
  }
};

const sTileInfo off_316D =
{
  .rotation_info = byte_3275,
  .data = {
    0x41, 0x41, 0x41, 0xFF
  }
};

const sTileInfo off_3173 =
{
  .rotation_info = byte_3275,
  .data = {
    0x42, 0x42, 0x42, 0xFF
  }
};

const sTileInfo off_3036 =
{
  .rotation_info = byte_31F1,
  .data = {
    0x2F, 0x4D, 0xFD, 0x4D, 
    0x2F, 0x2F, 0x5D, 0x5E, 
    0x4E, 0x5F, 0x6D, 0x6E, 
    0x2F, 0x2F, 0x7D, 0xFD, 
    0x7D, 0x2F, 0xFF
  }
};

const sTileInfo off_304B =
{
  .rotation_info = byte_31F1,
  .data = {
    0x08, 0x77, 0xFD, 0x77, 
    0xFD, 0x08, 0x18, 0x78, 
    0x43, 0x53, 0x7A, 0x7B, 
    0x50, 0x2F, 0x2F, 0x02, 
    0xFD, 0x7D, 0x2F, 0xFF
  }
};

const sTileInfo off_3061 =
{
  .rotation_info = byte_3221,
  .data = {
    0xB9, 0xFD, 0xB9, 0xBA, 
    0xFD, 0xBA, 0xFF
  }
};

const sTileInfo off_306A =
{
  .rotation_info = byte_3221,
  .data = {
    0x82, 0xFD, 0x82, 0x83, 
    0xFD, 0x83, 0xFF
  }
};

const sTileInfo off_3073 =
{
  .rotation_info = byte_3221,
  .data = {
    0x09, 0x0A, 0x3A, 0x3B, 
    0xFF
  }
};

const sTileInfo off_307A =
{
  .rotation_info = byte_3221,
  .data = {
    0x0B, 0x40, 0x7C, 0x6F, 
    0xFF
  }
};

const sTileInfo off_3179 =
{
  .rotation_info = byte_3275,
  .data = {
    0x52, 0x52, 0x52, 0x62, 
    0x62, 0x62, 0xFF
  }
};

const sTileInfo off_3182 =
{
  .rotation_info = byte_3275,
  .data = {
    0x51, 0x51, 0x51, 0x61, 
    0x61, 0x61, 0x71, 0x71, 
    0x71, 0xFF
  }
};

const sTileInfo off_3081 =
{
  .rotation_info = byte_3221,
  .data = {
    0xDC, 0xDD, 0xE0, 0xE1, 
    0xFF
  }
};

const sTileInfo off_3088 =
{
  .rotation_info = byte_3221,
  .data = {
    0xDE, 0xDF, 0xE0, 0xE1, 
    0xFF
  }
};

const sTileInfo off_308F =
{
  .rotation_info = byte_3221,
  .data = {
    0xDE, 0xE2, 0xE0, 0xE4, 
    0xFF
  }
};

const sTileInfo off_3096 =
{
  .rotation_info = byte_3221,
  .data = {
    0xDC, 0xEE, 0xE0, 0xE3, 
    0xFF
  }
};

const sTileInfo off_309D =
{
  .rotation_info = byte_3221,
  .data = {
    0xE5, 0xE6, 0xE7, 0xE8, 
    0xFF
  }
};

const sTileInfo off_30A4 =
{
  .rotation_info = byte_3221,
  .data = {
    0xFD, 0xE6, 0xFD, 0xE5, 
    0xFD, 0xE8, 0xFD, 0xE7, 
    0xFF
  }
};

const sTileInfo off_30AF =
{
  .rotation_info = byte_3221,
  .data = {
    0xE9, 0xEA, 0xEB, 0xEC, 
    0xFF
  }
};

const sTileInfo off_30B6 =
{
  .rotation_info = byte_3221,
  .data = {
    0xED, 0xEA, 0xEB, 0xEC, 
    0xFF
  }
};

const sTileInfo off_30BD =
{
  .rotation_info = byte_3221,
  .data = {
    0xF2, 0xF4, 0xF3, 0xBF, 
    0xFF
  }
};

const sTileInfo off_30C4 =
{
  .rotation_info = byte_3221,
  .data = {
    0xF4, 0xF2, 0xBF, 0xF3, 
    0xFF
  }
};

const sTileInfo off_30CB =
{
  .rotation_info = byte_3221,
  .data = {
    0xC2, 0xFD, 0xC2, 0xC3, 
    0xFD, 0xC3, 0xFF
  }
};

const sTileInfo off_30D4 =
{
  .rotation_info = byte_3221,
  .data = {
    0xC4, 0xFD, 0xC4, 0xC5, 
    0xFD, 0xC5, 0xFF
  }
};

const sTileInfo off_30DD =
{
  .rotation_info = byte_3221,
  .data = {
    0xDC, 0xFD, 0xDC, 0xEF, 
    0xFD, 0xEF, 0xFF
  }
};

const sTileInfo off_30E6 =
{
  .rotation_info = byte_3221,
  .data = {
    0xF0, 0xFD, 0xF0, 0xF1, 
    0xFD, 0xF1, 0xFF
  }
};

const sTileInfo off_30EF =
{
  .rotation_info = byte_3221,
  .data = {
    0xDC, 0xFD, 0xF0, 0xF1, 
    0xFD, 0xEF, 0xFF
  }
};

const sTileInfo off_30F8 =
{
  .rotation_info = byte_3221,
  .data = {
    0xF0, 0xFD, 0xDC, 0xEF, 
    0xFD, 0xF1, 0xFF
  }
};

const sTileInfo off_3101 =
{
  .rotation_info = byte_3221,
  .data = {
    0xBD, 0xBE, 0xBB, 0xBC, 
    0xFF
  }
};

const sTileInfo off_3108 =
{
  .rotation_info = byte_3221,
  .data = {
    0xB9, 0xBA, 0xDA, 0xDB, 
    0xFF
  }
};

const sTileInfo off_318E =
{
  .rotation_info = byte_31F1,
  .data = {
    0x2F, 0x2F, 0x2F, 0x2F, 
    0x2F, 0x2F, 0x2F, 0x2F, 
    0x63, 0x64, 0xFD, 0x64, 
    0xFD, 0x63, 0x66, 0x67, 
    0xFD, 0x67, 0xFD, 0x66, 
    0xFF
  }
};

const sTileInfo off_31A5 =
{
  .rotation_info = byte_3221,
  .data = {
    0x2F, 0x2F, 0x63, 0x64, 
    0xFF
  }
};

const sTileInfo off_31AC =
{
  .rotation_info = byte_3221,
  .data = {
    0x00, 0xFD, 0x00, 0x10, 
    0xFD, 0x10, 0x4F, 0xFD, 
    0x4F, 0x80, 0xFD, 0x80, 
    0x80, 0xFD, 0x80, 0x81, 
    0xFD, 0x81, 0x97, 0xFD, 
    0x97, 0xFF
  }
};

const sTileInfo off_31C4 =
{
  .rotation_info = byte_3221,
  .data = {
    0x98, 0xFD, 0x98, 0x99, 
    0xFD, 0x99, 0x80, 0xFD, 
    0x80, 0x9A, 0xFD, 0x9A, 
    0x9B, 0xFD, 0x9B, 0xFF
  }
};

const sTileInfo off_31D6 =
{
  .rotation_info = byte_3221,
  .data = {
    0xA8, 0xFD, 0xA8, 0xA9, 
    0xFD, 0xA9, 0xAA, 0xFD, 
    0xAA, 0xAB, 0xFD, 0xAB, 
    0xFF
  }
};

const sTileInfo off_31E5 =
{
  .rotation_info = byte_3221,
  .data = {
    0x41, 0x2F, 0x2F, 0xFF
  }
};

const sTileInfo off_31EB =
{
  .rotation_info = byte_3221,
  .data = {
    0x52, 0x2F, 0x62, 0xFF
  }
};


#endif
