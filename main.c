#include <stdio.h>
#include <stdlib.h>
#include "cpu.h"
#include "errors.h"
#include "config.h"

int main(int argc, char** argv)
{
	FILE* bios_file = fopen("bios-bochs","r");
	cpu_t* cpu = new_cpu(bios_file);
	int rv = 0;
	FILE* floppy = NULL;
	print_copyright();
	printf("\n");
	if(cpu == NULL)
	{
		fprintf(stderr,"Couldn't init CPU.  Try again please.\n");
		rv = -1;
	}
	if(argc == 2)
	{
		floppy = fopen(argv[1],"r");
	}
	else
	{
		fprintf(stderr,USAGE);
		return -1;
	}
	rv = boot_from_floppy(cpu,floppy);
	if(!rv)
	{
		run(cpu);
	}
	else
	{
		cpu->errno = ENO_BOOT_MEDIUM;
	}
	dump_state(*cpu);
	free_cpu(cpu);
	return 0;
}
