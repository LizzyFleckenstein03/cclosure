#include <stdio.h>
#include <stdlib.h>
#include "closure.h"
#include "player.h"

static bool player_adult(Player *self)
{
	return self->age >= 18;
}

static void player_print(Player *self)
{
	printf("Name: %s\nAge: %d\n", self->name, self->age);
}

static void player_birthday(Player *self)
{
	self->age++;
}

static int player_compare(Player *other, Player *self)
{
	return self->age - other->age;
}

static void player_delete(Player *self)
{
	closure_destroy(self->closure);
	free(self);
}

Player *player(char *name)
{
	Player *self = malloc(sizeof *self);
	self->name = name;
	self->age = 0;

	self->closure = closure_create(self, (ClosureParam[5]) {
		{&player_adult,    &self->adult,    0},
		{&player_print,    &self->print,    0},
		{&player_birthday, &self->birthday, 0},
		{&player_compare,  &self->compare,  1},
		{&player_delete,   &self->delete,   0},
	}, 5);

	return self;
}
