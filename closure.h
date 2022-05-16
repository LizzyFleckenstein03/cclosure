#ifndef _CLOSURE_H_
#define _CLOSURE_H_

typedef struct {
	void *fun;
	void *ptr;
	unsigned int arg;
} ClosureParam;

void *closure_create(void *self, ClosureParam *params, size_t num);
void closure_destroy(void *closure);

#endif
