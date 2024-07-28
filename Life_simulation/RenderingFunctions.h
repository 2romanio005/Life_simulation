#pragma once
#include <windows.h>

#include "RenderingVariables.h"

void DrawMap(HDC hdc);
void InvalidateMapRect(HWND hWnd);

void RedrawInterface();

void BuildWidget(HWND hWnd);
void MoveWidgets();
void UpdateWidget();
void DestroyWidget(HWND hWnd);

void BuildDrawEffecter(HWND hWnd);
void DestroyDrawEffecter(HWND hWnd);

void FullRedraw(HWND hWnd);