# sphinx_gallery_thumbnail_number = 3
import matplotlib.pyplot as plt
import numpy as np
def graph_1_3(mm,check,bit,_ylabel):
    fig, axs = plt.subplots(1, 3, constrained_layout=True)# figsize=(10, 8),
    fig.set_figheight(4)
    fig.set_figwidth(10)
    r_p = r_s = []

    #plt.axis('scaled')
    
    if(len(mm[0]) > 10):
        r_p = [i+1 for i in range(1500)]
        r_s = [i+2 for i in range(len(mm[0]))]
    else:
        r_p = [100,250,500,1000,1500]
        r_s = [5,25,50,75,100]

    axs[0].plot(r_s, mm[0],'o-',markersize=2, markeredgewidth=2,label='AP')
    axs[0].plot(r_s, mm[1],'o-', markersize=2, markeredgewidth=2,label='CPU')
    axs[0].legend()
    #axs[0].set_ylim([0,10000000])
    axs[0].set_title('Matrix Multiply')
    axs[0].set_ylabel(_ylabel, fontweight='bold')
    axs[0].set_xlabel('Matrix size', fontweight='bold')
   
    axs[1].plot(r_p,check[0], '.-', markersize=1, markeredgewidth=2, label='AP')
    axs[1].plot(r_p,check[1], '.-',markersize=1, markeredgewidth=2, label='CPU')
    axs[1].legend()
    axs[1].set_title('Checksum')
    axs[1].set_ylabel(_ylabel, fontweight='bold')
    axs[1].set_xlabel('Packet size', fontweight='bold')

    #axs[1].set_ylim([0,10000])

    axs[2].plot(r_p,bit[0], '.-', markersize=2, markeredgewidth=2, label='AP')
    axs[2].plot(r_p, bit[1], '.-',markersize=2, markeredgewidth=2, label='CPU')
    axs[2].legend()
    #axs[2].set_ylim([0,10000])
    axs[2].set_title('Bitcount')
    axs[2].set_ylabel(_ylabel, fontweight='bold')
    axs[2].set_xlabel('Packet size', fontweight='bold')
    plt.tight_layout()
    #plt.constrained_layout(pad=0.4, w_pad=0.5, h_pad=1.0)
    plt.show()

def graph_2_3(mm_i,check_i,bit_i, mm_m, check_m, bit_m):
    fig, axs = plt.subplots(2, 3, constrained_layout=True)# figsize=(10, 8),
    fig.set_figheight(4)
    fig.set_figwidth(10)
    r_p = r_s = []

    #plt.axis('scaled')
    
    r_p = [i+1 for i in range(1500)]
    r_s = [i+2 for i in range(len(mm_m[0]))]

    axs[0,0].plot(r_s, mm_i[0],'+',label='AP')
    axs[0,0].plot(r_s, mm_i[1],'^',label='CPU')
    axs[0,0].legend()
    #axs[0].set_ylim([0,10000000])
    axs[0,0].set_yscale('log')
    axs[0,0].set_title('Matrix Multiply')
    axs[0,0].set_ylabel('Cycles', fontweight='bold')

    axs[0,0].set_xlabel('Matrix size NxN', fontweight='bold')
   
    axs[0,1].plot(r_p,check_i[0], '+', label='AP')
    axs[0,1].plot(r_p,check_i[1], '^', label='CPU')
    axs[0,1].legend()
    axs[0,1].set_yscale('log')
    axs[0,1].set_title('Checksum')
    axs[0,1].set_ylabel('Cycles', fontweight='bold')
    axs[0,1].set_xlabel('Packet size', fontweight='bold')

    #axs[1].set_ylim([0,10000])

    axs[0,2].plot(r_p, bit_i[0], '+', label='AP')
    axs[0,2].plot(r_p, bit_i[1], '^', label='CPU')
    axs[0,2].legend()
    #axs[2].set_ylim([0,10000])
    axs[0,2].set_yscale('log')
    axs[0,2].set_title('Bitcount')
    axs[0,2].set_ylabel('Cycles', fontweight='bold')
    axs[0,2].set_xlabel('Packet size', fontweight='bold')

    # Memory Access
    axs[1,0].plot(r_s, mm_m[0],'+', label='AP')
    axs[1,0].plot(r_s, mm_m[1],'^', label='CPU')
    axs[1,0].legend()
    #axs[0].set_ylim([0,10000000])
    axs[1,0].set_yscale('log')
    axs[1,0].set_title('Matrix Multiply')
    axs[1,0].set_ylabel('Load/Store', fontweight='bold')
    axs[1,0].set_xlabel('Matrix size NxN', fontweight='bold')
   
    axs[1,1].plot(r_p,check_m[0], '+', label='AP')
    axs[1,1].plot(r_p,check_m[1], '^', label='CPU')
    axs[1,1].legend()
    axs[1,1].set_yscale('log')
    axs[1,1].set_title('Checksum')
    axs[1,1].set_ylabel('Load/Store', fontweight='bold')
    axs[1,1].set_xlabel('Packet size', fontweight='bold')

    #axs[1].set_ylim([0,10000])

    axs[1,2].plot(r_p, bit_m[0], '+', label='AP')
    axs[1,2].plot(r_p, bit_m[1], '^', label='CPU')
    axs[1,2].legend()
    axs[1,2].set_yscale('log')
    axs[1,2].set_title('Bitcount')
    axs[1,2].set_ylabel('Load/Store', fontweight='bold')
    axs[1,2].set_xlabel('Packet size', fontweight='bold')

    plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=1.0)
    plt.yscale("log")
    plt.show()


def extract(arq):
    counter = []
    with open(arq) as f:                                          
        for line in f:                                             
            counter.append(int(line))
    return counter
    
#inst = 0 | memory = 1
def main():
    #Cycles
    in_place_mm_cycles = extract("results_in_place_mm.txt")
    in_place_check_cycles = extract("results_in_place_check.txt")
    in_place_bit_cycles = extract("results_in_place_bit.txt")

    normal_mm_cycles = extract("results_normal_mm.txt")
    normal_check_cycles = extract("results_normal_check.txt")
    normal_bit_cycles = extract("results_normal_bit.txt")
    

    # Load/Store
    in_place_mm_ma = extract("results_in_place_mm_ma.out")
    in_place_check_ma = extract("results_in_place_check_ma.out")
    in_place_bit_ma = extract("results_in_place_bit_ma.out")

    normal_mm_ma = extract("results_normal_mm_ma.out")
    normal_check_ma = extract("results_normal_check_ma.out")
    normal_bit_ma = extract("results_normal_bit_ma.out")

    graph_2_3([in_place_mm_cycles, normal_mm_cycles],
            [in_place_check_cycles, normal_check_cycles],
            [in_place_bit_cycles, normal_bit_cycles],
            [in_place_mm_ma, normal_mm_ma],
            [in_place_check_ma, normal_check_ma],
            [in_place_bit_ma, normal_bit_ma])
main()










