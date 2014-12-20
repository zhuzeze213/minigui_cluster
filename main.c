#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>

#include<minigui/common.h>
#include<minigui/minigui.h>
#include<minigui/gdi.h>
#include<minigui/window.h>
#include<minigui/control.h>
#include "myarg.h"
#include "menu.h"
#include "notebook.h"

int algorithm=0,networks=0;
char filename[FILE_SIZE];
static int step = 12;

static int MainWinProc(HWND hWnd,int message,WPARAM wParam,LPARAM lParam)
{
	HDC hdc;
	static int iStart = 0;
    	static int iStartPos = 0;
	switch(message){
		case MSG_CREATE:
            	SetScrollRange (hWnd, SB_VERT, 0, 20*12);
		SetScrollRange (hWnd, SB_HORZ, 0, 20*12);
		EnableScrollBar (hWnd, SB_VERT, TRUE);
            	EnableScrollBar (hWnd, SB_HORZ, TRUE);
		ShowScrollBar(hWnd, SB_VERT, TRUE);
                ShowScrollBar(hWnd, SB_HORZ, TRUE); 
		return 0;
		
		case MSG_HSCROLL:
            	{
        	SCROLLINFO hscroll;
            	if (wParam == SB_LINERIGHT||wParam==SB_PAGERIGHT) {
                	hscroll.fMask = SIF_ALL;
                	GetScrollInfo(hWnd, SB_VERT, &hscroll);
                	if (hscroll.nPos + hscroll.nPage >= hscroll.nMax)
                    	break;
                	if (iStart < step) {
                    		iStart ++;
                    		ScrollWindow (hWnd, -20, 0, NULL, NULL);
                	}
           	}
            	else if (wParam == SB_LINELEFT||wParam==SB_PAGELEFT) {
                	if (iStart > 0) {
                    		iStart --;
                    		ScrollWindow (hWnd, 20, 0, NULL, NULL);
                	}
            	}
            	SetScrollPos (hWnd, SB_HORZ, iStart*20);
		return 0;
        	}

		case MSG_VSCROLL:
		{
        	SCROLLINFO vscroll;
            	if (wParam == SB_LINEDOWN||wParam==SB_PAGEDOWN) {
                	vscroll.fMask = SIF_ALL;
                	GetScrollInfo(hWnd, SB_VERT, &vscroll);
                	if (vscroll.nPos + vscroll.nPage >= vscroll.nMax)
                    	break;
                	if (iStart < step) {
                    		iStart ++;
                    		ScrollWindow (hWnd, 0, -20, NULL, NULL);
                	}
           	}
            	else if (wParam == SB_LINEUP||wParam==SB_PAGEUP) {
                	if (iStart > 0) {
                    		iStart --;
                    		ScrollWindow (hWnd, 0, 20, NULL, NULL);
                	}
            	}
            	SetScrollPos (hWnd, SB_VERT, iStart*20);
		return 0;
        	}
		
		case MSG_PAINT:
		if(!algorithm){
			hdc=BeginPaint(hWnd);
			TextOut(hdc,0,0,"Welcome to use \"Comunity detection algorithms platform!\"");
			EndPaint(hWnd,hdc);
		}
		else if(algorithm&&!networks){
			hdc=BeginPaint(hWnd);
			TextOut(hdc,0,0,"you have choosen the algorithm,please choose the network!");
			EndPaint(hWnd,hdc);
		}
		else{
			int row=0,i=1;
			hdc=BeginPaint(hWnd);
			TextOut(hdc,0,0,"result!\n");
			FILE *fp=fopen(filename,"r");
			char buffer[BUFFER_SIZE];
			while(fgets(buffer,BUFFER_SIZE,fp))
				TextOut(hdc,0,row+=LINE_SIZE*i,buffer);
			EndPaint(hWnd,hdc);
		}

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
			case IDM_FCM:
			algorithm=1;
			strcpy(filename,"fcm");
			InvalidateRect (hWnd, NULL, TRUE);
			break;

			case IDM_KARATE:
			networks=1;
			InvalidateRect(hWnd,NULL,TRUE);
			break;

			case IDM_RIGHT_BUTTON+5: //fresh
			algorithm=networks=0;
			InvalidateRect(hWnd,NULL,TRUE);
			
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

static int MiniGUIMain(int argc,const char *argv[])
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

	CreateInfo.dwStyle=WS_VISIBLE|WS_BORDER|WS_CAPTION|WS_MINIMIZEBOX|WS_HSCROLL|WS_VSCROLL;
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
