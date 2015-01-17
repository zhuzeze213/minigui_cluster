#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#define PAGE_VERSION	1
#define PAGE_CPU	2
#define PAGE_MEMINFO	3
#define PAGE_PARTITION  4
#define PAGE_MINIGUI    5

#define IDC_PROPSHEET	100

#define IDC_SYSINFO	100

#include "propsheet.h"


static DLGTEMPLATE PageSysInfo =
{
    WS_BORDER | WS_CAPTION,
    WS_EX_NONE,
    0, 0, 0, 0,
    "",
    0, 0,
    1, NULL,
    0
};

static CTRLDATA CtrlSysInfo [] =
{ 
    {
        CTRL_STATIC,
        WS_VISIBLE | SS_LEFT | WS_BORDER, 
        10, 10, 370, 160,
        IDC_SYSINFO,
        "",
        0
    }
};

#define BUF_LEN 10240

static void get_systeminfo (HWND hDlg)
{
    int type;
    HWND hwnd;
    char buff [BUF_LEN + 1];
    size_t size = 0;

    type = (int)GetWindowAdditionalData (hDlg);
    hwnd = GetDlgItem (hDlg, IDC_SYSINFO);

    buff [BUF_LEN] = 0;
    switch (type) {
    case PAGE_VERSION:
	    //size = read_sysinfo ("/proc/version", buff, BUF_LEN);
    	    buff [size] = 0;
	    break;

    case PAGE_CPU:
	    //size = read_sysinfo ("/proc/cpuinfo", buff, BUF_LEN);
    	    buff [size] = 0;
	    break;

    case PAGE_MEMINFO:
	    //size = read_sysinfo ("/proc/meminfo", buff, BUF_LEN);
    	    buff [size] = 0;
	    break;

    case PAGE_PARTITION:
	    //size = read_sysinfo ("/proc/partitions", buff, BUF_LEN);
    	    buff [size] = 0;
	    break;

    case PAGE_MINIGUI:
	    size = snprintf (buff, BUF_LEN,
		"MiniGUI Community Detection version 0.1\n"
		"The software is a useful, interesting "
        "GUI support system.\n\n"
		"For source code, please visit\n\n"
		"https://github.com/zhuzeze213/minigui_cluster"
		);
	    break;
    }

    if (size) {
	    SetWindowText (hwnd, buff);
    }
}

static int SysInfoPageProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case MSG_INITPAGE:
	get_systeminfo (hDlg);
        break;

    case MSG_SHOWPAGE:
        return 1;

    case MSG_SHEETCMD:
	if (wParam == IDOK) 
	    get_systeminfo (hDlg);
        return 0;
    }
    
    return DefaultPageProc (hDlg, message, wParam, lParam);
}

int PropSheetProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
        case MSG_INITDIALOG:
        {
            HWND pshwnd = GetDlgItem (hDlg, IDC_PROPSHEET);

            PageSysInfo.controls = CtrlSysInfo;
	    PageSysInfo.caption = version_info;
			PageSysInfo.dwAddData = PAGE_VERSION;
            SendMessage (pshwnd, PSM_ADDPAGE, (WPARAM)&PageSysInfo, (LPARAM)SysInfoPageProc);
	    PageSysInfo.caption = CPU_info;
	    PageSysInfo.dwAddData = PAGE_CPU;
            SendMessage (pshwnd, PSM_ADDPAGE, (WPARAM)&PageSysInfo, (LPARAM)SysInfoPageProc);
	    PageSysInfo.caption = mem_info;
	    PageSysInfo.dwAddData = PAGE_MEMINFO;
            SendMessage (pshwnd, PSM_ADDPAGE, (WPARAM)&PageSysInfo, (LPARAM)SysInfoPageProc);
	    PageSysInfo.caption = partition_info;
	    PageSysInfo.dwAddData = PAGE_PARTITION;
            SendMessage (pshwnd, PSM_ADDPAGE, (WPARAM)&PageSysInfo, (LPARAM)SysInfoPageProc);
	    PageSysInfo.caption = MiniGUI_info;
	    PageSysInfo.dwAddData = PAGE_MINIGUI;
            SendMessage (pshwnd, PSM_ADDPAGE, (WPARAM)&PageSysInfo, (LPARAM)SysInfoPageProc);
            break;
        }

        case MSG_COMMAND:
        switch (wParam) {
            case IDOK:
                SendDlgItemMessage (hDlg, IDC_PROPSHEET, PSM_SHEETCMD, IDOK, 0);
                break;

            case IDCANCEL:
                EndDialog (hDlg, wParam);
            break;
        }
        break;
    }

    return DefaultDialogProc (hDlg, message, wParam, lParam);
}

DLGTEMPLATE DlgPropSheet =
{
    WS_BORDER | WS_CAPTION,
    WS_EX_NONE,
    0, 0, 410, 285,
    System_info,
    0, 0,
    3, NULL,
    0
};

CTRLDATA CtrlPropSheet[] =
{ 
    {
        CTRL_PROPSHEET,
        WS_VISIBLE | PSS_COMPACTTAB, 
        10, 10, 390, 200,
        IDC_PROPSHEET,
        "",
        0
    },
    {
        CTRL_BUTTON,
        WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP | WS_GROUP,
        10, 220, 70, 25,
        IDOK, 
        Refresh,
        0
    },
    {
        CTRL_BUTTON,
        WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
        330, 220, 70, 25,
        IDCANCEL,
        Close,
        0
    },
};

#ifdef _MGRM_THREADS
#include <minigui/dti.c>
#endif

