#define MAX_PUBLIC_GARAGE   (150)

enum e_publicgarage
{
    pgName[64],
    Float:pgPOS[3],
    Float:pgSpawnPOS[4],

    pgInterior,
    pgWorld,

    pgArea,
    pgObject,
    pgIcon
}
new PublicGarage[MAX_PUBLIC_GARAGE][e_publicgarage],
    Iterator:PublicGarage<MAX_PUBLIC_GARAGE>;