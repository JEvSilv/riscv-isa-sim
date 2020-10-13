#include "aptemplate.h"

class APrv : public APTemplate
{
    public:
        APrv();
        ~APrv();

        void lookup_add_init();
        void lookup_mult_init();
        void lookup_sub_init();
        
        //logic
        template <typename T> void _and(T* mem)
        {
            for(uint32_t i = 0; i < this->mem_size; i++)
            {
                mem[i] &= this->factor;
            }
        };

        template <typename T> void _or(T* mem)
        {
            for(uint32_t i = 0; i < this->mem_size; i++)
            {
                mem[i] |= this->factor;
            }
        };

        template <typename T> void _xor(T* mem)
        {
            for(uint32_t i = 0; i < this->mem_size; i++)
            {
                mem[i] ^= this->factor;
            }
        };

        template <typename T> void _not(T* mem)
        {
            for(uint32_t i = 0; i < this->mem_size; i++)
            {
                mem[i] = ~mem[i];
            }
        };

        template <typename T> void _sll(T* mem)
        {
            for(uint32_t i = 0; i < this->mem_size; i++)
            {
                mem[i] <<= this->factor;
            }
        };

        template <typename T> void _srl(T* mem)
        {
            for(uint32_t i = 0; i < this->mem_size; i++)
            {
                mem[i] >>= this->factor;
            }
        };

        //arith
        template <typename T> void add(T* mem)
        {
            std::vector<T*> B_v, A_v;
            std::vector<bool*> Cr_v;
            std::vector<bool*> Tag_v;
            uint32_t op_size = this->mem_size/2;
            this->info_ops_m[op_id]->op_qt = op_size;
            uint32_t base    = op_size;
            uint32_t bit, pass, word, i;
            uint32_t word_size = 8 * sizeof(T);
            
            for (i = 0; i < op_size; i++) 
            {
                B_v.push_back(&mem[i]); 
                A_v.push_back(&mem[base + i]); 
        	Cr_v.push_back(new bool(0));
        	Tag_v.push_back(new bool(0));
            }
	
            for(bit = 0; bit < word_size; bit++)
            {
        	for(pass = 0; pass < 4; pass++)
	        {
            	    for(word = 0; word < op_size; word++)
	            {
        		this->set_mask(bit, 0, bit, bit);		
	        	this->set_key(this->lookup_add, pass, bit, 0, bit, bit);

		        this->compare<T>(A_v.at(word), B_v.at(word), NULL, Cr_v.at(word), Tag_v.at(word)); 
                        if(log_mode) {
    	        	    this->tracing_add<T>(bit, pass, word, *Tag_v.at(word), mem);	
                        }	
		        this->write<T>(this->lookup_add, pass, bit, 0, Cr_v.at(word), B_v.at(word), Tag_v.at(word));
	            }
            
                    if(this->info_ops_m[op_id]->cycle_w) {
                        this->info_ops_m[op_id]->cycles++;
                        this->info_ops_m[op_id]->cycle_w = false;
                    }

                    this->info_ops_m[op_id]->cycles++;
	        }	
            }
	    info_ops_m[op_id]->info_plot();
        };

        template <typename T> void sub(T* mem)
        {
            std::vector<T*> B_v, A_v;
            std::vector<bool*> Cr_v;
            std::vector<bool*> Tag_v;
            uint32_t op_size = this->mem_size/2;
            this->info_ops_m[op_id]->op_qt = op_size;
            uint32_t base    = op_size;
            uint32_t word_size = 8 * sizeof(T);
            uint32_t bit, pass, word, i;
            for (i = 0; i < op_size; i++) 
            {
                B_v.push_back(&mem[i]); 
                A_v.push_back(&mem[base + i]); 
        	Cr_v.push_back(new bool(0));
	        Tag_v.push_back(new bool(0));
            }
            
	    for(bit = 0; bit < word_size; bit++)
            {
        	for(pass = 0; pass < 4; pass++)
	        {
            	    for(word = 0; word < op_size; word++)
	            {
        	        this->set_mask(bit, 0, bit, bit);		
	        	this->set_key(this->lookup_sub, pass, bit, 0, bit, bit);

		        this->compare<T>(A_v.at(word), B_v.at(word), NULL, Cr_v.at(word), Tag_v.at(word)); 

                        if(log_mode) {
            		    this->tracing_add(bit, pass, word, *Tag_v.at(word), mem);		
                        }
                
                        this->write<T>(this->lookup_sub, pass, bit, 0, Cr_v.at(word), B_v.at(word), Tag_v.at(word));

                    }

                    if(this->info_ops_m[op_id]->cycle_w) {
                        this->info_ops_m[op_id]->cycles++;
                        this->info_ops_m[op_id]->cycle_w = false;
                    }

                    this->info_ops_m[op_id]->cycles++;
               	}	
            }
	    info_ops_m[op_id]->info_plot();
        };

        template <typename T> void mult(T* mem) {
            std::vector<T*> B_v, A_v;
            std::vector<T*> R_v;
            std::vector<bool*> Tag_v;
            uint32_t op_size = this->mem_size/2;
            this->info_ops_m[op_id]->op_qt = op_size;
            uint32_t base  = op_size;
            uint32_t bit_A, bit_B, pass, word, i;
            uint32_t r_k, cr_k;
            //uint32_t range = 4;
            uint32_t range = (8 * sizeof(T))/2;
            r_k  = 0;
            cr_k =  range - 1;
               
            for (i = 0; i < op_size; i++) 
            {
                B_v.push_back(&mem[i]); 
                A_v.push_back(&mem[base + i]); 
        	R_v.push_back(new T(0));
        	Tag_v.push_back(new bool(0));
            }

            for(bit_A = 0; bit_A < range; bit_A++)
            {
              cr_k++; 
              for(bit_B = 0; bit_B < range; bit_B++)
              {
                  r_k = bit_A + bit_B;
        	  for(pass = 0; pass < 4; pass++)
        	  {
            	      for(word = 0; word < op_size; word++)
        	      {
        		  this->set_mask(r_k, cr_k, bit_A, bit_B);	
        		  this->set_key(this->lookup_mult, pass, r_k, cr_k, bit_A, bit_B);
                          this->compare(A_v.at(word), B_v.at(word), R_v.at(word), NULL, Tag_v.at(word));
                          if(log_mode) {
                            this->tracing_mult(bit_A, pass, word, *Tag_v.at(word), mem, R_v);
                          }
                          this->write(this->lookup_mult, pass, r_k, cr_k, NULL, R_v.at(word), Tag_v.at(word));
        	      }
        
                      if(this->info_ops_m[op_id]->cycle_w) {
                        this->info_ops_m[op_id]->cycles++;
                        this->info_ops_m[op_id]->cycle_w = false;
                      }

                      this->info_ops_m[op_id]->cycles++;
  	          }	
               }
            }

            for(i = 0; i < op_size; i++)
            {
                mem[i] = *R_v.at(i);
            }

       	    info_ops_m[op_id]->info_plot();
        };

        template <typename T> void div(T* mem)
        {
            uint32_t op_size = this->mem_size/2;
            uint32_t base    = op_size;

            for(uint32_t i = 0; i < op_size; i++)
            {
                mem[i] = mem[i] / mem[base + i];
            }
        };
        
        //others
        template <typename T> void set_rva(T* mem)
        {
            for(uint32_t i = 0; i < this->mem_size; i++)
            {
                mem[i] = this->factor;
            }
        };       
        
        std::map<uint32_t, pass*> lookup_add;
        std::map<uint32_t, pass*> lookup_mult;
        std::map<uint32_t, pass*> lookup_sub;
};
