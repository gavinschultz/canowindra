#include <stdlib.h>

// characters
typedef enum CharacterStatus
{
    CharacterStatusStanding,
    CharacterStatusFallen,
    CharacterStatusRunning,
    CharacterStatusMounted,
    CharacterStatusDead,
    CharacterStatusSpeaking
} CharacterStatus;

typedef enum MountStatus
{
    MountStatusStanding,
    MountStatusFallen,
    MountStatusTrotting,
    MountStatusCantering,
    MountStatusGalloping,
    MountStatusDead
} MountStatus;

typedef struct Point
{
    float x, y;
} POINT;

struct Mount
{
    POINT *position;
    int health;
    int defense;
    int power;
    MountStatus status;
    float speed;
};

typedef struct Character
{
    POINT position;
    int health;
    int defense;    // defence factor e.g. armor
    int power;      // determines strength / muscles
    CharacterStatus status;
    float speed;
} CHARACTER;

CHARACTER *bleda = NULL;
CHARACTER *zerko = NULL;
CHARACTER *atilla = NULL;

void move_character(CHARACTER *character)
{

}

void die_character(CHARACTER *character)
{

}
