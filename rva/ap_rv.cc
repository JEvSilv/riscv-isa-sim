#include "ap_rv.h"

APrv::APrv()
{
    printf("\t # RV Across #\n");
    this->lookup_add_init();
    this->lookup_sub_init();
    this->lookup_mult_init();
}

APrv::~APrv()
{}

void APrv::lookup_add_init()
{
    this->lookup_add[0]	= new pass(0,0,1,1,1,0);
    this->lookup_add[1]	= new pass(0,0,0,1,0,1);
    this->lookup_add[2]	= new pass(1,0,0,0,0,1);
    this->lookup_add[3]	= new pass(1,0,1,0,1,0);
}


void APrv::lookup_sub_init()
{
    //order influences
    this->lookup_sub[0]	= new pass(1,0,1,0,0,0);
    this->lookup_sub[1]	= new pass(0,0,0,1,1,1);
    this->lookup_sub[2]	= new pass(1,0,0,0,1,1);
    this->lookup_sub[3]	= new pass(0,0,1,1,0,0);
}

void APrv::lookup_mult_init()
{
    this->lookup_mult[0] = new pass(0,1,1,1,1,0);
    this->lookup_mult[1] = new pass(0,0,1,1,0,1);
    this->lookup_mult[2] = new pass(1,0,0,1,0,1);
    this->lookup_mult[3] = new pass(1,1,0,1,1,0);
}
