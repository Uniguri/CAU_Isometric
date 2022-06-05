#pragma once

#include <bangtal.h>

#include "platform.h"
#include "Player.h"
#include "bullet.h"
#include "turret.h"

void GameSetting(void);
void MainGameSetting(void);
void ResetGame(void);

void timerCallback(TimerID timer);
void keyboardCallback(KeyCode code, KeyState state);
void mouseCallback(ObjectID obj, int x, int y, MouseAction action);

void StartSceneMCB(ObjectID obj, int x, int y, MouseAction action);
void GameOverSceneMCB(ObjectID obj, int x, int y, MouseAction action);
void ClearSceneMCB(ObjectID obj, int x, int y, MouseAction action);