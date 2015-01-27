#ifndef COMBOBOX_H
#define COMBOBOX_H

#define   OK                                                     "OK"
#define   Cancel                                                 "Cancel"

static const char* daxia [] =
{
    "Acut",
    "Ncut",
    "Ker_Lin",
    "Fast_Newman",
    "GA",
    "Fast_MO",
    "CM",
    "SA",
    "GN","MFC","FEC","FCM",
    "Infomap","Walktrap"
};
static const char* daxia_char [] =
{
    "",
};

int MyDateBoxProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam);
DLGTEMPLATE DlgMyDate;
CTRLDATA CtrlMyDate[7];

#endif

