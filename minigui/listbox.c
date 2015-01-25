
#include "listbox.h"


DLGTEMPLATE DlgDelFiles =
{
    WS_BORDER | WS_CAPTION,
    WS_EX_NONE,
    100, 100, 304, 225,
    look_the_files,
    0, 0,
    7, NULL,
    0
};

CTRLDATA CtrlDelFiles[] =
{ 
    {
        CTRL_STATIC,
        WS_VISIBLE | SS_SIMPLE, 
        10, 10, 130, 15,
        IDC_STATIC,
        directories,
        0
    },
    {
        CTRL_LISTBOX,
        WS_VISIBLE | WS_VSCROLL | WS_BORDER | LBS_SORT | LBS_NOTIFY,
        10, 30, 130, 100,
        IDL_DIR,
        "",
        0
    },
    {
        CTRL_STATIC,
        WS_VISIBLE | SS_SIMPLE, 
        150, 10, 130, 15, 
        IDC_STATIC, 
        files_,
        0
    },
    {
        CTRL_LISTBOX,
        WS_VISIBLE | WS_VSCROLL | WS_BORDER | LBS_SORT | LBS_AUTOCHECKBOX| LBS_NOTIFY,
        150, 30, 130, 100,
        IDL_FILE,
        "",
        0
    },
    {
        CTRL_STATIC,
        WS_VISIBLE | SS_SIMPLE, 
        10, 150, 290, 15, 
        IDC_PATH, 
        path_,
        0
    },
    {
        "button",
        WS_VISIBLE | BS_DEFPUSHBUTTON | WS_TABSTOP | WS_GROUP,
        10, 170, 130, 25,
        IDOK, 
        look_,
        0
    },
    {
        "button",
        WS_VISIBLE | BS_PUSHBUTTON | WS_TABSTOP,
        150, 170, 130, 25,
        IDCANCEL,
        cancel_,
        0
    },
};

static void fill_boxes (HWND hDlg, const char* path)
{
#ifdef __NOUNIX__
    LISTBOXITEMINFO lbii;

    lbii.string = "file.1";
    lbii.cmFlag = CMFLAG_BLANK;
    lbii.hIcon = 0;
    SendDlgItemMessage (hDlg, IDL_FILE, LB_ADDSTRING, 0, (LPARAM)&lbii);

    lbii.string = "file.2";
    SendDlgItemMessage (hDlg, IDL_FILE, LB_ADDSTRING, 0, (LPARAM)&lbii);

    lbii.string = "file.3";
    SendDlgItemMessage (hDlg, IDL_FILE, LB_ADDSTRING, 0, (LPARAM)&lbii);
#else
    struct dirent* dir_ent;
    DIR*   dir;
    struct stat ftype;
    char   fullpath [PATH_MAX + 1];

    SendDlgItemMessage (hDlg, IDL_DIR, LB_RESETCONTENT, 0, (LPARAM)0);
    SendDlgItemMessage (hDlg, IDL_FILE, LB_RESETCONTENT, 0, (LPARAM)0);
    SetWindowText (GetDlgItem (hDlg, IDC_PATH), path);
    
    if ((dir = opendir (path)) == NULL)
         return;

    while ( (dir_ent = readdir ( dir )) != NULL ) {

        /* Assemble full path name. */
        strncpy (fullpath, path, PATH_MAX);
        strcat (fullpath, "/");
        strcat (fullpath, dir_ent->d_name);
        
        if (stat (fullpath, &ftype) < 0 ) {
           continue;
        }

        if (S_ISDIR (ftype.st_mode))
            SendDlgItemMessage (hDlg, IDL_DIR, LB_ADDSTRING, 0, (LPARAM)dir_ent->d_name);
        else if (S_ISREG (ftype.st_mode)) {
            LISTBOXITEMINFO lbii;

            lbii.string = dir_ent->d_name;
            lbii.cmFlag = CMFLAG_BLANK;
            lbii.hIcon = 0;
            SendDlgItemMessage (hDlg, IDL_FILE, LB_ADDSTRING, 0, (LPARAM)&lbii);
        }
    }

    closedir (dir);
#endif
}

static void dir_notif_proc (HWND hwnd, int id, int nc, DWORD add_data)
{
    if (nc == LBN_DBLCLK || nc == LBN_ENTER) {
        int cur_sel = SendMessage (hwnd, LB_GETCURSEL, 0, 0L);
        if (cur_sel >= 0) {
            char cwd [MAX_PATH + 1];
            char dir [MAX_NAME + 1];
            GetWindowText (GetDlgItem (GetParent (hwnd), IDC_PATH), cwd, MAX_PATH);
            SendMessage (hwnd, LB_GETTEXT, cur_sel, (LPARAM)dir);

            if (strcmp (dir, ".") == 0)
                return;

            if (strcmp (dir, "..") == 0) {
                char* slash;

                if (strcmp (cwd, "/") == 0)
                    return;

                slash = strrchr (cwd, '/');
                if (slash == NULL)
                    return;
                if (slash == cwd)
                    strcpy (cwd, "/");
                else
                    *slash = '\0';
            }
            else {
                if (strcmp (cwd, "/") != 0)
                    strcat (cwd, "/");
                strcat (cwd, dir);
            }

            fill_boxes (GetParent (hwnd), cwd);
        }
    }
}

static void file_notif_proc (HWND hwnd, int id, int nc, DWORD add_data)
{
	if (nc == LBN_DBLCLK || nc == LBN_ENTER) {
		int cur_sel = SendMessage (hwnd, LB_GETCURSEL, 0, 0L);
		char file[1024];
        	if (cur_sel >= 0) {
			SendMessage (hwnd, LB_GETTEXT, cur_sel, (LPARAM)file);
		}
		//MessageBox (hwnd, file, looking_files_, MB_OK | MB_ICONINFORMATION);
		strcpy(choose_file,file);
		DlgBoxInputChar.controls = CtrlInputChar;
		DialogBoxIndirectParam (&DlgBoxInputChar, hwnd, InputCharDialogBoxProc, 0L);
	}
}

static void prompt (HWND hDlg)
{
    int i;
    char files [1024] = "The files followed will be looked\n";

    for (i = 0; i < SendDlgItemMessage (hDlg, IDL_FILE, LB_GETCOUNT, 0, 0L); i++) {
	char file [MAX_NAME + 1];
        int status = SendDlgItemMessage (hDlg, IDL_FILE, LB_GETCHECKMARK, i, 0);
        if (status == CMFLAG_CHECKED) {
            SendDlgItemMessage (hDlg, IDL_FILE, LB_GETTEXT, i, (LPARAM)file);
	    strcat (files, file);
	    strcat (files, "\n");
	    strcpy(choose_file,file);
	}
    }
	
    MessageBox (hDlg, files, looking_files_, MB_OK | MB_ICONINFORMATION);

}

int DelFilesBoxProc (HWND hDlg, int message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case MSG_INITDIALOG:
    {
        char cwd [MAX_PATH + 1];
        SetNotificationCallback (GetDlgItem (hDlg, IDL_DIR), dir_notif_proc);
        SetNotificationCallback (GetDlgItem (hDlg, IDL_FILE), file_notif_proc);
        fill_boxes (hDlg, getcwd (cwd, MAX_PATH));
        return 1;
    }
        
    case MSG_COMMAND:
        switch (wParam) {
        case IDOK:
            prompt (hDlg);
	    DlgBoxInputChar.controls = CtrlInputChar;
	    DialogBoxIndirectParam (&DlgBoxInputChar, hDlg, InputCharDialogBoxProc, 0L);
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

