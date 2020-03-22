/*
 * cpu.c
 *
 *  Created on: Mar 22, 2020
 *      Author: voyager
 */

#include "cpu.h"

void initialize(cpu_t cpu) {

    cpu.pc = 0x200; // Program counter starts at 0x200
    cpu.I = 0x000; // Clear index register
    cpu.opcode = 0x00; // Clear current OP Code
    cpu.sp = 0x00; // Clear stack pointer

    // Clear display
    for (int i = 0; i < DISP_RES; i++)
        gfx[i] = 0;

    // Clear stack
    for (int i = 0; i < STACK_SIZE; i++)
        cpu.stack[i] = 0;

    // Clear registers V0 - VF
    for (int i = 0; i < 16; i++)
        cpu.V[i] = 0;

    // Clear memory
    for (int i = 0; i < MEM_SIZE; i++)
        cpu.memory[i] = 0;

    // Clear timers
    delay_timer = 0x00;
    sound_timer = 0x00;

}

void emulateCycle(cpu_t cpu) {

    // Fetch opcode from memory
    cpu.opcode = cpu.memory[cpu.pc] << 8 | cpu.memory[cpu.pc + 1];

    // Decode opcode
    // First 4-bits are instruction type
    switch (cpu.opcode & 0xF000)
    {
        case 0x0000:
            switch (cpu.opcode & 0x000F)
            {
                case 0x0000: // 0x00E0 Clears the Screen
                    for (int i = 0; i < DISP_RES; i ++)
                        gfx[i] = 0;
                break;
                case 0x000E: // 0x00EE Returns from subroutine
                    cpu.pc = cpu.stack[cpu.sp];


            }
    }

}
