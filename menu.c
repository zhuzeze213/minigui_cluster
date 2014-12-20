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
	char *msg[] = {"Import algorithm","Import data","Evaluation result","Source code","Output data","fresh","Property"};
	memset (&mii, 0, sizeof(MENUITEMINFO));
	mii.type = MFT_STRING;
	mii.id = 0;
	mii.typedata = (DWORD)"right_button";
	hNewMenu = CreatePopupMenu (&mii);
	for ( i = 0; i <NUM_RIGHT_BUTTON; i ++ ) {
		memset ( &mii, 0, sizeof (MENUITEMINFO) );
		mii.type = MFT_STRING;
		mii.id = IDM_RIGHT_BUTTON+ i;
		mii.state = 0;
		mii.typedata= (DWORD) msg[i];
		InsertMenuItem ( hNewMenu, i, TRUE, &mii );
	}
	hMenuFloat = StripPopupHead(hNewMenu);
	TrackPopupMenu (hMenuFloat, TPM_CENTERALIGN | TPM_LEFTBUTTON ,x,y, hWnd);

}
 
static HMENU optimization_menu(void)
{
	HMENU hmnu;
	MENUITEMINFO mii;
	memset (&mii, 0, sizeof(MENUITEMINFO));
	mii.type = MFT_STRING;
	mii.id = IDM_OPTIMIZATION;
	mii.typedata =(DWORD)"Optimization";
	hmnu = CreatePopupMenu (&mii);

	mii.type = MFT_STRING;
	mii.state = 0;
	mii.id = IDM_KERNIGHAN_LIN;
	mii.typedata = (DWORD)"kernighan-lin";
	InsertMenuItem(hmnu, 0, TRUE, &mii);

    mii.type = MFT_STRING;
    mii.state = 0;
    mii.id = IDM_FAST_NEWMAN;
    mii.typedata = (DWORD)"fast-newman";
    InsertMenuItem(hmnu, 1, TRUE, &mii);

    mii.type = MFT_STRING;
    mii.state = 0;
    mii.id = IDM_FAST_MODULARITY;
    mii.typedata = (DWORD)"fast-modularity";
    InsertMenuItem(hmnu, 2, TRUE, &mii);

    mii.type = MFT_STRING;
    mii.state = 0;
    mii.id = IDM_GUIMERA_AMARAL;
    mii.typedata = (DWORD)"guimera-amaral";
    InsertMenuItem(hmnu, 3, TRUE, &mii);

	
	mii.type = MFT_SEPARATOR;
	mii.state = 0;
	mii.id = 0;
	mii.typedata = 0;
	InsertMenuItem(hmnu, 4, TRUE, &mii);
	
	mii.type = MFT_STRING;
    mii.state = 0;
    mii.id = IDM_CM;
    mii.typedata = (DWORD)"cm";
    InsertMenuItem(hmnu, 5, TRUE, &mii);
	
	mii.type = MFT_STRING;
    mii.state = 0;
    mii.id = IDM_SA;
    mii.typedata = (DWORD)"sa";
    InsertMenuItem(hmnu, 6, TRUE, &mii);	
	
	return hmnu;
}

static HMENU heuristic_menu(void)
{
        HMENU hmnu;
        MENUITEMINFO mii;
        memset (&mii, 0, sizeof(MENUITEMINFO));
        mii.type = MFT_STRING;
        mii.id = IDM_HEURISTIC;
        mii.typedata =(DWORD)"Heuristic";
        hmnu = CreatePopupMenu (&mii);

        mii.type = MFT_STRING;
        mii.state = 0;
        mii.id = IDM_MFC;
        mii.typedata = (DWORD)"mfc";
        InsertMenuItem(hmnu, 0, TRUE, &mii);

        mii.type = MFT_STRING;
        mii.state = 0;
        mii.id = IDM_GIRVAN_NEWMAN;
        mii.typedata = (DWORD)"girvan-newman";
        InsertMenuItem(hmnu, 1, TRUE, &mii);

        mii.type = MFT_STRING;
        mii.state = 0;
        mii.id = IDM_FEC;
        mii.typedata = (DWORD)"fec";
        InsertMenuItem(hmnu, 2, TRUE, &mii);

        mii.type = MFT_STRING;
        mii.state = 0;
        mii.id = IDM_CPM;
        mii.typedata = (DWORD)"cpm";
        InsertMenuItem(hmnu, 3, TRUE, &mii);
		
		mii.type = MFT_STRING;
        mii.state = 0;
        mii.id = IDM_FCM;
        mii.typedata = (DWORD)"fcm";
        InsertMenuItem(hmnu, 4, TRUE, &mii);

	return hmnu;
}

static HMENU others_menu(void)
{
        HMENU hmnu;
        MENUITEMINFO mii;
        memset (&mii, 0, sizeof(MENUITEMINFO));
        mii.type = MFT_STRING;
        mii.id = IDM_OTHERS;
        mii.typedata =(DWORD)"Others";
        hmnu = CreatePopupMenu (&mii);

        mii.type = MFT_STRING;
        mii.state = 0;
        mii.id = IDM_INFOMAP;
        mii.typedata = (DWORD)"infomap";
        InsertMenuItem(hmnu, 0, TRUE, &mii);

        mii.type = MFT_STRING;
        mii.state = 0;
        mii.id = IDM_WALKTRAP;
        mii.typedata = (DWORD)"walktrap";
        InsertMenuItem(hmnu, 1, TRUE, &mii);

        mii.type = MFT_STRING;
        mii.state = 0;
        mii.id = IDM_HALL;
        mii.typedata = (DWORD)"hall";
        InsertMenuItem(hmnu, 2, TRUE, &mii);

	return hmnu;
}

static HMENU networks_menu(void)
{
        HMENU hmnu;
        MENUITEMINFO mii;
        memset (&mii, 0, sizeof(MENUITEMINFO));
        mii.type = MFT_STRING;
        mii.id = IDM_NETWORKS;
        mii.typedata =(DWORD)"networks";
        hmnu = CreatePopupMenu (&mii);

        mii.type = MFT_STRING;
        mii.state = 0;
        mii.id = IDM_KARATE;
        mii.typedata = (DWORD)"karate";
        InsertMenuItem(hmnu, 0, TRUE, &mii);

        mii.type = MFT_STRING;
        mii.state = 0;
        mii.id = IDM_DOLPHINS;
        mii.typedata = (DWORD)"dolphins";
        InsertMenuItem(hmnu, 1, TRUE, &mii);

        mii.type = MFT_STRING;
        mii.state = 0;
        mii.id = IDM_FOOTBALL;
        mii.typedata = (DWORD)"football";
        InsertMenuItem(hmnu, 2, TRUE, &mii);

        mii.type = MFT_STRING;
        mii.state = 0;
        mii.id = IDM_ADJNOUN;
        mii.typedata = (DWORD)"adjnoun";
        InsertMenuItem(hmnu, 3, TRUE, &mii);
		
	mii.type = MFT_STRING;
        mii.state = 0;
        mii.id = IDM_LESMIS;
        mii.typedata = (DWORD)"lesmis";
        InsertMenuItem(hmnu, 4, TRUE, &mii);

	mii.type = MFT_STRING;
        mii.state = 0;
        mii.id = IDM_JAZZ;
        mii.typedata = (DWORD)"jazz";
        InsertMenuItem(hmnu, 5, TRUE, &mii);

	mii.type = MFT_SEPARATOR;
	mii.state = 0;
	mii.id = 0;
	mii.typedata = 0;
	InsertMenuItem(hmnu, 6, TRUE, &mii);

	mii.type = MFT_STRING;
        mii.state = 0;
        mii.id = IDM_GENERATED_NETWORKS;
        mii.typedata = (DWORD)"generated networks";
        InsertMenuItem(hmnu, 7, TRUE, &mii);

	mii.type = MFT_STRING;
        mii.state = 0;
        mii.id = IDM_MY_NETWORKS;
        mii.typedata = (DWORD)"my networks";
        InsertMenuItem(hmnu, 8, TRUE, &mii);
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
	mii.typedata =(DWORD)"Optimization";
	mii.hsubmenu =optimization_menu();
	InsertMenuItem(hmnu, 0, TRUE, &mii);

        mii.type = MFT_STRING;
        mii.id = IDM_2;
        mii.typedata =(DWORD)"Heuristic";
        mii.hsubmenu =heuristic_menu();
        InsertMenuItem(hmnu, 1, TRUE, &mii);

        mii.type = MFT_STRING;
        mii.id = IDM_3;
        mii.typedata =(DWORD)"Others";
        mii.hsubmenu =others_menu();
        InsertMenuItem(hmnu, 2, TRUE, &mii);

        mii.type = MFT_STRING;
        mii.id = IDM_4;
        mii.typedata =(DWORD)"Networks";
        mii.hsubmenu =networks_menu();
        InsertMenuItem(hmnu, 3, TRUE, &mii);

	return hmnu;
}
