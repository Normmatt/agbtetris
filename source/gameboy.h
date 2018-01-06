#ifndef GAMEBOY_FUNCTIONS
#define GAMEBOY_FUNCTIONS

typedef void (*Handler)(void);    /* A pointer to a handler function */
typedef void (*SoundHandler1)(vu8 *);

#define BUS_CLOCK (16756991)
#define TIMER_FREQ    (-BUS_CLOCK/1024) //16364Hz not quite the gameboys 16384Hz but should be close enough

#define REG_NR10        (*(vu8  *) (REG_BASE + 0x60))
#define REG_NR11        (*(vu8  *) (REG_BASE + 0x62))
#define REG_NR12        (*(vu8  *) (REG_BASE + 0x63))
#define REG_NR13        (*(vu8  *) (REG_BASE + 0x64))
#define REG_NR14        (*(vu8  *) (REG_BASE + 0x65))
#define REG_NR21        (*(vu8  *) (REG_BASE + 0x68))
#define REG_NR22        (*(vu8  *) (REG_BASE + 0x69))
#define REG_NR23        (*(vu8  *) (REG_BASE + 0x6c))
#define REG_NR24        (*(vu8  *) (REG_BASE + 0x6d))
#define REG_NR30        (*(vu8  *) (REG_BASE + 0x70))
#define REG_NR31        (*(vu8  *) (REG_BASE + 0x72))
#define REG_NR32        (*(vu8  *) (REG_BASE + 0x73))
#define REG_NR33        (*(vu8  *) (REG_BASE + 0x74))
#define REG_NR34        (*(vu8  *) (REG_BASE + 0x75))
#define REG_NR41        (*(vu8  *) (REG_BASE + 0x78))
#define REG_NR42        (*(vu8  *) (REG_BASE + 0x79))
#define REG_NR43        (*(vu8  *) (REG_BASE + 0x7c))
#define REG_NR44        (*(vu8  *) (REG_BASE + 0x7d))
#define REG_NR50        (*(vu8  *) (REG_BASE + 0x80))
#define REG_NR51        (*(vu8  *) (REG_BASE + 0x81))
#define REG_NR52        (*(vu8  *) (REG_BASE + 0x84))
#define REG_WAVERAM     ( (vu8  *) (REG_BASE + 0x90))

#define gJoyPressed                                     memory[0xFF80]
#define gJoyHeld                                        memory[0xFF81]
#define VBlank_Occured                                  memory[0xFF85]
#define curPiece_Tile                                   memory[0xFF89]
#define curBlock_Dest_High                              memory[0xFF8D]
#define curBlock_Dest_Low                               memory[0xFF8E]
#define UpdateBlocks_Recursion_Level                    memory[0xFF8F]
#define curPiece_X                                      memory[0xFF92]
#define curPiece_Y                                      memory[0xFF93]
#define gDelay                                          memory[0xFFA6]
#define gState                                          memory[0xFFE1]

enum {
   GBKEY_RIGHT=1,
   GBKEY_LEFT=2,
   GBKEY_UP=4,
   GBKEY_DOWN=8,
   GBKEY_A=16,
   GBKEY_B=32,
   GBKEY_SELECT=64,
   GBKEY_START=128,
};



void sub_153();
void AddToScore();
void Serial_Interrupt_Handler();
void sub_18E();
void ReadByteFromSerial();
void sub_1C7();
void sub_1DD();
void sub_1F3();
void VBlank_Interrupt_Handler();
void GB_Init();
void GotoSpecificStateHandler(u32 idx);
void GotoStateHandler();
void InitCopyrightScreen();
void DelayStateHandler();
void sub_419();
void sub_48C();
void sub_4E1();
void sub_4E6();
void sub_579();
void sub_5AF();
void sub_5EA();
void sub_5EF();
void sub_5F0();
void sub_620();
void sub_62D();
void sub_634();
void sub_63E();
void sub_664();
void sub_6DD();
void sub_6E4();
void sub_703();
void sub_792();
void sub_799();
void sub_7DA();
void sub_80F();
void sub_87B();
void sub_892();
void sub_895();
void sub_953();
void sub_AFB();
void sub_B07();
void sub_B10();
void sub_B41();
void sub_B95();
void sub_BFF();
void sub_C3A();
void sub_C54();
void sub_C80();
void sub_C92();
void sub_CB4();
void sub_CE6();
void sub_CF0();
void sub_D4F();
void sub_D96();
void sub_DE2();
void sub_DFD();
void sub_E11();
void sub_E1A();
void sub_E21();
void sub_E87();
void sub_ED3();
void sub_EEE();
void sub_F02();
void sub_F0B();
void sub_F12();
void sub_F7B();
void sub_FC4();
void sub_FD3();
void sub_10CE();
void sub_10E9();
void sub_113C();
void sub_1176();
void sub_11A3(u8 b, u8 c);
void InitRocketScreen();
void sub_1216();
void HandleRocketScreen();
void sub_1260();
void sub_1280();
void sub_12A8();
void sub_12DF();
void sub_1317();
void sub_1369();
void sub_137F();
void sub_1388();
void sub_13B5();
void sub_13CB();
void sub_13E2();
void sub_1419();
void sub_1449();
void sub_145E();
void sub_149B();
void HandleGameTypeMusicScreen();
void sub_14B3();
void stub_14F0();
void sub_14F1(vu8 *dst);
void sub_14F6(vu8 *dst);
void sub_1514();
void sub_157B();
void sub_1589();
void sub_15C2(vu8 *something, u8 val);
void sub_15C3();
void sub_15C7(vu8 *recursion_level);
void sub_15DB(vu8 *recursion_level);
void sub_15DF();
void sub_1623();
void sub_168D();
void sub_16D9();
void sub_16DE();
void sub_174A();
void sub_174F();
void sub_17B2(const u16 *src, vu8 *dst, u8 idx);
void sub_17B9(const u16 *src, vu8 *dst, u8 idx);
void sub_17CA(vu8* state);
void CopyTilemapSection_Width_6();
void ClearA0BytesFromC000();
void sub_17F9();
void sub_1813();
void sub_1839();
void sub_185B();
void sub_185D();
void sub_1864(u32 de);
void sub_192E();
void sub_1960();
void sub_1977();
void sub_1A62();
void sub_1A63();
void sub_1A6B();
void sub_1B43();
void sub_1B76();
void sub_1BC3();
void sub_1C29();
void sub_1C4F();
void sub_1C68();
void sub_1CE3();
void sub_1D26();
void sub_1D38();
void LoseHandler();
void sub_1D61();
void sub_1D81();
void sub_1DDF();
void sub_1E1B();
void sub_1E29();
void sub_1E8C();
void sub_1E96();
void sub_1E9C();
void sub_1EF0();
void sub_1F32();
void sub_1F71();
void GameOverTryAgainHandler();
void CopyTilemapSectionWidth8(const u8 *src, u16 *dst, u32 height);
void AddScoreForTetris();
void FillPlayArea(u8 val);
void sub_2038(u8 val);
void sub_204D();
void sub_2062();
void sub_20CC();
void sub_20F7();
void sub_20FF();
void sub_2199();
void sub_2240();
void sub_22AD();
void sub_22F3();
void sub_22FE();
void sub_230D();
void sub_231C();
void sub_232B();
void sub_233A();
void sub_2349();
void sub_2358();
void sub_2383();
void sub_2392();
void sub_23A1();
void sub_23B0();
void sub_23BF();
void sub_23CE();
void sub_23DD();
void sub_23EC();
void sub_23FE();
void sub_2417();
void sub_242C();
void sub_249B();
void sub_24AB();
void sub_2506(vu8 *src, u16 *dst);
void sub_2515();
void sub_25C7();
void sub_25F5();
void sub_262D();
void sub_26A5();
void sub_26B9();
void DrawCurrentBlock_C000_R2();
void DrawCurrentBlock_C000(u8 recursion_level);
void DrawCurrentBlock_C010();
void DrawPreviewBlock_C020();
void sub_26FD();
void sub_270A();
void Stub_Interrupt_Handler();
void sub_27E9();
void sub_27EC();
void CopyData();
void LoadFontData();
u32* LoadFontGlyphs();
void LoadTitleScreenTiles();
void CopyDataTo8000_Length1000();
void CopyDataTo8000();
void stub_283E();
void CopyTilemapSection_Height_12_Dest_9800();
void CopyTilemapSection_Height_12();
void CopyTilemapSection();
void sub_2858();
void DisableLCD();
void ReadJoypad();
void sub_2A2B();
void sub_2A58();
void sub_2A7E(vu8 *score, u16 *tilemap);
void DrawScore_C3(vu8 *score, u16 *tilemap);
void DrawScore(vu8 *score, u16 *tilemap, u8 numBytes);
void OAM_DMA_Transfer();
void UpdateBlocks(vu8 *src);
void sub_6552();
void UpdateAudio();
int sub_6603();
int sub_6609();
int sub_660F();
void sub_6624(vu8 *de);
void sub_662C();
void sub_6641(vu8 *de);
void sub_6649();
void sub_664E();
void sub_666C(vu8 *de);
void sub_6672();
void sub_66A3(vu8 *de);
void sub_66BC(vu8 *de);
void sub_66C4();
void sub_66F4(vu8 *de);
void sub_6704();
void sub_673D(vu8 *de);
void sub_6751();
void sub_6771(vu8 *de);
void sub_67DA();
void sub_67E2();
void sub_67EA();
void sub_6811();
void sub_6819();
void sub_6821();
void sub_683D();
void sub_6854();
void sub_6879();
void sub_68A8();
void sub_68C0();
void sub_68D1();
void sub_68E2();
void sub_68F3();
void sub_691F();
void sub_693E();
void sub_6967();
void SetupChannel1Registers();
void SetupChannel2Registers();
void SetupChannel3Registers();
void SetupChannel4Registers();
void CopySoundRegisters();
SoundHandler1 sub_69A9(const SoundHandler1 handlers[], vu8 **de, u8 a);
SoundHandler1 sub_69AD(const SoundHandler1 handlers[], vu8 **de, u8 a);
void sub_69BC();
void sub_69C9(u8 *src);
void ResetSound();
void sub_69F8();
void sub_6A0E();
void sub_6A2E();
void sub_6A4E();
void sub_6A52();
void sub_6A6D();
void sub_6A96();
void sub_6B33();
void sub_6B3E();
void sub_6B44();
void sub_6BEA();
void sub_6BF6();
void sub_6BFF();
void sub_6C75();
void sub_6D8F();
void sub_6D98();
void j_UpdateAudio();
void j_ResetSound();


#endif