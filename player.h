#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <stdbool.h>

typedef struct Player {
	int age;
	char *name;
	
	void *closure;
	bool (*adult)();
	void (*print)();
	void (*birthday)();
	int (*compare)(struct Player *other);
	void (*delete)();
} Player;

Player *player(char *name);

#endif
