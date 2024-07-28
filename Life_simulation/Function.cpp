#pragma once
#include "RenderingFunctions.h"

#include "Definition.h"
#include "Creature_Plant.h"
#include "Creature_Herbivore.h"
#include "Creature_Scavenger.h"



int parse_str_to_int_one_step(const std::string &s, int *iter, char separator) {
	int out = 0;
	bool flag = false;
	if (s.at(*iter) == '-') {
		flag = true;
		(*iter)++;
	}
	while (s.at(*iter) != separator) {
		out = out * 10 + s[*iter] - '0';
		(*iter)++;
	}
	(*iter)++;
	return flag ? -out : out;
}


DIRECTION turn(DIRECTION strt, DIRECTION step)
{
	return DIRECTION((strt + step + 4) % 4);
}





void OneStep() {
	for (int i = 0; i < size_map_x; i++)
	{
		for (int j = 0; j < size_map_y; j++)
		{
			map[i][j].Creature_step();
		}
	}

	for (int i = 0; i < size_map_x; i++)
	{
		for (int j = 0; j < size_map_y; j++)
		{
			map[i][j].Creature_allow_to_act(); // разрешаем ходить существам (запрещали чтобы они не ходили несколько раз)
		}
	}
	CountStep++;
}


void StopStep(HWND hWnd)
{
	FlagStop = false;
	KillTimer(hWnd, IndexTimerDraw);
	SetWindowTextA(ButtonStop, LPCSTR("Продолжить"));
}

void StartStep(HWND hWnd)
{
	FlagStop = true;
	SetTimer(hWnd, IndexTimerDraw, PosSliderTimeDraw * 100, NULL);
	SetWindowTextA(ButtonStop, LPCSTR("Остановить"));
}

void ResetMap(HWND hWnd) {
	StopStep(hWnd);

	DestroyObject();

	char new_size_map_str[5];

	int new_size_map_int = 0;
	int size = GetWindowTextA(EditSizeMapX, new_size_map_str, 5);
	for (int i = 0; i < size; i++)
	{
		if ('0' <= new_size_map_str[i] && new_size_map_str[i] <= '9') {
			new_size_map_int = new_size_map_int * 10 + new_size_map_str[i] - '0';
		}
	}
	if (new_size_map_int > 0) {
		size_map_x = new_size_map_int;
	}
	new_size_map_int = 0;
	size = GetWindowTextA(EditSizeMapY, new_size_map_str, 5);
	for (int i = 0; i < size; i++)
	{
		if ('0' <= new_size_map_str[i] && new_size_map_str[i] <= '9') {
			new_size_map_int = new_size_map_int * 10 + new_size_map_str[i] - '0';
		}
	}
	if (new_size_map_int > 0) {
		size_map_y = new_size_map_int;
	}

	CountStep = 0;
	BuildObject();

	SetWindowTextA(EditSizeMapX, LPCSTR(std::to_string(size_map_x).c_str()));
	SetWindowTextA(EditSizeMapY, LPCSTR(std::to_string(size_map_y).c_str()));

	RedrawInterface();

	UpdateSizeScreen(hWnd, size_screen_x, size_screen_y, true);
}




void BuildObject() {
	map = new Cell * [size_map_x];
	for (int i = 0; i < size_map_x; i++)
	{
		map[i] = new Cell[size_map_y];
		for (int j = 0; j < size_map_y; j++)
		{
			map[i][j].set_map_coords({ i, j });
			map[i][j].change_free_energy(rand() % limit_energy);
			//map[i][j].solar_energy = rand() % 500;

			switch (rand() % TYPE_CREATURE::TYPE_CREATURE_SIZE)
			{
				case TYPE_CREATURE::PLANT:
					map[i][j].set_Creature(new Creature_Plant({ i, j }, start_energy, DIRECTION(rand() % 4), rand() % limit_age));
					break;
				case TYPE_CREATURE::HERBIVORE:
					map[i][j].set_Creature(new Creature_Herbivore({ i, j }, start_energy, DIRECTION(rand() % 4), rand() % limit_age));
					break;
				case TYPE_CREATURE::SCAVENGER:
					map[i][j].set_Creature(new Creature_Scavenger({ i, j }, start_energy, DIRECTION(rand() % 4), rand() % limit_age));
					break;
				case TYPE_CREATURE::Void:
					break;
				default:
					MessageBoxA(GetActiveWindow(), "Called default case", __FUNCTION__, MB_ICONERROR);
			}
		}
	}

	//std::vector<Action*> br;
	//br.push_back(new Action_condition_by_Cell_energy(nullptr, DIRECTION::UNDER, 3, 1, 400));
	//br.push_back(new Action_eat(nullptr));
	//br.push_back(new Action_change_iter(nullptr, 0));
	//br.push_back(new Action_go(nullptr));
	//map[size_map_x / 2][size_map_y / 2].set_creature(new Creature_Plant({ size_map_x / 2, size_map_y / 2 }, 300, 400, 0, &br));

	//std::vector<Creature_Scavenger::Condition> br;
	//br.push_back(Creature_Scavenger::Condition(
	//	1,
	//	-1, -1,
	//	nullptr,
	//	DIRECTION::UP, TYPE_CREATURE::Void, 1000,
	//	Action_go
	//));
	//br.push_back(Creature_Scavenger::Condition(
	//	0,
	//	2, 0,
	//	nullptr,
	//	DIRECTION::UNDER, TYPE_CREATURE::Void, 250
	//));
	//br.push_back(Creature_Scavenger::Condition(
	//	1,
	//	-1, -1,
	//	nullptr,
	//	DIRECTION::UP, TYPE_CREATURE::Void, 1000,
	//	Action_eat
	//));
	//map[size_map_x / 2][size_map_y / 2].set_creature(new Creature_Scavenger({ size_map_x / 2, size_map_y / 2 }, start_energy, &br));


	//std::vector<Creature_Herbivore::Condition> br;
	//br.push_back(Creature_Herbivore::Condition(
	//	1,
	//	-1, -1,
	//	nullptr,
	//	DIRECTION::UP, TYPE_CREATURE::Void, 1000,
	//	Action_eat
	//));
	//br.push_back(Creature_Herbivore::Condition(
	//	1,
	//	-1, -1,
	//	nullptr,
	//	DIRECTION::UP, TYPE_CREATURE::Void, 1000,
	//	Action_go
	//));
	//map[size_map_x / 2][size_map_y / 2].set_creature(new Creature_Herbivore({ size_map_x / 2, size_map_y / 2 }, start_energy, 2000, &br));


}

void DestroyObject() {
	for (int i = 0; i < size_map_x; i++)
	{
		delete[] map[i];
	}
	delete[] map;

}




void MoveSlider(HWND hWnd, int type, int *pos, int min_pos, int max_pos) {
	(*pos) = max(min_pos, min((*pos), max_pos));
	switch (type)
	{
		case 0:
			SetScrollPos(SliderTimeDraw, SB_CTL, *pos, TRUE);
			if (FlagStop) {
				KillTimer(hWnd, IndexTimerDraw);
				SetTimer(hWnd, IndexTimerDraw, PosSliderTimeDraw * 100, NULL);
			}
			break;
		case 1:
			SetScrollPos(SliderStepDraw, SB_CTL, *pos, TRUE);
			break;
		case 2:
			SetScrollPos(SliderPeepBrain, SB_CTL, *pos, TRUE);
			if (peep_Creature != nullptr) {
				peep_Creature->draw_brain();
			}
			break;
		case 3:
			SetScrollPos(SliderRedEat, SB_CTL, *pos, TRUE);
			SetWindowTextA(StaticRedEat, LPCSTR(("Красный ест: " + std::to_string(PosSliderRedEat) + "%").c_str()));
			MaxPosSliderRedLeave = 100 - PosSliderRedEat;
			SetScrollRange(SliderRedLeave, SB_CTL, 0, MaxPosSliderRedLeave, TRUE);
			if (PosSliderRedLeave > MaxPosSliderRedLeave) {
				PosSliderRedLeave = MaxPosSliderRedLeave;
				SetScrollPos(SliderRedLeave, SB_CTL, PosSliderRedLeave, TRUE);
				SetWindowTextA(StaticRedLeave, LPCSTR(("Красный оставляет: " + std::to_string(PosSliderRedLeave) + "%").c_str()));
			}
			break;
		case 4:
			SetScrollPos(SliderRedLeave, SB_CTL, *pos, TRUE);
			SetWindowTextA(StaticRedLeave, LPCSTR(("Красный оставляет: " + std::to_string(PosSliderRedLeave) + "%").c_str()));
			break;
		case 5:
			SetScrollPos(SliderGreenEat, SB_CTL, *pos, TRUE);
			SetWindowTextA(StaticGreenEat, LPCSTR(("Зелёный ест: " + std::to_string(PosSliderGreenEat) + "%").c_str()));
			break;
		case 6:
			SetScrollPos(SliderBlueEat, SB_CTL, *pos, TRUE);
			SetWindowTextA(StaticBlueEat, LPCSTR(("Синий ест: " + std::to_string(PosSliderBlueEat) + "%").c_str()));
			break;
		case 7:
			SetScrollPos(SliderAllLose, SB_CTL, *pos, TRUE);
			SetWindowTextA(StaticAllLose, LPCSTR(("Все теряют: " + std::to_string(PosSliderAllLose) + "%").c_str()));
			break;
	}
}


void SetOpenFileParams(HWND hWnd, OPENFILENAMEA *ofn, char *path, const char *def_expansion, const char *filter, DWORD flag) {
	ZeroMemory(ofn, sizeof(*ofn));

	ofn->lStructSize = sizeof(*ofn);
	ofn->hwndOwner = hWnd;
	ofn->lpstrFile = path;
	ofn->nMaxFile = 260;
	ofn->lpstrFilter = filter;
	ofn->lpstrFileTitle = NULL;
	ofn->nMaxFileTitle = 0;
	ofn->lpstrInitialDir = ThisSaveDirectory;
	ofn->lpstrDefExt = def_expansion;
	ofn->Flags = flag;
}

bool CheckExpansion(const char *check_expansion, const char *right_expansion, unsigned int size) {
	for (unsigned int i = 0; i < size; i++) {
		if (check_expansion[i] != right_expansion[i]) {
			return true;
		}
	}
	return false;
}




std::string string_by_type_creature(TYPE_CREATURE type_creature)
{
	switch (type_creature)
	{
		case TYPE_CREATURE::PLANT:
			return "Растение";
		case TYPE_CREATURE::HERBIVORE:
			return "Хищник";
		case TYPE_CREATURE::SCAVENGER:
			return "Падальщик";
		case TYPE_CREATURE::Void:
			return "Никого";
	}
	return "???";
}


std::string string_by_dir_for_condition(DIRECTION dir)
{
	switch (dir)
	{
		case DIRECTION::to_FORWARD:
			return "Спереди";
		case DIRECTION::to_RIGHT:
			return "Справа";
		case DIRECTION::to_LEFT:
			return "Слева";
		case DIRECTION::to_BACK:
			return "Сзади";
		case DIRECTION::UP:
			return "Верх";
		case DIRECTION::RIGHT:
			return "Право";
		case DIRECTION::DOWN:
			return "Низ";
		case DIRECTION::LEFT:
			return "Лево";
		case DIRECTION::UNDER:
			return "Снизу";
	}
	return "???";
}

std::string string_by_dir_for_turn(DIRECTION dir)
{
	switch (dir)
	{
		case DIRECTION::to_FORWARD:
			return "Вперёд";
		case DIRECTION::to_RIGHT:
			return "Направо";
		case DIRECTION::to_LEFT:
			return "Налево";
		case DIRECTION::to_BACK:
			return "Назад";
		case DIRECTION::UP:
			return "Верх";
		case DIRECTION::RIGHT:
			return "Право";
		case DIRECTION::DOWN:
			return "Низ";
		case DIRECTION::LEFT:
			return "Лево";
		case DIRECTION::UNDER:
			return "Снизу";
	}

	return "???";
}




void UpdateSizeScreen(HWND hWnd, const int size_x, const int size_y, bool flag_always)
{
	size_screen_x = size_x;
	size_screen_y = size_y;
	int size_cell_by_x = (size_screen_x - (FlagFullscreen ? (margin_x * 2) : (220 + margin_x * 3))) / size_map_x;
	int size_cell_by_y = (size_screen_y - (FlagFullscreen ? (margin_y * 2) : (136 + margin_y * 3))) / size_map_y;
	int tmp_size_cell = min(size_cell_by_x, size_cell_by_y);
	tmp_size_cell -= (tmp_size_cell % 2 == 0);         // делаем клетку нечётной
	tmp_size_cell = max(MinSizeCell, tmp_size_cell);   // иначе проверку на отриц


	if (tmp_size_cell != size_cell || flag_always) {
		size_cell = tmp_size_cell;
		size_half_cell = (size_cell + 1) / 2;
		size_creature_radius = lround(size_cell * CreatureRadiusCoeff);

		SelectObject(SupHdc, GetStockObject(NULL_BRUSH));

		SelectObject(SupHdc, SupHold);
		DeleteObject(SupHbm);
		DeleteDC(SupHdc);

		HDC hdc;        //создаём контекст устройства
		PAINTSTRUCT ps; //создаём экземпляр структуры графического вывода

		hdc = BeginPaint(hWnd, &ps);
		SupHdc = CreateCompatibleDC(hdc);
		SupHbm = CreateCompatibleBitmap(hdc, size_cell * size_map_x, size_cell * size_map_y);
		SupHold = SelectObject(SupHdc, SupHbm);
		EndPaint(hWnd, &ps);


		//FullRedraw(hWnd);
		if (!position_WM_SETREDRAW) { SendMessage(hWnd, WM_SETREDRAW, true, 0); }  // включить отрисовку, но не поднимать флаг. После отрисовки в WM_PAINT, отрисовка выключится, так как флаг опущен

		//RedrawWindow(hWnd, NULL, NULL, RDW_ERASE | RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN);

		MoveWidgets();
		InvalidateRect(hWnd, NULL, true);

		//FullRedraw(hWnd);

		//UpdateWidget();

		//RedrawWindow(hWnd, NULL, NULL, RDW_ERASE | RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN);

		//SendMessage(hWnd, WM_SETREDRAW, true, 0);    // отрисовка только кода что-то меняется
	}
	//else {
	//	if (position_WM_SETREDRAW) {
	//		position_WM_SETREDRAW = false;      
	//		SendMessage(hWnd, WM_SETREDRAW, false, 0);     // убрать отрисовку если не меняется
	//	}
	//}
}
