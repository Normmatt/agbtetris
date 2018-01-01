
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

void sub_153()
{
    //Unimplemented - Unused?
    sub_2A2B();
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
    sub_18E();
    
    memory[0xFFCC] = 1;
}


void sub_18E()
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


void sub_1C7()
{
    //Unimplemented
}


void sub_1DD()
{
    //Unimplemented
}


void sub_1F3()
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
    
    sub_2240();
    sub_242C();
    sub_2417();
    sub_23FE();
    sub_23EC();
    sub_23DD();
    sub_23CE();
    sub_23BF();
    sub_23B0();
    sub_23A1();
    sub_2392();
    sub_2383();
    sub_2358();
    sub_2349();
    sub_233A();
    sub_232B();
    sub_231C();
    sub_230D();
    sub_22FE();
    sub_1F32();
    OAM_DMA_Transfer();
    sub_192E();
    
    if (memory[0xC0CE] != 0)
    {
        if(memory[0xFF98] == 0x3)
        {
            //hl = $986D
            sub_249B((u16*)(VRAM+0x9800 + (0x6D*2)));
            memory[0xFFE0] = 1;
            //hl = $9C6D
            sub_249B((u16*)(VRAM+0x9800 + (0x46D*2)));
            memory[0xC0CE] = 0;
        }
    }
    
    memory[0xC0CE]++;
    REG_BG0HOFS = 0;
    REG_BG0VOFS = 0;
    VBlank_Occured = 1;    
}


void GB_Init()
{
    debugPrint("GB_Init called");
    
    for(int i=0; i<16; i++)
        memory[0xDFFF-i] = 0;
    
loop:
    // Disable Interrupts
    REG_IME = 0;
    
    irqEnable(IRQ_VBLANK);
    
    REG_BG0HOFS = 0;
    REG_BG0VOFS = 0;
    
    memory[0xFFA4] = 0;
    
    REG_DISPCNT = MODE_0 | BG0_ENABLE | OBJ_ON;// | WIN0_ON;
    REG_BG0CNT = BG_SIZE_0 | BG_MAP_BASE(0x9800/0x800); //BG MAP is at 0x06006000
    
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
    
    sub_27E9();
    ResetSound();
    
    irqEnable(IRQ_VBLANK);
    irqEnable(IRQ_SERIAL);
    
    memory[0xFFC0] = 0x37;
    memory[0xFFC1] = 0x1C;
    gState = 0x24;
    
    //Turn display on
    REG_DISPCNT = MODE_0 | BG0_ENABLE | OBJ_ON | WIN0_ON;
    
    // Enable Interrupts
    REG_IME = 1;
    
    REG_WININ = 0x11; //BG0 + OBJ
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
            goto loop;
        
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
        while (VBlank_Occured == 0);
        VBlank_Occured = 0;
    }
}

Handler state_handlers[] = {
    &sub_1C29,
    &LoseHandler,
    &sub_12A8,
    &sub_12DF,
    &sub_1D61,
    &sub_1D81,
    &sub_419,
    &sub_4E6,
    &HandleGameTypeMusicScreen,
    &stub_14F0,
    &sub_1A6B,
    &sub_1E1B,
    &sub_1F71,
    &GameOverTryAgainHandler,
    &sub_1589,
    &sub_1514,
    &sub_15DF,
    &sub_1623,
    &sub_168D,
    &sub_16DE,
    &sub_174F,
    &sub_1977,
    &sub_6E4,
    &sub_799,
    &sub_892,
    &sub_953,
    &sub_B95,
    &sub_D4F,
    &sub_B41,
    &sub_D96,
    &sub_E87,
    &sub_1176,
    &sub_DFD,
    &sub_EEE,
    &sub_1E29,
    &sub_1E9C,
    &InitCopyrightScreen,
    &DelayStateHandler,
    &InitRocketScreen,
    &HandleRocketScreen,
    &sub_1260,
    &sub_1280,
    &sub_634,
    &sub_664,
    &sub_1317,
    &sub_1369,
    &sub_1388,
    &sub_13B5,
    &sub_13CB,
    &sub_13E2,
    &sub_1419,
    &sub_1449,
    &sub_137F,
    &stub_283E,
};

void GotoSpecificStateHandler(u32 idx)
{
    debugPrintf("GotoSpecificStateHandler %d",idx);
    state_handlers[idx]();
}

void GotoStateHandler()
{
    int idx = gState;
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
    gState = 0x25;    
    
    //while(1);
}


void DelayStateHandler()
{
    //debugPrint("DelayStateHandler called"); 
    if(gDelay != 0)
        return;
    
    //debugPrint("DelayStateHandler passed"); 
    gState = 0x6; 
}


void sub_419()
{
    //debugPrint("sub_419 called");
    
    memory[0xFFE9] = 0;
    memory[0xFF98] = 0;
    memory[0xFF9C] = 0;
    memory[0xFF9B] = 0;
    memory[0xFFFB] = 0;
    memory[0xFF9F] = 0;
    memory[0xFFE3] = 0;
    memory[0xFFE7] = 0;
    memory[0xFFC7] = 0;
    
    sub_22F3();
    sub_26A5();
    LoadTitleScreenTiles();
    
    for(int i=0; i<0x400; i++)
    {
        memory[0xC800+i] = 0x2F; 
    }
    
    //hl = $C801 
    sub_26FD();
    //hl = $C80C
    sub_26FD();
    
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
    //TODO:
    
    gState = 7;
    gDelay = 0x7D;
    
    memory[0xFFC6] = 4;
    
    if(memory[0xFFE4])
        return;
    
    memory[0xFFC6] = 0x13;
}


void sub_48C()
{
    //Unimplemented
    
    memory[0xFFC0] = 0x37;
    memory[0xFFC2] = 0x09;
    
    memory[0xFFC5] = 0x00;
    memory[0xFFB0] = 0x00;
    memory[0xFFED] = 0x00;
    memory[0xFFEA] = 0x00;
    
    memory[0xFFEB] = 0x63;
    memory[0xFFEC] = 0x30;
    
    if(memory[0xFFE4] == 0x02)
    {
        memory[0xFFC0] = 0x77;
        memory[0xFFC3] = 0x09;
        memory[0xFFC4] = 0x02;
        memory[0xFFEB] = 0x64;
        memory[0xFFEC] = 0x30;
        memory[0xFFB0] = 0x11;
        memory[0xFFE4] = 0x1;
    }
    else
    {
        memory[0xFFE4] = 0x2;
    }
    
    gState = 0x0A;
    
    DisableLCD();
    
    LoadFontData();
    
    CopyTilemapSection_Height_12_Dest_9800(GameType_1P_Tilemap);
    
    ClearA0BytesFromC000();
    
    //LCDC = $D3
}


void sub_4E1()
{
    memory[0xFFE9] = 0xFF;
}


void sub_4E6()
{
    //Seems to handle the input on the title screen
    
    if(gDelay == 0)
    {
        memory[0xFFC6]--;
        if(memory[0xFFC6] == 0)
        {
            sub_48C();
            return;
        }
        gDelay = 0x7D;
    }
    
    sub_B07();
    
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
    else if(gJoyHeld & GBKEY_SELECT)
    {
        memory[0xFFC5] ^= 1;
    }
    else if(gJoyHeld & GBKEY_LEFT)
    {
        if(!memory[0xFFC5])
            return;
        memory[0xFFC5] = 0; //1Player
    }
    else if(gJoyHeld & GBKEY_RIGHT)
    {
        if(memory[0xFFC5])
            return;
        memory[0xFFC5] = 2; //2Player
    }
    else if(gJoyHeld & GBKEY_START)
    {
        if(memory[0xFFC5] == 0)
        {
            //1Player stuff?
            if(gJoyPressed & GBKEY_DOWN)
            {
               memory[0xFFF4] = gJoyPressed;
            }
            else
            {
                gState = 8;
                gDelay = 0;
                memory[0xFFC2] = 0;
                memory[0xFFC3] = 0;
                memory[0xFFC4] = 0;
                memory[0xFFE4] = 0;
                return;
            }
        }
        else
        {
            //2Player stuff?
            if(gJoyHeld != GBKEY_START) //Check if only START is pressed
            {
                //If any other key is pressed return.
                return;
            }
            
            if(memory[0xFFCB] == 0x29)
            {
                gState = 0x2A;
                gDelay = 0;
                memory[0xFFC2] = 0;
                memory[0xFFC3] = 0;
                memory[0xFFC4] = 0;
                memory[0xFFE4] = 0;
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
                gState = 0x2A;
                gDelay = 0;
                memory[0xFFC2] = 0;
                memory[0xFFC3] = 0;
                memory[0xFFC4] = 0;
                memory[0xFFE4] = 0;
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


void sub_579()
{
    //Unimplemented
}


void sub_5AF()
{
    //Unimplemented
}


void sub_5EA()
{
    //Unused?
    
    memory[0xFFED] = 0;
    
    gJoyHeld = 0;
    memory[0xFFEE] = gJoyPressed;
    gJoyPressed = memory[0xFFED];
}


void sub_5EF()
{
    //This does nothing
}


void sub_5F0()
{
    //Unimplemented
}


void sub_620()
{
    if(!memory[0xFFE4])
        return;
    
    if(memory[0xFFE9])
        return;
    
    gJoyPressed = memory[0xFFEE];
}


void sub_62D()
{
    //Unimplemented
}


void sub_634()
{
    //Unimplemented
}


void sub_63E()
{
    //Unimplemented
}


void sub_664()
{
    //Unimplemented
}


void sub_6DD()
{
    //Unimplemented
}


void sub_6E4()
{
    //Unimplemented
}


void sub_703()
{
    //Unimplemented
}


void sub_792()
{
    //Unimplemented
}


void sub_799()
{
    //Unimplemented
}


void sub_7DA()
{
    //Unimplemented
}


void sub_80F()
{
    //Unimplemented
}


void sub_87B()
{
    //Unimplemented
}


void sub_892()
{
    DisableLCD();
    sub_895();
}


void sub_895()
{
    //Unimplemented
}


void sub_953()
{
    //Unimplemented
}


void sub_AFB()
{
    //Unimplemented
}


void sub_B07()
{
    //Unimplemented
}


void sub_B10()
{
    //Unimplemented
}


void sub_B41()
{
    //Unimplemented
}


void sub_B95()
{
    //Unimplemented
}


void sub_BFF()
{
    //Unimplemented
}


void sub_C3A()
{
    //Unimplemented
}


void sub_C54()
{
    //Unimplemented
}


void sub_C80()
{
    //Unimplemented
}


void sub_C92()
{
    //Unimplemented
}


void sub_CB4()
{
    //Unimplemented
}


void sub_CE6()
{
    //Unimplemented
}


void sub_CF0()
{
    //Unimplemented
}


void sub_D4F()
{
    //Unimplemented
}


void sub_D96()
{
    //Unimplemented
}


void sub_DE2()
{
    //Unimplemented
}


void sub_DFD()
{
    //Unimplemented
}


void sub_E11()
{
    sub_E21();
    DrawCurrentBlock_C000(3);
}


void sub_E1A()
{
    gState = 0x1F;
    memory[0xFFCC] = 0x1F;
}


void sub_E21()
{
    //Unimplemented
}


void sub_E87()
{
    //Unimplemented
}


void sub_ED3()
{
    //Unimplemented
}


void sub_EEE()
{
    //Unimplemented
}


void sub_F02()
{
    sub_F12();
    DrawCurrentBlock_C000(2);
}


void sub_F0B()
{
    gState = 0x1F;
    memory[0xFFCC] = 0x1F;
}


void sub_F12()
{
    //Unimplemented
}


void sub_F7B()
{
    //Unimplemented
}


void sub_FC4()
{
    //Unimplemented
}


void sub_FD3()
{
    //Unimplemented
}


void sub_10CE()
{
    //Unimplemented
}


void sub_10E9()
{
    //Unimplemented
}


void sub_113C()
{
    //Unimplemented
}


void sub_1176()
{
    //IE = 1;
    if(gDelay)
        return;
    
    ClearA0BytesFromC000();
    
    memory[0xFFEF] = 0;
    
    //b = $27
    //c = $79
    sub_11A3(0x27,0x79);
    j_ResetSound();
    
    if(memory[0xFFD7] != 5)
    {
        if(memory[0xFFD8] != 5)
        {
            memory[0xFFD6] = 1;
        }
    }
    
    gState = 0x16;
}


void sub_11A3(u8 b, u8 c)
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
    //Unimplemented
}


void sub_1216()
{
    //Unimplemented
}


void HandleRocketScreen()
{
    if(gDelay)
        return;
    
    memory[0xC210] = 0;
    memory[0xC220] = 0;
    gDelay = 0xFF;
    gState = 0x28;
}


void sub_1260()
{
    //Unimplemented
}


void sub_1280()
{
    //Unimplemented
}


void sub_12A8()
{
    //Unimplemented
}


void sub_12DF()
{
    //Unimplemented
}


void sub_1317()
{
    //Unimplemented
}


void sub_1369()
{
    if(gDelay)
        return;
    
    DisableLCD();
    LoadFontData();
    sub_22F3();
    
    //LCDC = $93
    
    gState = 5;
}


void sub_137F()
{
    if(gDelay)
        return;
    
    gState = 0x2E;
}


void sub_1388()
{
    //Unimplemented
}


void sub_13B5()
{
    if(gDelay)
        return;
    
    memory[0xC210] = 0;
    memory[0xC220] = 0;
    gDelay = 0xA0;
    gState = 0x30;
}


void sub_13CB()
{
    if(gDelay)
    {
        gState = 0x31;
        gDelay = 0x80;
        //a = 0x2F
        FillPlayArea();
    }
    else
    {
        sub_145E();
    }
}


void sub_13E2()
{
    //Unimplemented
}


void sub_1419()
{
    //Unimplemented
}


void sub_1449()
{
    DisableLCD();
    LoadFontData();
    j_ResetSound();
    sub_22F3();
    //LCDC = $93
    
    gState = 0x10;
}


void sub_145E()
{
    //Unimplemented
}


void sub_149B()
{
    //Unimplemented
}


void HandleGameTypeMusicScreen()
{
    irqEnable(IRQ_VBLANK);
    //REG_SB = 0;
    //REG_SC = 0;
    //IF = 1;
    sub_14B3();
}


void sub_14B3()
{
    //Unimplemented - Partial
    DisableLCD();
    LoadFontData();
    CopyTilemapSection_Height_12_Dest_9800(GameType_1P_Tilemap);
    ClearA0BytesFromC000();
    
    CopyTilemapSection_Width_6(byte_2723, &memory[0xC200], 2);
    
    sub_14F1(&memory[0xC201]);
    
    memory[0xC212] = memory[0xFFC0];
    
    if(memory[0xFFC0] == 0x37)
        memory[0xC213] = 0x1C;
    else
        memory[0xC213] = 0x1D;
    
    DrawCurrentBlock_C000_R2();
    sub_157B();
    
    //LCDC = $D3
    gState = 0x0E;
}

void stub_14F0()
{
    //This function does nothing
}

void sub_14F1(vu8 *dst)
{
    memory[0xDFE0] = 1;
    sub_14F6(dst);
}


void sub_14F6(vu8 *dst)
{
    //Unimplemented
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


void sub_1514()
{
    //Select Music Type
    //Differs slightly from original code in that theres no looping to dpad checks on B button...
    debugPrint("sub_1514 called");
    
    debugPrintf("0xC200 = 0x%02X", memory[0xC200]);
    sub_17CA(&memory[0xC200]);
    debugPrintf("0xC200 = 0x%02X", memory[0xC200]);
    
    if(gJoyHeld & GBKEY_START)
    {
        sub_15C7(&memory[0xC210]);
    }
    else if(gJoyHeld & GBKEY_A)
    {
        sub_15C7(&memory[0xC210]);
    }
    else if(gJoyHeld & GBKEY_B)
    {
        if(!memory[0xFFC5])
        {
            gState = 0x0E;
            sub_15C2(&memory[0xC201], 0);
        }
    }
    else if(gJoyHeld & GBKEY_UP)
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
            sub_14F1(&memory[0xC201]);
            sub_157B();
        }
    }
    else if(gJoyHeld & GBKEY_DOWN)
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
            sub_14F1(&memory[0xC201]);
            sub_157B();
        }
    }
    else if(gJoyHeld & GBKEY_RIGHT)
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
            sub_14F1(&memory[0xC201]);
            sub_157B();
        }
    }
    else if(gJoyHeld & GBKEY_LEFT)
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
            sub_14F1(&memory[0xC201]);
            sub_157B();
        }
    }
    else
    {
        //Any other time just update existing sprite
        sub_15C3();
    }
}


void sub_157B()
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


void sub_1589()
{
    //Select Game Type
    debugPrint("sub_1589 called");
    
    debugPrintf("0xC210 = 0x%02X", memory[0xC210]);
    sub_17CA(&memory[0xC210]);
    debugPrintf("0xC210 = 0x%02X", memory[0xC210]);
    
    if(gJoyHeld & GBKEY_START)
    {
        sub_15C7(&memory[0xC210]);
    }
    else if(gJoyHeld & GBKEY_A)
    {
        sub_15DB(&memory[0xC210]);
    }
    else if(gJoyHeld & GBKEY_RIGHT)
    {
        if(memory[0xFFC0] == 0x77)
        {
            sub_15C3();
        }
        else
        {
            memory[0xFFC0] = 0x77;
            memory[0xDFE0] = 1;
            memory[0xC212] = 0x77;
            sub_15C2(&memory[0xC213], 0x1D);
        }
    }
    else if(gJoyHeld & GBKEY_LEFT)
    {
        if(memory[0xFFC0] == 0x37)
        {
            sub_15C3();
        }
        else
        {
            memory[0xFFC0] = 0x37;
            memory[0xDFE0] = 1;
            memory[0xC212] = 0x37;
            sub_15C2(&memory[0xC213], 0x1C);
        }
    }
    else
    {
        //Any other time just update existing sprite
        sub_15C3();
    }
}


void sub_15C2(vu8 *something, u8 val)
{
    //[de] = a
    *something = val;
    sub_15C3();
}


void sub_15C3()
{
    DrawCurrentBlock_C000_R2();
}


void sub_15C7(vu8 *recursion_level)
{
    memory[0xDFE0] = 2;
    
    //TODO: Confirm these states are correct
    if(memory[0xFFC0] == 0x37)
    {
        gState = 0x10;
    }
    else
    {
        gState = 0x12;
    }
    
    sub_15C2(recursion_level, 0);
}


void sub_15DB(vu8 *recursion_level)
{
    gState = 0xF;
    sub_15C2(recursion_level, 0);
}


void sub_15DF()
{
    debugPrint("sub_15DF called");
    
    DisableLCD();
    CopyTilemapSection_Height_12_Dest_9800(TypeA_Level_Select_Tilemap);
    sub_1960();
    ClearA0BytesFromC000();
    CopyTilemapSection_Width_6(byte_272F, &memory[0xC200], 1);
    
    //Unused code?
    //ld      de, byte_C201
    //ld      a, [byte_FFC2]
    //ld      hl, byte_1679
    sub_17B2();
    
    DrawCurrentBlock_C000_R2();
    
    sub_17F9();
    sub_192E();
    
    //LCDC = $D3
    gState = 0x11;
    
    if(memory[0xFFC7])
    {
       gState = 0x15; 
    }
    else
    {
        sub_157B();
    }
}


void sub_1623()
{
    //Unimplemented
}


void sub_168D()
{
    //Unimplemented
}


void sub_16D9()
{
    //Unimplemented
}


void sub_16DE()
{
    //Unimplemented
}


void sub_174A()
{
    //Unimplemented
}


void sub_174F()
{
    //Unimplemented
}


void sub_17B2()
{
    memory[0xDFE0] = 1;
}


void sub_17B9()
{
    //Unimplemented
}


//Returns gJoyHeld in B
void sub_17CA(vu8* state)
{
    //Unimplemented
    if(gDelay)
        return;
    
    //have to delay this a bit less on gba
    gDelay = 0x2;//0x10;
    
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


void sub_17F9()
{
    //Unimplemented
}


void sub_1813()
{
    //Unimplemented
}


void sub_1839()
{
    //Unimplemented
}


void sub_185B()
{
    //Unimplemented
}


void sub_185D()
{
    //Unimplemented
}


void sub_1864()
{
    //Unimplemented
}


void sub_192E()
{
    //Unimplemented
}


void sub_1960()
{
    //Unimplemented
}


void sub_1977()
{
    //Unimplemented
}


void sub_1A62()
{
    //Unimplemented
}


void sub_1A63()
{
    //Unimplemented
}


void sub_1A6B()
{
    //Unimplemented
}


void sub_1B43()
{
    //Unimplemented
}


void sub_1B76()
{
    //Unimplemented
}


void sub_1BC3()
{
    //Unimplemented
}


void sub_1C29()
{
    sub_1C68();
    
    if(memory[0xFFAB])
        return;
    
    sub_579();
    sub_5AF();
    sub_5F0();
    sub_2515();
    sub_20F7();
    sub_2199();
    sub_25F5();
    sub_22AD();
    AddScoreForTetris();
    sub_620();
}


void sub_1C4F()
{
    //Unimplemented
}


void sub_1C68()
{
    //Unimplemented
}


void sub_1CE3()
{
    //Unimplemented
}


void sub_1D26()
{
    //Unimplemented
}


void sub_1D38()
{
    //Unimplemented
}


void LoseHandler()
{
    memory[0xC200] = 0x80;
    memory[0xC210] = 0x80;
    DrawCurrentBlock_C010();
    DrawPreviewBlock_C020();
    
    memory[0xFF98] = 0x00;
    memory[0xFF9C] = 0x00;
    sub_22F3();
    
    //a = $87
    FillPlayArea();
    
    gDelay = 0x46;
    gState = 0x0D;
}


void sub_1D61()
{
    //Unimplemented
}


void sub_1D81()
{
    //Unimplemented
}


void sub_1DDF()
{
    //Unimplemented
}


void sub_1E1B()
{
    if(gDelay)
        return;
    
    memory[0xC0C6] = 1;
    
    gDelay = 5;
}


void sub_1E29()
{
    //Unimplemented
}


void sub_1E8C()
{
    //Unimplemented
}


void sub_1E96()
{
    DrawCurrentBlock_C000(0x0A);
}


void sub_1E9C()
{
    //Unimplemented
}


void sub_1EF0()
{
    //Unimplemented
}


void sub_1F32()
{
    //Unimplemented
}


void sub_1F71()
{
    if(!gJoyHeld)
        return;
    
    gState = 2;
}


void GameOverTryAgainHandler()
{
    //Unimplemented
}


void CopyTilemapSectionWidth8()
{
    //Unimplemented
}


void AddScoreForTetris()
{
    //Unverified
    if(memory[0xFFC0] != 0x37)
        return;
    
    if(gState)
        return;
    
    if(memory[0xFFE3] != 0x05)
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
    for(int i=0; i<memory[0xFFA9]; i++)
    {
        AddToScore(&score, points);
    }
    
    memory[0xC0A0] = (score >>  0) & 0xFF;
    memory[0xC0A1] = (score >>  8) & 0xFF;
    memory[0xC0A2] = (score >> 16) & 0xFF;
}


void FillPlayArea()
{
    //Unimplemented - Partial
    memory[0xFFE3] = 2;
    
    sub_2038();
}


void sub_2038()
{
    //Unimplemented
}


void sub_204D()
{
    //Unimplemented
}


void sub_2062()
{
    //Unimplemented
}


void sub_20CC()
{
    //Unimplemented
}


void sub_20F7()
{
    if((gJoyPressed & (GBKEY_RIGHT|GBKEY_LEFT|GBKEY_DOWN)) == GBKEY_DOWN)
    {
        sub_20CC();
    }
    else
    {
        sub_20FF();
    }
}


void sub_20FF()
{
    //Unimplemented
}


void sub_2199()
{
    //Unimplemented
}


void sub_2240()
{
    //Unimplemented
}


void sub_22AD()
{
    //Unimplemented
}


void sub_22F3()
{
    for(int i=0; i<9; i++)
    {
        memory[0xC0A3+i] = 0;
    }
}


void sub_22FE()
{
    if(memory[0xFFE3] != 0x02)
        return;
    
    //hl = $9A22
    //de = $CA22
    sub_2506(&memory[0xCA22], (u16*)(VRAM+0x9800 + (0x222*2)));
}


void sub_230D()
{
    if(memory[0xFFE3] != 0x03)
        return;
    
    //hl = $9A02
    //de = $CA02
    sub_2506(&memory[0xCA02], (u16*)(VRAM+0x9800 + (0x202*2)));
}


void sub_231C()
{
    if(memory[0xFFE3] != 0x04)
        return;
    
    //hl = $99E2
    //de = $C9E2
    sub_2506(&memory[0xCA02], (u16*)(VRAM+0x9800 + (0x1E2*2)));
}


void sub_232B()
{
    if(memory[0xFFE3] != 0x05)
        return;
    
    //hl = $99C2
    //de = $C9C2
    sub_2506(&memory[0xC9C2], (u16*)(VRAM+0x9800 + (0x1C2*2)));
}


void sub_233A()
{
    if(memory[0xFFE3] != 0x06)
        return;
    
    //hl = $99A2
    //de = $C9A2
    sub_2506(&memory[0xC9A2], (u16*)(VRAM+0x9800 + (0x1A2*2)));
}


void sub_2349()
{
    if(memory[0xFFE3] != 0x07)
        return;
    
    //hl = $9982
    //de = $C982
    sub_2506(&memory[0xC982], (u16*)(VRAM+0x9800 + (0x182*2)));
}


void sub_2358()
{
    if(memory[0xFFE3] != 0x08)
        return;
    
    //hl = $9962
    //de = $C962
    sub_2506(&memory[0xC962], (u16*)(VRAM+0x9800 + (0x162*2)));
    
    if(memory[0xFFC5])
    {
        //2375
        if(gState != 0x1A)
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
        if(!gState)
        {
            memory[0xDFF8] = 1;
        }
    }
}


void sub_2383()
{
    if(memory[0xFFE3] != 0x09)
        return;
    
    //hl = $9942
    //de = $C942
    sub_2506(&memory[0xC942], (u16*)(VRAM+0x9800 + (0x142*2)));
}


void sub_2392()
{
    if(memory[0xFFE3] != 0x0A)
        return;
    
    //hl = $9922
    //de = $C922
    sub_2506(&memory[0xC922], (u16*)(VRAM+0x9800 + (0x122*2)));
}


void sub_23A1()
{
    if(memory[0xFFE3] != 0x0B)
        return;
    
    //hl = $9902
    //de = $C902
    sub_2506(&memory[0xC902], (u16*)(VRAM+0x9800 + (0x102*2)));
}


void sub_23B0()
{
    if(memory[0xFFE3] != 0x0C)
        return;
    
    //hl = $98E2
    //de = $C8E2
    sub_2506(&memory[0xC8E2], (u16*)(VRAM+0x9800 + (0xE2*2)));
}


void sub_23BF()
{
    if(memory[0xFFE3] != 0x0D)
        return;
    
    //hl = $98C2
    //de = $C8C2
    sub_2506(&memory[0xC8C2], (u16*)(VRAM+0x9800 + (0xC2*2)));
}


void sub_23CE()
{
    if(memory[0xFFE3] != 0x0E)
        return;
    
    //hl = $98A2
    //de = $C8A2
    sub_2506(&memory[0xC8A2], (u16*)(VRAM+0x9800 + (0xA2*2)));
}


void sub_23DD()
{
    if(memory[0xFFE3] != 0x0F)
        return;
    
    //hl = $9882
    //de = $C882
    sub_2506(&memory[0xC882], (u16*)(VRAM+0x9800 + (0x82*2)));
}


void sub_23EC()
{
    if(memory[0xFFE3] != 0x10)
        return;
    
    //hl = $9862
    //de = $C862
    sub_2506(&memory[0xC862], (u16*)(VRAM+0x9800 + (0x62*2)));
    
    sub_24AB();
}


void sub_23FE()
{
    if(memory[0xFFE3] != 0x11)
        return;
    
    //hl = $9842
    //de = $C842
    sub_2506(&memory[0xC842], (u16*)(VRAM+0x9800 + (0x42*2)));
    
    //hl = $9C6D
    sub_249B((u16*)(VRAM+0x9800 + (0x46D*2)));
    
    memory[0xFFE0] = 1;
}


void sub_2417()
{
    //Unimplemented - Partial
    if(memory[0xFFE3] != 0x12)
        return;
    
    //hl = $9822
    //de = $C822
    sub_2506(&memory[0xC822], (u16*)(VRAM+0x9800 + (0x22*2)));
    
    //hl = $986D
    sub_249B((u16*)(VRAM+0x9800 + (0x6D*2)));
}


void sub_242C()
{
    //Unimplemented
}


void sub_249B(u16 *tilemap)
{
    if(gState)
        return;
    
    if(memory[0xFFC0] == 0x37)
        return;
    
    //hl = $C0A2
    sub_2A7E(&memory[0xC0A2], tilemap);
}


void sub_24AB()
{
    //Unimplemented
}


void sub_2506(vu8 *src, u16 *dst)
{
    //Unimplemented
    //DE = src
    //HL = dst
    
    for(int i=0; i<10; i++)
    {
        *dst++ = *src++;
    }
    
    memory[0xFFE3]++;
}


void sub_2515()
{
    //Unimplemented
}


void sub_25C7()
{
    //Unimplemented
}


void sub_25F5()
{
    //Unimplemented
}


void sub_262D()
{
    //Unimplemented
}


void sub_26A5()
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


void sub_26B9()
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


void sub_26FD()
{
    //Unimplemented
}


void sub_270A()
{
    //Unimplemented
}


void Stub_Interrupt_Handler()
{
    //This function does nothing
}


void sub_27E9()
{
    //Unimplemented
}


void sub_27EC()
{
    //Unimplemented
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


void sub_2835()
{
    //This function does nothing
}


void CopyDataTo8000()
{
    //Unimplemented
}


void stub_283E()
{
    //Unimplemented
}

void CopyTilemapSection_Height_12_Dest_9800(u8 *src)
{
    CopyTilemapSection_Height_12(src, (u16*)(VRAM+0x9800));
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


void sub_2858()
{
    //Unimplemented
}


void DisableLCD()
{
    //Unimplemented
}


void ReadJoypad()
{
    //Unimplemented
    scanKeys();
    
    gJoyHeld = gJoyPressed;
    
    u32 keys = keysDown();
    gJoyPressed = ((keys&0xF0)>>4) | ((keys&0xF)<<4);
}


void sub_2A2B()
{
    //Unimplemented
}


void sub_2A58()
{
    //Unimplemented
}


void sub_2A7E(vu8 *score, u16 *tilemap)
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
    for(int i=0; i<0x80; i+=4)
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
    
    debugPrintf("tile = %02X", tile);
    
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
    
    debugPrintf("tileData = %08X", tileData + 1);
    
    debugPrintf("rotation_info = %08X", rotation_info);
    
    memory[0xFF90] = blockInfo->flagsL;
    memory[0xFF91] = blockInfo->flagsH;
    
    while(1)
    {
        //2B20
        tileData++;
        memory[0xFF94] = memory[0xFF8C];
        
        debugPrintf("*tileData = %02X", *tileData);
        
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
        debugPrintf("c = %02X", c);
        debugPrintf("memory[0xFF87] = %02X", memory[0xFF87]);
        debugPrintf("memory[0xFF88] = %02X", memory[0xFF88]);
        debugPrintf("memory[0xFF8B] = %02X", memory[0xFF8B]);
        debugPrintf("memory[0xFF90] = %02X", memory[0xFF90]);
        debugPrintf("memory[0xFF91] = %02X", memory[0xFF91]);
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
        
        debugPrintf("curPiece_Y = %02X", curPiece_Y);
        
        //rotation_info++;
        
        b = memory[0xFF88];
        c = *rotation_info++;
        
        //Adjust X position - TODO Fix
        if((memory[0xFF8B] & (1<<5)))
        {
            //2B72
            curPiece_X = b - memory[0xFF91] - 8;
        }
        else
        {
            //2B6E
            u32 temp_x = memory[0xFF91] + b + c;
            
            if(temp_x > 0x100)
               temp_x = (temp_x & 0xFF) + 1; 
            curPiece_X = temp_x;
        }
        
        debugPrintf("curPiece_X = %02X", curPiece_X);        
        debugPrintf("curPiece_Tile = %02X", curPiece_Tile);
        
        //2B7E
        u16 adr = curBlock_Dest_High << 8 | curBlock_Dest_Low;
        debugPrintf("adr = %04X", adr);
        vu8 *dst = &memory[adr];
        if(!memory[0xFF95])
        {
            //If not hidden
            *dst++ = curPiece_Y;
            *dst++ = curPiece_X;
        }
        else
        {
            //If Hidden draw off screen
            *dst++ = 0xFF;
            *dst++ = 0xFF;
        }
        *dst++ = curPiece_Tile;
        *dst++ = memory[0xFF94] | memory[0xFF8B] | memory[0xFF8A];
        
        adr += 4;
        curBlock_Dest_High = (adr & 0xFF00) >> 8;
        curBlock_Dest_Low  = (adr & 0x00FF);
    }
    
}


void sub_6552()
{
    //This does nothing
}


void UpdateAudio()
{
    //Unimplemented
}


void sub_683D()
{
    //Unimplemented
}


void sub_6854()
{
    //Unimplemented
}


void sub_6879()
{
    if(memory[0xDFF0] == 1)
    {
        sub_68A8();
    }
    else if(memory[0xDFF0] == 2)
    {
        sub_683D();
    }
    
    if(memory[0xDFF1] == 1)
    {
        sub_68F3();
    }
    else if(memory[0xDFF1] == 2)
    {
        sub_6854();
    }
}


void sub_68A8()
{
    //Unimplemented
}


void sub_68C0()
{
    //Unimplemented
}


void sub_68D1()
{
    //Unimplemented
}


void sub_68E2()
{
    //Unimplemented
}


void sub_68F3()
{
    //Unimplemented
}


void sub_691F()
{
    //Unimplemented
}


void sub_693E()
{
    //Unimplemented
}


void sub_6967()
{
    //Unimplemented
}


void sub_6987()
{
    //Unimplemented
}


void sub_698E()
{
    //Unimplemented
}


void sub_6995()
{
    //Unimplemented
}


void sub_699C()
{
    //Unimplemented
}


void sub_69A1()
{
    //Unimplemented
}


void sub_69A9()
{
    //Unimplemented
}


void sub_69AD()
{
    //Unimplemented
}


void sub_69BC()
{
    //Unimplemented
}

//Copy from hl to sound wave pattern ram
void sub_69C9(u8 *src)
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
    
    sub_69F8();
}


void sub_69F8()
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


void sub_6A0E()
{
    //Unimplemented
}


void sub_6A2E()
{
    //Unimplemented
}


void sub_6A4E()
{
    ResetSound();
}


void sub_6A52()
{
    if(memory[0xDFE8] == 0)
        return;
    
    if(memory[0xDFE8] == 0xFF)
    {
        sub_6A4E();
        return;
    }
    
    memory[0xDFE9] = memory[0xDFE8];
    
    //ld      b, a
    //ld      hl, off_6530
    //and     $1F
    //unused args?
    sub_69AD();
    
    sub_6B44();
    
    sub_6A6D();
}


void sub_6A6D()
{
    //Unimplemented
}


void sub_6A96()
{
    //Unimplemented
}


void sub_6B33()
{
    //Unimplemented
}


void sub_6B3E()
{
    //Unimplemented
}


void sub_6B44()
{
    //Unimplemented
}


void sub_6BEA()
{
    //Unimplemented
}


void sub_6BF6()
{
    //Unimplemented
}


void sub_6BFF()
{
    //Unimplemented
}


void sub_6C75()
{
    //Unimplemented
}


void sub_6D8F()
{
    //Unimplemented
}


void sub_6D98()
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


