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

    // Register paramaters to make code easier to follow
    uint8_t x = (opcode >> 8) & 0x000F;
    uint8_t y = (opcode >> 4) & 0x000F;

    // Decode opcode
    // First 4-bits are instruction type
    switch (opcode & 0xF000)
    {
        // 0x0nnn - CLS and RET
        case 0x0000:
            switch (opcode & 0x000F)
            {
                // CLS
                case 0x0000: // 0x00E0 Clears the Screen
                    for (int i = 0; i < DISP_RES; i ++)
                        gfx[i] = 0;
                    pc += 2;
                    drawFlag = true;
                break;
                // RET
                case 0x000E: // 0x00EE Returns from subroutine
                    pc = stack[sp];
                    --sp;
                break;

                default:
                    printf ("Unknown opcode [0x0000]: 0x%X\n", opcode);
            }
        break;
        // 0x1nnn - JP addr
        case 0x1000: // Jump to location nnn
            pc = opcode & 0x0FFF;
        break;

        // 0x2nnn - CALL addr
        case 0x2000: // Call subroutine at nnn
            stack[sp] = pc;
            sp++;
            pc = opcode & 0xFFF;
         break;

         // 0x3xkk - SE Vx, byte
        case 0x3000: // Skip next instruction if Vx = kk
            if (V[x] == (opcode & 0x00FF))
                pc += 4;
            else
                pc += 2;
        break;

        // 0x4xkk - SNE Vx, byte
        case 0x4000:
            if (V[x] != (opcode & 0x00FF))
                pc += 4;
            else
                pc += 2;
        break;

        // 0x5xy0 - SE Vx, Vy
        case 0x5000:
            if (V[x] == V[y])
                pc += 4;
            else
                pc += 2;
        break;

        // 0x6xkk - LD Vx, byte
        case 0x6000:
            V[x] = opcode & 0x00FF;
            pc += 2;
        break;

        // 0x7xkk - ADD Vx, byte
        case 0x7000:
            V[x] += (opcode & 0x00FF);
            pc += 2;
        break;

        case 0x8000:
            switch (opcode & 0x000F)
            {
                // 0x8xy0 - LD Vx, Vy
                case 0x0000:
                    V[x] = V[y];
                    pc += 2;
                break;

                // 8xy1 - OR Vx, Vy
                case 0x0001:
                    V[x] |= V[y];
                    pc += 2;
                break;

                // 8xy2 - AND Vx, Vy
                case 0x0002:
                    V[x] &= V[y];
                    pc += 2;
                break;

                // 8xy3 - XOR Vx, Vy
                case 0x0003:
                    V[x] ^= V[y];
                    pc += 2;
                break;

                // 8xy4 - ADD Vx, Vy
                case 0x0004:
                    // Set VF (carry) if results greater than 8-bits
                    if (((uint16_t) V[x] + (uint16_t) V[y]) > 255)
                        V[0xF]= 0x01;
                    else
                        V[0xF] = 0x01;
                    V[x] -= V[y];
                    pc += 2;
                break;

                // 8xy5 - SUB Vx, Vy
                case 0x0005:
                    // Set VF (borrow) if Vx > Vy
                    if (V[x] > V[y])
                        V[0xF]= 0x0001;
                    else
                        V[0xF] = 0x00;
                    V[x] -= V[y];
                    pc += 2;
                break;

                // 8xy6 - SHR Vx {, Vy}
                case 0x0006:
                    // Set VF if least significant bit is set
                    if (V[x] & 0x0001)
                        V[0xF] = 0x01;
                    else
                        V[0xF] = 0x00;
                    V[x] >>= 0x1;
                    pc += 2;
                break;

                // 8xy7 - SUBN Vx, Vy
                case 0x0007:
                    // Set VF (borrow) if Vy > Vx
                    if (V[y] > V[x])
                        V[0xF] = 0x01;
                    else
                        V[0xF] = 0x00;
                    V[x] = V[y] - V[x];
                    pc += 2;
                break;

                // 8xyE - SHL Vx {, Vy}
                case 0x000E:
                    // Set VF (borrow) if Vx > Vy
                    if (V[x] & 0x80)
                        V[0xF] = 0x01;
                    else
                        V[0xF] = 0x00;
                    V[x] <<= 1;
                    pc += 2;
                break;

            }

    }

}
