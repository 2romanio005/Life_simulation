#pragma once
#include "Definition.h"



Cell** map;


int size_screen_x;
int size_screen_y;
int size_map_x = 100;	// 120  // 220
int size_map_y = 50;	// 66	// 116
int size_cell;
int size_half_cell;
int size_creature_radius;



HBRUSH H_Gray[200];
HBRUSH H_Green;
HBRUSH H_Red;
HBRUSH H_Blue;

HPEN P_Null;

HBRUSH H_Background;
HDC MainHdc;
PAINTSTRUCT MainPs;

HDC SupHdc;
HBITMAP SupHbm;
HANDLE SupHold;

bool position_WM_SETREDRAW = true;

bool FlagFullscreen = false;
LONG FullscreenStyle;
WINDOWPLACEMENT FullscreenPlacement;



HWND StaticCountStep;
unsigned long long CountStep = 0;

HWND ButtonStop;
bool FlagStop = false;

HWND CheckBoxAutomaticStop;
bool FlagAutomaticStop = false;

HWND CheckBoxAutomaticReset;
bool FlagAutomaticReset = true;

HWND StaticTimeDrawMain;
HWND SliderTimeDraw;
HWND StaticTimeDrawLeft;
HWND StaticTimeDrawRight;
int PosSliderTimeDraw = 1;

HWND StaticStepDrawMain;
HWND SliderStepDraw;
HWND StaticStepDrawLeft;
HWND StaticStepDrawRight;
int PosSliderStepDraw = 1;


HWND CheckBoxRandDivision;
bool FlagRandDivision = false;

HWND StaticRedEat;
HWND SliderRedEat;
int PosSliderRedEat = 66;

HWND StaticRedLeave;
HWND SliderRedLeave;
int PosSliderRedLeave = 33;
int MaxPosSliderRedLeave = 100 - PosSliderRedEat;

HWND StaticGreenEat;
HWND SliderGreenEat;
int PosSliderGreenEat = 85;

HWND StaticBlueEat;
HWND SliderBlueEat;
int PosSliderBlueEat = 14;

HWND StaticAllLose;
HWND SliderAllLose;
int PosSliderAllLose = 3;


HWND StaticCountCreature;

HWND ButtonReset;

HWND ButtonSafeMap;
HWND ButtonLoadMap;

HWND EditSizeMapX;
HWND EditSizeMapY;

HWND StaticPeepData;
HWND StaticPeepBrainHeader;
std::vector<std::pair<HWND, int>> StaticPeepBrain;
HWND SliderPeepBrain;
int MaxPosSliderPeepBrain = 1;
int PosSliderPeepBrain = 0;
Creature* peep_Creature = nullptr;
bool life_peep_Creature = true;
bool last_draw_peep_Creature = true;

HWND ButtonSafeCrt;
HWND ButtonLoadCrt;


char ThisSaveDirectory[260];








