#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>
#include "listbox.h"

DLGTEMPLATE DlgBoxInputChar =
{
    WS_BORDER | WS_CAPTION |  WS_CHILD, 
    WS_EX_NONE,
    0, 0, 700, 400, 
    choose_file,
    0, 0,
    1, NULL,
    0
};



CTRLDATA CtrlInputChar [] =
{ 
	{
        CTRL_MLEDIT,
        WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_HSCROLL | /*ES_READONLY
            | ES_BASELINE | ES_AUTOWRAP |*/ ES_NOHIDESEL | ES_NOHIDESEL,//| WS_DISABLED,
        0, 0, 680, 370, 
        IDC_CHARS, 
        NULL,
        0,
        //WS_EX_TRANSPARENT 
	}
};

static void my_notif_proc (HWND hwnd, int id, int nc, DWORD add_data)
{
    /*char buff [256] = {0};
    if (id == IDC_CHAR && nc == EN_CHANGE) {

        GetWindowText (hwnd, buff, 4);
        SendMessage (hwnd, EM_SETCARETPOS, 0, 0);
        SendMessage (GetDlgItem (GetParent (hwnd), IDC_CHARS), MSG_CHAR, buff[0], 0L);
    }
    else if (id == IDC_CHARS && nc == EN_CHANGE) {
        GetWindowText (hwnd, buff, 255);
    }*/
	
}       

int InputCharDialogBoxProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
    HWND hwnd;

    switch (message) {
    case MSG_INITDIALOG:
	{
	char tmp[200000];
	char tmp1[1024];
	int line_pos;
	int char_pos;
	FILE *fp=fopen(choose_file,"r");
	if(fp){
		while(fgets(tmp1,1024,fp))
			strcat(tmp,tmp1);
		SetWindowText(GetDlgItem(hDlg, IDC_CHARS),tmp);
        }
        return 1;
        }
    case MSG_CLOSE:
        EndDialog (hDlg, IDCANCEL);
        break;
        
    case MSG_COMMAND:
        switch (wParam) {
        case IDOK:
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

