
//  gcc -O2 -o draw draw.c -lgdi32 -lm -mwindows
// just a preface... this file isnt apart of the project.. 
// it was just to have an interactive part for a basic visualization
// most of this was written by AI so I could focus more on the NN part
// again.. this file IS NOT apart of the project :)

#ifndef UNICODE
#define UNICODE
#endif

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// same as nn.c
#define INPUT   784
#define HIDDEN  128
#define OUTPUT  10

// canvas dimenstions
#define GRID        28
#define CELL        10
#define CANVAS      280
#define MARGIN      20
#define PANEL_X     (MARGIN + CANVAS + 30)
#define WIN_W       560
#define WIN_H       (MARGIN + CANVAS + 60)
#define BTN_GUESS   1001
#define BTN_CLEAR   1002

// NN weights and bias
static double W1[HIDDEN][INPUT];
static double b1[HIDDEN];
static double W2[OUTPUT][HIDDEN];
static double b2[OUTPUT];
static double canvas[GRID][GRID];

// results
static int    predicted_digit = -1;
static double confidence = 0.0;
static double all_probs[OUTPUT];

static int weights_loaded = 0;
static int left_down = 0;
static int right_down = 0;

// this loads the weights from the nn.c file 
// so the window we load will have a properly trained NN
static int load_weights(void) {
    FILE *f = fopen("weights.bin", "rb");
    if (!f) return 0;
    size_t r = 0;
    r += fread(W1, sizeof(double), HIDDEN * INPUT, f);
    r += fread(b1, sizeof(double), HIDDEN, f);
    r += fread(W2, sizeof(double), OUTPUT * HIDDEN, f);
    r += fread(b2, sizeof(double), OUTPUT, f);
    fclose(f);
    size_t expected = (size_t)(HIDDEN * INPUT + HIDDEN + OUTPUT * HIDDEN + OUTPUT);
    return (r == expected) ? 1 : 0;
}

// forward/back pass.. the same as nn.c but we condense it here
// because we are not actually training the model again
static void classify(void) {
    double input[INPUT];
    for (int r = 0; r < GRID; r++)
        for (int c = 0; c < GRID; c++)
            input[r * GRID + c] = canvas[r][c];

    double a1[HIDDEN];
    for (int i = 0; i < HIDDEN; i++) {
        double z = b1[i];
        for (int j = 0; j < INPUT; j++)
            z += W1[i][j] * input[j];
        a1[i] = z > 0.0 ? z : 0.0;
    }

    double z2[OUTPUT];
    double max_z = -1e30;
    for (int i = 0; i < OUTPUT; i++) {
        z2[i] = b2[i];
        for (int j = 0; j < HIDDEN; j++)
            z2[i] += W2[i][j] * a1[j];
        if (z2[i] > max_z) max_z = z2[i];
    }

    double sum = 0.0;
    for (int i = 0; i < OUTPUT; i++) {
        all_probs[i] = exp(z2[i] - max_z);
        sum += all_probs[i];
    }
    for (int i = 0; i < OUTPUT; i++)
        all_probs[i] /= sum;

    predicted_digit = 0;
    confidence = all_probs[0];
    for (int i = 1; i < OUTPUT; i++) {
        if (all_probs[i] > confidence) {
            confidence = all_probs[i];
            predicted_digit = i;
        }
    }
}

// brush dynamics
static void paint_at(int gx, int gy, int erase) {
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            int nx = gx + dx, ny = gy + dy;
            if (nx >= 0 && nx < GRID && ny >= 0 && ny < GRID) {
                if (erase) {
                    canvas[ny][nx] = 0.0;
                } else {
                    double dist = sqrt((double)(dx * dx + dy * dy));
                    double str = 1.0 - dist / 2.0;
                    if (str > 0.0 && canvas[ny][nx] < str)
                        canvas[ny][nx] = str;
                }
            }
        }
    }
}

static void clear_canvas(void) {
    memset(canvas, 0, sizeof(canvas));
    predicted_digit = -1;
    confidence = 0.0;
    memset(all_probs, 0, sizeof(all_probs));
}

// gets the location of the mouse (x and y coords)
// so we can accurately draw on the canvas
static void handle_mouse(HWND hwnd, int sx, int sy, int erase) {
    int gx = (sx - MARGIN) / CELL;
    int gy = (sy - MARGIN) / CELL;
    if (gx >= 0 && gx < GRID && gy >= 0 && gy < GRID) {
        paint_at(gx, gy, erase);
        InvalidateRect(hwnd, NULL, FALSE);
    }
}

// so now that we have a brush.. we need the paint too if we want to draw something
static void paint_window(HWND hwnd) {
    PAINTSTRUCT ps;
    HDC hdc_screen = BeginPaint(hwnd, &ps);
    HDC hdc = CreateCompatibleDC(hdc_screen);
    HBITMAP bmp = CreateCompatibleBitmap(hdc_screen, WIN_W, WIN_H);
    HBITMAP old_bmp = (HBITMAP)SelectObject(hdc, bmp);

    // clear background
    HBRUSH bg_brush = CreateSolidBrush(RGB(245, 245, 245));
    RECT full = {0, 0, WIN_W, WIN_H};
    FillRect(hdc, &full, bg_brush);
    DeleteObject(bg_brush);

    // the actual 28x28 canvas
    for (int r = 0; r < GRID; r++) {
        for (int c = 0; c < GRID; c++) {
            int v = (int)(canvas[r][c] * 255.0);
            if (v > 255) v = 255;
            HBRUSH cell_brush = CreateSolidBrush(RGB(v, v, v));
            RECT cell;
            cell.left   = MARGIN + c * CELL;
            cell.top    = MARGIN + r * CELL;
            cell.right  = cell.left + CELL;
            cell.bottom = cell.top + CELL;
            FillRect(hdc, &cell, cell_brush);
            DeleteObject(cell_brush);
        }
    }

    // border around canvas
    HPEN border_pen = CreatePen(PS_SOLID, 1, RGB(120, 120, 120));
    HPEN old_pen = (HPEN)SelectObject(hdc, border_pen);
    HBRUSH null_brush = (HBRUSH)GetStockObject(NULL_BRUSH);
    HBRUSH old_brush_sel = (HBRUSH)SelectObject(hdc, null_brush);
    Rectangle(hdc, MARGIN - 1, MARGIN - 1, MARGIN + CANVAS + 1, MARGIN + CANVAS + 1);
    SelectObject(hdc, old_pen);
    SelectObject(hdc, old_brush_sel);
    DeleteObject(border_pen);

    // right panel with the instructions and results
    int px = PANEL_X;
    SetBkMode(hdc, TRANSPARENT);

    // "creats fonts"
    HFONT title_font = CreateFontW(16, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, CLEARTYPE_QUALITY, 0, L"Segoe UI");
    HFONT normal_font = CreateFontW(14, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0, CLEARTYPE_QUALITY, 0, L"Segoe UI");
    HFONT big_font = CreateFontW(64, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, 0, 0, CLEARTYPE_QUALITY, 0, L"Segoe UI");

    // all the text on the panel
    SelectObject(hdc, title_font);
    SetTextColor(hdc, RGB(50, 50, 50));
    TextOutW(hdc, px, MARGIN, L"Draw a digit!", 13);

    SelectObject(hdc, normal_font);
    SetTextColor(hdc, RGB(120, 120, 120));
    TextOutW(hdc, px, MARGIN + 24, L"Left drag  = draw", 17);
    TextOutW(hdc, px, MARGIN + 42, L"Right drag = erase", 18);
    TextOutW(hdc, px, MARGIN + 60, L"G = guess   C = clear", 21);
    TextOutW(hdc, px, MARGIN + 78, L"Q = quit", 8);

    if (!weights_loaded) {
        SelectObject(hdc, title_font);
        SetTextColor(hdc, RGB(200, 40, 40));
        TextOutW(hdc, px, MARGIN + 110, L"weights.bin not found!", 22);
        SelectObject(hdc, normal_font);
        SetTextColor(hdc, RGB(50, 50, 50));
        TextOutW(hdc, px, MARGIN + 132, L"Run nn.exe first to train.", 26);
    }
    else if (predicted_digit >= 0) {
        wchar_t buf[64];

        // how "confident" the model is in its guess.. 
        SelectObject(hdc, normal_font);
        SetTextColor(hdc, RGB(50, 50, 50));
        wsprintfW(buf, L"Confidence: %d%%", (int)(confidence * 100.0));
        TextOutW(hdc, px, MARGIN + 300, buf, (int)wcslen(buf));

        // loads the probability bars
        int bar_top = MARGIN + 100;
        int bar_max = 120;

        for (int i = 0; i < OUTPUT; i++) {
            int y = bar_top + i * 17;
            int bar_w = (int)(all_probs[i] * bar_max);
            if (bar_w < 1 && all_probs[i] > 0.001) bar_w = 1;
            int pct = (int)(all_probs[i] * 100.0);

            wsprintfW(buf, L"%d", i);
            SetTextColor(hdc, (i == predicted_digit) ? RGB(30, 110, 210) : RGB(50, 50, 50));
            TextOutW(hdc, px, y, buf, 1);

            HBRUSH bg_bar = CreateSolidBrush(RGB(220, 220, 220));
            RECT bg_rect = {px + 16, y + 2, px + 16 + bar_max, y + 15};
            FillRect(hdc, &bg_rect, bg_bar);
            DeleteObject(bg_bar);

            COLORREF bar_col = (i == predicted_digit) ? RGB(30, 110, 210) : RGB(170, 170, 170);
            HBRUSH fill_bar = CreateSolidBrush(bar_col);
            RECT fill_rect = {px + 16, y + 2, px + 16 + bar_w, y + 15};
            FillRect(hdc, &fill_rect, fill_bar);
            DeleteObject(fill_bar);

            SetTextColor(hdc, RGB(50, 50, 50));
            wsprintfW(buf, L"%d%%", pct);
            TextOutW(hdc, px + 16 + bar_max + 6, y, buf, (int)wcslen(buf));
        }
    }

    BitBlt(hdc_screen, 0, 0, WIN_W, WIN_H, hdc, 0, 0, SRCCOPY);

    // general cleanups
    SelectObject(hdc, old_bmp);
    DeleteObject(bmp);
    DeleteDC(hdc);
    DeleteObject(title_font);
    DeleteObject(normal_font);
    DeleteObject(big_font);

    EndPaint(hwnd, &ps);
}

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {

    case WM_LBUTTONDOWN:
        left_down = 1;
        SetCapture(hwnd);  /* keep getting mouse events even outside window */
        handle_mouse(hwnd, LOWORD(lParam), HIWORD(lParam), 0);
        return 0;

    case WM_RBUTTONDOWN:
        right_down = 1;
        SetCapture(hwnd);
        handle_mouse(hwnd, LOWORD(lParam), HIWORD(lParam), 1);
        return 0;

    // if the mouse moves, and button is pressed.. then paint
    case WM_MOUSEMOVE:
        if (left_down)
            handle_mouse(hwnd, LOWORD(lParam), HIWORD(lParam), 0);
        else if (right_down)
            handle_mouse(hwnd, LOWORD(lParam), HIWORD(lParam), 1);
        return 0;

    // and yes... we actually have to define mouse clicks..
    case WM_LBUTTONUP:
        left_down = 0;
        ReleaseCapture();
        return 0;

    case WM_RBUTTONUP:
        right_down = 0;
        ReleaseCapture();
        return 0;

    // the three commands that we need "guess", "clear", and "quit"
    case WM_CHAR:
        if (wParam == 'g' || wParam == 'G') {
            if (weights_loaded) {
                classify();
                InvalidateRect(hwnd, NULL, FALSE);
            }
        }
        else if (wParam == 'c' || wParam == 'C') {
            clear_canvas();
            InvalidateRect(hwnd, NULL, FALSE);
        }
        else if (wParam == 'q' || wParam == 'Q' || wParam == 27) {
            DestroyWindow(hwnd);
        }
        return 0;

    // lays the paint
    case WM_PAINT:
        paint_window(hwnd);
        return 0;

    // stops annoying flickering when drawing
    case WM_ERASEBKGND:
        return 1;  // tells the program to shut up and we will handle erasing it later

    // close the window
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

// this is the main function that you normally see in a C program
// but on windows with the Win32 API, the entry point is WinMain instead of main
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    (void)hPrevInstance;
    (void)lpCmdLine;

    // loads the trained weights from nn.c and weights.bin
    weights_loaded = load_weights();

    // starts the canvas off as blank (all black zero values)
    clear_canvas();

    // make window class
    WNDCLASSW wc = {0};
    wc.lpfnWndProc   = WndProc;
    wc.hInstance      = hInstance;
    wc.hCursor        = LoadCursor(NULL, IDC_CROSS);
    wc.hbrBackground  = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName  = L"NNDraw";
    RegisterClassW(&wc);

    RECT rc = {0, 0, WIN_W, WIN_H};
    AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, FALSE);

    // creates the window
    HWND hwnd = CreateWindowW(
        L"NNDraw",
        L"MNIST Digit Recognizer",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,  // cant resize it!! otherwise the pixel calculations get messed up :(
        CW_USEDEFAULT, CW_USEDEFAULT,
        rc.right - rc.left, rc.bottom - rc.top,
        NULL, NULL, hInstance, NULL
    );

    if (!hwnd) return 1;

    // actually loads the window lol :)
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}