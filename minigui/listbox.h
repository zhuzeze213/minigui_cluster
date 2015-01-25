#ifndef LISTBOX_H
#define LISTBOX_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>
#include <errno.h>

#include <minigui/common.h>
#include <minigui/minigui.h>
#include <minigui/gdi.h>
#include <minigui/window.h>
#include <minigui/control.h>

#define IDL_DIR    100
#define IDL_FILE   110
#define IDC_PATH   120
#define IDC_CHAR   130
#define CHAR_CHANGE 50

#define     look_the_files               "looking the files"
#define     directories                      "Directories:"
#define     files_                           "Files:"
#define     path_                            "Path: "
#define     look_                             "Look"
#define     cancel_                          "Cancel"
#define     looking_files_                  "looking files"

#define     set_path                  "Set save path"

DLGTEMPLATE DlgDelFiles;
CTRLDATA CtrlDelFiles[7];

DLGTEMPLATE DlgSetPath;
CTRLDATA CtrlSetPath[8];
char cd[MAX_PATH+1];

int DelFilesBoxProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam);
int SetPathBoxProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam);
/* edit */
DLGTEMPLATE DlgBoxInputChar;
CTRLDATA CtrlInputChar [1];
int InputCharDialogBoxProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam);
char choose_file[1024];
#define IDC_CHARS       140

#endif

