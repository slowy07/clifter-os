#include <cpu/cpuid.h>


/**
 * checks if the cpuid instruction is available
 * returns true if available
 */
bool has_cpuid_ins(){
	int res;
	__asm__ __volatile__ (".intel_syntax\n\t"
	                      "pushfq\n\t"
	                      "pushfq\n\t"
	                      "xor dword ptr [%%rsp],0x200000\n\t"
	                      "popfq\n\t"
	                      "pushfq\n\t"
	                      "pop %%rax\n\t"
	                      "xor %%eax,[%%rsp]\n\t"
	                      "popfq\n\t"
	                      "and %%eax,0x200000\n\t"
	                      ".att_syntax"
	                      :"=a"(res));
	return res;
}