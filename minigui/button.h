#ifndef BUTTON_H
#define BUTTON_H

#include "menu.h"
#define  OK                                                                    "OK"
#define  Cancel                                                                "Cancel"
#define IDC_PROMPT              200


DLGTEMPLATE DlgYourTaste;
CTRLDATA CtrlYourTaste[7];

int DialogBoxProc2 (HWND hDlg, int message, WPARAM wParam, LPARAM lParam);


#endif

