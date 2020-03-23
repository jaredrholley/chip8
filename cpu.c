/*
 * cpu.c
 *
 *  Created on: Mar 22, 2020
 *      Author: voyager
 */

#include "cpu.h"

void initialize() {

    pc = 0x200; // Program counter starts at 0x200
    I = 0x000; // Clear index register
    opcode = 0x00; // Clear current OP Code
    sp = 0x00; // Clear stack pointer

    // Clear display
    for (int i = 0; i < DISP_RES; i++)
        gfx[i] = 0;

    // Clear stack
    for (int i = 0; i < STACK_SIZE; i++)
        stack[i] = 0;

    // Clear registers V0 - VF
    for (int i = 0; i < 16; i++)
        V[i] = 0;

    // Clear memory
    for (int i = 0; i < MEM_SIZE; i++)
        memory[i] = 0;

    // Clear timers
    delay_timer = 0x00;
    sound_timer = 0x00;

}

void emulateCycle() {

    // Fetch opcode from memory
    opcode = memory[pc] << 8 | memory[pc + 1];

    // Decode opcode
    // First 4-bits are instruction type
    switch (opcode & 0xF000)
    {
        case 0x0000:
            switch (opcode & 0x000F)
            {
                case 0x0000: // 0x00E0 Clears the Screen
                    for (int i = 0; i < DISP_RES; i ++)
                        gfx[i] = 0;
                break;
                case 0x000E: // 0x00EE Returns from subroutine
                    pc = stack[sp];


            }
    }

}
