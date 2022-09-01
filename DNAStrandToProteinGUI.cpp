// Project:     DNAStrandToProteinGUI
// Author:      Carlos Rodriguez
// Date:        8/31/2022
// Purpose:     Take in DNA strand txt file translate it to tRNA
//              translate tRNA to proteins

#include "framework.h"
#include "DNAStrandToProteinGUI.h"


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

TCHAR szInput[TCHAR_SIZE];
TCHAR szOutput[TCHAR_SIZE];
char cInputPath[MAX_PATH];					    // input file path, selected by user
char cOutputPath[MAX_PATH];					    // output file path, selected by user
TCHAR szInFName[MAX_PATH];	    				// input file name, selected by user
TCHAR szOutFName[MAX_PATH]; 					// output file name, selected by user
Translate trans;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

HWND hWnd_btnSubmit;                            // submit button
HWND hWnd_btnSelectInput;                       // open windows explorer
HWND hWnd_btnSelectOutput;                      // select an output file
HWND hWnd_txtData;                              // txt box to input data title
HWND hWnd_txtOutput;                            // txt box to name output data
bool GetOpenFileName();							// prompt for read filespec using common open dialog box
bool GetSaveFileName();                         // prompt for read filespec using common open dialog box

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DNASTRANDTOPROTEINGUI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DNASTRANDTOPROTEINGUI));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DNASTRANDTOPROTEINGUI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+0);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_DNASTRANDTOPROTEINGUI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 600, 300, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case BN_CLICKED:
                if (LOWORD(lParam) == (WORD)hWnd_btnSelectOutput)
                {
                    if (GetSaveFileName())
                    {
                        SendMessage(                        // message to window
                            hWnd_txtOutput,                 // filename label
                            WM_SETTEXT,                     // set the label's text
                            NULL,                           // wParam not used
                            LPARAM(szOutFName));            // filename only
                    }
                }
                if (LOWORD(lParam) == (WORD)hWnd_btnSelectInput)
                {
                    if (GetOpenFileName())
                    {
                        SendMessage(                       // message to window
                            hWnd_txtData,                  // filename label
                            WM_SETTEXT,                    // set the label's text
                            NULL,                          // wParam not used
                            LPARAM(szInFName));            // filename only
                    }
                    
                }
                if (LOWORD(lParam) == (WORD)hWnd_btnSubmit)
                {
                    GetWindowText(hWnd_txtData, szInput, TCHAR_SIZE);
                    GetWindowText(hWnd_txtOutput, szOutput, TCHAR_SIZE);
                    trans.readFile(cInputPath);
                    trans.toTrna();
                    trans.toProtein();
                    trans.outputFile(cOutputPath);
                }
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            RECT rClient;
            int cx, cy;                         // hold client x and y
            GetClientRect(                      // get client rectangle size
                hWnd, &rClient);
            cx = rClient.right - rClient.left;  // capture rectangle width
            cy = rClient.bottom - rClient.top;  // capture rectangle heigth

            // load the background butmap recourse
            HDC hmemdc = CreateCompatibleDC(hdc);       // memory do ( copy of hdc)
            HBITMAP hBitmap1;                           // handle to bitmaps
            BITMAP bitmap;                              // bitmap

            hBitmap1 =                                  // returns a handle to the bitmap
                (HBITMAP)LoadImage(                     // load image function
                    hInst,                              // the program that contains the resource
                    MAKEINTRESOURCE(IDB_BITMAP1),       // match the id number with the rescource
                    IMAGE_BITMAP,                       // type of resource
                    0,                                  // x coordinate // usually 0 , 0 can
                    0,                                  // y coordinate //    be offset
                    NULL);                              // special load instuction

            SelectObject(hmemdc, hBitmap1);             // points the memory do to the bitmap handle
            GetObject(hBitmap1, sizeof(BITMAP), &bitmap); // copies resource into bitmap

            // stretch background bitmap into window
            StretchBlt(
                hdc,                            // handle to the destination do
                0,                              // x of the upper left corner of the destination
                0,                              // y of the upper left corner of the destintaion
                rClient.right,                  // width of the client rectangle
                rClient.bottom,                 // heigth of the client rectangle
                hmemdc,                         // handle to the memory do
                0,                              // x of the upper left corner of the bitmap
                0,                              // y of the upper left corner of the bitmap
                bitmap.bmWidth,                 // width of the bitmap
                bitmap.bmHeight,                // heigth of the bitmap
                SRCCOPY);                       // perform a copy

            // clean up
            DeleteObject(hBitmap1);             // delete the handle to the first bitmap
            DeleteDC(hmemdc);                   // delet the memory dc

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_CREATE:
        hWnd_btnSubmit = CreateWindow(          // submit button
            TEXT("BUTTON"),
            TEXT("Translate"),
            WS_CHILD | WS_VISIBLE | WS_BORDER | BS_DEFPUSHBUTTON,
            260, 190, 80, 40,
            hWnd, NULL, NULL, NULL);           

        CreateWindow(                           // label for input file
            TEXT("STATIC"),
            TEXT("Input File Name"),
            WS_CHILD | WS_VISIBLE,
            5, 10, 120, 20,
            hWnd, NULL, NULL, NULL);

        hWnd_txtData = CreateWindow(            // data txt file box
            TEXT("EDIT"),
            TEXT("file.txt"),
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            5, 35, 250, 30,
            hWnd, NULL, NULL, NULL);

        hWnd_btnSelectInput = CreateWindow(      // search for file to use as input  
            TEXT("BUTTON"),
            TEXT("Select File"),
            WS_CHILD | WS_VISIBLE | WS_BORDER | BS_DEFPUSHBUTTON,
            150, 70, 100, 30,
            hWnd, NULL, NULL, NULL);

        hWnd_btnSelectOutput = CreateWindow(      // search for file to use as output  
            TEXT("BUTTON"),
            TEXT("Select File"),
            WS_CHILD | WS_VISIBLE | WS_BORDER | BS_DEFPUSHBUTTON,
            150, 145, 100, 30,
            hWnd, NULL, NULL, NULL);

        CreateWindow(                           // label for output file
            TEXT("STATIC"),
            TEXT("Output File Name"),
            WS_CHILD | WS_VISIBLE,
            5, 85, 120, 20,
            hWnd, NULL, NULL, NULL);

        hWnd_txtOutput = CreateWindow(          // txt box for output file name
            TEXT("EDIT"),
            TEXT("Output.txt"),
            WS_CHILD | WS_VISIBLE | WS_BORDER,
            5, 110, 250, 30,
            hWnd, NULL, NULL, NULL);


        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

// use common file open dialog box to get input filespec
bool GetOpenFileName()
{
    OPENFILENAME ofn;                                   // struct for GetOpenFileNameA()
    char czFile[MAX_PATH];                              // local copy of input file name

    // set up OPENFILENAME struct
    ZeroMemory(&cInputPath, sizeof(cInputPath));        // empty (global) path variable
    ZeroMemory(&ofn, sizeof(ofn));                      // empty struct
    ofn.lStructSize = sizeof(ofn);                      // set size of struct
    ofn.hwndOwner = NULL;                               // set owner window to null
    ofn.lpstrFilter = LPWSTR("Any File\0*.*\0");        // set filename filter
    ofn.lpstrFile = LPWSTR(cInputPath);                 // point to (global) path variable
    ofn.nMaxFile = MAX_PATH;                            // set max size of path
    ofn.lpstrFileTitle = LPWSTR(czFile);                // point to (local) filename
    ofn.nMaxFileTitle = MAX_PATH;                       // set max size of filename
    ofn.lpstrTitle = LPWSTR("Select an input File");    // set title text of dialog box
    ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST; // set flags

    // display dialog box
    if (GetOpenFileNameA(LPOPENFILENAMEA(&ofn)))        // TRUE if user selected an input file
    {
        // convert (global) filename to TCHAR for future display
        size_t pReturnValue;
        mbstowcs_s(&pReturnValue, szInFName, MAX_LOADSTRING, czFile, MAX_LOADSTRING);
        // cInputPath cannot be converted to TCHAR because of \ in file path

        return true;                                    // user selected a file
    }
    else
        return false;                                   // user cancelled selection
}

// use common save file dialog box to get output filespec
bool GetSaveFileName()
{
    OPENFILENAME ofn;                                   // struct for GetOpenFileNameA()
    char czFile[MAX_PATH];                              // local copy of input file name

    // set up OPENFILENAME struct
    ZeroMemory(&cOutputPath, sizeof(cOutputPath));      // empty (global) path variable
    ZeroMemory(&ofn, sizeof(ofn));                      // empty struct
    ofn.lStructSize = sizeof(ofn);                      // set size of struct
    ofn.hwndOwner = NULL;                               // set owner window to null
    ofn.lpstrFilter = LPWSTR("Any File\0*.*\0");        // set filename filter
    ofn.lpstrFile = LPWSTR(cOutputPath);                // point to (global) path variable
    ofn.nMaxFile = MAX_PATH;                            // set max size of path
    ofn.lpstrFileTitle = LPWSTR(czFile);                // point to (local) filename
    ofn.nMaxFileTitle = MAX_PATH;                       // set max size of filename
    ofn.lpstrTitle = LPWSTR("Select an output File");   // set title text of dialog box
    ofn.Flags = OFN_DONTADDTORECENT | OFN_OVERWRITEPROMPT; // set flags

    if (GetSaveFileNameA(LPOPENFILENAMEA(&ofn))) // user selected an output file
    {
        // convert file name to TCHAR for future display
        size_t pReturnValue;
        mbstowcs_s(&pReturnValue, szOutFName, MAX_LOADSTRING, czFile, MAX_LOADSTRING);
        // cOutputPath  cannot be converted to TCHAR because of \ in file path

        return true;
    }
    else
        return false;
}