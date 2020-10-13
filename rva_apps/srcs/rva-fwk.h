#include <stdint.h>

#define STR1(x) #x
#ifndef STR
#define STR(x) STR1(x)
#endif
#define EXTRACT(a, size, offset) (((~(~0 << size) << offset) & a) >> offset)

#define EXTRACT_RAW(rd, rs1, rs2, size, offset) \
  not x ## rs1, x0;                             \
  slli x ## rs1, x ## rs1, size;                \
  not x ## rs1, x ## rs1;                       \
  slli x ## rs1, x ## rs1, offset;              \
  and x ## rd, x ## rs1, x ## rs2;              \
  srai x ## rd, x ## rd, offset;

#define XCUSTOM_OPCODE(x) XCUSTOM_OPCODE_ ## x
#define XCUSTOM_OPCODE_0 0b0001011
#define XCUSTOM_OPCODE_1 0b0101011
#define XCUSTOM_OPCODE_2 0b1011011
#define XCUSTOM_OPCODE_3 0b1111011

#define XCUSTOM(x, rd, rs1, rs2, funct)         \
  XCUSTOM_OPCODE(x)                   |         \
  (rd                   << (7))       |         \
  (0x3                  << (7+5))     |         \
  ((rd != 0) & 1        << (7+5+2))   |         \
  (rs1                  << (7+5+3))   |         \
  (rs2                  << (7+5+3+5)) |         \
  (EXTRACT(funct, 7, 0) << (7+5+3+5+5))

#define ROCC_INSTRUCTION_RAW_R_R_R(x, rd, rs1, rs2, funct)      \
  .word XCUSTOM(x, ## rd, ## rs1, ## rs2, funct)

// Standard macro that passes rd, rs1, and rs2 via registers
#define ROCC_INSTRUCTION(x, rd, rs1, rs2, funct)                \
  ROCC_INSTRUCTION_R_R_R(x, rd, rs1, rs2, funct, 10, 11, 12)

// rd, rs1, and rs2 are data
// rd_n, rs_1, and rs2_n are the register numbers to use
#define ROCC_INSTRUCTION_R_R_R(x, rd, rs1, rs2, funct, rd_n, rs1_n, rs2_n) \
  {                                                                     \
    register uint64_t rd_  asm ("x" # rd_n);                            \
    register uint64_t rs1_ asm ("x" # rs1_n) = (uint64_t) rs1;          \
    register uint64_t rs2_ asm ("x" # rs2_n) = (uint64_t) rs2;          \
    asm volatile (                                                      \
        ".word " STR(XCUSTOM(x, rd_n, rs1_n, rs2_n, funct)) "\n\t"      \
        : "=r" (rd_)                                                    \
        : [_rs1] "r" (rs1_), [_rs2] "r" (rs2_));                        \
    /*rd = rd_; */                                                          \
  } \


#define AND_RVA(in, out, length, factor, word_size) { \
	    ROCC_INSTRUCTION(0, 0, in, out, 0) \
            ROCC_INSTRUCTION(0, 0, length, factor, (8 | word_size)) \
        } \
// 2 -> 16
#define OR_RVA(in, out, length, factor, word_size) { \
            ROCC_INSTRUCTION(0, 0, in, out, 0) \
            ROCC_INSTRUCTION(0, 0, length, factor, (16 | word_size)) \
        } \
// 3 -> 24
#define XOR_RVA(in, out, length, factor, word_size) { \
            ROCC_INSTRUCTION(0, 0, in, out, 0) \
            ROCC_INSTRUCTION(0, 0, length, factor, (24 | word_size))   } \
//4 -> 32
#define NOT_RVA(in, out, length, factor, word_size) { \
            ROCC_INSTRUCTION(0, 0, in, out, 0) \
            ROCC_INSTRUCTION(0, 0, length, factor, (32 | word_size)) \
        } \
// 5 -> 40 
#define SLL_RVA(in, out, length, factor, word_size) { \
            ROCC_INSTRUCTION(0, 0, in, out, 0) \
            ROCC_INSTRUCTION(0, 0, length, factor, (40 | word_size))     } \
// 6 -> 48
#define SRL_RVA(in, out, length, factor, word_size) { \
            ROCC_INSTRUCTION(0, 0, in, out, 0) \
            ROCC_INSTRUCTION(0, 0, length, factor, (48 | word_size))   } \

#define ADD_RVA(in_a, in_b, out, length, word_size) { \
            ROCC_INSTRUCTION(1, 0, in_a, in_b, 0) \
   	    ROCC_INSTRUCTION(1, 0, length, out, (8 | word_size)) \
        } \

#define SUB_RVA(in_a, in_b, out, length, word_size) { \
            ROCC_INSTRUCTION(1, 0, in_a, in_b, 0) \
   	    ROCC_INSTRUCTION(1, 0, length, out, (16 | word_size)) \
        } \

#define MULT_RVA(in_a, in_b, out, length, word_size) { \
            ROCC_INSTRUCTION(1, 0, in_a, in_b, 0) \
   	    ROCC_INSTRUCTION(1, 0, length, out, (24 | word_size)) \
        } \

#define DIV_RVA(in_a, in_b, out, length, word_size) { \
            ROCC_INSTRUCTION(1, 0, in_a, in_b, 0) \
   	    ROCC_INSTRUCTION(1, 0, length, out, (32 | word_size))  } \

#define SET_RVA(in, length, factor, word_size) {\
            ROCC_INSTRUCTION(2, 0, in, in, 0)\
            ROCC_INSTRUCTION(2, 0, length, factor, (8 | word_size))   }\

