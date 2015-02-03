#include <stdio.h>
#include <string.h>
#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
#include "menu.h"

#include "combobox.h"
#include "myarg.h"
#include "progressbar.h"

#define IDC_HOUR   100
#define IDL_DAXIA  200

#define IDC_PROMPT 300

CTRLDATA CtrlMyDate[] =
{ 
    {
        "static",
        WS_CHILD | SS_RIGHT | WS_VISIBLE,
         10, 20, 90, 20,
        IDC_STATIC,
        "Modules   ",
        0
    },
    {
        CTRL_COMBOBOX,
        WS_CHILD | WS_VISIBLE | 
            /*CBS_READONLY | */CBS_AUTOSPIN | CBS_AUTOLOOP,
        100, 18, 40, 20,
        IDC_HOUR, 
        "",
        WS_EX_TRANSPARENT
    },
    {
        "static",
        WS_CHILD | SS_CENTER | WS_VISIBLE,
        140, 20, 95, 20,
        IDC_STATIC,
        "Choose algorithms:",
        0
    },


    {
        CTRL_COMBOBOX,
        WS_VISIBLE | CBS_DROPDOWNLIST | CBS_NOTIFY,
        240, 15, 100, 25,
        IDL_DAXIA,
        "",
        80
    },
    {
        "static",
        WS_CHILD | SS_LEFT | WS_VISIBLE,
        15, 50, 280, 70,
        IDC_PROMPT,
        "",
        0
    },
    {
        CTRL_BUTTON,
        WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP | WS_GROUP,
        30, 120, 70, 25,
        IDOK, 
        OK,
        0
    },
    {
        "button",
        WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
        260, 120, 70, 25,
        IDCANCEL,
        Cancel,
        0
    },
};

DLGTEMPLATE DlgMyDate =
{
    WS_BORDER | WS_CAPTION,
    WS_EX_NONE,
    100, 100, 360, 180,
    "Please Choose~",
    0, 0,
    TABLESIZE(CtrlMyDate),
	NULL,
    0
};

static void daxia_notif_proc (HWND hwnd, int id, int nc, DWORD add_data)
{
    if (nc == CBN_SELCHANGE) {
        int cur_sel = SendMessage (hwnd, CB_GETCURSEL, 0, 0);
	if (cur_sel >= 0) {
		//SetWindowText (GetDlgItem (GetParent(hwnd), IDC_PROMPT), daxia_char [cur_sel]);
	}
    }
}

static void prompt (HWND hDlg)
{
    modules = SendDlgItemMessage(hDlg, IDC_HOUR, CB_GETSPINVALUE, 0, 0);
    int sel = SendDlgItemMessage(hDlg, IDL_DAXIA, CB_GETCURSEL, 0, 0);    
}

int MyDateBoxProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
    int i;
    switch (message) {
    case MSG_INITDIALOG:
        SendDlgItemMessage(hDlg, IDC_HOUR, CB_SETSPINFORMAT, 0, (LPARAM)"%02d");
        SendDlgItemMessage(hDlg, IDC_HOUR, CB_SETSPINRANGE, 0, 23);
        //SendDlgItemMessage(hDlg, IDC_HOUR, CB_SETSPINVALUE, 20, 0);
        SendDlgItemMessage(hDlg, IDC_HOUR, CB_SETSPINPACE, 1, 1);
	if(kind_of_algorithm==IDM_OPTIMIZATION){
        	for (i = 0; i < 8; i++) {
            	SendDlgItemMessage(hDlg, IDL_DAXIA, CB_ADDSTRING, 0, (LPARAM)daxia [i]);
        	}
	}
	else if(kind_of_algorithm==IDM_HEURISTIC){
		for (i = 8; i < 12; i++) {
            		SendDlgItemMessage(hDlg, IDL_DAXIA, CB_ADDSTRING, 0, (LPARAM)daxia [i]);
        		}
	}
	else{
		for (i = 12; i < 14; i++) {
            		SendDlgItemMessage(hDlg, IDL_DAXIA, CB_ADDSTRING, 0, (LPARAM)daxia [i]);
        		}
	}
        SetNotificationCallback (GetDlgItem (hDlg, IDL_DAXIA), daxia_notif_proc);
        SendDlgItemMessage(hDlg, IDL_DAXIA, CB_SETCURSEL, 0, 0);
#ifdef _LANG_ZHCN
	SetWindowText (GetDlgItem (hDlg, IDC_PROMPT), daxia_char [0]);
#endif
        return 1;
        
    case MSG_COMMAND:
        switch (wParam) {
        case IDOK:{
            prompt (hDlg);
            char tmp[1024];
	    GetWindowText(GetDlgItem (hDlg, IDL_DAXIA),tmp,1024);
            strcpy(choose_algorithm,tmp);
	   
	    //printf("%d\n",modules);
	    CreateProgressBar (hDlg);
	    break;
	}
	    
        case IDCANCEL:
            EndDialog (hDlg, wParam);
            break;
        }
        break;
        
    }
    
    return DefaultDialogProc (hDlg, message, wParam, lParam);
}

#ifdef _MGRM_THREADS
#include <minigui/dti.c>
#endif

