#include <stdio.h>
#include<stdlib.h>
#include<string.h>

#include<minigui/common.h>
#include<minigui/minigui.h>
#include<minigui/gdi.h>
#include<minigui/window.h>
#include<minigui/control.h>

#include "menu.h"
#include "menu2.h"
#include "notebook.h"
static int MainWinProc(HWND hWnd,int message,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	switch(message){
		case MSG_PAINT:
		hdc=BeginPaint(hWnd);
		TextOut(hdc,0,0,"Welcome to use \"Comunity detection algorithms platform!\"");
		EndPaint(hWnd,hdc);
		return 0;

		case MSG_CLOSE:
		DestroyMainWindow(hWnd);
		PostQuitMessage(hWnd);
		return 0;
		
/*		case MSG_ACTIVEMENU:
		if (wParam == 2) {
		CheckMenuRadioItem ((HMENU)lParam,
		IDM_40X15, IDM_CUSTOMIZE,
		pNoteInfo->winType, MF_BYCOMMAND);
		CheckMenuRadioItem ((HMENU)lParam,
		IDM_DEFAULT, IDM_BIG5,
		pNoteInfo->editCharset, MF_BYCOMMAND);
*/
		case MSG_COMMAND:
		switch (wParam) {
			case IDM_KERNIGHAN_LIN:
			break;
		}
		return 0;

		case MSG_RBUTTONDOWN:
		{
		int x=LOWORD(lParam);
		int y=HIWORD(lParam);
//		ScreenToClient(hWnd,&x,&y);
		right_button_menu(hWnd,x,y);
		return 0;
		}

	}
	return DefaultMainWinProc(hWnd,message,wParam,lParam);
}

int MiniGUIMain(int argc,const char *argv[])
{
	MSG Msg;
	HWND hMainWnd;
	MAINWINCREATE CreateInfo;
	
	#ifdef _MGRM_PROCESSES
	JoinLayer(NAME_DEF_LAYER,"Community Detection v0.1",0,0);
	if(!ServerStartup(0,0,0)){
		fprintf(stderr,"Can not start the server of Minigui_Processes:mginit.\n");
		return 1;
	}
	#endif

	CreateInfo.dwStyle=WS_VISIBLE|WS_BORDER|WS_CAPTION|WS_MINIMIZEBOX;
	CreateInfo.dwExStyle=WS_EX_NONE;
	CreateInfo.spCaption="Community Detection v0.1";
	CreateInfo.hMenu=createmenu();
	CreateInfo.hCursor=GetSystemCursor(0);
	CreateInfo.hIcon=0;
	CreateInfo.MainWindowProc=MainWinProc;
	CreateInfo.lx=50;
	CreateInfo.ty=50;
	CreateInfo.rx=500;
	CreateInfo.by=500;
	CreateInfo.iBkColor=COLOR_lightwhite;
	CreateInfo.dwAddData=0;
	CreateInfo.hHosting=HWND_DESKTOP;
	hMainWnd=CreateMainWindow(&CreateInfo);
	if(hMainWnd==HWND_INVALID)
		return -1;

	ShowWindow(hMainWnd,SW_SHOWNORMAL);
	while(GetMessage(&Msg,hMainWnd)){
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	MainWindowThreadCleanup(hMainWnd);
	return 0;
}

#ifndef _MGRM_PROCESSES
#include<minigui/dti.c>

#endif
