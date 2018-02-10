
#include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_timers.h>
#include <gba_sprites.h>
#include <gba_input.h>
#include <stdio.h>
#include <stdlib.h>
#include "debugprint.h"
#include "gameboy.h"
#include "gameboy_data.h"
#include "blockinfo.h"

//Memory Map
//9800 is now 06009800
//C000 is now 07000000 //or atleast thats where its copied too (after transformation)


vu8 memory[0x10000] EWRAM_DATA;

void stub_153()
{
    //Unimplemented - Unused?
    stub_2A2B();
}


void AddToScore(int *curScore, int val)
{
    int binaryInput = *curScore + val; 
    int bcdResult = 0;
    int shift = 0;

    while (binaryInput > 0) {
        bcdResult |= (binaryInput % 10) << (shift++ << 2);
        binaryInput /= 10;
    }
    
    if(bcdResult > 999999)
        bcdResult = 999999;
    
    *curScore = bcdResult;
}


void Serial_Interrupt_Handler()
{
    stub_18E();
    
    memory[0xFFCC] = 1;
}


void stub_18E()
{
    //Unimplemented - Partial
    u32 idx = memory[0xFFCD];
    GotoSpecificStateHandler(idx); //GotoStateHandler
    
    //TODO: Finish
}


void ReadByteFromSerial()
{
    //Unimplemented
}


void stub_1C7()
{
    //Unimplemented
}


void stub_1DD()
{
    //Unimplemented
}


void stub_1F3()
{
    //Unimplemented
}


void VBlank_Interrupt_Handler()
{
    //debugPrint("VBlank_Interrupt_Handler called");
    //Unimplemented
    if (memory[0xFFCE] != 0)
    {
        if(memory[0xFFCB] == 0x29)
        {
            memory[0xFFCE] = 0;
            debugPrint("VBlank_Interrupt_Handler sb/sc crap");
            //REG_SB = memory[0xFFCF];
            //REG_SC = 0x81;
        }
    }
    
    stub_2240();
    UpdateBoardStage19();
    UpdateBoardStage18();
    UpdateBoardStage17();
    UpdateBoardStage16();
    UpdateBoardStage15();
    UpdateBoardStage14();
    UpdateBoardStage13();
    UpdateBoardStage12();
    UpdateBoardStage11();
    UpdateBoardStage10();
    UpdateBoardStage9();
    UpdateBoardStage8();
    UpdateBoardStage7();
    UpdateBoardStage6();
    UpdateBoardStage5();
    UpdateBoardStage4();
    UpdateBoardStage3();
    UpdateBoardStage2();
    stub_1F32();
    OAM_DMA_Transfer();
    stub_192E();
    
    if (memory[0xC0CE] != 0)
    {
        if(hCurPieceState == 0x3)
        {
            //hl = $986D
            PrintIngameScore(GB_VRAM_TO_GBA_VRAM(0x986D));
            memory[0xFFE0] = 1;
            //hl = $9C6D
            PrintIngameScore(GB_VRAM_TO_GBA_VRAM(0x9C6D));
            memory[0xC0CE] = 0;
        }
    }
    
    memory[0xC0CE]++;
    REG_BG0HOFS = 0;
    REG_BG0VOFS = 0;
    hVBlankSignal = 1;    
}


void GB_Init()
{
    debugPrint("GB_Init called");
    
    for(int i=0; i<16; i++)
        memory[0xDFFF-i] = 0;
    
    GB_Main();
}


__attribute__ ((noreturn)) void GB_Main()
{
    while(1)
    {
        // Disable Interrupts
        REG_IME = 0;
        
        irqEnable(IRQ_VBLANK);
        
        REG_BG0HOFS = 0;
        REG_BG0VOFS = 0;
        
        memory[0xFFA4] = 0;
        
        REG_DISPCNT = MODE_0 | BG0_ENABLE | OBJ_ON;// | WIN0_ON;
        REG_BG0CNT = BG_SIZE_0 | BG_MAP_BASE(0x9800/0x800); //BG MAP is at 0x06006000
        
        //Do this for convenience
        REG_BG1CNT = BG_SIZE_0 | BG_MAP_BASE(0xA000/0x800); //BG MAP is at 0x06006000
        
        //Wait for GB Vblank 148
        //Probably should be set to GBA 160
        //while (REG_VCOUNT >= SCREEN_HEIGHT);
        //while (REG_VCOUNT < SCREEN_HEIGHT);
        VBlankIntrWait();
        
        REG_DISPCNT = MODE_0 | BG0_ENABLE | OBJ_ON;// | WIN0_ON;
        
        BG_PALETTE[0] = RGB8(224, 248, 208); //Lightest Green
        BG_PALETTE[1] = RGB8(136, 192, 112); //Light Green
        BG_PALETTE[2] = RGB8( 52, 104,  86); //Dark Green
        BG_PALETTE[3] = RGB8(  8,  24,  32); //Darkest Green
        
        SPRITE_PALETTE[0] = RGB8(224, 248, 208); //Lightest Green
        SPRITE_PALETTE[1] = RGB8(136, 192, 112); //Light Green
        SPRITE_PALETTE[2] = RGB8( 52, 104,  86); //Dark Green
        SPRITE_PALETTE[3] = RGB8(  8,  24,  32); //Darkest Green
        
        SPRITE_PALETTE[16] = RGB8(224, 248, 208); //Lightest Green
        SPRITE_PALETTE[17] = RGB8(136, 192, 112); //Light Green
        SPRITE_PALETTE[18] = RGB8( 52, 104,  86); //Dark Green
        SPRITE_PALETTE[19] = RGB8(  8,  24,  32); //Darkest Green

        REG_NR52 = 0x80;
        REG_NR51 = 0xFF;
        REG_NR50 = 0x77;
        
        //On gameboy if X/Y are 0 its hidden it doesn't work that way on GBA
        //So prime all sprites to be out of bounds
        for(int i=0; i<128; i++)
        {
            OAM[i].attr0 = OBJ_Y(240); 
            OAM[i].attr1 = OBJ_X(160); 
            OAM[i].attr2 = 0; 
        }
        
        //Why do this again with zero length wtf
        for(int i=0; i<1; i++)
            memory[0xDFFF-i] = 0;
        
        for(int i=0; i<16; i++)
            memory[0xCFFF-i] = 0;
        
        //Clear some BG Tilemap entries?
        for(int i=0; i<32; i++)
            memory[0x9FFF-i] = 0;
        
        for(int i=0; i<1; i++)
            memory[0xFEFF-i] = 0;
        
        for(int i=0; i<0x80; i++)
            memory[(0xFFFE)-i] = 0;
        
        stub_27E9();
        ResetSound();
        
        irqEnable(IRQ_VBLANK);
        irqEnable(IRQ_SERIAL);
        
        memory[0xFFC0] = 0x37;
        memory[0xFFC1] = 0x1C;
        hState = 0x24;
        
        //Turn display on
        REG_DISPCNT = MODE_0 | BG0_ENABLE | OBJ_ON | WIN0_ON;
        
        // Enable Interrupts
        REG_IME = 1;
        
        REG_WININ = 0x13; //BG0 + BG1 + OBJ
        //Bit   Expl.
        //0-7   X2, Rightmost coordinate of window, plus 1
        //8-15  X1, Leftmost coordinate of window
        REG_WIN0V = (144+1) | (0<<8);
        //Bit   Expl.
        //0-7   Y2, Bottom-most coordinate of window, plus 1
        //8-15  Y1, Top-most coordinate of window
        REG_WIN0H = (160+1) | (0<<8);
        REG_TM0CNT_L = 0;
        
        while(1)
        {
            ReadJoypad();
            GotoStateHandler();
            j_UpdateAudio();
            if(keysDown() == (KEY_A|KEY_B|KEY_SELECT|KEY_START))
                break;
            
            if (gDelay != 0) {
                gDelay -= 1;
            }
            if (memory[0xFFA7] != 0) {
                memory[0xFFA7] -= 1;
            }
            
            if (memory[0xFFC5] != 0) {
                irqEnable(IRQ_VBLANK);
                irqEnable(IRQ_SERIAL);
            }
            while (hVBlankSignal == 0);
            hVBlankSignal = 0;
        }
    }
}

Handler state_handlers[] = {
    &stub_1C29,
    &LoseHandler,
    &stub_12A8,
    &stub_12DF,
    &stub_1D61,
    &stub_1D81,
    &stub_419,
    &stub_4E6,
    &HandleGameTypeMusicScreen,
    &stub_14F0,
    &stub_1A6B,
    &stub_1E1B,
    &stub_1F71,
    &GameOverTryAgainHandler,
    &stub_1589,
    &stub_1514,
    &stub_15DF,
    &stub_1623,
    &stub_168D,
    &stub_16DE,
    &stub_174F,
    &stub_1977,
    &stub_6E4,
    &stub_799,
    &stub_892,
    &stub_953,
    &stub_B95,
    &stub_D4F,
    &stub_B41,
    &stub_D96,
    &stub_E87,
    &stub_1176,
    &stub_DFD,
    &stub_EEE,
    &stub_1E29,
    &stub_1E9C,
    &InitCopyrightScreen,
    &DelayStateHandler,
    &InitRocketScreen,
    &HandleRocketScreen,
    &stub_1260,
    &stub_1280,
    &stub_634,
    &stub_664,
    &stub_1317,
    &stub_1369,
    &stub_1388,
    &stub_13B5,
    &stub_13CB,
    &stub_13E2,
    &stub_1419,
    &stub_1449,
    &stub_137F,
    &stub_283E,
};

void GotoSpecificStateHandler(u32 idx)
{
    debugPrintf("GotoSpecificStateHandler %d",idx);
    state_handlers[idx]();
}

void GotoStateHandler()
{
    int idx = hState;
    GotoSpecificStateHandler(idx);
}

void InitCopyrightScreen()
{
    //Unimplemented
    debugPrint("InitCopyrightScreen called");
    DisableLCD();
    LoadTitleScreenTiles();
    CopyTilemapSection_Height_12_Dest_9800(CopyrightScreen_Tilemap);
    ClearA0BytesFromC000();
    
    for(int i=0; i<sizeof(byte_64D0); i++)
        memory[0xC300+i] = byte_64D0[i];
    
    gDelay = 0x7D;
    hState = 0x25;    
    //while(1);
}


void DelayStateHandler()
{
    //debugPrint("DelayStateHandler called"); 
    if(gDelay != 0)
        return;
    
    //debugPrint("DelayStateHandler passed"); 
    hState = 0x6; 
}


void stub_419()
{
    //debugPrint("stub_419 called");
    
    memory[0xFFE9] = 0;
    hCurPieceState = 0;
    memory[0xFF9C] = 0;
    memory[0xFF9B] = 0;
    memory[0xFFFB] = 0;
    memory[0xFF9F] = 0;
    hBoardUpdateState = 0;
    memory[0xFFE7] = 0;
    memory[0xFFC7] = 0;
    
    stub_22F3();
    stub_26A5();
    LoadTitleScreenTiles();
    
    for(int i=0; i<0x400; i++)
    {
        memory[0xC800+i] = 0x2F; 
    }
    
    //hl = $C801 
    stub_26FD();
    //hl = $C80C
    stub_26FD();
    
    for(int i=0; i<12; i++)
    {
        memory[0xCA41+i] = 0x8E; 
    }
    
    CopyTilemapSection_Height_12_Dest_9800(TitleScreen_Tilemap);
    ClearA0BytesFromC000();
    
    memory[0xC000] = 0x80;
    memory[0xC001] = 0x10;
    memory[0xC002] = 0x58;
    
    memory[0xDFE8] = 3;
    
    //LCDC = $D3
    SET_LCDC(0xD3);
    
    hState = 7;
    gDelay = 0x7D;
    
    memory[0xFFC6] = 4;
    
    if(hDemo)
        return;
    
    memory[0xFFC6] = 0x13;
}


void stub_48C()
{
    //Unimplemented
    
    memory[0xFFC0] = 0x37;
    hTypeASelectedLevel = 0x09;
    
    memory[0xFFC5] = 0x00;
    memory[0xFFB0] = 0x00;
    memory[0xFFED] = 0x00;
    memory[0xFFEA] = 0x00;
    
    memory[0xFFEB] = 0x63;
    memory[0xFFEC] = 0x30;
    
    if(hDemo == 0x02)
    {
        memory[0xFFC0] = 0x77;
        hTypeBSelectedLevel = 0x09;
        hTypeBSelectedHigh = 0x02;
        memory[0xFFEB] = 0x64;
        memory[0xFFEC] = 0x30;
        memory[0xFFB0] = 0x11;
        hDemo = 0x1;
    }
    else
    {
        hDemo = 0x2;
    }
    
    hState = 0x0A;
    
    DisableLCD();
    
    LoadFontData();
    
    CopyTilemapSection_Height_12_Dest_9800(GameType_1P_Tilemap);
    
    ClearA0BytesFromC000();
    
    //LCDC = $D3
    SET_LCDC(0xD3);
}


void stub_4E1()
{
    memory[0xFFE9] = 0xFF;
}


void stub_4E6()
{
    //Seems to handle the input on the title screen
    
    if(gDelay == 0)
    {
        memory[0xFFC6]--;
        if(memory[0xFFC6] == 0)
        {
            stub_48C();
            return;
        }
        gDelay = 0x7D;
    }
    
    stub_B07();
    
    //REG_SB = 0x55;
    //REG_SC = 0x80;
    if(memory[0xFFCC] != 0)
    {
        if(memory[0xFFCB] == 0)
        {
            memory[0xFFCC] = 0;
            memory[0xFFC5] = 0;
        }
    }
    else if(hJoyPressed & GBKEY_SELECT)
    {
        memory[0xFFC5] ^= 1;
    }
    else if(hJoyPressed & GBKEY_LEFT)
    {
        if(!memory[0xFFC5])
            return;
        memory[0xFFC5] = 0; //1Player
    }
    else if(hJoyPressed & GBKEY_RIGHT)
    {
        if(memory[0xFFC5])
            return;
        memory[0xFFC5] = 2; //2Player
    }
    else if(hJoyPressed & GBKEY_START)
    {
        if(memory[0xFFC5] == 0)
        {
            //1Player stuff?
            if(hJoyDown & GBKEY_DOWN)
            {
               memory[0xFFF4] = hJoyDown;
            }
            else
            {
                hState = 8;
                gDelay = 0;
                hTypeASelectedLevel = 0;
                hTypeBSelectedLevel = 0;
                hTypeBSelectedHigh = 0;
                hDemo = 0;
                return;
            }
        }
        else
        {
            //2Player stuff?
            if(hJoyPressed != GBKEY_START) //Check if only START is pressed
            {
                //If any other key is pressed return.
                return;
            }
            
            if(memory[0xFFCB] == 0x29)
            {
                hState = 0x2A;
                gDelay = 0;
                hTypeASelectedLevel = 0;
                hTypeBSelectedLevel = 0;
                hTypeBSelectedHigh = 0;
                hDemo = 0;
                return;
            }
            
            //REG_SB = 0x29;
            //REG_SC = 0x81;
            while(memory[0xFFCC] == 0);
            
            if(memory[0xFFCB] == 0)
            {
                memory[0xFFC5] = 0;
            }
            else
            {
                hState = 0x2A;
                gDelay = 0;
                hTypeASelectedLevel = 0;
                hTypeBSelectedLevel = 0;
                hTypeBSelectedHigh = 0;
                hDemo = 0;
                return;
            }
        }
    }
    else
    {
        return;
    }
    //Update the cursor's X position
    if(memory[0xFFC5] == 0)
        memory[0xC001] = 0x10;
    else
        memory[0xC001] = 0x60;
}


void stub_579()
{
    //Unimplemented - Multiplayer related?
}


void stub_5AF()
{
    //Unimplemented
}


void stub_5EA()
{
    //Unused?
    
    memory[0xFFED] = 0;
    
    hJoyPressed = 0;
    memory[0xFFEE] = hJoyDown;
    hJoyDown = memory[0xFFED];
}


void stub_5EF()
{
    //This does nothing
}


void stub_5F0()
{
    //Unimplemented - Partial
    
    if(!hDemo)
        return;
    
    if(memory[0xFFE9] != 0xFF)
        return;
    
    if(hJoyDown == memory[0xFFED])
    {
        memory[0xFFEA]++;
        return;
    }
    
    //0601
    u16 adr = memory[0xFFEB] << 8 | memory[0xFFEC]; //TODO: Verify this isn't in vram
    
    memory[adr++] = memory[0xFFED];
    memory[adr++] = memory[0xFFEA];
    
    memory[0xFFEB] = (adr >> 8) & 0xFF;
    memory[0xFFEC] = (adr >> 0) & 0xFF;
    
    memory[0xFFED] = hJoyDown;
    memory[0xFFEA] = 0;
}


void stub_620()
{
    if(!hDemo)
        return;
    
    if(memory[0xFFE9])
        return;
    
    hJoyDown = memory[0xFFEE];
}


void stub_62D()
{
    //Unimplemented - Partial
    //set 7 in [SC]
    stub_63E();
}


void stub_634()
{
    memory[0xFFCD] = 3;
    
    if(memory[0xFFCB] != 0x29)
    {
        stub_62D();
        return;
    }
    
    stub_63E();
}


void stub_63E()
{
    stub_14B3();
    memory[0xC210] = 0x80;
    DrawCurrentBlock_C000_R2();
    memory[0xFFCE] = 0; //TODO: Verify this is correct
    //[SB] = 0;
    memory[0xFFCF] = 0;
    memory[0xFFDC] = 0;
    memory[0xFFD2] = 0;
    memory[0xFFD3] = 0;
    memory[0xFFD4] = 0;
    memory[0xFFD5] = 0;
    hBoardUpdateState = 0;
    
    j_ResetSound();
    
    hState = 0x2B;
}


void stub_664()
{
    //Unimplemented
}


void stub_6DD()
{
    //Unimplemented
}


void stub_6E4()
{
    //Unimplemented
}


void stub_703()
{
    //Unimplemented
}


void stub_792()
{
    //Unimplemented
}


void stub_799()
{
    //Unimplemented
}


void stub_7DA()
{
    //Unimplemented
}


void stub_80F()
{
    //Unimplemented
}


void stub_87B()
{
    //Unimplemented
}


void stub_892()
{
    DisableLCD();
    stub_895();
}


void stub_895()
{
    //Unimplemented
}


void stub_953()
{
    //Unimplemented
}


void stub_AFB()
{
    for(int i=0; i<10; i++)
    {
        memory[0xCA42+i] = 0x80;
    }
}


void stub_B07()
{
    //Unimplemented - Delay routine?
}


void stub_B10()
{
    //Unimplemented
}


void stub_B41()
{
    //Unimplemented
}


void stub_B95()
{
    //Unimplemented
}


void stub_BFF()
{
    //Unimplemented
}


void stub_C3A()
{
    //Unimplemented
}


void stub_C54()
{
    //Unimplemented
}


void stub_C80()
{
    //Unimplemented
}


void stub_C92()
{
    //Unimplemented
}


void stub_CB4()
{
    //Unimplemented
}


void stub_CE6()
{
    //Unimplemented
}


void stub_CF0()
{
    //Unimplemented
}


void stub_D4F()
{
    //Unimplemented
}


void stub_D96()
{
    //Unimplemented
}


void stub_DE2()
{
    //Unimplemented
}


void stub_DFD()
{
    //Unimplemented
}


void stub_E11()
{
    stub_E21();
    DrawCurrentBlock_C000(3);
}


void stub_E1A()
{
    hState = 0x1F;
    memory[0xFFCC] = 0x1F;
}


void stub_E21()
{
    //Unimplemented
}


void stub_E87()
{
    //Unimplemented
}


void stub_ED3()
{
    //Unimplemented
}


void stub_EEE()
{
    //Unimplemented
}


void stub_F02()
{
    stub_F12();
    DrawCurrentBlock_C000(2);
}


void stub_F0B()
{
    hState = 0x1F;
    memory[0xFFCC] = 0x1F;
}


void stub_F12()
{
    //Unimplemented
}


void stub_F7B()
{
    //Unimplemented
}


void stub_FC4()
{
    for(int i=0; i<9; i++)
    {
        memory[0xC060+(i*4)] = 0;
    }
}


void stub_FD3()
{
    //Unimplemented
}


void stub_10CE()
{
    //Unimplemented
}


void stub_10E9()
{
    //Unimplemented
}


void stub_113C()
{
    //Unimplemented
}


void stub_1176()
{
    //IE = 1;
    if(gDelay)
        return;
    
    ClearA0BytesFromC000();
    
    memory[0xFFEF] = 0;
    
    //b = $27
    //c = $79
    stub_11A3(0x27,0x79);
    j_ResetSound();
    
    if(memory[0xFFD7] != 5)
    {
        if(memory[0xFFD8] != 5)
        {
            memory[0xFFD6] = 1;
        }
    }
    
    hState = 0x16;
}


void stub_11A3(u8 b, u8 c)
{
    if(!memory[0xFFCC])
    {
        return;
    }
    
    memory[0xFFCC] = 0;
    if(memory[0xFFCD] != 0x29)
    {
        if(memory[0xFFD0] != c)
        {
            memory[0xFFCF] = b;
        }
        return;
    }
    
    if(memory[0xFFD0] == b)
    {
        memory[0xFFCF] = c;
        memory[0xFFCE] = c;
    }
    else
    {
        memory[0xFFCF] = 2;
        memory[0xFFCE] = 2;
    }
}


void InitRocketScreen()
{    
    stub_1216();
    
    //hl = $9CE6
    //de = byte_147F
    //b  = 7
    stub_149B(GB_VRAM_TO_GBA_VRAM(0x9CE6), byte_147F, 7);
    
    //hl = $9CE7
    //de = byte_1486
    //b  = 7
    stub_149B(GB_VRAM_TO_GBA_VRAM(0x9CE7), byte_1486, 7);
    
    *GB_VRAM_TO_GBA_VRAM(0x9D08) = 0x72;
    *GB_VRAM_TO_GBA_VRAM(0x9D09) = 0xC4;
    
    *GB_VRAM_TO_GBA_VRAM(0x9D28) = 0xB7;
    *GB_VRAM_TO_GBA_VRAM(0x9D29) = 0xB8;
    
    CopyTilemapSection_Width_6(byte_27C5, &memory[0xC200], 3);
    
    DrawCurrentBlock_C000(3);
    
    //LCDC = $DB
    SET_LCDC(0xDB);
    gDelay = 0xBB;
    hState = 0x27;
    memory[0xDFE8] = 0x10;
}


void stub_1216()
{
    DisableLCD();
    
    CopyDataTo8000(byte_55F4, 0x1000);
    
    //hl = $9FFF
    stub_27EC(GB_VRAM_TO_GBA_VRAM(0x9FFF));
    
    CopyTilemapSection(byte_520C, GB_VRAM_TO_GBA_VRAM(0x9DC0), 4);
    
    //hl = $9CEC
    //de = byte_148D
    //b  = 7
    stub_149B(GB_VRAM_TO_GBA_VRAM(0x9CEC), byte_148D, 7);
    
    //hl = $9CED
    //de = byte_1494
    //b  = 7
    stub_149B(GB_VRAM_TO_GBA_VRAM(0x9CED), byte_1494, 7);
}


void HandleRocketScreen()
{
    if(gDelay)
        return;
    
    memory[0xC210] = 0;
    memory[0xC220] = 0;
    gDelay = 0xFF;
    hState = 0x28;
}


void stub_1260()
{
    if(gDelay)
    {
        stub_145E();
        return;
    }
    
    hState = 0x29;
    wPreviewPiece = 0x35;
    memory[0xC223] = 0x35;
    gDelay = 0xFF;
    
    FillPlayArea(0x2F);
}


void stub_1280()
{
    if(gDelay)
    {
        stub_145E();
        return;
    }
    
    hState = 0x02;
    
    stub_1A63(GB_VRAM_TO_GBA_VRAM(0x9D08), 0x2F);
    stub_1A63(GB_VRAM_TO_GBA_VRAM(0x9D09), 0x2F);
    stub_1A63(GB_VRAM_TO_GBA_VRAM(0x9D28), 0x2F);
    stub_1A63(GB_VRAM_TO_GBA_VRAM(0x9D29), 0x2F);
}


void stub_12A8()
{
    if(gDelay)
    {
        stub_145E();
        return;
    }
    
    gDelay = 0x0A;
    
    wCurPieceY--;
    
    if(wCurPieceY != 0x58)
    {
        stub_145E();
        return;
    }
    
    memory[0xC210] = 0;
    wPreviewPieceY = wCurPieceY + 0x20;
    wPreviewPieceX = 0x4C;
    wPreviewPiece = 0x40;
    memory[0xC220] = 0x80;
    
    DrawCurrentBlock_C000(3);
    
    hState = 3;
    memory[0xDFF8] = 4;
}


void stub_12DF()
{
    if(!gDelay)
    {
        //12E4
        
        gDelay = 0x0A;
    
        wPreviewPieceY--;
        wCurPieceY--;
        
        if(wCurPieceY == 0xD0)
        {
            //12F4
            memory[0xFFC9] = 0x9C;
            memory[0xFFCA] = 0x82;
            hState = 0x2C;
            return;
        }
    }
    
    //1301
    if(!memory[0xFFA7])
    {
        //1306
        memory[0xFFA7] = 6;
        wPreviewPiece ^= 1;
    }
    
    //1311
    DrawCurrentBlock_C000(3);
}


void stub_1317()
{
    //Prints CONGRATULATIONS! after rocket scene
    
    if(gDelay)
        return;
    
    gDelay = 0x06; //Maybe this should be extended on GBA?
    
    //131F
    u16 adr = memory[0xFFC9] << 8 | memory[0xFFCA];
    u8 val = byte_1359[memory[0xFFCA]-0x82];
    
    stub_1A62(GB_VRAM_TO_GBA_VRAM(adr), val);
    stub_1A63(GB_VRAM_TO_GBA_VRAM(adr+0x20), 0xB6);
    
    adr++;
    
    memory[0xDFE0] = 2;
    memory[0xFFC9] = (adr >> 8) & 0xFF;
    memory[0xFFCA] = (adr >> 0) & 0xFF;
    
    if(memory[0xFFCA] != 0x92)
        return;
    
    gDelay = 0xFF;
    hState = 0x2D;
}


void stub_1369()
{
    if(gDelay)
        return;
    
    DisableLCD();
    LoadFontData();
    stub_22F3();
    
    //LCDC = $93
    SET_LCDC(0x93);
    hState = 5;
}


void stub_137F()
{
    if(gDelay)
        return;
    
    hState = 0x2E;
}


void stub_1388()
{
    stub_1216();
    CopyTilemapSection_Width_6(byte_27D7, &memory[0xC200], 3);
    wCurPiece = memory[0xFFF3];
    
    DrawCurrentBlock_C000(3);
    
    memory[0xFFF3] = 0;
    
    //LCDC = $DB
    SET_LCDC(0xDB);
    gDelay = 0xBB;
    hState = 0x2F;
    memory[0xDFE8] = 0x10;
}


void stub_13B5()
{
    if(gDelay)
        return;
    
    memory[0xC210] = 0;
    memory[0xC220] = 0;
    gDelay = 0xA0;
    hState = 0x30;
}


void stub_13CB()
{
    if(gDelay)
    {
        hState = 0x31;
        gDelay = 0x80;
        FillPlayArea(0x2F);
    }
    else
    {
        stub_145E();
    }
}


void stub_13E2()
{
    if(gDelay)
    {
        stub_145E();
        return;
    }
    
    gDelay = 0x0A;
    
    wCurPieceY--;
    if(wCurPieceY != 0x6A)
    {
        stub_145E();
        return;
    }
    
    memory[0xC210] = 0;
    wPreviewPieceY = wCurPieceY + 0x10;
    wPreviewPieceX = 0x54;
    wPreviewPieceX = 0x5C;
    memory[0xC220] = 0x80;
    
    DrawCurrentBlock_C000(3);
    
    hState = 0x32;
    memory[0xDFF8] = 4;
}


void stub_1419()
{
    if(!gDelay)
    {
        //141E
        gDelay = 0x0A;
        wPreviewPieceY--;
        wCurPieceY--;
        
        if(wCurPieceY == 0xE0)
        {
            hState = 0x33;
            return;
        }
    }
    
    //1433
    if(!memory[0xFFA7])
    {
        memory[0xFFA7] = 6;
        wPreviewPiece ^= 1;
    }
    
    DrawCurrentBlock_C000(3);
}


void stub_1449()
{
    DisableLCD();
    LoadFontData();
    j_ResetSound();
    stub_22F3();
    //LCDC = $93
    SET_LCDC(0x93);
    hState = 0x10;
}


void stub_145E()
{
    if(memory[0xFFA7])
        return;
    
    memory[0xFFA7] = 0x0A;
    memory[0xDFF8] = 0x03;
    
    //gameboy has a loop here for some reason?
    memory[0xC210] ^= 0x80;
    memory[0xC220] ^= 0x80;
    
    DrawCurrentBlock_C000(3);
}


void stub_149B(u16 *dst, const u8 *src, u32 len)
{
    for(int i=0; i<len; i++)
    {
        *dst = *src++;
        dst += 0x20; //TODO Confirm this is correct
    }
}


void HandleGameTypeMusicScreen()
{
    irqEnable(IRQ_VBLANK);
    //REG_SB = 0;
    //REG_SC = 0;
    //IF = 1;
    stub_14B3();
}


void stub_14B3()
{
    DisableLCD();
    LoadFontData();
    CopyTilemapSection_Height_12_Dest_9800(GameType_1P_Tilemap);
    ClearA0BytesFromC000();
    
    CopyTilemapSection_Width_6(byte_2723, &memory[0xC200], 2);
    
    stub_14F1(&wCurPieceY);
    
    wPreviewPieceX = memory[0xFFC0];
    
    if(memory[0xFFC0] == 0x37)
        wPreviewPiece = 0x1C;
    else
        wPreviewPiece = 0x1D;
    
    DrawCurrentBlock_C000_R2();
    stub_157B();
    
    //LCDC = $D3
    SET_LCDC(0xD3);
    hState = 0x0E;
}

void stub_14F0()
{
    //This function does nothing
}

void stub_14F1(vu8 *dst)
{
    memory[0xDFE0] = 1;
    stub_14F6(dst);
}


void stub_14F6(vu8 *dst)
{
    u32 idx = ((memory[0xFFC1] - 0x1C) * 2); //GB code doesn't bounds check
    
    //debugPrintf("idx = %02X", idx);
    
    const u8 byte_150C[] =
    {
      0x70, 0x37, 0x70, 0x77, 0x80, 0x37, 0x80, 0x77
    };
    
    *dst++ = byte_150C[idx++];
    *dst++ = byte_150C[idx++];
    *dst++ = memory[0xFFC1];
}


void stub_1514()
{
    //Select Music Type
    //Differs slightly from original code in that theres no looping to dpad checks on B button...
    debugPrint("stub_1514 called");
    
    stub_17CA(&memory[0xC200]);
    
    if(hJoyPressed & GBKEY_START)
    {
        stub_15C7(&memory[0xC210]);
    }
    else if(hJoyPressed & GBKEY_A)
    {
        stub_15C7(&memory[0xC210]);
    }
    else if(hJoyPressed & GBKEY_B)
    {
        if(!memory[0xFFC5])
        {
            hState = 0x0E;
            stub_15C2(&wCurPieceY, 0);
        }
    }
    else if(hJoyPressed & GBKEY_UP)
    {
        if(memory[0xFFC1] == 0x1C)
        {
            DrawCurrentBlock_C000_R2();
        }
        else if(memory[0xFFC1] == 0x1D)
        {
            DrawCurrentBlock_C000_R2();
        }
        else
        {
            memory[0xFFC1] -= 2;
            stub_14F1(&wCurPieceY);
            stub_157B();
        }
    }
    else if(hJoyPressed & GBKEY_DOWN)
    {
        if(memory[0xFFC1] == 0x1E)
        {
            DrawCurrentBlock_C000_R2();
        }
        else if(memory[0xFFC1] == 0x1F)
        {
            DrawCurrentBlock_C000_R2();
        }
        else
        {
            memory[0xFFC1] += 2;
            stub_14F1(&wCurPieceY);
            stub_157B();
        }
    }
    else if(hJoyPressed & GBKEY_RIGHT)
    {
        if(memory[0xFFC1] == 0x1D)
        {
            DrawCurrentBlock_C000_R2();
        }
        else if(memory[0xFFC1] == 0x1F)
        {
            DrawCurrentBlock_C000_R2();
        }
        else
        {
            memory[0xFFC1]++;
            stub_14F1(&wCurPieceY);
            stub_157B();
        }
    }
    else if(hJoyPressed & GBKEY_LEFT)
    {
        if(memory[0xFFC1] == 0x1C)
        {
            DrawCurrentBlock_C000_R2();
        }
        else if(memory[0xFFC1] == 0x1E)
        {
            DrawCurrentBlock_C000_R2();
        }
        else
        {
            memory[0xFFC1]--;
            stub_14F1(&wCurPieceY);
            stub_157B();
        }
    }
    else
    {
        //Any other time just update existing sprite
        stub_15C3();
    }
}


void stub_157B()
{
    if((memory[0xFFC1] - 0x17) == 8)
    {
        memory[0xDFE8] = 0xFF;
    }
    else
    {
        memory[0xDFE8] = (memory[0xFFC1] - 0x17);
    }
}


void stub_1589()
{
    //Select Game Type
    debugPrint("stub_1589 called");
    
    stub_17CA(&memory[0xC210]);
    
    if(hJoyPressed & GBKEY_START)
    {
        stub_15C7(&memory[0xC210]);
    }
    else if(hJoyPressed & GBKEY_A)
    {
        stub_15DB(&memory[0xC210]);
    }
    else if(hJoyPressed & GBKEY_RIGHT)
    {
        if(memory[0xFFC0] == 0x77)
        {
            stub_15C3();
        }
        else
        {
            memory[0xFFC0] = 0x77;
            memory[0xDFE0] = 1;
            wPreviewPieceX = 0x77;
            stub_15C2(&wPreviewPiece, 0x1D);
        }
    }
    else if(hJoyPressed & GBKEY_LEFT)
    {
        if(memory[0xFFC0] == 0x37)
        {
            stub_15C3();
        }
        else
        {
            memory[0xFFC0] = 0x37;
            memory[0xDFE0] = 1;
            wPreviewPieceX = 0x37;
            stub_15C2(&wPreviewPiece, 0x1C);
        }
    }
    else
    {
        //Any other time just update existing sprite
        stub_15C3();
    }
}


void stub_15C2(vu8 *something, u8 val)
{
    //[de] = a
    *something = val;
    stub_15C3();
}


void stub_15C3()
{
    DrawCurrentBlock_C000_R2();
}


void stub_15C7(vu8 *recursion_level)
{
    memory[0xDFE0] = 2;
    
    if(memory[0xFFC0] == 0x37)
    {
        hState = 0x10;
    }
    else
    {
        hState = 0x12;
    }
    
    stub_15C2(recursion_level, 0);
}


void stub_15DB(vu8 *recursion_level)
{
    hState = 0xF;
    stub_15C2(recursion_level, 0);
}


void stub_15DF()
{
    debugPrint("stub_15DF called");
    
    DisableLCD();
    CopyTilemapSection_Height_12_Dest_9800(TypeA_Level_Select_Tilemap);
    stub_1960();
    
    ClearA0BytesFromC000();
    CopyTilemapSection_Width_6(byte_272F, &memory[0xC200], 1);
    stub_17B2(word_1679, &wCurPieceY, hTypeASelectedLevel);
    DrawCurrentBlock_C000_R2();
    
    stub_17F9();
    stub_192E();
    
    //LCDC = $D3
    SET_LCDC(0xD3);
    hState = 0x11;
    
    if(memory[0xFFC7])
    {
       hState = 0x15; 
    }
    else
    {
        stub_157B();
    }
}


void stub_1623()
{
    //Select A-Type Level
    debugPrint("stub_1623 called");
    
    stub_17CA(&memory[0xC200]);
    
    if(hJoyPressed & GBKEY_START)
    {
        hState = 0x0A;
    }
    else if(hJoyPressed & GBKEY_A)
    {
        hState = 0x0A;
    }
    else if(hJoyPressed & GBKEY_RIGHT)
    {
        if(hTypeASelectedLevel == 0x09)
        {
            DrawCurrentBlock_C000_R2();
        }
        else
        {
            hTypeASelectedLevel++;
            stub_17B2(word_1679, &wCurPieceY, hTypeASelectedLevel);
            stub_17F9();
            
            DrawCurrentBlock_C000_R2();
        }
    }
    else if(hJoyPressed & GBKEY_LEFT)
    {
        if(hTypeASelectedLevel == 0x00)
        {
            DrawCurrentBlock_C000_R2();
        }
        else
        {
            hTypeASelectedLevel--;
            stub_17B2(word_1679, &wCurPieceY, hTypeASelectedLevel);
            stub_17F9();
            
            DrawCurrentBlock_C000_R2();
        }
    }
    else if(hJoyPressed & GBKEY_UP)
    {
        if(hTypeASelectedLevel < 5)
        {
            DrawCurrentBlock_C000_R2();
        }
        else
        {
            hTypeASelectedLevel -= 5;
            stub_17B2(word_1679, &wCurPieceY, hTypeASelectedLevel);
            stub_17F9();
            
            DrawCurrentBlock_C000_R2();
        }
    }
    else if(hJoyPressed & GBKEY_DOWN)
    {
        if(hTypeASelectedLevel >= 5)
        {
            DrawCurrentBlock_C000_R2();
        }
        else
        {
            hTypeASelectedLevel += 5;
            stub_17B2(word_1679, &wCurPieceY, hTypeASelectedLevel);
            stub_17F9();
            
            DrawCurrentBlock_C000_R2();
        }
    }
    else
    {
        //Any other time just update existing sprite
        stub_15C3();
    }
}


void stub_168D()
{
    //B-Type level select init
    debugPrint("stub_168D called");
    
    DisableLCD();
    CopyTilemapSection_Height_12_Dest_9800(TypeB_Level_Select_Tilemap);
    
    ClearA0BytesFromC000();
    CopyTilemapSection_Width_6(byte_2735, &memory[0xC200], 1);
    stub_17B2(word_1736, &wCurPieceY, hTypeBSelectedLevel);
    stub_17B2(word_17A5, &wPreviewPieceY, hTypeBSelectedHigh);
    DrawCurrentBlock_C000_R2();
    
    stub_1813();
    stub_192E();
    
    //LCDC = $D3
    SET_LCDC(0xD3);
    hState = 0x13;
    
    if(memory[0xFFC7])
    {
       hState = 0x15; 
    }
    else
    {
        stub_157B();
    }
}


void stub_16D9(vu8 *de, u32 newState)
{
    hState = newState;
    *de = 0;
}


void stub_16DE()
{
    //Select B-Type Level
    debugPrint("stub_16DE called");
    
    stub_17CA(&memory[0xC200]);
    
    if(hJoyPressed & GBKEY_START)
    {
        stub_16D9(&memory[0xC200], 0x0A);
    }
    else if(hJoyPressed & GBKEY_A)
    {
        stub_16D9(&memory[0xC200], 0x14);
    }
    else if(hJoyPressed & GBKEY_B)
    {
        stub_16D9(&memory[0xC200], 0x08);
    }
    else if(hJoyPressed & GBKEY_RIGHT)
    {
        if(hTypeBSelectedLevel == 0x09)
        {
            DrawCurrentBlock_C000_R2();
        }
        else
        {
            hTypeBSelectedLevel++;
            stub_17B2(word_1736, &wCurPieceY, hTypeBSelectedLevel);
            stub_1813();
            
            DrawCurrentBlock_C000_R2();
        }
    }
    else if(hJoyPressed & GBKEY_LEFT)
    {
        if(hTypeBSelectedLevel == 0x00)
        {
            DrawCurrentBlock_C000_R2();
        }
        else
        {
            hTypeBSelectedLevel--;
            stub_17B2(word_1736, &wCurPieceY, hTypeBSelectedLevel);
            stub_1813();
            
            DrawCurrentBlock_C000_R2();
        }
    }
    else if(hJoyPressed & GBKEY_UP)
    {
        if(hTypeBSelectedLevel < 5)
        {
            DrawCurrentBlock_C000_R2();
        }
        else
        {
            hTypeBSelectedLevel -= 5;
            stub_17B2(word_1736, &wCurPieceY, hTypeBSelectedLevel);
            stub_1813();
            
            DrawCurrentBlock_C000_R2();
        }
    }
    else if(hJoyPressed & GBKEY_DOWN)
    {
        if(hTypeBSelectedLevel >= 5)
        {
            DrawCurrentBlock_C000_R2();
        }
        else
        {
            hTypeBSelectedLevel += 5;
            stub_17B2(word_1736, &wCurPieceY, hTypeBSelectedLevel);
            stub_1813();
            
            DrawCurrentBlock_C000_R2();
        }
    }
    else
    {
        //Any other time just update existing sprite
        DrawCurrentBlock_C000_R2();
    }
}


void stub_174A()
{
    //Unimplemented
}


void stub_174F()
{
    //Unimplemented
}


void stub_17B2(const u16 *src, vu8 *dst, u8 idx)
{
    memory[0xDFE0] = 1;
    stub_17B9(src, dst, idx);
}

//src is really an X/Y pair 
void stub_17B9(const u16 *src, vu8 *dst, u8 idx)
{
    u16 val = src[idx];
    *dst++ = (val >> 0) & 0xFF;
    *dst++ = (val >> 8) & 0xFF;
    *dst++ = idx + 0x20;
}


//Returns hJoyPressed in B
void stub_17CA(vu8* state)
{
    //Unimplemented
    if(gDelay)
        return;
    
    gDelay = 0x10;
    
    *state ^= 0x80;
}


void CopyTilemapSection_Width_6(u8 *src, u8 *dst, u32 height)
{
    //Unimplemented
    for(int y=0; y<height; y++)
    {
        for(int x=0; x<6; x++)
        {
            *dst++ = *src++;
        }
        
        dst += 0x10-6;
    }
    *dst = 0x80;
}


void ClearA0BytesFromC000()
{
    for(int i=0; i<0xA0; i++)
    {
        memory[0xC000+i] = 0;
    }
}


void stub_17F9()
{
    //Unimplemented
}


void stub_1813()
{
    stub_1960();
    
    u32 mem = 0xD000;
    
    u32 idx = hTypeBSelectedLevel;
    mem += (idx*0xA2);
    
    u32 idx2 = hTypeBSelectedHigh;
    mem += (idx2*0x1B);
    
    mem++;
    mem++;
    
    stub_1864(mem);
    
}


void stub_1839()
{
    //Unimplemented
}


void stub_185B()
{
    //Unimplemented
}


void stub_185D()
{
    //Unimplemented
}


void stub_1864(u32 de)
{
    //Unimplemented - Partial
    
    memory[0xFFFB] = (de >> 0) & 0xFF;
    memory[0xFFFC] = (de >> 8) & 0xFF;
    
    int c = 3;
    u32 temp_de = de;
    do
    {
       u32 hl = 0xC0A2;
       int b = 3;
       do
       {
           s8 temp = (s8)memory[temp_de]; 
           temp -= memory[hl];
           if(temp < 0)
           {
               //loc_1886 - TODO
           }
           else if(temp == 0)
           {
               hl--;
               temp_de--;
               b--;
           }
           else
           {
               break;
           }
           
           temp_de = de;
           temp_de += 3;
           c--;
       } while(b);
       
    } while(c);
}


void stub_192E()
{
    //Unimplemented
}


void stub_1960()
{
    for(int h=0; h<3; h++)
    {
        for(int w=0; w<14; w++)
        {
            memory[0xC9A4+w+(h*0x20)] = 0x60;
        }
        
    }
}


void stub_1977()
{
    //Unimplemented
}


void stub_1A62(u16 *dst, u8 val)
{
    stub_1A63(dst, val);
}


void stub_1A63(u16 *dst, u8 val)
{
    while(REG_DISPSTAT & 3);
    *dst = val;
}


void stub_1A6B()
{
    //Main Game State Init
    DisableLCD();
    
    memory[0xC210] = 0;
    hCurPieceState = 0;
    memory[0xFF9C] = 0;
    memory[0xFF9B] = 0;
    memory[0xFFFB] = 0;
    memory[0xFF9F] = 0;
    
    FillPlayArea(0x2F);
    stub_204D();
    stub_26A5();
    
    hBoardUpdateState = 0;
    memory[0xFFE7] = 0;
    
    ClearA0BytesFromC000();
    
    if(memory[0xFFC0] == 0x77)
    {
        //B-Type
        memory[0xFFE6] = 0x50;
        hLevel = hTypeBSelectedLevel;
        CopyTilemapSection_Height_12_Dest_9800(MainGame_TypeB_Tilemap);
        CopyTilemapSection_Height_12(MainGame_TypeB_Tilemap, GB_VRAM_TO_GBA_VRAM(0x9C00));
    }
    else
    {
        //A-Type
        memory[0xFFE6] = 0xF1;
        hLevel = hTypeASelectedLevel;
        CopyTilemapSection_Height_12_Dest_9800(MainGame_TypeA_Tilemap);
        CopyTilemapSection_Height_12(MainGame_TypeA_Tilemap, GB_VRAM_TO_GBA_VRAM(0x9C00));
    }
    
    CopyTilemapSectionWidth8(PauseMenu_Tilemap, GB_VRAM_TO_GBA_VRAM(0x9C63), 10);
    
    u16 *vram = GB_VRAM_TO_GBA_VRAM(0x9800);
    vram += memory[0xFFE6];
    
    *vram = hLevel;
    *(vram + 0x400) = hLevel;
    
    //TODO
    if(memory[0xFFF4])
    {
        //1AD0
        vram++;
        *(vram + 0x400) = 0x27;
        *vram = 0x27;
    }
    
    //1AD7
    
    //hl = $C200
    //de = byte_2713
    stub_270A(&memory[0xC200],byte_2713);
    
    //hl = $C210
    //de = byte_271B
    stub_270A(&memory[0xC210],byte_271B);
    
    if(memory[0xFFC0] == 0x77)
    {
        hNumFinishedLines = 0x25;
    }
    else
    {
        hNumFinishedLines = 0x00;
    }
    
    u32 val = hNumFinishedLines & 0x0F;
    *GB_VRAM_TO_GBA_VRAM(0x9951) = val;
    
    if(val)
    {
        *GB_VRAM_TO_GBA_VRAM(0x9950) = 0x02;
    }
    
    stub_1B43();
    GetNextPiece();
    GetNextPiece();
    GetNextPiece();
    DrawCurrentBlock_C010();
    
    memory[0xFFA0] = 0;
    
    if(memory[0xFFC0] == 0x77)
    {
        //1B16
        hRemainingFrameDelay = 0x34;
        
        *GB_VRAM_TO_GBA_VRAM(0x98B0) = hTypeBSelectedHigh;
        *GB_VRAM_TO_GBA_VRAM(0x9CB0) = hTypeBSelectedHigh;
        
        if(hTypeBSelectedHigh)
        {
            //1B26
            if(hDemo)
            {
                //1B2C
                //b = hTypeBSelectedHigh
                InitDemoFillHighLines();
            }
            else
            {
                //1B31
                //a = hTypeBSelectedHigh
                //de = $FFC0
                //hl = $9A02
                FillGarbageRows();
            }
        }
    }
    
    //1B3B
    //LCDC = $D3
    SET_LCDC(0xD3);
    hState = 0;
}


void stub_1B43()
{
    u32 idx = hLevel;
    if(memory[0xFFF4])
    {
        idx += 0x0A;
        if(idx >= 0x15) //TODO Check this is correct
        {
            idx = 0x14;
        }
    }
    
    hRemainingFrameDelay = LevelFramesPerRow[idx];
    hLvlFrameDelay = LevelFramesPerRow[idx];
}


void InitDemoFillHighLines()
{
    //Unimplemented
}


void FillGarbageRows()
{
    //Unimplemented
}


void stub_1C29()
{
    stub_1C68();
    
    if(hGamePaused)
        return;
    
    stub_579();
    stub_5AF();
    stub_5F0();
    HandleRotationAndShift();
    HandleDrop();
    HandleFinishedRows();
    LockCurPiece();
    MoveUpFinishedRows();
    AddScoreForTetris();
    stub_620();
}


void stub_1C4F()
{
    //Toggle preview block on/off
    if(hJoyPressed & GBKEY_SELECT)
    {
        memory[0xC0DE] ^= 1;
        
        if(memory[0xC0DE])
        {
            //1C5C
            memory[0xC210] = 0x80;
        }
        else
        {
            //1C65
            memory[0xC210] = 0x00;
        }
        
        DrawPreviewBlock_C020();
    }
}


void stub_1C68()
{
    if((hJoyDown & (GBKEY_A|GBKEY_B|GBKEY_SELECT|GBKEY_START)) == (GBKEY_A|GBKEY_B|GBKEY_SELECT|GBKEY_START))
    {
        GB_Main();
    }
    
    if(hDemo)
    {
        return;
    }
    
    if(!(hJoyPressed & GBKEY_START))
    {
        stub_1C4F();
        return;
    }
    
    if(memory[0xFFC5] == 0)
    {
        //1C80
        hGamePaused ^= 1;
        
        if(hGamePaused)
        {
            //1C8B
            //LCDC |= 1<<3; This changes the tilemap address...
            REG_DISPCNT ^= BG0_ON | BG1_ON; //On GBA I'm just going to toggle BG0 and BG1 to simulate this
            
            memory[0xDF7F] = 1;
            
            u16 *src = GB_VRAM_TO_GBA_VRAM(0x994E);
            u16 *dst = GB_VRAM_TO_GBA_VRAM(0x9D4E);
            for(int i=0; i<4; i++)
            {
                while(REG_DISPSTAT & 3);
                
                *dst++ = *src++;
                
            }
            
            memory[0xC210] = 0x80;
            memory[0xC200] = 0x80;
            
            DrawCurrentBlock_C010();
            DrawPreviewBlock_C020();
        }
        else
        {
            //1CB5
            //LCDC |= 1<<3; This changes the tilemap address...
            REG_DISPCNT ^= BG0_ON | BG1_ON; //On GBA I'm just going to toggle BG0 and BG1 to simulate this
            
            memory[0xDF7F] = 2;
            
            if(!memory[0xC0DE])
            {
                //1CA8
                memory[0xC210] = memory[0xC0DE];
                memory[0xC200] = memory[0xC0DE];
            }
            else
            {
                //1CC2
                memory[0xC200] = 0;
            }
            
            DrawCurrentBlock_C010();
            DrawPreviewBlock_C020();
        }        
    }
    else
    {
        //1CC5
        if(memory[0xFFCB] == 0x29)
        {
            //1CCA
            hGamePaused ^= 1;
            
            if(hGamePaused)
            {
                //1CD2
                memory[0xDF7F] = 1;
                memory[0xFFF2] = memory[0xFFD0];
                memory[0xFFF1] = memory[0xFFCF];
                
                stub_1D26();
            }
            else
            {
                //1D05
                memory[0xFFD0] = memory[0xFFF2];
                memory[0xFFCF] = memory[0xFFF1];
                memory[0xDF7F] = 2;
                memory[0xDFAB] = 0;
                
                for(int i=0; i<5; i++)
                {
                    stub_1A63(GB_VRAM_TO_GBA_VRAM((0x98EE)+i), 0x8E);
                }
            }
        }
    }
}


void stub_1CE3()
{
    //Unimplemented
}


void stub_1D26()
{
    //Unimplemented
}


void stub_1D38()
{
    //Unimplemented
}


void LoseHandler()
{
    memory[0xC200] = 0x80;
    memory[0xC210] = 0x80;
    DrawCurrentBlock_C010();
    DrawPreviewBlock_C020();
    
    hCurPieceState = 0x00;
    memory[0xFF9C] = 0x00;
    stub_22F3();
    
    FillPlayArea(0x87);
    
    gDelay = 0x46;
    hState = 0x0D;
}


void stub_1D61()
{
    //Unimplemented
}


void stub_1D81()
{
    //Unimplemented
}


void stub_1DDF()
{
    //Unimplemented
}


void stub_1E1B()
{
    if(gDelay)
        return;
    
    memory[0xC0C6] = 1;
    
    gDelay = 5;
}


void stub_1E29()
{
    //Unimplemented
}


void stub_1E8C()
{
    //Unimplemented
}


void stub_1E96()
{
    DrawCurrentBlock_C000(0x0A);
}


void stub_1E9C()
{
    //Unimplemented
}


void stub_1EF0()
{
    //Unimplemented
}


void stub_1F32()
{
    //Unimplemented
}


void stub_1F71()
{
    if(!hJoyPressed)
        return;
    
    hState = 2;
}


void GameOverTryAgainHandler()
{
    //Unimplemented
}


void CopyTilemapSectionWidth8(const u8 *src, u16 *dst, u32 height)
{
    for(int y=0; y<height; y++)
    {
        for(int x=0; x<0x08; x++)
        {
            *dst++ = *src++;
        }
        
        dst += 0x20-8; //-8 is for GBA
    }
}


void AddScoreForTetris()
{
    //Unverified
    if(memory[0xFFC0] != 0x37)
        return;
    
    if(hState)
        return;
    
    if(hBoardUpdateState != 0x05)
        return;
    
    u32 points;
    
    if(memory[0xC0AC])
    {
        points = 0x40;
        if(memory[0xC0AC + (5*1)])
        {
            points = 0x100;
            if(memory[0xC0AC + (5*2)])
            {
                points = 0x300;
                if(memory[0xC0AC + (5*3)])
                {
                    points = 0x1200;
                }
            }
        }
    }
    else
    {
        return;
    }
    
    int score = memory[0xC0A0] | memory[0xC0A1] << 8 | memory[0xC0A2] << 16;
    
    //This might need to be done once more?
    for(int i=0; i<hLevel; i++)
    {
        AddToScore(&score, points);
    }
    
    memory[0xC0A0] = (score >>  0) & 0xFF;
    memory[0xC0A1] = (score >>  8) & 0xFF;
    memory[0xC0A2] = (score >> 16) & 0xFF;
}


void FillPlayArea(u8 val)
{
    //Unimplemented - Partial
    hBoardUpdateState = 2;
    
    stub_2038(val);
}


void stub_2038(u8 val)
{
    for(int h=0; h<0x12; h++)
    {
        for(int i=0; i<10; i++)
        {
            memory[0xC802+i+(h*0x20-8)] = val;
        }
        
    }
}


void stub_204D()
{
    //TODO check that 0x16 is valid for GBA
    for(int h=0; h<2; h++)
    {
        for(int w=0; w<10; w++)
        {
            memory[0xCBC2+w+(h*0x16)] = 0x2F;
        }
        
    }
}


void GetNextPiece()
{
    memory[0xC200] = 0x00;
    wCurPieceY = 0x18;
    wCurPieceX = 0x3F;
    wCurPiece = wPreviewPiece;
    
    u8 masked_c = wPreviewPiece & 0xFC;
    u8 val = 0;
    
    if(hDemo)
    {
        //207F
        u16 adr = 0xC300 | memory[0xFFB0];
        val = memory[adr++];
        
        if(adr >= 0xC400)
        {
            adr = 0xC300;
        }
        
        memory[0xFFB0] = (adr >> 0) & 0xFF;
        
        if(memory[0xFFD3] != 0)
        {
            //2096
            memory[0xFFD3] |= 0x80;
        }
    }
    else
    {
        //207A
        if(memory[0xFFC5] == 0)
        {
            //209C
            u8 h = 3;
            u8 d = 0;
            while(1)
            {
                u8 div = REG_DIV;
                u8 tmp = 0;
                
                while(1)
                {
                    div--;
                    if(div == 0)
                        break;
                    
                    tmp++;
                    tmp++;
                    tmp++;
                    tmp++;
                    
                    if(tmp == 0x1C)
                        tmp = 0;
                }
                
                //20AF
                d = tmp;
                val = memory[0xFFAE];
                
                h--;
                if(h == 0)
                    break;
                
                u8 masked_a = (val | d | masked_c) & 0xFC;
                if(masked_a != masked_c)
                    break;
            }
            
            //20BD
            memory[0xFFAE] = d;
            debugPrintf("hNextPreviewPiece = %02X (%d)",d,d);
        }
    }
    
    //20C0
    wPreviewPiece = val;
    DrawPreviewBlock_C020();
    hRemainingFrameDelay = hLvlFrameDelay;
}


void stub_20CC()
{
    //Unimplemented
}


void HandleDrop()
{
    if((hJoyDown & (GBKEY_RIGHT|GBKEY_LEFT|GBKEY_DOWN)) == GBKEY_DOWN)
    {
        stub_20CC();
    }
    else
    {
        stub_20FF();
    }
}


void stub_20FF()
{
    //Unimplemented
}


void HandleFinishedRows()
{
    //Unimplemented
}


void stub_2240()
{
    if(hCurPieceState != 3)
        return;
    
    if(gDelay)
        return;
    
    u16 de = 0xC0A3;
    if(memory[0xFF9C] & 1)
    {
        //Happens when a line is cleared?
        //Moves things down one line?
        
        //228E
        do
        {
            u16 adr = (memory[de] << 8) | memory[de+1];
            de++;

            for(u32 i=0; i<10; i++)
            {
                //2298
                *GB_VRAM_TO_GBA_VRAM(adr+i-0x3000) = memory[adr+i];
            }
        } while (memory[++de]);
    }
    else
    {
        //2252
        if(memory[de] == 0)
        {
            GetNextPiece();
            
            //228A
            hCurPieceState = 0;
            return;
        }
        
        //2256
        do
        {
            u16 adr = ((memory[de]-0x30) << 8) | memory[de+1];
            u8 val = 0;
            de++;
            
            if(memory[0xFF9C] == 6)
            {
                val = 0x2F;
            }
            else
            {
                val = 0x8C;
            }
            
            for(u32 i=0; i<10; i++)
            {
                //2298
                *GB_VRAM_TO_GBA_VRAM(adr++) = val;
            }
        } while (memory[++de]);
    }
    
    memory[0xFF9C]++;
    
    if(memory[0xFF9C] == 7)
    {
        //2280
        memory[0xFF9C] = 0;
        gDelay = 13;
        hBoardUpdateState = 1;
        
        //228A
        hCurPieceState = 0;
    }
    else
    {
        //227A
        gDelay = 10;
    }
}


void MoveUpFinishedRows()
{
    //Unimplemented
}


void stub_22F3()
{
    for(int i=0; i<9; i++)
    {
        memory[0xC0A3+i] = 0;
    }
}


void UpdateBoardStage2()
{
    if(hBoardUpdateState != 0x02)
        return;
    
    //hl = $9A22
    //de = $CA22
    UpdateBoardRow(&memory[0xCA22], GB_VRAM_TO_GBA_VRAM(0x9A22));
}


void UpdateBoardStage3()
{
    if(hBoardUpdateState != 0x03)
        return;
    
    //hl = $9A02
    //de = $CA02
    UpdateBoardRow(&memory[0xCA02], GB_VRAM_TO_GBA_VRAM(0x9A02));
}


void UpdateBoardStage4()
{
    if(hBoardUpdateState != 0x04)
        return;
    
    //hl = $99E2
    //de = $C9E2
    UpdateBoardRow(&memory[0xCA02], GB_VRAM_TO_GBA_VRAM(0x99E2));
}


void UpdateBoardStage5()
{
    if(hBoardUpdateState != 0x05)
        return;
    
    //hl = $99C2
    //de = $C9C2
    UpdateBoardRow(&memory[0xC9C2], GB_VRAM_TO_GBA_VRAM(0x99C2));
}


void UpdateBoardStage6()
{
    if(hBoardUpdateState != 0x06)
        return;
    
    //hl = $99A2
    //de = $C9A2
    UpdateBoardRow(&memory[0xC9A2], GB_VRAM_TO_GBA_VRAM(0x99A2));
}


void UpdateBoardStage7()
{
    if(hBoardUpdateState != 0x07)
        return;
    
    //hl = $9982
    //de = $C982
    UpdateBoardRow(&memory[0xC982], GB_VRAM_TO_GBA_VRAM(0x9982));
}


void UpdateBoardStage8()
{
    if(hBoardUpdateState != 0x08)
        return;
    
    //hl = $9962
    //de = $C962
    UpdateBoardRow(&memory[0xC962], GB_VRAM_TO_GBA_VRAM(0x9962));
    
    if(memory[0xFFC5])
    {
        //2375
        if(hState != 0x1A)
        {
            if(memory[0xFFD4])
            {
                memory[0xDFE0] = 5;
            }
        }
    }
    else
    {
        //236D
        if(!hState)
        {
            memory[0xDFF8] = 1;
        }
    }
}


void UpdateBoardStage9()
{
    if(hBoardUpdateState != 0x09)
        return;
    
    //hl = $9942
    //de = $C942
    UpdateBoardRow(&memory[0xC942], GB_VRAM_TO_GBA_VRAM(0x9942));
}


void UpdateBoardStage10()
{
    if(hBoardUpdateState != 0x0A)
        return;
    
    //hl = $9922
    //de = $C922
    UpdateBoardRow(&memory[0xC922], GB_VRAM_TO_GBA_VRAM(0x9922));
}


void UpdateBoardStage11()
{
    if(hBoardUpdateState != 0x0B)
        return;
    
    //hl = $9902
    //de = $C902
    UpdateBoardRow(&memory[0xC902], GB_VRAM_TO_GBA_VRAM(0x9902));
}


void UpdateBoardStage12()
{
    if(hBoardUpdateState != 0x0C)
        return;
    
    //hl = $98E2
    //de = $C8E2
    UpdateBoardRow(&memory[0xC8E2], GB_VRAM_TO_GBA_VRAM(0x98E2));
}


void UpdateBoardStage13()
{
    if(hBoardUpdateState != 0x0D)
        return;
    
    //hl = $98C2
    //de = $C8C2
    UpdateBoardRow(&memory[0xC8C2], GB_VRAM_TO_GBA_VRAM(0x98C2));
}


void UpdateBoardStage14()
{
    if(hBoardUpdateState != 0x0E)
        return;
    
    //hl = $98A2
    //de = $C8A2
    UpdateBoardRow(&memory[0xC8A2], GB_VRAM_TO_GBA_VRAM(0x98A2));
}


void UpdateBoardStage15()
{
    if(hBoardUpdateState != 0x0F)
        return;
    
    //hl = $9882
    //de = $C882
    UpdateBoardRow(&memory[0xC882], GB_VRAM_TO_GBA_VRAM(0x9882));
}


void UpdateBoardStage16()
{
    if(hBoardUpdateState != 0x10)
        return;
    
    //hl = $9862
    //de = $C862
    UpdateBoardRow(&memory[0xC862], GB_VRAM_TO_GBA_VRAM(0x9862));
    
    stub_24AB();
}


void UpdateBoardStage17()
{
    if(hBoardUpdateState != 0x11)
        return;
    
    //hl = $9842
    //de = $C842
    UpdateBoardRow(&memory[0xC842], GB_VRAM_TO_GBA_VRAM(0x9842));
    
    //hl = $9C6D
    PrintIngameScore(GB_VRAM_TO_GBA_VRAM(0x9C6D));
    
    memory[0xFFE0] = 1;
}


void UpdateBoardStage18()
{
    if(hBoardUpdateState != 0x12)
        return;
    
    //hl = $9822
    //de = $C822
    UpdateBoardRow(&memory[0xC822], GB_VRAM_TO_GBA_VRAM(0x9822));
    
    //hl = $986D
    PrintIngameScore(GB_VRAM_TO_GBA_VRAM(0x986D));
}


void UpdateBoardStage19()
{
    if(hBoardUpdateState != 0x13)
        return;
    
    wPreventHoldDown = hBoardUpdateState;
    
    //hl = $9802
    //de = $C802
    UpdateBoardRow(&memory[0xC802], GB_VRAM_TO_GBA_VRAM(0x9802));
    
    hBoardUpdateState = 0x00;
    
    if(memory[0xFFC5])
    {
        //2447
        if(hState)
            return;
    }
    else
    {
        //248F
        if(hState != 0x1A)
        {
            return;
        }
        
        if(memory[0xFFD4])
        {
            //2497
            memory[0xFFD4] = 0;
            return;
        }
    }    
    
    //2449
    u16 *tilemap = GB_VRAM_TO_GBA_VRAM(0x994E);
    vu8 *score = &memory[0xFF9F];
    u16 numBytes = 0x02;
    
    if(memory[0xFFC0] != 0x37)
    {
        tilemap = GB_VRAM_TO_GBA_VRAM(0x9950);
        score = &hNumFinishedLines;
        numBytes = 0x01;
    }
    
    //245F
    DrawScore(score, tilemap, numBytes);
    
    if(memory[0xFFC0] == 0x37)
    {
        GetNextPiece();
        return;
    }
    
    //2468
    if(hNumFinishedLines)
    {
        GetNextPiece();
        return;
    }
    
    //246D
    gDelay = 0x64;
    memory[0xDFE8] = 0x02;
    
    if(!memory[0xFFC5])
    {
        //247E
        if(hTypeBSelectedLevel == 0x09)
        {
            hState = 0x22;
        }
        else
        {
            hState = 0x05;
        }
    }
    else
    {
        //247B
        memory[0xFFD5] = memory[0xFFC5];
    }
}


void PrintIngameScore(u16 *tilemap)
{
    if(hState)
        return;
    
    if(memory[0xFFC0] == 0x37)
        return;
    
    //hl = $C0A2
    stub_2A7E(&memory[0xC0A2], tilemap);
}


void stub_24AB()
{
    //Unimplemented
}


void UpdateBoardRow(vu8 *src, u16 *dst)
{
    //Unimplemented
    //DE = src
    //HL = dst
    
    for(int i=0; i<10; i++)
    {
        *dst++ = *src++;
    }
    
    hBoardUpdateState++;
}


void HandleRotationAndShift()
{
    //Unimplemented - Partial   
    memory[0xFFA0] = wCurPiece;
    
    if(hJoyPressed & GBKEY_B)
    {
        //2534
        if((wCurPiece & 3) == 3)
        {
            //253E
            wCurPiece &= 0xFC;
        }
        else
        {
            //253B
            wCurPiece++;
        }
        
        //2542
        memory[0xDFE0] = 3;
        DrawCurrentBlock_C010();
        
        u8 tmp = CheckSpriteCollision();
        if(tmp)
        {
            //2550
            memory[0xDFE0] = 0;
            wCurPiece = memory[0xFFA0];
            DrawCurrentBlock_C010();
        }
    }
    else if(hJoyPressed & GBKEY_A)
    {
        //2526
        if((wCurPiece & 3) == 0)
        {
            //252B
            wCurPiece |= 3;
        }
        else
        {
            //252B
            wCurPiece--;
        }
        
        //2542
        memory[0xDFE0] = 3;
        DrawCurrentBlock_C010();
        
        u8 tmp = CheckSpriteCollision();
        if(tmp)
        {
            //2550
            memory[0xDFE0] = 0;
            wCurPiece = memory[0xFFA0];
            DrawCurrentBlock_C010();
        }
    }
    
    //255D
    memory[0xFFA0] = wCurPieceX;
    
    u8 a = 0;
    
    if(hJoyPressed & GBKEY_RIGHT)
    {
        a = 0x17; 
        
        //257B 
        hButtonHoldCounter = a;
        wCurPieceX += 8;
        DrawCurrentBlock_C010();
        memory[0xDFE0] = 4;
        
        u8 tmp = CheckSpriteCollision();
        if(tmp)
        {
            //258E
            memory[0xDFE0] = 0;
            wCurPieceX = memory[0xFFA0];
            DrawCurrentBlock_C010();
            hButtonHoldCounter = 1;
        }
    }
    else if(hJoyDown & GBKEY_RIGHT)
    {
        //2573
        hButtonHoldCounter--;
        if(hButtonHoldCounter)
            return;
        
        a = 0x09;
        
        //257B 
        hButtonHoldCounter = a;
        wCurPieceX += 8;
        DrawCurrentBlock_C010();
        memory[0xDFE0] = 4;
        
        u8 tmp = CheckSpriteCollision();
        if(tmp)
        {
            //258E
            memory[0xDFE0] = 0;
            wCurPieceX = memory[0xFFA0];
            DrawCurrentBlock_C010();
            hButtonHoldCounter = 1;
        }
    }
    else if(hJoyPressed & GBKEY_LEFT)
    {
        a = 0x17; 
        
        //25B2 
        hButtonHoldCounter = a;
        wCurPieceX -= 8;
        DrawCurrentBlock_C010();
        memory[0xDFE0] = 4;
        
        u8 tmp = CheckSpriteCollision();
        if(tmp)
        {
            //258E
            memory[0xDFE0] = 0;
            wCurPieceX = memory[0xFFA0];
            DrawCurrentBlock_C010();
            hButtonHoldCounter = 1;
        }
    }
    else if(hJoyDown & GBKEY_LEFT)
    {
        //2573
        hButtonHoldCounter--;
        if(hButtonHoldCounter)
            return;
        
        a = 0x09;
        
        //257B 
        hButtonHoldCounter = a;
        wCurPieceX -= 8;
        DrawCurrentBlock_C010();
        memory[0xDFE0] = 4;
        
        u8 tmp = CheckSpriteCollision();
        if(tmp)
        {
            //258E
            memory[0xDFE0] = 0;
            wCurPieceX = memory[0xFFA0];
            DrawCurrentBlock_C010();
            hButtonHoldCounter = 1;
        }
    }
    else
    {
        hButtonHoldCounter = 0x17;
    }
}


u8 CheckSpriteCollision()
{
    u16 adr = 0xC010;
    for(u32 i=0; i<4; i++)
    {
        memory[0xFFB2] = memory[adr++];
        
        if(memory[adr] == 0)
        {
            memory[0xFF9B] = 0;
            return 0;
        }
        memory[0xFFB3] = memory[adr++];
        
        u16 ptr = stub_2A2B();
        if(memory[ptr+0x3000] != 0x2F)
        {
            memory[0xFF9B] = 1;
            return 1;
        }
        
        adr++;
        adr++;
    }
    
    memory[0xFF9B] = 0;
    return 0;
}


void LockCurPiece()
{
    //This seems to be related to checking if a block has landed?
    if(hCurPieceState != 1)
        return;
    
    u16 adr = 0xC010;
    memory[0xFFB2] = memory[adr++];
    
    for(int i=0; i<4; i++)
    {
        if(memory[adr] == 0)
        {
            break;
        }
        
        memory[0xFFB3] = memory[adr++];
        
        u16 ptr = stub_2A2B();
        
        while(REG_DISPSTAT & 3);
        
        *GB_VRAM_TO_GBA_VRAM(ptr) = memory[adr];
        memory[ptr+0x3000] = memory[adr++];
    }
    
    hCurPieceState = 2;
    memory[0xC200] = 0x80;
}


void stub_262D()
{
    //Unimplemented
}


void stub_26A5()
{
    for(int i=0; i<0x1B; i++)
    {
        memory[0xC0AC+i] = 0;
    }
    
    for(int i=0; i<3; i++)
    {
        memory[0xC0A0+i] = 0;
    }
}


void stub_26B9()
{
    //Unimplemented - Unused?
}


void DrawCurrentBlock_C000_R2()
{
    debugPrint("DrawCurrentBlock_C000_R2 called.");
    DrawCurrentBlock_C000(2);
}


void DrawCurrentBlock_C000(u8 recursion_level)
{
    debugPrint("DrawCurrentBlock_C000 called.");
    
    UpdateBlocks_Recursion_Level = recursion_level;
    curBlock_Dest_Low = 0;
    curBlock_Dest_High = 0xC0;
    
    UpdateBlocks(&memory[0xC200]);
}


void DrawCurrentBlock_C010()
{
    debugPrint("DrawCurrentBlock_C010 called.");
    
    UpdateBlocks_Recursion_Level = 1;
    curBlock_Dest_Low = 0x10;
    curBlock_Dest_High = 0xC0;

    UpdateBlocks(&memory[0xC200]);
}


void DrawPreviewBlock_C020()
{
    debugPrint("DrawPreviewBlock_C020 called.");
    UpdateBlocks_Recursion_Level = 1;
    curBlock_Dest_Low = 0x20;
    curBlock_Dest_High = 0xC0;
    
    UpdateBlocks(&memory[0xC210]);
}


void stub_26FD()
{
    //Unimplemented
}


void stub_270A(vu8 *dst, const u8 *src)
{
    while(*src != 0xFF)
    {
        *dst++ = *src++;
    }
}


void Stub_Interrupt_Handler()
{
    //This function does nothing
}


void stub_27E9()
{
    //Unimplemented
}


void stub_27EC(u16 *dst)
{
    for(int i=0; i<0x400; i++)
    {
        *dst-- = 0x2F;
    }
}


void CopyData()
{
    //Unimplemented
}


//2Bpp Planar
void CopyDataFrom2Bpp(u32 *dst, const u8 *src, u32 len)
{
    for(int i=0; i<len; i+=2)
    {
        u32 val = src[i];
        u32 val2 = src[i+1];
        u32 temp = 0;
        
        for(int j=0; j<8; j++)
        {
            temp |= ((val&1)|(val2&1)<<1) << ((4*(7-j)));
            
            val >>= 1;
            val2 >>= 1;
        }
        
        *dst++ = temp;
    }
}


void LoadFontData()
{
    LoadFontGlyphs((u32 *)CHAR_BASE_ADR(0));
    //Duplicate for OAM as GBA can't use bg tiles as sprites :(
    LoadFontGlyphs((u32 *)CHAR_BASE_ADR(4));
    
    CopyDataFrom2Bpp((u32 *)(CHAR_BASE_ADR(0)+0x4E0), TitleScreen_Tiles_2BPP, 0xA0);
    CopyDataFrom2Bpp((u32 *)(CHAR_BASE_ADR(0)+0x600), HeadingBoxTiles, 0xD00);
}


u32* LoadFontGlyphs(u32 *dst)
{
    debugPrint("LoadFontGlyphs called");
    for(int i=0; i<sizeof(Font_1BPP); i++)
    {
        u32 val = Font_1BPP[i];
        u32 temp = 0;
        
        for(int j=0; j<7; j++)
        {
            if(val&(1<<(7-j)))
                temp |= 3 << ((4*j));
        }
        
        *dst++ = temp;
    }
    
    return dst;
}

void LoadTitleScreenTiles()
{
    u32 *dst = LoadFontGlyphs((u32 *)CHAR_BASE_ADR(0));
    CopyDataFrom2Bpp(dst, TitleScreen_Tiles_2BPP, sizeof(TitleScreen_Tiles_2BPP));
    
    //Duplicate for OAM as GBA can't use bg tiles as sprites :(
    dst = LoadFontGlyphs((u32 *)CHAR_BASE_ADR(4));
    CopyDataFrom2Bpp(dst, TitleScreen_Tiles_2BPP, sizeof(TitleScreen_Tiles_2BPP));
}


void CopyDataTo8000_Length1000(const u8 *src)
{
    //This function does nothing
    CopyDataTo8000(src, 0x1000);
}


void CopyDataTo8000(const u8 *src, u32 len)
{
    CopyDataFrom2Bpp((u32 *)(CHAR_BASE_ADR(0)), src, len);
    
    //Duplicate for OAM as GBA can't use bg tiles as sprites :(
    CopyDataFrom2Bpp((u32 *)(CHAR_BASE_ADR(4)), src, len); 
}


void stub_283E()
{
    //Unimplemented
}

void CopyTilemapSection_Height_12_Dest_9800(u8 *src)
{
    CopyTilemapSection_Height_12(src, GB_VRAM_TO_GBA_VRAM(0x9800));
}


void CopyTilemapSection_Height_12(u8 *src, u16 *dst)
{
    CopyTilemapSection(src, dst, 0x12);
}


void CopyTilemapSection(u8 *src, u16 *dst, u32 height)
{
    for(int y=0; y<height; y++)
    {
        for(int x=0; x<0x14; x++)
        {
            *dst++ = *src++;
        }
        
        dst += 12;
    }
}


void stub_2858(u8 *src, vu8 *dst)
{
    int src_idx = 0, dst_idx = 0;
    while(1)
    {
        for(int i=0; i<10; i++)
        {
            u8 val = src[src_idx];
            if(val == 0xFF)
            {
                hBoardUpdateState = 2;
                return;
            }
            
            dst[dst_idx++] = val;
            src_idx++;
        }
        
        dst_idx += 0x20;
        
    }
}


void DisableLCD()
{
    //Unimplemented
}


void ReadJoypad()
{
    //Unimplemented
    scanKeys();
    
    hJoyPressed = hJoyDown;
    
    u32 keys = keysDown();
    hJoyDown = ((keys&0xF0)>>4) | ((keys&0xF)<<4);
}


u16 stub_2A2B()
{
    //Unimplemented
    //Returns a value in HL
    
    u16 val = (memory[0xFFB2] - 16) / 8;
    u16 adr = 0x9800;
    
    //basically val * 0x20
    for(int i=0; i<0x20; i++)
        adr += val;
    
    u16 val2 = (memory[0xFFB3] - 8) / 8;
    
    adr += val2;
    
    memory[0xFFB5] = (adr >> 8) & 0xFF;
    memory[0xFFB4] = (adr >> 0) & 0xFF;
    
    return adr;
}


void stub_2A58()
{
    //Unimplemented
}


void stub_2A7E(vu8 *score, u16 *tilemap)
{
    if(!memory[0xFFE0])
        return;
    
    DrawScore_C3(score, tilemap);
}


void DrawScore_C3(vu8 *score, u16 *tilemap)
{
    DrawScore(score, tilemap, 3);
}


void DrawScore(vu8 *score, u16 *tilemap, u8 numBytes)
{
    //Unimplemented
}

void OAM_DMA_Transfer()
{
    //debugPrint("OAM_DMA_Transfer called.");
    for(int i=0; i<0xA0; i+=4)
    {
        u8 Y = memory[0xC000+i] - 16;
        u8 X = memory[0xC001+i] - 8;
        u8 Tile = memory[0xC002+i];
        u8 Flags = memory[0xC003+i];
        
        //On gameboy if X/Y are 0 its hidden it doesn't work that way on GBA
        if(Y==0 && X==0 && Tile==0 && Flags==0)
        {
            Y = 240;
            X = 160;
        }
        
        OAM[i/4].attr0 = ATTR0_COLOR_16 | ATTR0_SQUARE | OBJ_Y(Y); 
        OAM[i/4].attr1 = OBJ_X(X) | ((Flags&0x60)<<7); 
        OAM[i/4].attr2 = OBJ_CHAR(Tile) | OBJ_PALETTE((Flags&0x10)>>4) | ATTR2_PRIORITY(0); 
        
        if(Flags & 0x80)
        {
            debugPrint("OAM_DMA_Transfer BG Prio 0x80.");
        }
    }
}


void UpdateBlocks(vu8 *src)
{
    //Unimplemented - Partial    
    debugPrint("UpdateBlocks called.");
    
    vu8 *temp_src = src;
    
    if(*src)
    {
        if(*src == 0x80)
        {
            memory[0xFF95] = *src;
        }
        else
        {
            temp_src += 0x10;
            UpdateBlocks_Recursion_Level--;
            s8 temp_r = (s8)UpdateBlocks_Recursion_Level;
            if(temp_r > 0)
            {
                debugPrintf("UpdateBlocks_Recursion_Level = %02X", UpdateBlocks_Recursion_Level);
                UpdateBlocks(temp_src);
                return;
            }
            else
            {
                debugPrint("UpdateBlocks finished.");
                return;
            }
        }
    }

    //Copy loop
    //setup 0xFF86 through 0xFF8D
    for(int i=0; i<7; i++)
    {
        memory[0xFF86+i] = *src++;
    }
    
    u8 tile = curPiece_Tile;
    
    //debugPrintf("tile = %02X", tile);
    
    if(tile > sizeof(BlockInfoList))
    {
        debugPrintf("tile is too high %02X", tile);
        return;
    }
        
    //2B05
    const sBlockInfo *blockInfo = BlockInfoList[tile];
    const sTileInfo *tileInfo = blockInfo->tilemap;
    u8 *tileData = (u8*)tileInfo->data - 1;
    u8 *rotation_info = (u8*)tileInfo->rotation_info;
    
    //debugPrintf("tileData = %08X", tileData + 1);
    
    //debugPrintf("rotation_info = %08X", rotation_info);
    
    memory[0xFF90] = blockInfo->flagsL;
    memory[0xFF91] = blockInfo->flagsH;
    
    while(1)
    {
        //2B20
        tileData++;
        memory[0xFF94] = memory[0xFF8C];
        
        //debugPrintf("*tileData = %02X", *tileData);
        
        if(*tileData == 0xFF)
        {
            memory[0xFF95] = 0;
            
            temp_src += 0x10;
            UpdateBlocks_Recursion_Level--;
            s8 temp_r = (s8)UpdateBlocks_Recursion_Level;
            if(temp_r > 0)
            {
                debugPrintf("UpdateBlocks_Recursion_Level = %02X", UpdateBlocks_Recursion_Level);
                UpdateBlocks(temp_src);
                return;
            }
            else
            {
                debugPrint("UpdateBlocks finished.");
                return;
            }
        }
        else if(*tileData == 0xFD)
        {
            //2B2E
            memory[0xFF94] = memory[0xFF8C] ^ 0x20;
            tileData++;
        }
        else if(*tileData == 0xFE)
        {
            //2B3C
            //2B38
            //rotation_info++;
            //rotation_info++;
            continue;
        }
        
        //2B40
        //de = rotation_info
        u8 b,c;
        curPiece_Tile = *tileData;
        b = memory[0xFF87];
        c = *rotation_info++;
        
        //Adjust Y position - TODO Fix
        //debugPrintf("c = %02X", c);
        //debugPrintf("memory[0xFF87] = %02X", memory[0xFF87]);
        //debugPrintf("memory[0xFF88] = %02X", memory[0xFF88]);
        //debugPrintf("memory[0xFF8B] = %02X", memory[0xFF8B]);
        //debugPrintf("memory[0xFF90] = %02X", memory[0xFF90]);
        //debugPrintf("memory[0xFF91] = %02X", memory[0xFF91]);
        if((memory[0xFF8B] & (1<<6)))
        {
            //2B53
            curPiece_Y = b - memory[0xFF90] - 8;
        }
        else
        {
            //2B4D
            u32 temp_y = memory[0xFF90] + b + c;
            
            if(temp_y > 0x100)
               temp_y = (temp_y & 0xFF) + 1; 
            curPiece_Y = temp_y;
        }
        
        //debugPrintf("curPiece_Y = %02X", curPiece_Y);
        
        //rotation_info++;
        
        b = memory[0xFF88];
        c = *rotation_info++;
        
        //Adjust X position - TODO Fix
        if((memory[0xFF8B] & (1<<5)))
        {
            //2B72
            curPiece_X = b - memory[0xFF91] - c - 8;
        }
        else
        {
            //2B6E
            u32 temp_x = memory[0xFF91] + b + c;
            
            if(temp_x > 0x100)
               temp_x = (temp_x & 0xFF) + 1; 
            curPiece_X = temp_x;
        }
        
        //debugPrintf("curPiece_X = %02X", curPiece_X);        
        //debugPrintf("curPiece_Tile = %02X", curPiece_Tile);
        
        //2B7E
        u16 adr = curBlock_Dest_High << 8 | curBlock_Dest_Low;
        //debugPrintf("adr = %04X", adr);
        vu8 *dst = &memory[adr];
        if(!memory[0xFF95])
        {
            //If not hidden
            *dst++ = curPiece_Y;
        }
        else
        {
            //If Hidden draw off screen
            *dst++ = 0xFF;
        }
        *dst++ = curPiece_X;
        *dst++ = curPiece_Tile;
        *dst++ = memory[0xFF94] | memory[0xFF8B] | memory[0xFF8A];
        
        adr += 4;
        curBlock_Dest_High = (adr & 0xFF00) >> 8;
        curBlock_Dest_Low  = (adr & 0x00FF);
    }
    
}


void stub_6552()
{
    //This does nothing
}


void UpdateAudio()
{
    //Unimplemented
}


//TO Add to header
int stub_6603()
{
    return memory[0xDFF1] == 1;
}


int stub_6609()
{
    return memory[0xDFF1] == 5;
}


int stub_660F()
{
    return memory[0xDFF1] == 7;
}


void stub_6624(vu8 *de)
{
    //Unimplemented
}


void stub_662C()
{
    //Unimplemented
}


void stub_6641(vu8 *de)
{
    //Unimplemented
}


void stub_6649()
{
    //Unimplemented
}


void stub_664E()
{
    memory[0xDFE1] = 0;
    REG_NR10 = 0;
    REG_NR12 = 0x08;
    REG_NR14 = 0x80;
    memory[0xDFE1] = memory[0xDFE1] & ~(1<<7);
}


void stub_666C(vu8 *de)
{
    //Unimplemented
}


void stub_6672()
{
    //Unimplemented
}


void stub_66A3(vu8 *de)
{
    //Unimplemented - Partial
    
    if(stub_6603())
        return;
    
    if(stub_660F())
        return;
    
    if(stub_6609())
        return;
    
    //a = $2
    //hl = $669E
    stub_6967();
}


void stub_66BC(vu8 *de)
{
    //Unimplemented
}


void stub_66C4()
{
    //Unimplemented - Partial
    
    //de = something
    stub_69BC();
    
    memory[0xDFE4]++;
    if(memory[0xDFE4] == 3)
    {
        stub_664E();
    }
}


void stub_66F4(vu8 *de)
{
    //Unimplemented
}


void stub_6704()
{
    //Unimplemented
}


void stub_673D(vu8 *de)
{
    //Unimplemented
}


void stub_6751()
{
    //Unimplemented
}


void stub_6771(vu8 *de)
{
    //Unimplemented
}


void stub_67DA()
{
    //Unimplemented
}


void stub_67E2()
{
    //Unimplemented
}


void stub_67EA()
{
    //Unimplemented
}


void stub_6811()
{
    //Unimplemented
}


void stub_6819()
{
    //Unimplemented
}


void stub_6821()
{
    //Unimplemented
}
//END

void stub_683D()
{
    //Unimplemented
}


void stub_6854()
{
    //Unimplemented
}


void stub_6879()
{
    if(memory[0xDFF0] == 1)
    {
        stub_68A8();
    }
    else if(memory[0xDFF0] == 2)
    {
        stub_683D();
    }
    
    if(memory[0xDFF1] == 1)
    {
        stub_68F3();
    }
    else if(memory[0xDFF1] == 2)
    {
        stub_6854();
    }
}


void stub_68A8()
{
    //Unimplemented - Partial
    
    //hl = $6EDA
    stub_693E();
    
    memory[0xDFF6] = byte_6897[0];
    memory[0xDFF5] = 1;
    SetupChannel3Registers(byte_6894);
}


void stub_68C0()
{
    memory[0xDFF5] = 0;
    memory[0xDFF6] = byte_689C[0];
    SetupChannel3Registers(byte_6899);
}


void stub_68D1()
{
    memory[0xDFF5] = 1;
    memory[0xDFF6] = byte_68A1[0];
    SetupChannel3Registers(byte_689E);
}


void stub_68E2()
{
    memory[0xDFF5] = 2;
    memory[0xDFF6] = byte_68A6[0];
    SetupChannel3Registers(byte_68A3);
}


void stub_68F3()
{
    //Unimplemented
}


void stub_691F()
{
    //Unimplemented
}


void stub_693E()
{
    //Unimplemented
}


void stub_6967()
{
    //Unimplemented
}


void SetupChannel1Registers(u8 *src)
{
    REG_NR10 = *src++;
    REG_NR11 = *src++;
    REG_NR12 = *src++;
    REG_NR13 = *src++;
    REG_NR14 = *src++;
}


void SetupChannel2Registers(u8 *src)
{
    REG_NR21 = *src++;
    REG_NR22 = *src++;
    REG_NR23 = *src++;
    REG_NR24 = *src++;
}


void SetupChannel3Registers(u8 *src)
{
    REG_NR30 = *src++;
    REG_NR31 = *src++;
    REG_NR32 = *src++;
    REG_NR33 = *src++;
    REG_NR34 = *src++;
}


void SetupChannel4Registers(u8 *src)
{
    REG_NR41 = *src++;
    REG_NR42 = *src++;
    REG_NR43 = *src++;
    REG_NR44 = *src++;
}


void CopySoundRegisters()
{
    //Unused in this port..
}


//Sound struct
const SoundHandler1 off_6500[] = 
{
    &stub_6624,
    &stub_6641,
    &stub_673D,
    &stub_66A3,
    &stub_6771,
    &stub_66F4,
    &stub_666C,
    &stub_66BC
};

const SoundHandler1 off_6510[] = 
{
    &stub_662C,
    &stub_6649,
    &stub_6751,
    &stub_6649,
    &stub_6649,
    &stub_6704,
    &stub_6672,
    &stub_66C4,
};


SoundHandler1 stub_69A9(const SoundHandler1 handlers[], vu8 **de, u8 a)
{
    de++;
    memory[0xDF71] = a;
    return stub_69AD(handlers, de,a);
}


SoundHandler1 stub_69AD(const SoundHandler1 handlers[], vu8 **de, u8 a) 
{
    de++;
    a--;
    //a * = 2;
    return *handlers[a];
}

u8 *stub_69AD_2(u8 *pointers[], vu8 **de, u8 a)
{
    de++;
    a--;
    //a * = 2;
    return pointers[a];
}


void stub_69BC()
{
    //Unimplemented
}

//Copy from hl to sound wave pattern ram
void stub_69C9(u8 *src)
{
    for(int i=0; i<0x10; i++)
    {
        REG_WAVERAM[i] = *src++;
    }
}


void ResetSound()
{
    memory[0xDFE1] = 0;
    memory[0xDFE9] = 0;
    memory[0xDFF1] = 0;
    memory[0xDFF9] = 0;
    memory[0xDF9F] = 0;
    memory[0xDFAF] = 0;
    memory[0xDFBF] = 0;
    memory[0xDFCF] = 0;
    REG_NR51 = 0xFF;
    memory[0xDF78] = 0;
    
    stub_69F8();
}


void stub_69F8()
{
    REG_NR12 = 8;
    REG_NR22 = 8;
    REG_NR42 = 8;
    
    REG_NR14 = 0x80;
    REG_NR24 = 0x80;
    REG_NR44 = 0x80;
    
    REG_NR10 = 0;
    REG_NR30 = 0;
}

void stub_6A0E()
{
    //Unimplemented
    
    vu8 *de = &memory[0xDFE0];
    
    if(*de)
    {
        //6A15
        memory[0xDF9F] |= (1 << 7);
        
        stub_69A9(off_6500, &de, *de)(de);
    }
    else
    {
        //6A21
        de++;
        if(*de)
        {
            stub_69AD(off_6510, &de, *de)(de);
        }
    }
}


void stub_6A2E()
{
    //Unimplemented - Partial
    if(memory[0xDFF8] == 0)
    {
        //6A41
    }
    else
    {
        //6A35
    }
}


void stub_6A4E()
{
    ResetSound();
}


void stub_6A52()
{
    //Unimplemented - Partial just call to stub_69AD to go
    if(memory[0xDFE8] == 0)
        return;
    
    if(memory[0xDFE8] == 0xFF)
    {
        stub_6A4E();
        return;
    }
    
    memory[0xDFE9] = memory[0xDFE8];
    
    //ld      b, a
    //ld      hl, off_6530
    //and     $1F
    //unused args?
    //stub_69AD_2();
    
    stub_6B44();
    
    stub_6A6D();
}


void stub_6A6D()
{
    u8 temp = memory[0xDFE9];
    if(!temp)
        return;
    
    u8 *hl = (u8 *)byte_6AEF;
    
    while(temp--)
    {
        hl += 4;
    }
    
    memory[0xDF78] = *hl++;
    memory[0xDF76] = *hl++;
    memory[0xDF79] = *hl++;
    memory[0xDF7A] = *hl++;
    memory[0xDF75] = 0;
    memory[0xDF77] = 0;
}


void stub_6A96()
{
    //Unimplemented
}


void stub_6B33()
{
    //Unimplemented
}


void stub_6B3E()
{
    //Unimplemented
}


void stub_6B44()
{
    //Unimplemented
}


void stub_6BEA()
{
    //Unimplemented
}


void stub_6BF6()
{
    //Unimplemented
}


void stub_6BFF()
{
    //Unimplemented
}


void stub_6C75()
{
    //Unimplemented
}


void stub_6D8F()
{
    //Unimplemented
}


void stub_6D98()
{
    //Unimplemented
}


void j_UpdateAudio()
{
    UpdateAudio();
}


void j_ResetSound()
{
    ResetSound();
}


