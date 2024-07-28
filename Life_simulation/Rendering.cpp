#include "Rendering.h"

namespace Rendering {

	void HANDLER_WM_PAINT(HWND hWnd)
	{
	}



	//! отрисовка основной карты
	void DrawMap(HDC hdc) {
		//if (PosSliderStepDraw != MaxPosSliderStepDraw) {
		//	for (int i = 0; i < size_map_x; i++)
		//	{
		//		for (int j = 0; j < size_map_y; j++)
		//		{
		//			map[i][j].draw_myself(SupHdc);
		//		}
		//	}

		//	BitBlt(hdc, margin_x + FlagFullscreen * (size_screen_x - 2 * margin_x - size_cell * size_map_x) / 2, margin_y + FlagFullscreen * (size_screen_y - 2 * margin_y - size_cell * size_map_y) / 2, size_cell * size_map_x, size_cell * size_map_y, SupHdc, 0, 0, SRCCOPY);
		//}
	}

	void InvalidateMapRect(HWND hWnd) {
		//int x = margin_x + FlagFullscreen * (size_screen_x - 2 * margin_x - size_cell * size_map_x) / 2;
		//int y = margin_y + FlagFullscreen * (size_screen_y - 2 * margin_y - size_cell * size_map_y) / 2;
		//RECT update { x, y, x + size_cell * size_map_x, y + size_cell * size_map_y };
		//InvalidateRect(hWnd, &update, false);
	}


	//! отрисовка интерфейса TODO разнести в несколько функций
	void RedrawInterface() {
		/*SetWindowTextA(StaticCountStep, LPCSTR(("ШАГ: " + std::to_string(CountStep)).c_str()));
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
		}*/

	}


	//! Обработка виджетов
	void BuildWidget(HWND hWnd) {
		//int height = margin_y;
		//int width = margin_x * 2 + size_map_x * size_cell + FlagFullscreen * size_screen_x;

		//StaticCountStep = CreateWindowA("STATIC", "ШАГ: 0", WS_VISIBLE | WS_CHILD | ES_CENTER, width, height, 220, 20, hWnd, NULL, NULL, NULL);
		//ButtonStop = CreateWindowA("BUTTON", "Начать", WS_VISIBLE | WS_CHILD | ES_CENTER, width + 60, height += 20, 100, 20, hWnd, HMENU(IndexButtonStop), NULL, NULL);
		////SendMessage(ButtonStop, WM_CHANGEUISTATE, (WPARAM)(0x10001), (LPARAM)(0));

		//CheckBoxAutomaticStop = CreateWindowA("BUTTON", "Остановка при вымирании", WS_VISIBLE | WS_CHILD | ES_CENTER | BS_CHECKBOX, width, height += 30, 220, 20, hWnd, HMENU(IndexCheckBoxAutomaticStop), NULL, NULL);
		//SendMessage(CheckBoxAutomaticStop, BM_SETCHECK, FlagAutomaticStop, 0);

		//CheckBoxAutomaticReset = CreateWindowA("BUTTON", "Пересоздать при вымирании", WS_VISIBLE | WS_CHILD | ES_CENTER | BS_CHECKBOX, width, height += 20, 220, 20, hWnd, HMENU(IndexCheckBoxAutomaticReset), NULL, NULL);
		//SendMessage(CheckBoxAutomaticReset, BM_SETCHECK, FlagAutomaticReset, 0);

		//StaticTimeDrawMain = CreateWindowA("STATIC", "Время кадра", WS_VISIBLE | WS_CHILD | ES_CENTER, width, height += 20, 220, 20, hWnd, NULL, NULL, NULL);
		//SliderTimeDraw = CreateWindowA("SCROLLBAR", NULL, WS_VISIBLE | WS_CHILD | SBS_HORZ, width, height += 20, 220, 20, hWnd, NULL, NULL, NULL);
		//SetScrollRange(SliderTimeDraw, SB_CTL, 1, MaxPosSliderTimeDraw, TRUE);
		//SetScrollPos(SliderTimeDraw, SB_CTL, PosSliderTimeDraw, TRUE);
		//StaticTimeDrawLeft = CreateWindowA("STATIC", "быстро", WS_VISIBLE | WS_CHILD | ES_LEFT, width, height += 20, 100, 16, hWnd, NULL, NULL, NULL);
		//StaticTimeDrawRight = CreateWindowA("STATIC", "долго", WS_VISIBLE | WS_CHILD | ES_RIGHT, width + 120, height, 100, 16, hWnd, NULL, NULL, NULL);
		//// SS_SIMPLE  SS_WHITEFRAME  

		//StaticStepDrawMain = CreateWindowA("STATIC", "Пропущено кадкор", WS_VISIBLE | WS_CHILD | ES_CENTER, width, height += 20, 220, 20, hWnd, NULL, NULL, NULL);
		//SliderStepDraw = CreateWindowA("SCROLLBAR", NULL, WS_VISIBLE | WS_CHILD | SBS_HORZ, width, height += 20, 220, 20, hWnd, NULL, NULL, NULL);
		//SetScrollRange(SliderStepDraw, SB_CTL, 1, MaxPosSliderStepDraw, TRUE);
		//SetScrollPos(SliderStepDraw, SB_CTL, PosSliderStepDraw, TRUE);
		//StaticStepDrawLeft = CreateWindowA("STATIC", "ни одного", WS_VISIBLE | WS_CHILD | ES_LEFT, width, height += 20, 100, 20, hWnd, NULL, NULL, NULL);
		//StaticStepDrawRight = CreateWindowA("STATIC", "без отрисовки", WS_VISIBLE | WS_CHILD | ES_RIGHT, width + 120, height, 100, 20, hWnd, NULL, NULL, NULL);


		//CheckBoxRandDivision = CreateWindowA("BUTTON", "Деление в случайное место", WS_VISIBLE | WS_CHILD | ES_CENTER | BS_CHECKBOX, width, height += 50, 220, 20, hWnd, HMENU(IndexCheckBoxRandDivision), NULL, NULL);
		//SendMessage(CheckBoxRandDivision, BM_SETCHECK, FlagRandDivision, 0);

		//StaticRedEat = CreateWindowA("STATIC", ("Красный ест: " + std::to_string(PosSliderRedEat) + "%").c_str(), WS_VISIBLE | WS_CHILD | ES_CENTER, width, height += 20, 220, 20, hWnd, NULL, NULL, NULL);
		//SliderRedEat = CreateWindowA("SCROLLBAR", NULL, WS_VISIBLE | WS_CHILD | SBS_HORZ, width, height += 20, 220, 20, hWnd, NULL, NULL, NULL);
		//SetScrollRange(SliderRedEat, SB_CTL, 0, MaxPosSliderRedEat, TRUE);
		//SetScrollPos(SliderRedEat, SB_CTL, PosSliderRedEat, TRUE);

		//StaticRedLeave = CreateWindowA("STATIC", ("Красный оставляет: " + std::to_string(PosSliderRedLeave) + "%").c_str(), WS_VISIBLE | WS_CHILD | ES_CENTER, width, height += 20, 220, 20, hWnd, NULL, NULL, NULL);
		//SliderRedLeave = CreateWindowA("SCROLLBAR", NULL, WS_VISIBLE | WS_CHILD | SBS_HORZ, width, height += 20, 220, 20, hWnd, NULL, NULL, NULL);
		//SetScrollRange(SliderRedLeave, SB_CTL, 0, MaxPosSliderRedLeave, TRUE);
		//SetScrollPos(SliderRedLeave, SB_CTL, PosSliderRedLeave, TRUE);

		//StaticGreenEat = CreateWindowA("STATIC", ("Зелёный ест: " + std::to_string(PosSliderGreenEat) + "%").c_str(), WS_VISIBLE | WS_CHILD | ES_CENTER, width, height += 20, 220, 20, hWnd, NULL, NULL, NULL);
		//SliderGreenEat = CreateWindowA("SCROLLBAR", NULL, WS_VISIBLE | WS_CHILD | SBS_HORZ, width, height += 20, 220, 20, hWnd, NULL, NULL, NULL);
		//SetScrollRange(SliderGreenEat, SB_CTL, 0, MaxPosSliderGreenEat, TRUE);
		//SetScrollPos(SliderGreenEat, SB_CTL, PosSliderGreenEat, TRUE);

		//StaticBlueEat = CreateWindowA("STATIC", ("Синий ест: " + std::to_string(PosSliderBlueEat) + "%").c_str(), WS_VISIBLE | WS_CHILD | ES_CENTER, width, height += 20, 220, 20, hWnd, NULL, NULL, NULL);
		//SliderBlueEat = CreateWindowA("SCROLLBAR", NULL, WS_VISIBLE | WS_CHILD | SBS_HORZ, width, height += 20, 220, 20, hWnd, NULL, NULL, NULL);
		//SetScrollRange(SliderBlueEat, SB_CTL, 0, MaxPosSliderBlueEat, TRUE);
		//SetScrollPos(SliderBlueEat, SB_CTL, PosSliderBlueEat, TRUE);

		//StaticAllLose = CreateWindowA("STATIC", ("Все теряют: " + std::to_string(PosSliderAllLose) + "%").c_str(), WS_VISIBLE | WS_CHILD | ES_CENTER, width, height += 20, 220, 20, hWnd, NULL, NULL, NULL);
		//SliderAllLose = CreateWindowA("SCROLLBAR", NULL, WS_VISIBLE | WS_CHILD | SBS_HORZ, width, height += 20, 220, 20, hWnd, NULL, NULL, NULL);
		//SetScrollRange(SliderAllLose, SB_CTL, 0, MaxPosSliderAllLose, TRUE);
		//SetScrollPos(SliderAllLose, SB_CTL, PosSliderAllLose, TRUE);

		//StaticCountCreature = CreateWindowA("STATIC", "R: 0  G: 0  B: 0", WS_VISIBLE | WS_CHILD | ES_CENTER, width, height += 50, 220, 20, hWnd, NULL, NULL, NULL);

		//ButtonReset = CreateWindowA("BUTTON", "Пересоздать", WS_VISIBLE | WS_CHILD | ES_CENTER, width + 60, height += 30, 100, 20, hWnd, HMENU(IndexButtonReset), NULL, NULL);

		//ButtonSafeMap = CreateWindowA("BUTTON", "Сохранить мир", WS_VISIBLE | WS_CHILD | ES_CENTER, width, height += 30, 105, 20, hWnd, HMENU(IndexButtonSafeMap), NULL, NULL);
		//ButtonLoadMap = CreateWindowA("BUTTON", "Загрузить мир", WS_VISIBLE | WS_CHILD | ES_CENTER, width + 115, height, 105, 20, hWnd, HMENU(IndexButtonLoadMap), NULL, NULL);

		//EditSizeMapX = CreateWindowA("EDIT", std::to_string(size_map_x).c_str(), WS_VISIBLE | WS_CHILD | ES_CENTER, width, height += 30, 105, 16, hWnd, NULL, NULL, NULL);
		//Edit_LimitText(EditSizeMapX, 4);
		//EditSizeMapY = CreateWindowA("EDIT", std::to_string(size_map_y).c_str(), WS_VISIBLE | WS_CHILD | ES_CENTER, width + 115, height, 105, 16, hWnd, NULL, NULL, NULL);
		//Edit_LimitText(EditSizeMapY, 4);


		//height = margin_y * 2 + size_map_y * size_cell + FlagFullscreen * size_screen_y;

		//StaticPeepData = CreateWindowA("STATIC", "Энергия: 0 Возраст: 0  Направление: -  Действие: 0  Живо: нет", WS_VISIBLE | WS_CHILD | ES_CENTER, margin_x, height, size_map_x * size_cell, 20, hWnd, NULL, NULL, NULL);

		//StaticPeepBrainHeader = CreateWindowA("STATIC", "Номер\nИмя\nНапр\nЗнач\nДа\nНет\n", WS_VISIBLE | WS_CHILD | ES_LEFT, margin_x, height += 20, 43, 96, hWnd, NULL, NULL, NULL);
		//SliderPeepBrain = CreateWindowA("SCROLLBAR", NULL, WS_VISIBLE | WS_CHILD | SBS_HORZ, margin_x + size_map_x * size_cell / 3, height += 96, size_map_x * size_cell / 3, 20, hWnd, NULL, NULL, NULL);
		//SetScrollRange(SliderPeepBrain, SB_CTL, 0, MaxPosSliderPeepBrain, TRUE);
		//SetScrollPos(SliderPeepBrain, SB_CTL, PosSliderPeepBrain, TRUE);

		//ButtonSafeCrt = CreateWindowA("BUTTON", "Сохранить существо", WS_VISIBLE | WS_CHILD | ES_CENTER, margin_x + (size_map_x * size_cell / 3 - 150) / 2, height, 150, 20, hWnd, HMENU(IndexButtonSafeCrt), NULL, NULL);
		//ButtonLoadCrt = CreateWindowA("BUTTON", "Загрузить существо", WS_VISIBLE | WS_CHILD | ES_CENTER, margin_x + size_map_x * size_cell * 2 / 3 + (size_map_x * size_cell / 3 - 150) / 2, height, 150, 20, hWnd, HMENU(IndexButtonLoadCrt), NULL, NULL);
		////StaticPeepData = CreateWindowA("STATIC", "_______________________________________________________________________________________________________________________________________", WS_VISIBLE | WS_CHILD | ES_LEFT, margin_x, height + 100, size_map_x * size_cell, 20, hWnd, NULL, NULL, NULL);
	}

	void MoveWidgets()
	{
		/*int height = margin_y;
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
		SetWindowPos(ButtonLoadCrt, nullptr, margin_x + size_map_x * size_cell * 2 / 3 + (size_map_x * size_cell / 3 - 150) / 2, height, 0, 0, SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER);*/
	}

	void UpdateWidget()
	{
		/*UpdateWindow(StaticCountStep);
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
		for (auto &el : StaticPeepBrain)
		{
			UpdateWindow(el.first);
		}
		UpdateWindow(SliderPeepBrain);

		UpdateWindow(ButtonSafeCrt);
		UpdateWindow(ButtonLoadCrt);*/
	}

	void DestroyWidget(HWND hWnd) {
		/*DestroyWindow(StaticCountStep);
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
		for (auto &el : StaticPeepBrain)
		{
			DestroyWindow(el.first);
		}
		StaticPeepBrain.clear();
		DestroyWindow(SliderPeepBrain);

		DestroyWindow(ButtonSafeCrt);
		DestroyWindow(ButtonLoadCrt);*/
	}


	//! Обработка инстрементов для рисования
	void BuildDrawEffecter(HWND hWnd) {
		//for (int i = 0; i < 200; i++)
		//{
		//	H_Gray[i] = CreateSolidBrush(RGB(255 - i, 255 - i, 255 - i));
		//}
		//H_Green = CreateSolidBrush(RGB(0, 255, 0));
		//H_Red = CreateSolidBrush(RGB(255, 0, 0));
		//H_Blue = CreateSolidBrush(RGB(0, 0, 255));

		//P_Null = CreatePen(PS_NULL, 1, RGB(255, 255, 255));
	}

	void DestroyDrawEffecter(HWND hWnd) {
		/*for (int i = 0; i < 200; i++)
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
		DeleteDC(SupHdc);*/
	}


	//! посылает сигналы для перерисовки всего
	void FullRedraw(HWND hWnd)
	{
		InvalidateMapRect(hWnd);
		RedrawInterface();
	}


}
