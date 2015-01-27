#include <stdio.h>
#include <stdlib.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#include "myarg.h"
#include "button.h"
#include "combobox.h"

char* prompts [] = {
    "",
    "include gn,fcm,fec!",
    "include infomap,walktrap!",
	"include a_cut,n_cut,kl,fn,ga,fm,cm,sa!",
};

DLGTEMPLATE DlgYourTaste =
{
    WS_BORDER | WS_CAPTION,
    WS_EX_NONE,
    0, 0, 370, 300,
    "What kind of clustering algorithms?",
    0, 0,
    7, NULL,
    0
};

CTRLDATA CtrlYourTaste[] =
{ 
    {
        "static",
        WS_VISIBLE | SS_GROUPBOX, 
        16, 10, 230, 160,
        IDC_STATIC,
        "option",
        0,
        WS_EX_TRANSPARENT
    },
    {
        "button",
        WS_VISIBLE | BS_AUTORADIOBUTTON | BS_CHECKED | WS_TABSTOP | WS_GROUP,
        36, 38, 200, 20,
        IDM_OPTIMIZATION,
        "Optimization" ,
        0
    },
    {
        "button",
        WS_VISIBLE | BS_AUTORADIOBUTTON, 
        36, 64, 200, 20, 
        IDM_HEURISTIC, 
        "Heuristic",
        0
    },
    {
        "button",
        WS_VISIBLE | BS_AUTORADIOBUTTON,
        36, 90, 200, 20,
        IDM_OTHERS,
        "Others",
        0
    },
    {
        "static",
        WS_VISIBLE | SS_LEFT | WS_GROUP,
        16, 180, 360, 40,
        IDC_PROMPT,
        "include a_cut,n_cut,kl,fn,ga,fm,cm,sa!",
        0
    },
    {
        "button",
        WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP | WS_GROUP,
        70, 230, 70, 30,
        IDOK, 
        OK,
        0
    },
    {
        "button",
        WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
        200, 230, 70, 30,
        IDCANCEL,
        Cancel,
        0
    },
};

static void my_notif_proc (HWND hwnd, int id, int nc, DWORD add_data)
{
    if (nc == BN_CLICKED) {
        SetWindowText (GetDlgItem (GetParent (hwnd), IDC_PROMPT), prompts [id]);
	kind_of_algorithm=id;
	//printf("%d\n",id);
    }

}

int DialogBoxProc2 (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case MSG_INITDIALOG:
        {
            SetNotificationCallback (GetDlgItem (hDlg, IDM_OPTIMIZATION), my_notif_proc);
			SetNotificationCallback (GetDlgItem (hDlg, IDM_HEURISTIC), my_notif_proc);
			SetNotificationCallback (GetDlgItem (hDlg, IDM_OTHERS), my_notif_proc);
        }
        return 1;
        
    case MSG_COMMAND:
        switch (wParam) {
        case IDOK:
		DlgMyDate.controls = CtrlMyDate;  
		DialogBoxIndirectParam (&DlgMyDate, hDlg, MyDateBoxProc, 0L);
		break;
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

