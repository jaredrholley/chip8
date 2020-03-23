/*
 * cpu.h
 *
 *  Created on: Mar 22, 2020
 *      Author: voyager
 */

#include "msp.h"

/*
 * 0x000-0x1FF - Chip 8 interpreter (contains font set in emu)
 * 0x050-0x0A0 - Used for the built in 4x5 pixel font set (0-F)
 * 0x200-0xFFF - Program ROM and work RAM
 */


#ifndef CPU_H_
#define CPU_H_

/**********************
 *      DEFINES
 **********************/
#define DISP_RES 64 * 32
#define STACK_SIZE 16
#define MEM_SIZE 4096

/**********************
 *      SYSVARS
 **********************/

// Black and white pixel array
uint8_t gfx[DISP_RES];

// Count down at 60Hz when set above zero
// Replace with HW timers
uint8_t delay_timer;
uint8_t sound_timer;

// Key status
uint8_t key[16];

uint8_t memory[MEM_SIZE]; // Total memory space of 4K
uint8_t V[16];        // 15 8-bit general purpose registers V0-VE (hex) - 16th used for carry flag
uint16_t opcode;      // 16 Bit opcodes
uint16_t I;           // Index register (range 0x000 - 0xFFF)
uint16_t pc;          // Program Counter (range 0x000 - 0xFFF)
uint8_t stack[STACK_SIZE];    // Array for Stack Emulation
uint8_t sp;           // Stack pointer



/**********************
 *      FUNCTIONS
 **********************/

// Clears all system variables and CPU attributes
void initialize();

// Emulate once cycle of the CPU
void emulateCycle();

#endif /* CPU_H_ */
