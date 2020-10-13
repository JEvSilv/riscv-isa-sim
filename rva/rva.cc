#include "rocc.h"
#include "mmu.h"
#include "extension.h"
#include "rva.h"
#include <vector>
#include <iostream>

rva_t::rva_t()
{
    this->ap = new APrv();
    this->ap->reset();
};

void rva_t::set_log(bool log_mode)
{
    this->ap->log_mode = log_mode;
}

rva_t::~rva_t() {}

const char* rva_t::name() 
{
    return "rva"; 
}

reg_t rva_t::custom0(rocc_insn_t insn, reg_t xs1, reg_t xs2)
{
  
  uint8_t funct_op = (insn.funct >> 3);
  uint8_t funct_size = (insn.funct & 7);
  
  if (insn.funct == 0) 
  {
    ap->input_addr = xs1;
    ap->output_addr = xs2;
  }else
  {
	ap->mem_size = xs1;
        ap->factor = xs2;
        ap->word_size = funct_size * 8;
        void* mem;
	switch (ap->word_size)
	{
	    case 8:
	 	mem = (uint8_t*) malloc(sizeof(uint8_t)*ap->mem_size);
                in_place_load_uint8((uint8_t*) mem, LOGIC);
                this->custom0_exec<uint8_t>(insn, (uint8_t*) mem);
                in_place_store_uint8((uint8_t*) mem, LOGIC);
		break;
	    case 16:
	 	mem = (uint16_t*) malloc(sizeof(uint16_t)*ap->mem_size);
	        in_place_load_uint16((uint16_t*) mem, LOGIC);
                this->custom0_exec<uint16_t>(insn, (uint16_t*) mem);
                in_place_store_uint16((uint16_t*) mem, LOGIC);	
                break;
	    case 32:
	 	mem = (uint32_t*) malloc(sizeof(uint32_t)*ap->mem_size);
	        in_place_load_uint32((uint32_t*) mem, LOGIC);
                this->custom0_exec<uint32_t>(insn, (uint32_t*) mem);
                in_place_store_uint32((uint32_t*) mem, LOGIC);	
		break;
	    case 64:
	 	mem = (uint64_t*) malloc(sizeof(uint64_t)*ap->mem_size);
	        in_place_load_uint64((uint64_t*) mem, LOGIC);
                this->custom0_exec<uint64_t>(insn, (uint64_t*) mem);
                in_place_store_uint64((uint64_t*) mem, LOGIC);	
		break;
	    default:
	 	mem = (uint64_t*) malloc(sizeof(uint64_t)*ap->mem_size);
	        in_place_load_uint64((uint64_t*) mem, LOGIC);
                this->custom0_exec<uint64_t>(insn, (uint64_t*) mem);
                in_place_store_uint64((uint64_t*) mem, LOGIC);	
		break;
	}
	
        free(mem);
        ap->reset();
        ap->op_id++;
  }  
    
    return -1; // in all cases, the accelerator returns nothing
   
}

template <typename T> 
void rva_t::custom0_exec(rocc_insn_t insn, T* mem)
{
    uint8_t funct_op = (insn.funct >> 3);
    switch (funct_op)
    {
        case 1: 
            ap->register_op("AND");
            ap->set_cycles(ap->word_size);
            ap->_and<T>(mem);
	    break;
        case 2: 
            ap->register_op("OR");
            ap->set_cycles(ap->word_size*2);
            ap->_or<T>(mem);
	    break;
        case 3:
            ap->register_op("XOR");
            ap->set_cycles(ap->word_size*2);
	          ap->_xor<T>(mem);
	    break;
        case 4:
            ap->register_op("NOT");
            ap->set_cycles(ap->word_size);
       	    ap->_not<T>(mem);
	    break;
        case 5:
            ap->register_op("SLL");
            ap->set_cycles(ap->word_size);
   	        ap->_sll<T>(mem);
	    break;
	case 6:
            ap->register_op("SRL");
            ap->set_cycles(ap->word_size);
   	        ap->_srl<T>(mem);
	    break;
       	default:
            illegal_instruction();
    }
    
}

reg_t rva_t::custom1(rocc_insn_t insn, reg_t xs1, reg_t xs2)
{
  
  uint8_t funct_op = (insn.funct >> 3);
  uint8_t funct_size = (insn.funct & 7);
  if (funct_op == 0) 
  {
    ap->input_addr_a = xs1;
    ap->input_addr_b = xs2;
  } else
  {
        ap->mem_size = xs1 * 2;
        ap->output_addr = xs2;
        ap->word_size = funct_size * 8;
        void* mem;
	
        switch (ap->word_size)
	{
	    case 8:
                mem = (uint8_t*) malloc(sizeof(uint8_t)*ap->mem_size);
    	        in_place_load_uint8((uint8_t*)mem, ARITH);
                this->custom1_exec<uint8_t>(insn, (uint8_t*) mem);
                in_place_store_uint8((uint8_t*)mem, ARITH);
		break;
	    case 16:
	 	mem = (uint16_t*) malloc(sizeof(uint16_t)*ap->mem_size);
    	        in_place_load_uint16((uint16_t*) mem, ARITH);
                this->custom1_exec<uint16_t>(insn, (uint16_t*) mem);
                in_place_store_uint16((uint16_t*)mem, ARITH);
		break;
	    case 32:
	 	mem = (uint32_t*) malloc(sizeof(uint32_t)*ap->mem_size);
    	        in_place_load_int32((int*)mem, ARITH);
                this->custom1_exec<uint32_t>(insn, (uint32_t*) mem);
                in_place_store_uint32((uint32_t*)mem, ARITH);
		break;
	    case 64:
	 	mem = (uint64_t*) malloc(sizeof(uint64_t)*ap->mem_size);
    	        in_place_load_uint64((uint64_t*)mem, ARITH);
                this->custom1_exec<uint64_t>(insn, (uint64_t*) mem);
                in_place_store_uint64((uint64_t*)mem, ARITH);
	    default:
	 	mem = (uint64_t*) malloc(sizeof(uint64_t)*ap->mem_size);
    	        in_place_load_uint64((uint64_t*)mem, ARITH);
                this->custom1_exec<uint64_t>(insn, (uint64_t*) mem);
                in_place_store_uint64((uint64_t*)mem, ARITH);
		break;
	}
    free(mem);
    ap->reset();
    ap->op_id++;
   }  
    
   
    return -1; // in all cases, the accelerator returns nothing
    
}

template <typename T> 
void rva_t::custom1_exec(rocc_insn_t insn, T* mem)
{
    
    uint8_t funct_op = (insn.funct >> 3);
    switch (funct_op)
        {
    	case 1:
            ap->register_op("ADD");
    	    ap->add<T>(mem);
	    break;
        case 2: 
            ap->register_op("SUB");
            ap->sub<T>(mem);
	    break;
        case 3:
            ap->register_op("MULT");
            ap->mult<T>(mem);
	    break;
        case 4:
            ap->register_op("DIV");
            ap->div<T>(mem);
	    break;
	default:
            illegal_instruction();
	}
       
}

reg_t rva_t::custom2(rocc_insn_t insn, reg_t xs1, reg_t xs2)
{
  
  uint8_t funct_op = (insn.funct >> 3);
  uint8_t funct_size = (insn.funct & 7);
  if (insn.funct == 0) 
  {
    ap->input_addr = xs1;
    ap->output_addr = xs2;
  }else
  {
        ap->mem_size = xs1;	
        ap->factor = xs2;
        ap->word_size = funct_size * 8;
        void* mem;
	
        switch (ap->word_size)
	{
	    case 8:
	 	mem = (uint8_t*) malloc(sizeof(uint8_t)*ap->mem_size);
                in_place_load_uint8((uint8_t*) mem, LOGIC);
                this->custom2_exec<uint8_t>(insn, (uint8_t*) mem);
                in_place_store_uint8((uint8_t*) mem, LOGIC);
		break;
	    case 16:
	 	mem = (uint16_t*) malloc(sizeof(uint16_t)*ap->mem_size);
	        in_place_load_uint16((uint16_t*) mem, LOGIC);
                this->custom2_exec<uint16_t>(insn, (uint16_t*) mem);
                in_place_store_uint16((uint16_t*) mem, LOGIC);	
                break;
	    case 32:
	 	mem = (uint32_t*) malloc(sizeof(uint32_t)*ap->mem_size);
	        in_place_load_uint32((uint32_t*) mem, LOGIC);
                this->custom2_exec<uint32_t>(insn, (uint32_t*) mem);
                in_place_store_uint32((uint32_t*) mem, LOGIC);	
		break;
	    case 64:
	 	mem = (uint64_t*) malloc(sizeof(uint64_t)*ap->mem_size);
	        in_place_load_uint64((uint64_t*) mem, LOGIC);
                this->custom2_exec<uint64_t>(insn, (uint64_t*) mem);
                in_place_store_uint64((uint64_t*) mem, LOGIC);	
		break;
	    default:
	 	mem = (uint64_t*) malloc(sizeof(uint64_t)*ap->mem_size);
	        in_place_load_uint64((uint64_t*) mem, LOGIC);
                this->custom2_exec<uint64_t>(insn, (uint64_t*) mem);
                in_place_store_uint64((uint64_t*) mem, LOGIC);	
		break;
	}

        free(mem);
        ap->reset();
        ap->op_id++;
  }  
    
  
    return -1; // in all cases, the accelerator returns nothing
    
}

template <typename T> 
void rva_t::custom2_exec(rocc_insn_t insn, T* mem)
{
    uint8_t funct_op = (insn.funct >> 3);
    switch (funct_op)
    {
        case 1: 
            ap->register_op("SET_RVA");
            ap->set_cycles(ap->word_size*2);
            ap->set_rva<T>(mem);
	    break;
	default:
            illegal_instruction();
    }
    
}

void rva_t::count_info(){
    uint64_t total_cycles = 0;
    uint64_t op_cycles = 0;

    for (const auto& kv : this->ap->info_ops_m) {
        op_cycles += kv.second->cycles;
    }

    total_cycles = op_cycles; 
    printf("Op Cycles: %u\n", total_cycles);
    printf("PIM Write Count: %u\n", pim_write_count);
    printf("PIM Load Count: %u\n", pim_load_count);
    printf("Total PIM Cycles:%u\n", total_cycles);
}
