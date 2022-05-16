#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include "closure.h"

typedef struct __attribute__((packed)) {
	uint16_t opcode_0;
	void *operand_0;

	uint16_t opcode_1;
	void *operand_1;

	uint16_t opcode_2;
} Closure;

// rdi, rsi, rdx, rcx, r8, r9
static const uint16_t mov[6] = {0xbf48, 0xbe48, 0xba48, 0xb948, 0xb849, 0xb949};
static size_t size;

__attribute__((constructor)) static void init()
{
	size = sysconf(_SC_PAGESIZE);
}

void *closure_create(void *self, ClosureParam *param, size_t num)
{
	Closure *block = mmap(NULL, size, PROT_WRITE | PROT_READ, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);

	for (size_t i = 0; i < num; i++) {
		if (param[i].arg >= 6)
			abort(); // TODO

		block[i].opcode_0 = 0xb848;
		block[i].operand_0 = param[i].fun;

		block[i].opcode_1 = mov[param[i].arg];
		block[i].operand_1 = self;

		block[i].opcode_2 = 0xe0ff;

		*((void **) param[i].ptr) = &block[i];
	}

	mprotect(block, size, PROT_READ | PROT_EXEC);
	return block;	
}

void closure_destroy(void *closure)
{
	munmap(closure, size);	
}
