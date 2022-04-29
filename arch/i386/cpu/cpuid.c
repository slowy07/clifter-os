#include <cpu/cpuid.h>


bool has_cpuid_ins() {
    int res;
    __asm__ __volatile__ (".intel_syntax\n\t"
	                      "pushfd\n\t"
	                      "pushfd\n\t"
	                      "xor dword ptr [%%esp],0x200000\n\t"
	                      "popfd\n\t"
	                      "pushfd\n\t"
	                      "pop %%eax\n\t"
	                      "xor %%eax,[%%esp]\n\t"
	                      "popfd\n\t"
	                      "and %%eax,0x200000\n\t"
	                      ".att_syntax"
	                      :"=a"(res));
    
    return res;
}
