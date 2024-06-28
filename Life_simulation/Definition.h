#pragma once

#include <windows.h>
#include <WindowsX.h>

#include <fstream>

#include <algorithm>
#include <ctime>
#include <vector>
#include <string>



extern int size_screen_x;
extern int size_screen_y;
extern int size_map_x;
extern int size_map_y;
extern int size_cell;
extern int size_half_cell;

//#define size_cell 10
//#define size_half_cell 5
//#define size_map_x 93
//#define size_map_y 47

//#define size_cell 14
//#define size_half_cell 7
//#define size_map_x 93
//#define size_map_y 47

//#define size_cell 24
//#define size_half_cell 12
//#define size_map_x 46
//#define size_map_y 23

//#define size_cell 45
//#define size_half_cell 25
//#define size_map_x 22
//#define size_map_y 14

//#define size_cell 90
//#define size_half_cell 50
//#define size_map_x 11
//#define size_map_y 7

//#define size_cell 650
//#define size_half_cell 325
//#define size_map_x 1
//#define size_map_y 1



#define margin_x 10
#define margin_y 10

#define limit_energy 2000
#define limit_age 100
#define limit_power_step 5 // количество незаканивающих ход действий за ход

#define mut_chence 5 // %
#define mut_type_chence 0 // %

#define	max_brain_size 100
#define min_multiply_energy 3000 // минимальная энергия для деления

#define start_energy 70000
#define start_max_len_brain 4








class Cell;

enum TYPE_CREATURE;
enum DIRECTION;
class Creature;
class Creature_Plant;
class Creature_Herbivore;
class Creature_Scavenger;

enum TYPE_ACTION;
class Action;
class Action_go_global;
class Action_multiply_global;
class Action_eat_global;
class Action_turn_global;
class Action_condition_by_TYPE_CREATURE_global;
class Action_condition_by_Cell_global;


// в Creature.cpp
std::pair<int, int> near_cell_cord(std::pair<int, int> now_map_cord, DIRECTION to_dir);
Creature* parse_str_to_Creature(const std::pair<int, int>& map_cord, std::string str);
std::vector<Action*>* copy_brain(const std::vector<Action*>& sample_brain);

// в Cell.cpp
Cell* get_Cell_by_map_cord(const std::pair<int, int>& map_cord);

// сверху Function.cpp
int parse_str_to_int_one_step(const std::string& s, int* iter, char separator = ';');
DIRECTION turn(DIRECTION strt, DIRECTION step);
// снизу Function.cpp
std::string string_by_type_creature(TYPE_CREATURE type_creature);
std::string string_by_dir_for_condition(DIRECTION dir);
std::string string_by_dir_for_turn(DIRECTION dir);





extern Cell** map;






void OneStep();
void DrawInterface();
void Draw(HDC hdc);
void UpdateDraw(HWND hWnd);
void UpdateSizeScreen(HWND hWnd, const int size_x, const int size_y, bool flag_always = false);
void MoveWidget();
void UpdateWidget();

void StopStep(HWND hWnd);
void StartStep(HWND hWnd);


void BuildWidget(HWND hWnd);
void BuildObject();
void BuildDrawEffecter(HWND hWnd);

void DestroyWidget(HWND hWnd);
void DestroyObject();
void DestroyDrawEffecter(HWND hWnd);




extern HBRUSH H_Gray[200];
extern HBRUSH H_Green;
extern HBRUSH H_Red;

extern HPEN P_Null;


extern HBRUSH H_Background;
extern HDC MainHdc;
extern PAINTSTRUCT MainPs;

extern HDC SupHdc;
extern HBITMAP SupHbm;
extern HANDLE SupHold;
extern HBRUSH H_Blue;

#define MinSizeCell 6
extern bool position_WM_SETREDRAW;
extern int height_right_interface;



#define IndexTimerDraw 1

#define IndexButtonStop 2
#define IndexCheckBoxAutomaticStop 3

#define IndexCheckBoxRandDivision 4

#define IndexButtonReset 5

#define IndexButtonSafeMap 6
#define IndexButtonLoadMap 7
#define IndexButtonSafeCrt 8
#define IndexButtonLoadCrt 9







extern HWND StaticCountStep;
extern unsigned long long CountStep;


extern HWND ButtonStop;
extern bool FlagStop;

extern HWND CheckBoxAutomaticStop;
extern bool FlagAutomaticStop;

extern HWND StaticTimeDrawMain;
extern HWND SliderTimeDraw;
extern HWND StaticTimeDrawLeft;
extern HWND StaticTimeDrawRight;
#define MaxPosSliderTimeDraw 20
extern int PosSliderTimeDraw;

extern HWND StaticStepDrawMain;
extern HWND SliderStepDraw;
extern HWND StaticStepDrawLeft;
extern HWND StaticStepDrawRight;
#define MaxPosSliderStepDraw 20
extern int PosSliderStepDraw;


extern HWND CheckBoxRandDivision;
extern bool FlagRandDivision;

extern HWND StaticRedEat;
extern HWND SliderRedEat;
extern int PosSliderRedEat;
#define MaxPosSliderRedEat 100

extern HWND StaticRedLeave;
extern HWND SliderRedLeave;
extern int PosSliderRedLeave;
extern int MaxPosSliderRedLeave;

extern HWND StaticGreenEat;
extern HWND SliderGreenEat;
extern int PosSliderGreenEat;
#define MaxPosSliderGreenEat 100

extern HWND StaticBlueEat;
extern HWND SliderBlueEat;
extern int PosSliderBlueEat;
#define MaxPosSliderBlueEat 100

extern HWND StaticAllLose;
extern HWND SliderAllLose;
extern int PosSliderAllLose;
#define MaxPosSliderAllLose 300


extern HWND StaticCountCreature;

extern HWND ButtonReset;

extern HWND ButtonSafeMap;
extern HWND ButtonLoadMap;

extern HWND EditSizeMapX;
extern HWND EditSizeMapY;

extern HWND StaticPeepData;
extern HWND StaticPeepBrainHeader;
extern std::vector<std::pair<HWND, int>> StaticPeepBrain;
extern HWND SliderPeepBrain;
extern int MaxPosSliderPeepBrain;
extern int PosSliderPeepBrain;
extern Creature* peep_Creature;
extern bool life_peep_Creature;
extern bool last_draw_peep_Creature;

extern HWND ButtonSafeCrt;
extern HWND ButtonLoadCrt;



void MoveSlider(HWND hWnd, int type, int* pos, int min_pos, int max_pos);


void SetOpenFileParams(HWND hWnd, OPENFILENAMEA* ofn, char* path, const char* def_expansion, const char* filter, DWORD flag);
bool CheckExpansion(const char* check_expansion, const char* right_expansion, unsigned int size = 3);
extern char ThisSaveDirectory[260];



LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);







