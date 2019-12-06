#pragma once

const int FPS = 60;

const int DELAY_TIME = 1000.0f / FPS;

const enum class keyPressed { UP, DOWN, LEFT, RIGHT, ESC, SPACE, W, A, S, D, COUNT };

const enum class entityType {OBSTACLE, PLAYER, GOLD};