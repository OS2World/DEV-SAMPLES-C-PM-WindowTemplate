#define INCL_WIN
#define INCL_GPI
#include <os2.h>
#include <string.h>
#include <stdlib.h>
#include <smslib.h>
#include <stdio.h>

#define ID_DLG   10
#define ID_FRAME 11
#define ID_MENU  12

MRESULT EXPENTRY ClientWinProc (HWND hwnd, USHORT msg, MPARAM mp1, MPARAM mp2);

HAB   hab;
CHAR  bug_buf[100];

USHORT cdecl main(void)
{
    HMQ   hmq;
    QMSG  qmsg;
    HWND  hwnd;

    static CHAR szClientClass[] = "Client Window";

    hab = WinInitialize(0);
    hmq = WinCreateMsgQueue(hab, 0);

    WinRegisterClass((HAB)hab, (PSZ)szClientClass, (PFNWP)ClientWinProc,
                      CS_SIZEREDRAW | CS_PARENTCLIP | CS_CLIPSIBLINGS, 0);

    hwnd = WinLoadDlg(HWND_DESKTOP, HWND_DESKTOP, NULL, NULL, ID_DLG, NULL);

    while (WinGetMsg(hab, &qmsg, NULL, 0, 0))
         WinDispatchMsg(hab, &qmsg);

    WinDestroyWindow(hwnd);
    WinDestroyMsgQueue(hmq);
    WinTerminate(hab);

    return 0;

}

MRESULT EXPENTRY ClientWinProc (HWND hwnd, USHORT msg, MPARAM mp1, MPARAM mp2)
{
      HWND hwndSMS;
      HWND hwndMenu;

      switch  (msg)
      {

          case WM_CREATE:
              WinPostMsg(hwnd, WM_USER+1,0L,0L);
              return(WinDefWindowProc(hwnd, msg, mp1, mp2));
              break;
          case WM_USER+1:
            hwndSMS=WinQueryWindow(hwnd, QW_PARENT,FALSE);
            hwndMenu=WinLoadMenu(hwndSMS,NULL,ID_MENU);
            WinSendMsg(hwndSMS, WM_UPDATEFRAME, (ULONG)FCF_MENU, NULL);
            WinSetWindowPos(hwndSMS,HWND_TOP,50,50,150,150,SWP_MOVE|SWP_SHOW|SWP_SIZE|SWP_ACTIVATE);
            break;
          case WM_ERASEBACKGROUND:
            return ((MRESULT)TRUE);
            break;
          default:
             return(WinDefWindowProc(hwnd, msg, mp1, mp2));
             break;
    }
    return (MRESULT)NULL;
}
