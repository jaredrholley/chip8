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
 *      TYPEDEFS
 **********************/

// All opcodes are 16 bits
typedef uint16_t opcode;

/**********************
 *      STRUCTS
 **********************/

typedef struct cpu_s {
    uint8_t memory[4096]; // Total memory space of 4K
    uint8_t V[16];        // 15 8-bit general purpose registers V0-VE (hex) - 16th used for carry flag
    uint8_t I;            // Index register (range 0x000 - 0xFFF)
    uint8_t pc;           // // Program Counter (range 0x000 - 0xFFF)
    uint8_t stack[16];
    uint
} cpu_t;

#endif /* CPU_H_ */
