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

#define     deleting_the_files              "Deleting the files"
#define     directories                     "Directories:"
#define     files_                           "Files:"
#define     path_                            "Path: "
#define     delete_                         "Delete"
#define     cancel_                          "Cancel"
#define     deleting_files_                  "Deleting files"

DLGTEMPLATE DlgDelFiles;
CTRLDATA CtrlDelFiles[7];

int DelFilesBoxProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam);
#endif
