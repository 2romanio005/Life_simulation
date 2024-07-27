#pragma once
#include "Definition.h"
#include "Creature_Plant.h"
#include "Creature_Herbivore.h"
#include "Creature_Scavenger.h"



int parse_str_to_int_one_step(const std::string& s, int* iter, char separator) {
	int out = 0;
	bool flag = false;
	if (s.at(*iter) == '-') {
		flag = true;
		(*iter)++;
	}
	while (s[*iter] != separator) {
		out = out * 10 + s.at(*iter) - '0';
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

void ResetMap(HWND hWnd){
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

	DrawInterface();

	UpdateSizeScreen(hWnd, size_screen_x, size_screen_y, true);
}


void Draw(HDC hdc) {

	if (PosSliderStepDraw != MaxPosSliderStepDraw) {
		for (int i = 0; i < size_map_x; i++)
		{
			for (int j = 0; j < size_map_y; j++)
			{
				map[i][j].draw_myself(SupHdc);
			}
		}

		BitBlt(hdc, margin_x + FlagFullscreen * (size_screen_x - 2 * margin_x - size_cell * size_map_x) / 2, margin_y + FlagFullscreen * (size_screen_y - 2 * margin_y - size_cell * size_map_y) / 2, size_cell * size_map_x, size_cell * size_map_y, SupHdc, 0, 0, SRCCOPY);
	}
}

void DrawInterface() {
	SetWindowTextA(StaticCountStep, LPCSTR(("ШАГ: " + std::to_string(CountStep)).c_str()));
	SetWindowTextA(StaticCountCreature, LPCSTR((
		"R: " + std::to_string(Creature_Herbivore::get_type_count()) +
		"  G: " + std::to_string(Creature_Plant::get_type_count()) +
		"  B: " + std::to_string(Creature_Scavenger::get_type_count())
		).c_str()));

	if (last_draw_peep_Creature) {
		last_draw_peep_Creature = false;
		if (peep_Creature != nullptr) {
			SetWindowTextA(StaticPeepData, LPCSTR((
				"Энергия: " + std::to_string(peep_Creature->get_energy())
				+ "  Возраст: " + std::to_string(peep_Creature->get_age())
				+ "  Действие: " + std::to_string(peep_Creature->get_iter())
				+ "  Направление: " + string_by_dir_for_turn(peep_Creature->get_dir())
				+ "  Живо: " + (life_peep_Creature ? "да" : "нет"))
				.c_str()));

			if (life_peep_Creature) {
				last_draw_peep_Creature = true;
			}
		}
	}

}


void FullUpdateDraw(HWND hWnd)
{
	UpdateDraw(hWnd);
	DrawInterface();
}

void UpdateDraw(HWND hWnd) {
	int x = margin_x + FlagFullscreen * (size_screen_x - 2 * margin_x - size_cell * size_map_x) / 2;
	int y = margin_y + FlagFullscreen * (size_screen_y - 2 * margin_y - size_cell * size_map_y) / 2;
	RECT update{ x, y, x + size_cell * size_map_x, y + size_cell * size_map_y };
	InvalidateRect(hWnd, &update, false);
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
		size_creature_radius = round(size_cell * CreatureRadiusCoeff);

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


		//FullUpdateDraw(hWnd);
		if (!position_WM_SETREDRAW) { SendMessage(hWnd, WM_SETREDRAW, true, 0); }  // включить отрисовку но не поднимать флаг - в WM_PAINT отрисовка выключится так как флаг опущен

		//RedrawWindow(hWnd, NULL, NULL, RDW_ERASE | RDW_FRAME | RDW_INVALIDATE | RDW_ALLCHILDREN);
		InvalidateRect(hWnd, NULL, true);

		MoveWidget();

		UpdateWidget();

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

void MoveWidget()
{
	int height = margin_y;
	int width = margin_x * 2 + size_map_x * size_cell + FlagFullscreen * size_screen_x;

	SetWindowPos(StaticCountStep, nullptr, width, height, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	SetWindowPos(ButtonStop, nullptr, width + 60, height += 20, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	SetWindowPos(CheckBoxAutomaticStop, nullptr, width, height += 30, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	SetWindowPos(CheckBoxAutomaticReset, nullptr, width, height += 20, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	SetWindowPos(StaticTimeDrawMain, nullptr, width, height += 20, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	SetWindowPos(SliderTimeDraw, nullptr, width, height += 20, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	SetWindowPos(StaticTimeDrawLeft, nullptr, width, height += 20, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	SetWindowPos(StaticTimeDrawRight, nullptr, width + 120, height, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	SetWindowPos(StaticStepDrawMain, nullptr, width, height += 20, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	SetWindowPos(SliderStepDraw, nullptr, width, height += 20, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	SetWindowPos(StaticStepDrawLeft, nullptr, width, height += 20, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	SetWindowPos(StaticStepDrawRight, nullptr, width + 120, height, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);



	SetWindowPos(CheckBoxRandDivision, nullptr, width, height += 50, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	SetWindowPos(StaticRedEat, nullptr, width, height += 20, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	SetWindowPos(SliderRedEat, nullptr, width, height += 20, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	SetWindowPos(StaticRedLeave, nullptr, width, height += 20, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	SetWindowPos(SliderRedLeave, nullptr, width, height += 20, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	SetWindowPos(StaticGreenEat, nullptr, width, height += 20, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	SetWindowPos(SliderGreenEat, nullptr, width, height += 20, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	SetWindowPos(StaticBlueEat, nullptr, width, height += 20, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	SetWindowPos(SliderBlueEat, nullptr, width, height += 20, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);	

	SetWindowPos(StaticAllLose, nullptr, width, height += 20, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	SetWindowPos(SliderAllLose, nullptr, width, height += 20, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);


	if (peep_Creature != nullptr) {
		peep_Creature->draw_brain();
	}
	SetWindowPos(StaticCountCreature, nullptr, width, height += 50, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	SetWindowPos(ButtonReset, nullptr, width + 60, height += 30, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	SetWindowPos(ButtonSafeMap, nullptr, width, height += 30, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	SetWindowPos(ButtonLoadMap, nullptr, width + 115, height, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	SetWindowPos(EditSizeMapX, nullptr, width, height += 30, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	SetWindowPos(EditSizeMapY, nullptr, width + 115, height, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	

	height = margin_y * 2 + size_map_y * size_cell + FlagFullscreen * size_screen_y;

	SetWindowPos(StaticPeepData, nullptr, margin_x, height, size_map_x * size_cell, 20, SWP_NOOWNERZORDER | SWP_NOZORDER);

	SetWindowPos(StaticPeepBrainHeader, nullptr, margin_x, height += 20, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	SetWindowPos(SliderPeepBrain, nullptr, margin_x + size_map_x * size_cell / 3, height += 96, size_map_x * size_cell / 3, 20, SWP_NOOWNERZORDER | SWP_NOZORDER);


	SetWindowPos(ButtonSafeCrt, nullptr, margin_x + (size_map_x * size_cell / 3 - 150) / 2, height, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);
	SetWindowPos(ButtonLoadCrt, nullptr, margin_x + size_map_x * size_cell * 2 / 3 + (size_map_x * size_cell / 3 - 150) / 2, height, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);
}

void UpdateWidget()
{
	UpdateWindow(StaticCountStep);
	UpdateWindow(ButtonStop);

	UpdateWindow(CheckBoxAutomaticStop);
	UpdateWindow(CheckBoxAutomaticReset);

	UpdateWindow(StaticTimeDrawMain);
	UpdateWindow(SliderTimeDraw);
	UpdateWindow(StaticTimeDrawLeft);
	UpdateWindow(StaticTimeDrawRight);

	UpdateWindow(StaticStepDrawMain);
	UpdateWindow(SliderStepDraw);
	UpdateWindow(StaticStepDrawLeft);
	UpdateWindow(StaticStepDrawRight);

	UpdateWindow(CheckBoxRandDivision);

	UpdateWindow(StaticRedEat);
	UpdateWindow(SliderRedEat);

	UpdateWindow(StaticRedLeave);
	UpdateWindow(SliderRedLeave);

	UpdateWindow(StaticGreenEat);
	UpdateWindow(SliderGreenEat);

	UpdateWindow(StaticBlueEat);
	UpdateWindow(SliderBlueEat);

	UpdateWindow(StaticAllLose);
	UpdateWindow(SliderAllLose);

	UpdateWindow(StaticCountCreature);

	UpdateWindow(ButtonReset);

	UpdateWindow(ButtonSafeMap);
	UpdateWindow(ButtonLoadMap);

	UpdateWindow(EditSizeMapX);
	UpdateWindow(EditSizeMapY);



	UpdateWindow(StaticPeepData);
	UpdateWindow(StaticPeepBrainHeader);
	for (auto& el : StaticPeepBrain)
	{
		UpdateWindow(el.first);
	}
	UpdateWindow(SliderPeepBrain);

	UpdateWindow(ButtonSafeCrt);
	UpdateWindow(ButtonLoadCrt);


}




void BuildWidget(HWND hWnd) {
	int height = margin_y;
	int width = margin_x * 2 + size_map_x * size_cell + FlagFullscreen * size_screen_x;

	StaticCountStep = CreateWindowA("STATIC", "ШАГ: 0", WS_VISIBLE | WS_CHILD | ES_CENTER, width, height, 220, 20, hWnd, NULL, NULL, NULL);
	ButtonStop = CreateWindowA("BUTTON", "Начать", WS_VISIBLE | WS_CHILD | ES_CENTER, width + 60, height += 20, 100, 20, hWnd, HMENU(IndexButtonStop), NULL, NULL);
	//SendMessage(ButtonStop, WM_CHANGEUISTATE, (WPARAM)(0x10001), (LPARAM)(0));

	CheckBoxAutomaticStop = CreateWindowA("BUTTON", "Остановка при вымирании", WS_VISIBLE | WS_CHILD | ES_CENTER | BS_CHECKBOX, width, height += 30, 220, 20, hWnd, HMENU(IndexCheckBoxAutomaticStop), NULL, NULL);
	SendMessage(CheckBoxAutomaticStop, BM_SETCHECK, FlagAutomaticStop, 0);

	CheckBoxAutomaticReset = CreateWindowA("BUTTON", "Пересоздать при вымирании", WS_VISIBLE | WS_CHILD | ES_CENTER | BS_CHECKBOX, width, height += 20, 220, 20, hWnd, HMENU(IndexCheckBoxAutomaticReset), NULL, NULL);
	SendMessage(CheckBoxAutomaticReset, BM_SETCHECK, FlagAutomaticReset, 0);

	StaticTimeDrawMain = CreateWindowA("STATIC", "Время кадра", WS_VISIBLE | WS_CHILD | ES_CENTER, width, height += 20, 220, 20, hWnd, NULL, NULL, NULL);
	SliderTimeDraw = CreateWindowA("SCROLLBAR", NULL, WS_VISIBLE | WS_CHILD | SBS_HORZ, width, height += 20, 220, 20, hWnd, NULL, NULL, NULL);
	SetScrollRange(SliderTimeDraw, SB_CTL, 1, MaxPosSliderTimeDraw, TRUE);
	SetScrollPos(SliderTimeDraw, SB_CTL, PosSliderTimeDraw, TRUE);
	StaticTimeDrawLeft = CreateWindowA("STATIC", "быстро", WS_VISIBLE | WS_CHILD | ES_LEFT, width, height += 20, 100, 16, hWnd, NULL, NULL, NULL);
	StaticTimeDrawRight = CreateWindowA("STATIC", "долго", WS_VISIBLE | WS_CHILD | ES_RIGHT, width + 120, height, 100, 16, hWnd, NULL, NULL, NULL);
	// SS_SIMPLE  SS_WHITEFRAME  

	StaticStepDrawMain = CreateWindowA("STATIC", "Пропущено кадкор", WS_VISIBLE | WS_CHILD | ES_CENTER, width, height += 20, 220, 20, hWnd, NULL, NULL, NULL);
	SliderStepDraw = CreateWindowA("SCROLLBAR", NULL, WS_VISIBLE | WS_CHILD | SBS_HORZ, width, height += 20, 220, 20, hWnd, NULL, NULL, NULL);
	SetScrollRange(SliderStepDraw, SB_CTL, 1, MaxPosSliderStepDraw, TRUE);
	SetScrollPos(SliderStepDraw, SB_CTL, PosSliderStepDraw, TRUE);
	StaticStepDrawLeft = CreateWindowA("STATIC", "ни одного", WS_VISIBLE | WS_CHILD | ES_LEFT, width, height += 20, 100, 20, hWnd, NULL, NULL, NULL);
	StaticStepDrawRight = CreateWindowA("STATIC", "без отрисовки", WS_VISIBLE | WS_CHILD | ES_RIGHT, width + 120, height, 100, 20, hWnd, NULL, NULL, NULL);


	CheckBoxRandDivision = CreateWindowA("BUTTON", "Деление в случайное место", WS_VISIBLE | WS_CHILD | ES_CENTER | BS_CHECKBOX, width, height += 50, 220, 20, hWnd, HMENU(IndexCheckBoxRandDivision), NULL, NULL);
	SendMessage(CheckBoxRandDivision, BM_SETCHECK, FlagRandDivision, 0);

	StaticRedEat = CreateWindowA("STATIC", ("Красный ест: " + std::to_string(PosSliderRedEat) + "%").c_str(), WS_VISIBLE | WS_CHILD | ES_CENTER, width, height += 20, 220, 20, hWnd, NULL, NULL, NULL);
	SliderRedEat = CreateWindowA("SCROLLBAR", NULL, WS_VISIBLE | WS_CHILD | SBS_HORZ, width, height += 20, 220, 20, hWnd, NULL, NULL, NULL);
	SetScrollRange(SliderRedEat, SB_CTL, 0, MaxPosSliderRedEat, TRUE);
	SetScrollPos(SliderRedEat, SB_CTL, PosSliderRedEat, TRUE);

	StaticRedLeave = CreateWindowA("STATIC", ("Красный оставляет: " + std::to_string(PosSliderRedLeave) + "%").c_str(), WS_VISIBLE | WS_CHILD | ES_CENTER, width, height += 20, 220, 20, hWnd, NULL, NULL, NULL);
	SliderRedLeave = CreateWindowA("SCROLLBAR", NULL, WS_VISIBLE | WS_CHILD | SBS_HORZ, width, height += 20, 220, 20, hWnd, NULL, NULL, NULL);
	SetScrollRange(SliderRedLeave, SB_CTL, 0, MaxPosSliderRedLeave, TRUE);
	SetScrollPos(SliderRedLeave, SB_CTL, PosSliderRedLeave, TRUE);

	StaticGreenEat = CreateWindowA("STATIC", ("Зелёный ест: " + std::to_string(PosSliderGreenEat) + "%").c_str(), WS_VISIBLE | WS_CHILD | ES_CENTER, width, height += 20, 220, 20, hWnd, NULL, NULL, NULL);
	SliderGreenEat = CreateWindowA("SCROLLBAR", NULL, WS_VISIBLE | WS_CHILD | SBS_HORZ, width, height += 20, 220, 20, hWnd, NULL, NULL, NULL);
	SetScrollRange(SliderGreenEat, SB_CTL, 0, MaxPosSliderGreenEat, TRUE);
	SetScrollPos(SliderGreenEat, SB_CTL, PosSliderGreenEat, TRUE);

	StaticBlueEat = CreateWindowA("STATIC", ("Синий ест: " + std::to_string(PosSliderBlueEat) + "%").c_str(), WS_VISIBLE | WS_CHILD | ES_CENTER, width, height += 20, 220, 20, hWnd, NULL, NULL, NULL);
	SliderBlueEat = CreateWindowA("SCROLLBAR", NULL, WS_VISIBLE | WS_CHILD | SBS_HORZ, width, height += 20, 220, 20, hWnd, NULL, NULL, NULL);
	SetScrollRange(SliderBlueEat, SB_CTL, 0, MaxPosSliderBlueEat, TRUE);
	SetScrollPos(SliderBlueEat, SB_CTL, PosSliderBlueEat, TRUE);

	StaticAllLose = CreateWindowA("STATIC", ("Все теряют: " + std::to_string(PosSliderAllLose) + "%").c_str(), WS_VISIBLE | WS_CHILD | ES_CENTER, width, height += 20, 220, 20, hWnd, NULL, NULL, NULL);
	SliderAllLose = CreateWindowA("SCROLLBAR", NULL, WS_VISIBLE | WS_CHILD | SBS_HORZ, width, height += 20, 220, 20, hWnd, NULL, NULL, NULL);
	SetScrollRange(SliderAllLose, SB_CTL, 0, MaxPosSliderAllLose, TRUE);
	SetScrollPos(SliderAllLose, SB_CTL, PosSliderAllLose, TRUE);

	StaticCountCreature = CreateWindowA("STATIC", "R: 0  G: 0  B: 0", WS_VISIBLE | WS_CHILD | ES_CENTER, width, height += 50, 220, 20, hWnd, NULL, NULL, NULL);

	ButtonReset = CreateWindowA("BUTTON", "Пересоздать", WS_VISIBLE | WS_CHILD | ES_CENTER, width + 60, height += 30, 100, 20, hWnd, HMENU(IndexButtonReset), NULL, NULL);

	ButtonSafeMap = CreateWindowA("BUTTON", "Сохранить мир", WS_VISIBLE | WS_CHILD | ES_CENTER, width, height += 30, 105, 20, hWnd, HMENU(IndexButtonSafeMap), NULL, NULL);
	ButtonLoadMap = CreateWindowA("BUTTON", "Загрузить мир", WS_VISIBLE | WS_CHILD | ES_CENTER, width + 115, height, 105, 20, hWnd, HMENU(IndexButtonLoadMap), NULL, NULL);

	EditSizeMapX = CreateWindowA("EDIT", std::to_string(size_map_x).c_str(), WS_VISIBLE | WS_CHILD | ES_CENTER, width, height += 30, 105, 16, hWnd, NULL, NULL, NULL);
	Edit_LimitText(EditSizeMapX, 4);
	EditSizeMapY = CreateWindowA("EDIT", std::to_string(size_map_y).c_str(), WS_VISIBLE | WS_CHILD | ES_CENTER, width + 115, height, 105, 16, hWnd, NULL, NULL, NULL);
	Edit_LimitText(EditSizeMapY, 4);


	height = margin_y * 2 + size_map_y * size_cell + FlagFullscreen * size_screen_y;

	StaticPeepData = CreateWindowA("STATIC", "Энергия: 0 Возраст: 0  Направление: -  Действие: 0  Живо: нет", WS_VISIBLE | WS_CHILD | ES_CENTER, margin_x, height, size_map_x * size_cell, 20, hWnd, NULL, NULL, NULL);

	StaticPeepBrainHeader = CreateWindowA("STATIC", "Номер\nИмя\nНапр\nЗнач\nДа\nНет\n", WS_VISIBLE | WS_CHILD | ES_LEFT, margin_x, height += 20, 43, 96, hWnd, NULL, NULL, NULL);
	SliderPeepBrain = CreateWindowA("SCROLLBAR", NULL, WS_VISIBLE | WS_CHILD | SBS_HORZ, margin_x + size_map_x * size_cell / 3, height += 96, size_map_x * size_cell / 3, 20, hWnd, NULL, NULL, NULL);
	SetScrollRange(SliderPeepBrain, SB_CTL, 0, MaxPosSliderPeepBrain, TRUE);
	SetScrollPos(SliderPeepBrain, SB_CTL, PosSliderPeepBrain, TRUE);

	ButtonSafeCrt = CreateWindowA("BUTTON", "Сохранить существо", WS_VISIBLE | WS_CHILD | ES_CENTER, margin_x + (size_map_x * size_cell / 3 - 150) / 2, height, 150, 20, hWnd, HMENU(IndexButtonSafeCrt), NULL, NULL);
	ButtonLoadCrt = CreateWindowA("BUTTON", "Загрузить существо", WS_VISIBLE | WS_CHILD | ES_CENTER, margin_x + size_map_x * size_cell * 2 / 3 + (size_map_x * size_cell / 3 - 150) / 2, height, 150, 20, hWnd, HMENU(IndexButtonLoadCrt), NULL, NULL);
	//StaticPeepData = CreateWindowA("STATIC", "_______________________________________________________________________________________________________________________________________", WS_VISIBLE | WS_CHILD | ES_LEFT, margin_x, height + 100, size_map_x * size_cell, 20, hWnd, NULL, NULL, NULL);
}

void BuildObject() {
	map = new Cell * [size_map_x];
	for (int i = 0; i < size_map_x; i++)
	{
		map[i] = new Cell[size_map_y];
		for (int j = 0; j < size_map_y; j++)
		{
			map[i][j].set_map_cord({ i, j });
			map[i][j].change_free_energy(rand() % limit_energy);
			//map[i][j].solar_energy = rand() % 500;

			switch (rand() % 4)
			{
			case TYPE_CREATURE::PLANT:
				map[i][j].set_Creature(new Creature_Plant({i, j}, start_energy, DIRECTION(rand() % 4), rand() % limit_age));
				break;
			case TYPE_CREATURE::HERBIVORE:
				map[i][j].set_Creature(new Creature_Herbivore({ i, j }, start_energy, DIRECTION(rand() % 4), rand() % limit_age));
				break;
			case TYPE_CREATURE::SCAVENGER:
				map[i][j].set_Creature(new Creature_Scavenger({ i, j }, start_energy, DIRECTION(rand() % 4), rand() % limit_age));
				break;
			default:
				break;
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

void BuildDrawEffecter(HWND hWnd) {
	//UpdateSizeScreen(hWnd, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	//DPIScale::Initialize(hWnd);


	//HDC hdc;        //создаём контекст устройства
	//PAINTSTRUCT ps; //создаём экземпляр структуры графического вывода

	//hdc = BeginPaint(hWnd, &ps);
	//SupHdc = CreateCompatibleDC(hdc);
	//SupHbm = CreateCompatibleBitmap(hdc, size_cell * size_map_x, size_cell * size_map_y);
	//SupHold = SelectObject(SupHdc, SupHbm);
	//EndPaint(hWnd, &ps);

	for (int i = 0; i < 200; i++)
	{
		H_Gray[i] = CreateSolidBrush(RGB(255 - i, 255 - i, 255 - i));
	}
	H_Green = CreateSolidBrush(RGB(0, 255, 0));
	H_Red = CreateSolidBrush(RGB(255, 0, 0));
	H_Blue = CreateSolidBrush(RGB(0, 0, 255));

	P_Null = CreatePen(PS_NULL, 1, RGB(255, 255, 255));

	//void (*ReadI)(HDC & I_, std::string way) = [](HDC& I_, std::string way) {
	//	I_ = CreateCompatibleDC(hdcMem);
	//	HANDLE tmp = LoadImageA(NULL, way.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//	SelectObject(I_, tmp);
	//	DeleteObject(tmp);
	//};

	//ReadI(I_Player, "images\\I_Player.bmp");


}


void DestroyWidget(HWND hWnd) {
	DestroyWindow(StaticCountStep);
	DestroyWindow(ButtonStop);

	DestroyWindow(CheckBoxAutomaticStop);
	DestroyWindow(CheckBoxAutomaticReset);

	DestroyWindow(StaticTimeDrawMain);
	DestroyWindow(SliderTimeDraw);
	DestroyWindow(StaticTimeDrawLeft);
	DestroyWindow(StaticTimeDrawRight);
	
	DestroyWindow(StaticStepDrawMain);
	DestroyWindow(SliderStepDraw);
	DestroyWindow(StaticStepDrawLeft);
	DestroyWindow(StaticStepDrawRight);

	DestroyWindow(CheckBoxRandDivision);

	DestroyWindow(StaticRedEat);
	DestroyWindow(SliderRedEat);

	DestroyWindow(StaticRedLeave);
	DestroyWindow(SliderRedLeave);

	DestroyWindow(StaticGreenEat);
	DestroyWindow(SliderGreenEat);

	DestroyWindow(StaticBlueEat);
	DestroyWindow(SliderBlueEat);
	
	DestroyWindow(StaticAllLose);
	DestroyWindow(SliderAllLose);

	DestroyWindow(StaticCountCreature);

	DestroyWindow(ButtonReset);

	DestroyWindow(ButtonSafeMap);
	DestroyWindow(ButtonLoadMap);

	DestroyWindow(EditSizeMapX);
	DestroyWindow(EditSizeMapY);




	DestroyWindow(StaticPeepData);
	DestroyWindow(StaticPeepBrainHeader);
	for (auto& el : StaticPeepBrain)
	{
		DestroyWindow(el.first);
	}
	StaticPeepBrain.clear();
	DestroyWindow(SliderPeepBrain);

	DestroyWindow(ButtonSafeCrt);
	DestroyWindow(ButtonLoadCrt);
}

void DestroyObject() {
	for (int i = 0; i < size_map_x; i++)
	{
		delete[] map[i];
	}
	delete[] map;

}

void DestroyDrawEffecter(HWND hWnd) {
	for (int i = 0; i < 200; i++)
	{
		DeleteObject(H_Gray[i]);
	}
	DeleteObject(H_Green);
	DeleteObject(H_Red);
	DeleteObject(H_Blue);

	DeleteObject(P_Null);


	SelectObject(SupHdc, GetStockObject(NULL_BRUSH));

	SelectObject(SupHdc, SupHold);
	DeleteObject(SupHbm);
	DeleteDC(SupHdc);
}




void MoveSlider(HWND hWnd, int type, int* pos, int min_pos, int max_pos) {
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


void SetOpenFileParams(HWND hWnd, OPENFILENAMEA* ofn, char* path, const char* def_expansion, const char* filter, DWORD flag) {
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

bool CheckExpansion(const char* check_expansion, const char* right_expansion, unsigned int size) {
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













