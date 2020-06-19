#pragma once

#ifndef ENUMS_H
#define ENUMS_H

#include <fstream>
#include <string>

using namespace std;

enum enemy_type {UNDEAD, GHOUL, HELLHOUND, NOONWRAITH, BASILISK, SIREN};
enum player_class {PALADIN, MAGE, ROGUE};
enum body_part {HEAD, TORSO, LEGS, HANDS, FEET};
enum direction {UP, DOWN, LEFT, RIGHT, STAY};
enum attack_type {SLAIN, KICK, SPELL, BITE, SCRATCH, TEAR, MELEE, SLAP};
enum map_type {COUNTRYSIDE, DUNGEON, TESTROOM};
enum prop_type {WALL, TREE, STONE, BUSH, VOID};


/*void writeString(ofstream& os, string text);
string loadString(ifstream& is);*/

#endif