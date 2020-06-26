#pragma once

#ifndef ENUMS_H
#define ENUMS_H

enum enemy_type {UNDEAD, GHOUL, HELLHOUND, NOONWRAITH, BASILISK, SIREN};
enum player_class {PALADIN, MAGE, ROGUE, BUILDER};
enum body_part {HEAD, TORSO, LEGS, HANDS, FEET};
enum direction {UP, DOWN, LEFT, RIGHT, STAY};
enum attack_type {SLASH, KICK, SPELL, BITE, SCRATCH, TEAR, MELEE, SLAP};
enum map_type {COUNTRYSIDE, DUNGEON, TESTROOM};
enum prop_type {WALL, TREE, STONE, BUSH, VOID};

#endif