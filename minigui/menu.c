#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<minigui/common.h>
#include<minigui/minigui.h>
#include<minigui/gdi.h>
#include<minigui/window.h>
#include<minigui/control.h>

#include"menu.h"

HMENU right_button_menu(HWND hWnd,int x,int y)
{
	int i;
	HMENU hNewMenu;
	MENUITEMINFO mii;
	HMENU hMenuFloat;
	char *msg[] = {"Import algorithm","Import data","Evaluation Result","Source Code","Output Data","Fresh","Property"};
	memset (&mii, 0, sizeof(MENUITEMINFO));
	mii.type = MFT_STRING;
	mii.id = 0;
	mii.typedata = (DWORD)"right_button";
	hNewMenu = CreatePopupMenu (&mii);
/*	for ( i = 0; i <NUM_RIGHT_BUTTON; i ++ ) {
		memset ( &mii, 0, sizeof (MENUITEMINFO) );
		mii.type = MFT_STRING;
		mii.id = IDM_RIGHT_BUTTON+ i;
		mii.state = 0;
		mii.typedata= (DWORD) msg[i];
		InsertMenuItem ( hNewMenu, i, TRUE, &mii );
	}
	*/
	memset ( &mii, 0, sizeof (MENUITEMINFO) );
	mii.type = MFT_STRING;
	mii.id = IDM_IMPORT_A;
	mii.state = 0;
	mii.typedata= (DWORD) msg[0];
	InsertMenuItem ( hNewMenu, 0, TRUE, &mii );
	
	memset ( &mii, 0, sizeof (MENUITEMINFO) );
	mii.type = MFT_STRING;
	mii.id = IDM_IMPORT_D;
	mii.state = 0;
	mii.typedata= (DWORD) msg[1];
	InsertMenuItem ( hNewMenu, 1, TRUE, &mii );
	
	memset ( &mii, 0, sizeof (MENUITEMINFO) );
	mii.type = MFT_STRING;
	mii.id = IDM_EVALUATE;
	mii.state = 0;
	mii.typedata= (DWORD) msg[2];
	InsertMenuItem ( hNewMenu, 2, TRUE, &mii );	
	
	memset ( &mii, 0, sizeof (MENUITEMINFO) );
	mii.type = MFT_STRING;
	mii.id = IDM_SOURCE_CODE;
	mii.state = 0;
	mii.typedata= (DWORD) msg[3];
	InsertMenuItem ( hNewMenu, 3, TRUE, &mii );

	memset ( &mii, 0, sizeof (MENUITEMINFO) );
	mii.type = MFT_STRING;
	mii.id = IDM_OUTPUT;
	mii.state = 0;
	mii.typedata= (DWORD) msg[4];
	InsertMenuItem ( hNewMenu, 4, TRUE, &mii );

	memset ( &mii, 0, sizeof (MENUITEMINFO) );
	mii.type = MFT_STRING;
	mii.id = IDM_FRESH;
	mii.state = 0;
	mii.typedata= (DWORD) msg[5];
	InsertMenuItem ( hNewMenu, 5, TRUE, &mii );

/*	memset ( &mii, 0, sizeof (MENUITEMINFO) );
	mii.type = MFT_STRING;
	mii.id = IDM_EVALUATE;
	mii.state = 0;
	mii.typedata= (DWORD) msg[6];
	InsertMenuItem ( hNewMenu, 6, TRUE, &mii );*/
	
	hMenuFloat = StripPopupHead(hNewMenu);
	TrackPopupMenu (hMenuFloat, TPM_CENTERALIGN | TPM_LEFTBUTTON ,x,y, hWnd);

}
 
static HMENU file_menu(void)
{
	HMENU hmnu;
	MENUITEMINFO mii;
	memset (&mii, 0, sizeof(MENUITEMINFO));
	mii.type = MFT_STRING;
	mii.id = IDM_FILE;
	mii.typedata =(DWORD)"FILE";
	hmnu = CreatePopupMenu (&mii);

	mii.type = MFT_STRING;
	mii.state = 0;
	mii.id = IDM_NEW;
	mii.typedata = (DWORD)"New";
	InsertMenuItem(hmnu, 0, TRUE, &mii);

    mii.type = MFT_STRING;
    mii.state = 0;
    mii.id = IDM_SAVE_RESULT;
    mii.typedata = (DWORD)"Save results";
    InsertMenuItem(hmnu, 1, TRUE, &mii);

	mii.type = MFT_SEPARATOR;
	mii.state = 0;
	mii.id = 0;
	mii.typedata = 0;
	InsertMenuItem(hmnu, 2, TRUE, &mii);
	
    mii.type = MFT_STRING;
    mii.state = 0;
    mii.id = IDM_OUTPUT;
    mii.typedata = (DWORD)"Output Data";
    InsertMenuItem(hmnu, 3, TRUE, &mii);

    mii.type = MFT_STRING;
    mii.state = 0;
    mii.id = IDM_SET_PATH;
    mii.typedata = (DWORD)"Set Save Path";
    InsertMenuItem(hmnu, 4, TRUE, &mii);

	
	mii.type = MFT_SEPARATOR;
	mii.state = 0;
	mii.id = 0;
	mii.typedata = 0;
	InsertMenuItem(hmnu, 5, TRUE, &mii);
	
	mii.type = MFT_STRING;
    mii.state = 0;
    mii.id = IDM_IMPORT_A;
    mii.typedata = (DWORD)"Import Algorithm";
    InsertMenuItem(hmnu, 6, TRUE, &mii);
	
	mii.type = MFT_STRING;
    mii.state = 0;
    mii.id = IDM_IMPORT_D;
    mii.typedata = (DWORD)"Import Data";
    InsertMenuItem(hmnu, 7, TRUE, &mii);	

	mii.type = MFT_SEPARATOR;
	mii.state = 0;
	mii.id = 0;
	mii.typedata = 0;
	InsertMenuItem(hmnu, 8, TRUE, &mii);	
	
	mii.type = MFT_STRING;
    mii.state = 0;
    mii.id = IDM_EXIT;
    mii.typedata = (DWORD)"Exit";
    InsertMenuItem(hmnu, 9, TRUE, &mii);	
	
	return hmnu;
}

static HMENU edit_menu(void)
{
        HMENU hmnu;
        MENUITEMINFO mii;
        memset (&mii, 0, sizeof(MENUITEMINFO));
        mii.type = MFT_STRING;
        mii.id = IDM_EDIT;
        mii.typedata =(DWORD)"EDIT";
        hmnu = CreatePopupMenu (&mii);

        mii.type = MFT_STRING;
        mii.state = 0;
        mii.id = IDM_SOURCE_CODE;
        mii.typedata = (DWORD)"Source Code";
        InsertMenuItem(hmnu, 0, TRUE, &mii);

        mii.type = MFT_STRING;
        mii.state = 0;
        mii.id = IDM_EVALUATE;
        mii.typedata = (DWORD)"Evaluate result";
        InsertMenuItem(hmnu, 1, TRUE, &mii);
		
		mii.type = MFT_SEPARATOR;
		mii.state = 0;
		mii.id = 0;
		mii.typedata = 0;
		InsertMenuItem(hmnu, 2, TRUE, &mii);
		
        mii.type = MFT_STRING;
        mii.state = 0;
        mii.id = IDM_FRESH;
        mii.typedata = (DWORD)"Fresh";
        InsertMenuItem(hmnu, 3, TRUE, &mii);

        mii.type = MFT_STRING;
        mii.state = 0;
        mii.id = IDM_CLEAR_W;
        mii.typedata = (DWORD)"Clear Window";
        InsertMenuItem(hmnu, 4, TRUE, &mii);
		
		mii.type = MFT_STRING;
        mii.state = 0;
        mii.id = IDM_CLEAR_F;
        mii.typedata = (DWORD)"Clear Tmpfile";
        InsertMenuItem(hmnu, 5, TRUE, &mii);

	return hmnu;
}

static HMENU help_menu(void)
{
        HMENU hmnu;
        MENUITEMINFO mii;
        memset (&mii, 0, sizeof(MENUITEMINFO));
        mii.type = MFT_STRING;
        mii.id = IDM_HELP;
        mii.typedata =(DWORD)"HELP";
        hmnu = CreatePopupMenu (&mii);

        mii.type = MFT_STRING;
        mii.state = 0;
        mii.id = IDM_HOW_TO;
        mii.typedata = (DWORD)"How To Use";
        InsertMenuItem(hmnu, 0, TRUE, &mii);

        mii.type = MFT_STRING;
        mii.state = 0;
        mii.id = IDM_ABOUT;
        mii.typedata = (DWORD)"About";
        InsertMenuItem(hmnu, 1, TRUE, &mii);


	return hmnu;
}

HMENU createmenu(void)
{
	HMENU hmnu;
	MENUITEMINFO mii;
	hmnu = CreateMenu();
	memset (&mii, 0, sizeof(MENUITEMINFO));
	mii.type = MFT_STRING;
	mii.id = IDM_1;
	mii.typedata =(DWORD)"FILE";
	mii.hsubmenu =file_menu();
	InsertMenuItem(hmnu, 0, TRUE, &mii);

    mii.type = MFT_STRING;
    mii.id = IDM_2;
    mii.typedata =(DWORD)"EDIT";
    mii.hsubmenu =edit_menu();
    InsertMenuItem(hmnu, 1, TRUE, &mii);

    mii.type = MFT_STRING;
    mii.id = IDM_3;
    mii.typedata =(DWORD)"HELP";
    mii.hsubmenu =help_menu();
    InsertMenuItem(hmnu, 2, TRUE, &mii);

	return hmnu;
}
