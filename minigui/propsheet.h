#ifndef PROPSHEET_H
#define PROPSHEET_H

#define    version_info                "Version Info" 
#define    CPU_info                    "File Help"
#define    mem_info                    "Edit Help"
#define    partition_info              "Time"
#define    MiniGUI_info                "Contact us"
#define    System_info                 "How To Use"
#define    Refresh                     "Refresh"
#define    Close                       "Close"

DLGTEMPLATE DlgPropSheet;
CTRLDATA CtrlPropSheet[3];
int PropSheetProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam);

#endif
