#ifndef GAMEBOY_FUNCTIONS
#define GAMEBOY_FUNCTIONS

typedef void (*Handler)(void);    /* A pointer to a handler function */
typedef void (*SoundHandler1)(vu8 *);

#define BUS_CLOCK (16756991)
#define TIMER_FREQ    (-BUS_CLOCK/1024) //16364Hz not quite the gameboys 16384Hz but should be close enough

//	Causes the timer to count at (16756991 / 1024) MHz.
#define TIMER_DIV_1024  (3)

#define REG_SCX         REG_BG0HOFS
#define REG_SCY         REG_BG0VOFS
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
#define REG_DIV         (*(vu8  *) (REG_BASE + 0x108))

#define wPreventHoldDown                                memory[0xC0C7]

#define wCurPieceY                                      memory[0xC201]
#define wCurPieceX                                      memory[0xC202]
#define wCurPiece                                       memory[0xC203]
#define wPreviewPieceY                                  memory[0xC211]
#define wPreviewPieceX                                  memory[0xC212]
#define wPreviewPiece                                   memory[0xC213]

#define hJoyDown                                        memory[0xFF80]
#define hJoyPressed                                     memory[0xFF81]
#define hVBlankSignal                                   memory[0xFF85]
#define hCurPieceTile                                   memory[0xFF89]
#define hCurPieceDstHigh                                memory[0xFF8D]
#define hCurPieceDstLow                                 memory[0xFF8E]
#define hUpdateBlocks_Recursion_Level                   memory[0xFF8F]
#define hCurPieceX                                      memory[0xFF92]
#define hCurPieceY                                      memory[0xFF93]
#define hCurPieceState                                  memory[0xFF98]
#define hRemainingFrameDelay                            memory[0xFF99]
#define hLvlFrameDelay                                  memory[0xFF9A]
#define hNumFinishedLines                               memory[0xFF9E]
#define hDelay                                          memory[0xFFA6]
#define hLevel                                          memory[0xFFA9]
#define hButtonHoldCounter                              memory[0xFFAA]
#define hGamePaused                                     memory[0xFFAB]
#define hP1High                                         memory[0xFFAC]
#define hP2High                                         memory[0xFFAD]
#define hNextPreviewPiece                               memory[0xFFAE]
#define hDemoNextPiecePtr                               memory[0xFFAF]
#define hTypeASelectedLevel                             memory[0xFFC2]
#define hTypeBSelectedLevel                             memory[0xFFC3]
#define hTypeBSelectedHigh                              memory[0xFFC4]
#define hState                                          memory[0xFFE1]
#define hVBlankCounter                                  memory[0xFFE2]
#define hBoardUpdateState                               memory[0xFFE3]
#define hDemo                                           memory[0xFFE4]
#define hCurPieceDropCount                              memory[0xFFE5]

#define GB_VRAM_TO_GBA_VRAM(adr)  (((u16*)(VRAM+0x9800)) + (adr-0x9800))
#define SET_LCDC(val) \
        do{ \
            REG_DISPCNT &= ~(BG0_ON | BG1_ON); \
            if(val & (1<<3)) \
            { \
                REG_DISPCNT |= BG1_ON; /*On GBA I'm just going to toggle BG0 and BG1 to simulate this*/ \
            } \
            else \
            { \
                REG_DISPCNT |= BG0_ON; /*On GBA I'm just going to toggle BG0 and BG1 to simulate this*/ \
            } \
        }while(0)

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

void stub_153();
void AddToScore();
void Serial_Interrupt_Handler();
void stub_18E();
void ReadByteFromSerial();
void stub_1C7();
void stub_1DD();
void stub_1F3();
void VBlank_Interrupt_Handler();
void GB_Init();
__attribute__ ((noreturn)) void GB_Main();
void GotoSpecificStateHandler(u32 idx);
void GotoStateHandler();
void InitCopyrightScreen();
void DelayStateHandler();
void stub_419();
void stub_48C();
void stub_4E1();
void stub_4E6();
void stub_579();
void stub_5AF();
void stub_5EA();
void stub_5EF();
void stub_5F0();
void stub_620();
void stub_62D();
void stub_634();
void stub_63E();
void stub_664();
void stub_6DD();
void stub_6E4();
void stub_703();
void stub_792();
void stub_799();
void stub_7DA();
void stub_80F();
void stub_87B();
void stub_892();
void stub_895();
void stub_953();
void stub_AFB();
void stub_B07();
void stub_B10();
void stub_B41();
void stub_B95();
void stub_BFF();
void stub_C3A();
void stub_C54();
void stub_C80();
void stub_C92();
void stub_CB4();
void stub_CE6();
void stub_CF0();
void stub_D4F();
void stub_D96();
void stub_DE2();
void stub_DFD();
void stub_E11();
void stub_E1A();
void stub_E21();
void stub_E87();
void stub_ED3();
void stub_EEE();
void stub_F02();
void stub_F0B();
void stub_F12();
void stub_F7B();
void stub_FC4();
void stub_FD3();
void stub_10CE();
void stub_10E9();
void stub_113C();
void stub_1176();
void stub_11A3(u8 b, u8 c);
void InitRocketScreen();
void stub_1216();
void HandleRocketScreen();
void stub_1260();
void stub_1280();
void stub_12A8();
void stub_12DF();
void stub_1317();
void stub_1369();
void stub_137F();
void stub_1388();
void stub_13B5();
void stub_13CB();
void stub_13E2();
void stub_1419();
void stub_1449();
void stub_145E();
void stub_149B(u16 *dst, const u8 *src, u32 len);
void HandleGameTypeMusicScreen();
void stub_14B3();
void stub_14F0();
void stub_14F1(vu8 *dst);
void stub_14F6(vu8 *dst);
void stub_1514();
void stub_157B();
void stub_1589();
void stub_15C2(vu8 *something, u8 val);
void stub_15C3();
void stub_15C7(vu8 *recursion_level);
void stub_15DB(vu8 *recursion_level);
void stub_15DF();
void stub_1623();
void stub_168D();
void stub_16D9();
void stub_16DE();
void stub_174A();
void stub_174F();
void stub_17B2(const u16 *src, vu8 *dst, u8 idx);
void stub_17B9(const u16 *src, vu8 *dst, u8 idx);
void stub_17CA(vu8* state);
void CopyTilemapSection_Width_6();
void ClearA0BytesFromC000();
void stub_17F9();
void stub_1813();
void stub_1839();
void stub_185B();
void stub_185D();
void stub_1864(u32 de);
void stub_192E();
void stub_1960();
void stub_1977();
void stub_1A62(u16 *dst, u8 val);
void stub_1A63(u16 *dst, u8 val);
void stub_1A6B();
void stub_1B43();
void InitDemoFillHighLines();
void FillGarbageRows();
void stub_1C29();
void stub_1C4F();
void stub_1C68();
void stub_1CE3();
void stub_1D26();
void stub_1D38();
void LoseHandler();
void stub_1D61();
void stub_1D81();
void stub_1DDF();
void stub_1E1B();
void stub_1E29();
void stub_1E8C();
void stub_1E96();
void stub_1E9C();
void stub_1EF0();
void stub_1F32();
void stub_1F71();
void GameOverTryAgainHandler();
void CopyTilemapSectionWidth8(const u8 *src, u16 *dst, u32 height);
void AddScoreForTetris();
void FillPlayArea(u8 val);
void stub_2038(u8 val);
void stub_204D();
void GetNextPiece();
void stub_20CC();
void HandleDrop();
void stub_20FF();
void HandleFinishedRows();
void HandleRowBlink();
void MoveUpFinishedRows();
void stub_22F3();
void UpdateBoardStage2();
void UpdateBoardStage3();
void UpdateBoardStage4();
void UpdateBoardStage5();
void UpdateBoardStage6();
void UpdateBoardStage7();
void UpdateBoardStage8();
void UpdateBoardStage9();
void UpdateBoardStage10();
void UpdateBoardStage11();
void UpdateBoardStage12();
void UpdateBoardStage13();
void UpdateBoardStage14();
void UpdateBoardStage15();
void UpdateBoardStage16();
void UpdateBoardStage17();
void UpdateBoardStage18();
void UpdateBoardStage19();
void PrintIngameScore();
void UpdateLevel();
void UpdateBoardRow(vu8 *src, u16 *dst);
void HandleRotationAndShift();
u8 CheckSpriteCollision();
void LockCurPiece();
void stub_262D();
void stub_26A5();
void stub_26B9();
void DrawCurrentBlock_C000_R2();
void DrawCurrentBlock_C000(u8 recursion_level);
void DrawCurrentBlock_C010();
void DrawPreviewBlock_C020();
void stub_26FD();
void stub_270A(vu8 *dst, const u8 *src);
void Stub_Interrupt_Handler();
void FillTileMap0();
void stub_27EC();
void CopyData();
void LoadFontData();
u32* LoadFontGlyphs();
void LoadTitleScreenTiles();
void CopyDataTo8000_Length1000(const u8 *src);
void CopyDataTo8000(const u8 *src, u32 len);
void stub_283E();
void CopyTilemapSection_Height_12_Dest_9800();
void CopyTilemapSection_Height_12();
void CopyTilemapSection();
void stub_2858(u8 *src, vu8 *dst);
void DisableLCD();
void ReadJoypad();
u16 SpritePosToBoardPos();
void stub_2A58();
void stub_2A7E(vu8 *score, u16 *tilemap);
void DrawScore_C3(vu8 *score, u16 *tilemap);
void DrawScore(vu8 *score, u16 *tilemap, u8 numBytes);
void OAM_DMA_Transfer();
void UpdateBlocks(vu8 *src);
void stub_6552();
void UpdateAudio();
int stub_6603();
int stub_6609();
int stub_660F();
void stub_6624(vu8 *de);
void stub_662C();
void stub_6641(vu8 *de);
void stub_6649();
void stub_664E();
void stub_666C(vu8 *de);
void stub_6672();
void stub_66A3(vu8 *de);
void stub_66BC(vu8 *de);
void stub_66C4();
void stub_66F4(vu8 *de);
void stub_6704();
void stub_673D(vu8 *de);
void stub_6751();
void stub_6771(vu8 *de);
void stub_67DA();
void stub_67E2();
void stub_67EA();
void stub_6811();
void stub_6819();
void stub_6821();
void stub_683D();
void stub_6854();
void stub_6879();
void stub_68A8();
void stub_68C0();
void stub_68D1();
void stub_68E2();
void stub_68F3();
void stub_691F();
void stub_693E();
void stub_6967();
void SetupChannel1Registers();
void SetupChannel2Registers();
void SetupChannel3Registers();
void SetupChannel4Registers();
void CopySoundRegisters();
SoundHandler1 stub_69A9(const SoundHandler1 handlers[], vu8 **de, u8 a);
SoundHandler1 stub_69AD(const SoundHandler1 handlers[], vu8 **de, u8 a);
void stub_69BC();
void stub_69C9(u8 *src);
void ResetSound();
void stub_69F8();
void stub_6A0E();
void stub_6A2E();
void stub_6A4E();
void stub_6A52();
void stub_6A6D();
void stub_6A96();
void stub_6B33();
void stub_6B3E();
void stub_6B44();
void stub_6BEA();
void stub_6BF6();
void stub_6BFF();
void stub_6C75();
void stub_6D8F();
void stub_6D98();
void j_UpdateAudio();
void j_ResetSound();


#endif