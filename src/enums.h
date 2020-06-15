#ifndef ENUMS_H
#define ENUMS_H


enum enemy_type {UNDEAD, GHOUL, HELLHOUND, NOONWRAITH, BASILISK, SIREN};    // UNDEAD - F ,BASILISK - ~ , GHOUL - G, HELLHOUND - E, DRYAD - Y, SIREN - %
enum player_class {PALADIN, MAGE, ROGUE};                              // this out
enum body_part {HEAD, TORSO, ARMS, LEGS, HANDS, FEET};
enum direction {UP, DOWN, LEFT, RIGHT, STAY};
enum attack_type {SLAIN, KICK, SPELL, BITE, SCRATCH, TEAR, MELEE, SLAP};                           // todo 
enum map_type {COUNTRYSIDE, DUNGEON, TESTROOM};


#endif