#include <stdio.h>
#include "player.h"

int main()
{
	Player *p1 = player("Fleckenstein");
	p1->age = 16;

	Player *p2 = player("lizzy22");
	p2->age = 22;

	p1->print();
	printf("age diff = %d; adult = %d\n", p1->compare(p2), p1->adult());

	for (int i = 0; i < 10; i++)
		p1->birthday();

	printf("age diff = %d; adult = %d\n", p1->compare(p2), p1->adult());

	p1->delete();
	p2->delete();
}
