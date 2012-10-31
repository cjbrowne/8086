#include <stdio.h>
#include <stdlib.h>
#include "include/cpu.h"

int main(int argc, char** argv)
{
	cpu_t* cpu = new_cpu();
	int rv = 0;
	FILE* floppy = NULL;
	if(cpu == NULL)
	{
		fprintf(stderr,"Couldn't init CPU.  Try again please.\n");
		rv = -1;
	}
	if(argc == 2)
	{
		floppy = fopen(argv[1],"r");
	}
	rv = boot_from_floppy(cpu,floppy);
	if(!rv)
	{
		run(cpu);
	}
	dump_state(*cpu);
	free_cpu(cpu);
	return 0;
}
