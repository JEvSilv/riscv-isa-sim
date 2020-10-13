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

    axs[0,0].plot(r_s, mm_i[0],'o-',markersize=2, markeredgewidth=2,label='AP')
    axs[0,0].plot(r_s, mm_i[1],'o-', markersize=2, markeredgewidth=2,label='CPU')
    axs[0,0].legend()
    #axs[0].set_ylim([0,10000000])
    axs[0,0].set_title('Matrix Multiply')
    axs[0,0].set_ylabel('Instructions', fontweight='bold')

    axs[0,0].set_xlabel('Matrix size', fontweight='bold')
   
    axs[0,1].plot(r_p,check_i[0], '.-', markersize=1, markeredgewidth=2, label='AP')
    axs[0,1].plot(r_p,check_i[1], '.-',markersize=1, markeredgewidth=2, label='CPU')
    axs[0,1].legend()
    axs[0,1].set_title('Checksum')
    axs[0,1].set_ylabel('Instructions', fontweight='bold')
    axs[0,1].set_xlabel('Packet size', fontweight='bold')

    #axs[1].set_ylim([0,10000])

    axs[0,2].plot(r_p, bit_i[0], '.-', markersize=2, markeredgewidth=2, label='AP')
    axs[0,2].plot(r_p, bit_i[1], '.-',markersize=2, markeredgewidth=2, label='CPU')
    axs[0,2].legend()
    #axs[2].set_ylim([0,10000])
    axs[0,2].set_title('Bitcount')
    axs[0,2].set_ylabel('Instructions', fontweight='bold')
    axs[0,2].set_xlabel('Packet size', fontweight='bold')

    # Memory Access
    axs[1,0].plot(r_s, mm_m[0],'o-',markersize=2, markeredgewidth=2,label='AP')
    axs[1,0].plot(r_s, mm_m[1],'o-', markersize=2, markeredgewidth=2,label='CPU')
    axs[1,0].legend()
    #axs[0].set_ylim([0,10000000])
    axs[1,0].set_title('Matrix Multiply')
    axs[1,0].set_ylabel('Memory access', fontweight='bold')
    axs[1,0].set_xlabel('Matrix size', fontweight='bold')
   
    axs[1,1].plot(r_p,check_m[0], '.-', markersize=1, markeredgewidth=2, label='AP')
    axs[1,1].plot(r_p,check_m[1], '.-',markersize=1, markeredgewidth=2, label='CPU')
    axs[1,1].legend()
    axs[1,1].set_title('Checksum')
    axs[1,1].set_ylabel('Memory acess', fontweight='bold')
    axs[1,1].set_xlabel('Packet size', fontweight='bold')

    #axs[1].set_ylim([0,10000])

    axs[1,2].plot(r_p, bit_m[0], '.-', markersize=2, markeredgewidth=2, label='AP')
    axs[1,2].plot(r_p, bit_m[1], '.-',markersize=2, markeredgewidth=2, label='CPU')
    axs[1,2].legend()
    #axs[2].set_ylim([0,10000])
    axs[1,2].set_title('Bitcount')
    axs[1,2].set_ylabel('Memory access', fontweight='bold')
    axs[1,2].set_xlabel('Packet size', fontweight='bold')

    plt.tight_layout(pad=0.4, w_pad=0.5, h_pad=1.0)
    plt.show()


def extract(arq):
    inst_count = []
    ma_count = []
    i = 1
    with open(arq) as f:                                          
        for line in f:                                             
            if i > 2 : 
                if(i % 2):
                    inst_count.append(int(line.split(",")[1]))
                else:
                    ma_count.append(int(line.split(",")[1]))
            i = i + 1
    return inst_count, ma_count
    
#inst = 0 | memory = 1
def main():
    mm_inst = check_inst = bit_inst = []
    mm_mem = check_mem = bit_mem = []

    im_inst, im_mem = extract("results_im.csv")
    nm_inst, nm_mem = extract("results_nm.csv")
    
    mm_inst = [im_inst, nm_inst]
    mm_mem = [im_mem, nm_mem]

    ic_inst, ic_mem = extract("results_ic.csv")
    nc_inst, nc_mem = extract("results_nc.csv")
    
    check_inst = [ic_inst, nc_inst]
    check_mem = [ic_mem, nc_mem]
   
    print(ic_inst[1499], nc_inst[1499])
    print(ic_mem[1499], nc_mem[1499])
   
    ib_inst, ib_mem = extract("results_ib.csv")
    nb_inst, nb_mem = extract("results_nb.csv")

    bit_inst = [ib_inst, nb_inst]
    bit_mem = [ib_mem, nb_mem]

    graph_2_3(mm_inst, check_inst, bit_inst, mm_mem, check_mem, bit_mem)
    #print(mm_inst)
    #graph(mm_inst,check_inst,bit_inst,'Instructions')
    #graph(mm_mem,check_mem,bit_mem,'Memory access')
    
    #---------------------------------- Começa por 3 pq mm começa por 2
    mm_inst_sel = [[im_inst[3],im_inst[23],im_inst[48],im_inst[74],im_inst[98]],
                   [nm_inst[3],nm_inst[23],nm_inst[48],nm_inst[74],nm_inst[98]]]

    mm_mem_sel = [[im_mem[3],im_mem[23],im_mem[48],im_mem[74],im_mem[98]],
                   [nm_mem[3],nm_mem[23],nm_mem[48],nm_mem[74],nm_mem[98]]]

    check_inst_sel = [[ic_inst[99],ic_inst[249],ic_inst[499],ic_inst[999],ic_inst[1499]],
                     [nc_inst[99],nc_inst[249],nc_inst[499],nc_inst[999],nc_inst[1499]]]

    check_mem_sel = [[ic_mem[99],ic_mem[249],ic_mem[499],ic_mem[999],ic_mem[1499]],
                     [nc_mem[99],nc_mem[249],nc_mem[499],nc_mem[999],nc_mem[1499]]]

    bit_inst_sel = [[ib_inst[99],ib_inst[249],ib_inst[499],ib_inst[999],ib_inst[1499]],
                     [nb_inst[99],nb_inst[249],nb_inst[499],nb_inst[999],nb_inst[1499]]]

    bit_mem_sel = [[ib_mem[99],ib_mem[249],ib_mem[499],ib_mem[999],ib_mem[1499]],
                   [nb_mem[99],nb_mem[249],nb_mem[499],nb_mem[999],nb_mem[1499]]]
    #print(mm_mem_sel)
    #graph(mm_inst_sel,check_inst_sel,bit_inst_sel,'Instructions')
    #graph(mm_mem_sel,check_mem_sel,bit_mem_sel,'Memory access')
main()










