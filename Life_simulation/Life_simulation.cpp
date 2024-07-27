#pragma once
#include "Definition.h"
#include "MainConnection.h"
#include "Creature_Plant.h"
#include "Creature_Herbivore.h"
#include "Creature_Scavenger.h"
#include "resource.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wcex = { 0 };

	//wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	//HBRUSH Background = CreateSolidBrush(RGB(170, 0, 196));
	H_Background = CreateSolidBrush(RGB(40, 40, 40));
	wcex.hbrBackground = H_Background;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));
	//wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.lpszClassName = L"Life_simulation";
	wcex.lpfnWndProc = WndProc;
	//wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = NULL;
	//wcex.cbClsExtra = 0;
	//wcex.cbWndExtra = 0;
	//wcex.lpszMenuName = NULL;
	//wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

	if (!RegisterClassW(&wcex)) { return -1; }

	CreateWindow(L"Life_simulation", L"Life_simulation", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, GetSystemMetrics(SM_CXSCREEN) - 10, GetSystemMetrics(SM_CYSCREEN) - 40, NULL, NULL, NULL, NULL);



	// Main message loop:
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	DeleteObject(H_Background);
	return 0;
}







LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)  // обработка событий
{
	switch (message)
	{
	case WM_HSCROLL:   // горизонтальные
	//case WM_VSCROLL:   // вертикальные
	{
		int type = 0;

		int* pos = &type;
		int min_pos = -1;
		int max_pos = -1;
		int one_step = 1;
		if (SliderTimeDraw == (HWND)lParam) { type = 0; pos = &PosSliderTimeDraw; min_pos = 1; max_pos = MaxPosSliderTimeDraw; one_step = (MaxPosSliderTimeDraw + 4) / 5; } else
		if (SliderStepDraw == (HWND)lParam) { type = 1;	pos = &PosSliderStepDraw; min_pos = 1; max_pos = MaxPosSliderTimeDraw; one_step = (MaxPosSliderTimeDraw + 4) / 5; } else
		if (SliderPeepBrain == (HWND)lParam) { type = 2; pos = &PosSliderPeepBrain; min_pos = 0; max_pos = MaxPosSliderPeepBrain; one_step = (MaxPosSliderPeepBrain + 9) / 10; } else

		if (SliderRedEat == (HWND)lParam) { type = 3; pos = &PosSliderRedEat; min_pos = 0; max_pos = MaxPosSliderRedEat; one_step = 10; } else
		if (SliderRedLeave == (HWND)lParam) { type = 4; pos = &PosSliderRedLeave; min_pos = 0; max_pos = MaxPosSliderRedLeave; one_step = (MaxPosSliderRedLeave + 9) / 10; } else
		if (SliderGreenEat == (HWND)lParam) { type = 5; pos = &PosSliderGreenEat; min_pos = 0; max_pos = MaxPosSliderGreenEat; one_step = 10; } else
		if (SliderBlueEat == (HWND)lParam) { type = 6; pos = &PosSliderBlueEat; min_pos = 0; max_pos = MaxPosSliderBlueEat; one_step = 10; } else
		if (SliderAllLose == (HWND)lParam) { type = 7; pos = &PosSliderAllLose; min_pos = 0; max_pos = MaxPosSliderAllLose; one_step = 10; }



		switch (LOWORD(wParam)) {
		case SB_LINERIGHT:     // стрелочки
			(*pos)++;
			break;
		case SB_LINELEFT:     // стрелочки
			(*pos)--;
			break;
		case SB_PAGERIGHT:     // пустая область
			(*pos) += one_step;
			break;
		case SB_PAGELEFT:     // пустая область
			(*pos) -= one_step;
			break;
		case SB_THUMBTRACK:    // тянем за ползунок
		//case SB_THUMBPOSITION:  // отпускаем ползунок
			(*pos) = HIWORD(wParam);
			break;
		}

		MoveSlider(hWnd, type, pos, min_pos, max_pos);
		//SCROLLBARINFO scrol_bar;
		//scrol_bar.cbSize = sizeof(SCROLLBARINFO);
		//GetScrollBarInfo(SliderTimeDraw, OBJID_CLIENT, &scrol_bar);
		break;
	}
	case WM_COMMAND:
	{
		switch (wParam) {
		case IndexButtonStop:
		{
			SetFocus(hWnd);
			if (FlagStop) {
				StopStep(hWnd);
			}
			else {
				StartStep(hWnd);
			}
			break;
		}
		case IndexCheckBoxAutomaticStop:
		{
			SetFocus(hWnd);
			FlagAutomaticStop = !FlagAutomaticStop;
			break;
		}
		case IndexCheckBoxAutomaticReset:
		{
			SetFocus(hWnd);
			FlagAutomaticReset = !FlagAutomaticReset;
			break;
		}

		case IndexCheckBoxRandDivision:
		{
			SetFocus(hWnd);
			FlagRandDivision = !FlagRandDivision;
			break;
		}
		
		case IndexButtonReset:
		{
			SetFocus(hWnd);
			if (MessageBoxA(hWnd, "Вы уверены, что хотите пересоздать мир? Все несохранённые данные будут утеряны.", "Внимание!", MB_OKCANCEL | MB_ICONEXCLAMATION | MB_DEFBUTTON2) == IDOK) {
				ResetMap(hWnd);
			}
			break;
		}

		case IndexButtonSafeCrt:
		{
			SetFocus(hWnd);
			if (peep_Creature == nullptr) { MessageBoxA(hWnd, "Существо не выбрано.", "Внимание!", MB_OK | MB_ICONEXCLAMATION); break; }

			bool flag_step = FlagStop;
			StopStep(hWnd);

			OPENFILENAMEA ofn;
			char PathSafeCrt[260]{};
			SetOpenFileParams(hWnd, &ofn, PathSafeCrt, ".crt", "Существо(*.crt)\0*.crt\0", OFN_PATHMUSTEXIST);

			if (GetSaveFileNameA(&ofn)) {
				if (CheckExpansion(PathSafeCrt + ofn.nFileExtension, "crt")) {
					MessageBoxA(hWnd, "Ошибка открытия файла. Неправильное расширение файла. Требуется: *.crt", "Ошибка!", MB_OK | MB_ICONERROR);
				}
				else {
					//std::string str_to_write = peep_Creature->write_myself();
					//
					//HANDLE FileToWrite = CreateFileA(PathSafeCrt, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
					//DWORD len_write_str;
					//WriteFile(FileToWrite, str_to_write.c_str(), str_to_write.size(), &len_write_str, NULL);
					//
					//CloseHandle(FileToWrite);

					std::ofstream fout;
					fout.open(PathSafeCrt);
					try {
						fout << peep_Creature->write_myself();
						MessageBoxA(hWnd, "Существо успешно сохранено.", "Успех!", MB_OK | MB_ICONINFORMATION);
					}
					catch (...) {
						MessageBoxA(hWnd, "Ошибка записи в файл. Неизвестная ошибка.", "Ошибка!", MB_OK | MB_ICONERROR);
					}
					fout.close();
				}
			}

			if (flag_step) { StartStep(hWnd); }
			break;
		}
		case IndexButtonLoadCrt:
		{
			SetFocus(hWnd);
			bool flag_step = FlagStop;
			StopStep(hWnd);

			OPENFILENAMEA ofn;
			char PathLoadCrt[260]{};
			SetOpenFileParams(hWnd, &ofn, PathLoadCrt, ".crt", "Существо(*.crt)\0*.crt\0", OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST);

			if (GetOpenFileNameA(&ofn)) {
				if (CheckExpansion(PathLoadCrt + ofn.nFileExtension, "crt")) {
					MessageBoxA(hWnd, "Ошибка открытия файла. Неправильное расширение файла. Требуется: *.crt", "Ошибка!", MB_OK | MB_ICONERROR);
				}
				else {
					std::ifstream fin;
					fin.open(PathLoadCrt);
					std::string str_to_read;
					std::getline(fin, str_to_read);

					Creature* load_peep_Creature = nullptr;
					try {
						load_peep_Creature = parse_str_to_Creature({ 0, 0 }, str_to_read);

						if (!life_peep_Creature) { delete peep_Creature; }
						peep_Creature = load_peep_Creature;
						load_peep_Creature = nullptr;

						life_peep_Creature = false;
						last_draw_peep_Creature = true;

						MaxPosSliderPeepBrain = peep_Creature->get_brain_size() - 1;
						SetScrollRange(SliderPeepBrain, SB_CTL, 0, MaxPosSliderPeepBrain, TRUE);
						PosSliderPeepBrain = min(PosSliderPeepBrain, MaxPosSliderPeepBrain);
						SetScrollPos(SliderPeepBrain, SB_CTL, PosSliderPeepBrain, TRUE);

						peep_Creature->build_brain(hWnd);
						peep_Creature->draw_brain();
						DrawInterface();
					}
					catch (const std::out_of_range& oor)
					{
						MessageBoxA(hWnd, "Ошибка чтения файла. Файл неожиданно закончился. Проверьте целостность файла.", "Ошибка!", MB_OK | MB_ICONERROR);
					}
					catch (...) {
						MessageBoxA(hWnd, "Ошибка чтения файла. Неизвестная ошибка.", "Ошибка!", MB_OK | MB_ICONERROR);
					}
					fin.close();
				}
			}

			if (flag_step) { StartStep(hWnd); }
			break;
		}

		case IndexButtonSafeMap:
		{
			SetFocus(hWnd);
			bool flag_step = FlagStop;
			StopStep(hWnd);

			OPENFILENAMEA ofn;
			char PathSafeMap[260]{};
			SetOpenFileParams(hWnd, &ofn, PathSafeMap, ".map", "Мир(*.map)\0*.map\0", OFN_PATHMUSTEXIST);

			if (GetSaveFileNameA(&ofn)) {
				if (CheckExpansion(PathSafeMap + ofn.nFileExtension, "map")) {
					MessageBoxA(hWnd, "Ошибка открытия файла. Неправильное расширение файла. Требуется: *.map", "Ошибка!", MB_OK | MB_ICONERROR);
				}
				else {
					//HANDLE FileToWrite = CreateFileA(PathSafeMap, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
					//DWORD len_write_str;
					//
					//std::string str_to_write = std::to_string(CountStep) + ';' + std::to_string(size_map_x) + ';' + std::to_string(size_map_y) + '\n';
					//WriteFile(FileToWrite, str_to_write.c_str(), str_to_write.size(), &len_write_str, NULL);
					//
					//for (int i = 0; i < size_map_x; i++)
					//{
					//	for (int j = 0; j < size_map_y; j++)
					//	{
					//		str_to_write = map[i][j].write_myself();
					//		WriteFile(FileToWrite, str_to_write.c_str(), str_to_write.size(), &len_write_str, NULL);
					//	}
					//}
					//
					//CloseHandle(FileToWrite);

					std::ofstream fout;
					fout.open(PathSafeMap);
					fout << std::to_string(CountStep) + ';' + 
						std::to_string(size_map_x) + ';' + 
						std::to_string(size_map_y) + ';' + 
						std::to_string(PosSliderRedEat) + ';' + 
						std::to_string(PosSliderRedLeave) + ';' +
						std::to_string(PosSliderGreenEat) + ';' + 
						std::to_string(PosSliderBlueEat) + ';' +
						std::to_string(PosSliderAllLose) + ';' +
						std::to_string(FlagRandDivision) + ";\n";
					for (int i = 0; i < size_map_x; i++)
					{
						for (int j = 0; j < size_map_y; j++)
						{
							fout << map[i][j].write_myself();
						}
					}
					fout.close();

					MessageBoxA(hWnd, "Мир успешно сохранён.", "Успех!", MB_OK | MB_ICONINFORMATION);
				}
			}

			if (flag_step) { StartStep(hWnd); }
			break;
		}
		case IndexButtonLoadMap:
		{
			SetFocus(hWnd);
			StopStep(hWnd);

			OPENFILENAMEA ofn;
			char PathLoadMap[260]{};
			SetOpenFileParams(hWnd, &ofn, PathLoadMap, ".map", "Мир(*.map)\0*.map\0", OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST);

			if (GetOpenFileNameA(&ofn)) {
				if (CheckExpansion(PathLoadMap + ofn.nFileExtension, "map")) {
					MessageBoxA(hWnd, "Ошибка открытия файла. Неправильное расширение файла. Требуется: *.map", "Ошибка!", MB_OK | MB_ICONERROR);
				}
				else {
					std::ifstream fin;
					fin.open(PathLoadMap);
					std::string str_to_read;
					std::getline(fin, str_to_read);  // размеры карты и текущий шаг

					Cell** load_map = nullptr;
					int load_size_map_x, load_size_map_y, iter = 0;
					int LoadPosSliderRedEat, LoadPosSliderRedLeave, LoadPosSliderGreenEat, LoadPosSliderBlueEat, LoadPosSliderAllLose;
					bool LoadFlagRandDivision;
					long long LoadCountStep = 0;

					try {
						while (str_to_read[iter] != ';') {    // !!!!!!!!!!!!!!!!!!!!!!!  чтение long long переменной
							LoadCountStep = LoadCountStep * 10 + str_to_read.at(iter) - '0';
							iter++;
						}
						iter++;

						load_size_map_x = parse_str_to_int_one_step(str_to_read, &iter);  // x
						load_size_map_y = parse_str_to_int_one_step(str_to_read, &iter);  // y

						LoadPosSliderRedEat = parse_str_to_int_one_step(str_to_read, &iter);
						LoadPosSliderRedLeave = parse_str_to_int_one_step(str_to_read, &iter);
						LoadPosSliderGreenEat = parse_str_to_int_one_step(str_to_read, &iter);
						LoadPosSliderBlueEat = parse_str_to_int_one_step(str_to_read, &iter);
						LoadPosSliderAllLose = parse_str_to_int_one_step(str_to_read, &iter);

						LoadFlagRandDivision = parse_str_to_int_one_step(str_to_read, &iter);
					}
					catch (...) {
						LoadCountStep = -1;
					}

					try {
						if (LoadCountStep == -1) {
							throw int(-1);
						}

						load_map = new Cell * [load_size_map_x];
						for (int i = 0; i < load_size_map_x; i++)
						{
							load_map[i] = new Cell[load_size_map_y];
						}

						for (int i = 0; i < load_size_map_x; i++)
						{
							for (int j = 0; j < load_size_map_y; j++)
							{
								std::getline(fin, str_to_read);
								load_map[i][j].set_map_cord({i, j});
								load_map[i][j].read_myself(str_to_read);
							}
						}

						for (int i = 0; i < size_map_x; i++)
						{
							delete[] map[i];
						}
						delete[] map;

						map = load_map;
						CountStep = LoadCountStep;

						size_map_x = load_size_map_x;
						size_map_y = load_size_map_y;
						SetWindowTextA(EditSizeMapX, LPCSTR(std::to_string(size_map_x).c_str()));
						SetWindowTextA(EditSizeMapY, LPCSTR(std::to_string(size_map_y).c_str()));

						SendMessage(CheckBoxRandDivision, BM_SETCHECK, FlagRandDivision = LoadFlagRandDivision, 0);

						DrawInterface();

						MoveSlider(hWnd, 3, &(PosSliderRedEat = LoadPosSliderRedEat), 0, MaxPosSliderRedEat);
						MoveSlider(hWnd, 4, &(PosSliderRedLeave = LoadPosSliderRedLeave), 0, MaxPosSliderRedLeave);
						MoveSlider(hWnd, 5, &(PosSliderGreenEat = LoadPosSliderGreenEat), 0, MaxPosSliderGreenEat);
						MoveSlider(hWnd, 6, &(PosSliderBlueEat = LoadPosSliderBlueEat), 0, MaxPosSliderBlueEat);
						MoveSlider(hWnd, 7, &(PosSliderAllLose = LoadPosSliderAllLose), 0, MaxPosSliderAllLose);

						UpdateSizeScreen(hWnd, size_screen_x, size_screen_y, true);
					}
					catch (int read_size_map_error) {
						MessageBoxA(hWnd, "Ошибка чтения файла. Не удалось прочитать данные о номере хода, размерах мира и положениях слайдеров. Проверьте целостность первой строки файла.", "Ошибка!", MB_OK | MB_ICONERROR);
					}
					catch (const std::out_of_range& oor)
					{
						for (int i = 0; i < load_size_map_x; i++)
						{
							delete[] load_map[i];
							load_map[i] = nullptr;
						}
						delete[] load_map;
						load_map = nullptr;

						MessageBoxA(hWnd, "Ошибка чтения файла. Файл неожиданно закончился. Проверьте целостность файла.", "Ошибка!", MB_OK | MB_ICONERROR);
					}
					catch (...) {
						for (int i = 0; i < load_size_map_x; i++)
						{
							delete[] load_map[i];
							load_map[i] = nullptr;
						}
						delete[] load_map;
						load_map = nullptr;	

						MessageBoxA(hWnd, "Ошибка чтения файла. Неизвестная ошибка.", "Ошибка!", MB_OK | MB_ICONERROR);
					}

					fin.close();
				}
			}
			break;
		}
		}
		break;
	}

	case WM_TIMER:
	{
		switch (wParam) {
		case IndexTimerDraw:
			//CheckFin();
			//UpdatePlayInfo(hWnd);
			for (int step = 0; step < PosSliderStepDraw; step++)   // прокрутка неотрисованных кадров
			{
				OneStep();

				DrawInterface();

				if (FlagAutomaticStop && (Creature_Plant::get_type_count() < 5 || Creature_Herbivore::get_type_count() < 5 || Creature_Scavenger::get_type_count() < 5)) {
					StopStep(hWnd);
					break;
				}

				if (FlagAutomaticReset && (Creature_Plant::get_type_count() == 0 || Creature_Herbivore::get_type_count() == 0 || Creature_Scavenger::get_type_count() == 0)) {
					ResetMap(hWnd);
					StartStep(hWnd);
					break;
				}
			}
			//if (CountStep % PosSliderStepDraw == 0) {
			UpdateDraw(hWnd);
			//}
			break;
		}
		break;
	}
	case WM_PAINT:
	{
		MainHdc = BeginPaint(hWnd, &MainPs);

		Draw(MainHdc);
		//ValidateRect(hWnd, RECT);

		//SelectObject(MainHdc, CreatePen(PS_SOLID, 1, RGB(255, 255, 255)));
		//SelectObject(MainHdc, CreatePen(PS_NULL, 1, RGB(0, 0, 0)));
		//SelectObject(hdc, H_Gray[min(this->free_energy / (limit_energy / 200), 199)]);
		//SelectObject(hdc, (HGDIOBJ)NULL_PEN);
		//SelectObject(MainHdc, H_Gray[0]);
		//Rectangle(MainHdc, 30, 30, 130, 130);
		//SelectObject(MainHdc, H_Gray[140]);
		//Rectangle(MainHdc, 120, 30, 230, 230);
		EndPaint(hWnd, &MainPs);

		if (!position_WM_SETREDRAW) { SendMessage(hWnd, WM_SETREDRAW, false, 0); }  // убрать отрисовку если она не нужна

		break;
	}

	case WM_KEYDOWN:    // http://www.cyberguru.ru/programming/win32/win32-keyboard.html?showall=
						// https://learn.microsoft.com/ru-ru/windows/win32/inputdev/virtual-key-codes
	{
		switch (wParam) {
		case ' ':
			SendMessage(hWnd, WM_COMMAND, IndexButtonStop, 0);
			break;
		case VK_F11:
			if (FlagFullscreen) {  // когда в полноэкранном режиме
				FlagFullscreen = false;  // вЫключить полноэкранный режим
				
				SetWindowLong(hWnd, GWL_STYLE, FullscreenStyle); // Загружаем стиль оконного режима
				SetWindowPlacement(hWnd, &FullscreenPlacement); // Загружаем размещение оконного режима
				ShowWindow(hWnd, SW_SHOW);
			}
			else {
				FlagFullscreen = true; // включить полноэкранный режим

				FullscreenStyle = GetWindowLong(hWnd, GWL_STYLE); // Сохраняем текущий стиль
				FullscreenPlacement.length = sizeof(WINDOWPLACEMENT);
				GetWindowPlacement(hWnd, &FullscreenPlacement); // Сохраняем размещение
				SetWindowLong(hWnd, GWL_STYLE, WS_POPUP); // Устанавливаем новый стиль
				ShowWindow(hWnd, SW_SHOWMAXIMIZED); // Окно во весь экран
			}
			break;
		}
		break;
	}

	case WM_LBUTTONDOWN:
	{		
		//std::pair<int, int> map_cord((GET_X_LPARAM(lParam) - margin_x) / size_cell, (GET_Y_LPARAM(lParam) - margin_y) / size_cell);
		if (PosSliderStepDraw == MaxPosSliderStepDraw || FlagFullscreen) { break; }

		int xPos = GET_X_LPARAM(lParam);
		int yPos = GET_Y_LPARAM(lParam);

		if (xPos >= margin_x && xPos < (margin_x + size_cell * size_map_x) &&
			yPos >= margin_y && yPos < (margin_y + size_cell * size_map_y)) {

			std::pair<int, int> map_cord((GET_X_LPARAM(lParam) - margin_x) / size_cell, (GET_Y_LPARAM(lParam) - margin_y) / size_cell);

			Cell* place = get_Cell_by_map_cord(map_cord);

			if (wParam & MK_SHIFT) {
				SetCapture(hWnd);

				if (peep_Creature != nullptr) {
					place->set_Creature(peep_Creature->copy(map_cord));
				}
				else {
					place->set_Creature();
				}
			}
			else {
				last_draw_peep_Creature = true;

				if (!life_peep_Creature) {
					delete peep_Creature;
					life_peep_Creature = true;
				}
				peep_Creature = nullptr;
				if (place->get_TYPE_CREATURE() != TYPE_CREATURE::Void) {

					peep_Creature = place->get_Creature();

					MaxPosSliderPeepBrain = peep_Creature->get_brain_size() - 1;
					SetScrollRange(SliderPeepBrain, SB_CTL, 0, MaxPosSliderPeepBrain, TRUE);
					PosSliderPeepBrain = min(PosSliderPeepBrain, MaxPosSliderPeepBrain);
					SetScrollPos(SliderPeepBrain, SB_CTL, PosSliderPeepBrain, TRUE);

					peep_Creature->build_brain(hWnd);
					peep_Creature->draw_brain();
				}
				else {
					for (auto& act : StaticPeepBrain) {
						ShowWindow(act.first, SW_HIDE);
						DestroyWindow(act.first);
					}
					StaticPeepBrain.clear();
					SetWindowTextA(StaticPeepData, LPCSTR("Энергия: 0  Энергия деления: 0  Возраст: 0  Направление: -  Действие: 0  Живо: нет"));
				}
			}

			FullUpdateDraw(hWnd);
		}
		break;
	}
	case WM_MOUSEMOVE:
	{
		if (wParam & MK_LBUTTON) {
			if (wParam & MK_SHIFT) {
				if (PosSliderStepDraw == MaxPosSliderStepDraw || FlagFullscreen) { break; }

				int xPos = GET_X_LPARAM(lParam);
				int yPos = GET_Y_LPARAM(lParam);

				if (xPos >= margin_x && xPos < (margin_x + size_cell * size_map_x) &&
					yPos >= margin_y && yPos < (margin_y + size_cell * size_map_y)) {

					std::pair<int, int> map_cord((GET_X_LPARAM(lParam) - margin_x) / size_cell, (GET_Y_LPARAM(lParam) - margin_y) / size_cell);

					Cell* place = get_Cell_by_map_cord(map_cord);

					if (peep_Creature != nullptr) {
						place->set_Creature(peep_Creature->copy(map_cord));
					}
					else {
						place->set_Creature();
					}

					FullUpdateDraw(hWnd);
				}
			}
		}
		break;
	}
	case WM_LBUTTONUP:
	{
		ReleaseCapture();
		break;
	}

	case WM_ENTERSIZEMOVE:
	{
		SendMessage(hWnd, WM_SETREDRAW, false, 0);
		position_WM_SETREDRAW = false;
		break;
	}
	case WM_EXITSIZEMOVE:
	{
		SendMessage(hWnd, WM_SETREDRAW, true, 0);
		position_WM_SETREDRAW = true;

		//if(1 || size_cell == MinSizeCell || (size_cell * size_map_y + 3 * margin_y + 136) < 
		// ){  // это чтобы самый маленький экран отрисовался когда ты отпустил
		//	InvalidateRect(hWnd, NULL, true);

		//	UpdateWidget();
		//}// 
		// приходится обновлять всегда из за не отрисовки при перетягивании полноэкранного окна
		InvalidateRect(hWnd, NULL, true);  

		UpdateWidget();


		break;
	}
	case WM_SIZE:
	{
		UpdateSizeScreen(hWnd, LOWORD(lParam), HIWORD(lParam));   // это можно перенести в WM_EXITSIZEMOVE только нужно получать размеры экрана
		return 0;
	}

	//case WM_CTLCOLOREDIT:
	case WM_CTLCOLORSCROLLBAR:
	case WM_CTLCOLORSTATIC:
	{
		//return (LRESULT)GetSysColorBrush(COLOR_WINDOW);
		SetTextColor((HDC)wParam, RGB(200, 200, 200));	
		SetBkMode((HDC)wParam, TRANSPARENT);
		return (LRESULT)H_Background;
		break;
	}

	case WM_CREATE:
	{
		srand(unsigned int(time(0)));
		int size = GetCurrentDirectoryA(260, ThisSaveDirectory);
		for (int i = 0; i < 22; i++)
		{
			ThisSaveDirectory[size + i] = "\\Saves_Life_simulation"[i];
		}
		CreateDirectoryA(ThisSaveDirectory, NULL);

		BuildDrawEffecter(hWnd);
		BuildWidget(hWnd);
		BuildObject();

		FullUpdateDraw(hWnd);
		break;
	}
	case WM_DESTROY:
	{
		KillTimer(hWnd, IndexTimerDraw);

		if (!life_peep_Creature) {
			delete peep_Creature;
		}
		peep_Creature = nullptr;

		DestroyDrawEffecter(hWnd);
		DestroyWidget(hWnd);
		DestroyObject();

		PostQuitMessage(0);
		break;
	}
	default:
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	}

	return 0;
}



