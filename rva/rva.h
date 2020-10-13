#ifndef _RISCV_RIM_ROCC_H
#define _RISCV_RIM_ROCC_H

#include "rocc.h"
#include "mmu.h"

#include <stdint.h>
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include <map>
#include <vector>
#include <fstream>
#include "ap_rv.h"

class rva_t : public rocc_t
{
public:

  rva_t();
  ~rva_t();
  const char* name();
  void count_info();
  void set_log(bool log_mode); 
  reg_t custom0(rocc_insn_t insn, reg_t xs1, reg_t xs2); 
  reg_t custom1(rocc_insn_t insn, reg_t xs1, reg_t xs2);
  reg_t custom2(rocc_insn_t insn, reg_t xs1, reg_t xs2);  

  template <typename T> void custom0_exec(rocc_insn_t insn, T* mem);
  template <typename T> void custom1_exec(rocc_insn_t insn, T* mem);
  template <typename T> void custom2_exec(rocc_insn_t insn, T* mem);

  enum OperationType { LOGIC, ARITH };

#define in_place_load_func(type) \
void in_place_load_##type(type##_t* mem, OperationType op_t) { \
    uint32_t block_size = this->ap->mem_size/2;  \
    uint8_t  jump = sizeof(type##_t); \
    switch(op_t) { \
        case LOGIC:{ \
            reg_t in = this->ap->input_addr;\
            pim_load_count++; \
            for(uint32_t i = 0; i < this->ap->mem_size; i++) { \
                mem[i] = this->p->get_mmu()->load_##type(in + (i*jump), true); \
            } \
            break; \
                   }\
        case ARITH: {\
            reg_t in_a =  this->ap->input_addr_a;\
            reg_t in_b =  this->ap->input_addr_b;\
            pim_load_count += 2; \
            for(uint32_t i = 0; i < block_size; i++) { \
                mem[i] = this->p->get_mmu()->load_##type(in_a + (i*jump), true); \
                mem[block_size + i] = this->p->get_mmu()->load_##type(in_b + (i*jump), true); \
            }} \
            break; \
        default: \
            printf("Invalid type!"); \
    } \
} \

    in_place_load_func(uint8);
    in_place_load_func(uint16);
    in_place_load_func(uint32);
    in_place_load_func(uint64);
    
    in_place_load_func(int8);
    in_place_load_func(int16);
    in_place_load_func(int32);
    in_place_load_func(int64);

#define in_place_store_func(type) \
  void in_place_store_##type(type##_t* mem, OperationType op_t){ \
    uint32_t block_size = this->ap->mem_size/2; \
    reg_t o_addr = this->ap->output_addr; \
    uint8_t  jump = sizeof(type##_t); \
    pim_write_count++; \
    switch(op_t) { \
        case LOGIC:\
            for(uint32_t i = 0; i < this->ap->mem_size; i++) { \
                this->p->get_mmu()->store_##type(o_addr + (i*jump), mem[i], true);\
            }\
            break;\
        case ARITH:\
            for(uint32_t i = 0; i < block_size; i++) { \
                this->p->get_mmu()->store_##type(o_addr + (i*jump), mem[i], true);\
            }\
            break;\
        default:\
            printf("Invalid type!");\
    }\
}\

    in_place_store_func(uint8);
    in_place_store_func(uint16);
    in_place_store_func(uint32);
    in_place_store_func(uint64);

    APrv* ap;

private:
    uint64_t pim_load_count;
    uint64_t pim_write_count;
};

REGISTER_EXTENSION(rva, []() { return new rva_t; })

#endif
