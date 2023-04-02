 ²  &é"'(-è_çà#ifndef RUSH_HOUR_ETU_COORDONNEES_H
#define RUSH_HOUR_ETU_COORDONNEES_H

typedef struct Coordonnees {
	int x;
	int y;

	Coordonnees(int x, int y);

} Coordonnees;

bool operator==(const Coordonnees &a, const Coordonnees &b);
bool operator!=(const Coordonnees &a, const Coordonnees &b);

#endif //RUSH_HOUR_ETU_COORDONNEES_H
