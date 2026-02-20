#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <wchar.h>
#include <string.h>
#include <stdio.h>
#include "mnist_math.h"
#include "model.h"

Model g_model;
float g_canvas[M_IN] = {0};
int g_prediction = -1;

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_MOUSEMOVE:
        if (wParam & MK_LBUTTON) {
            int x = LOWORD(lParam) / 20;
            int y = HIWORD(lParam) / 20;
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    int nx = x + dx, ny = y + dy;
                    if (nx >= 0 && nx < 28 && ny >= 0 && ny < 28) {
                        g_canvas[ny * 28 + nx] = 1.0f;
                    }
                }
            }

            // Run Prediction
            float z1[M_H], a1[M_H], z2[M_OUT], p[M_OUT];
            forward(&g_model, g_canvas, z1, a1, z2, p);
            g_prediction = argmax(p, M_OUT);

            InvalidateRect(hwnd, NULL, FALSE);
        }
        return 0;

    case WM_KEYDOWN:
        if (wParam == 'C') { // Press 'C' key to clear
            memset(g_canvas, 0, sizeof(g_canvas));
            g_prediction = -1;
            InvalidateRect(hwnd, NULL, TRUE);
        }
        return 0;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        
        // Draw the 28x28 grid
        for (int i = 0; i < M_IN; i++) {
            if (g_canvas[i] > 0.1f) {
                RECT rect = { (i % 28) * 20, (i / 28) * 20, ((i % 28) + 1) * 20, ((i / 28) + 1) * 20 };
                FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
            }
        }

        // Draw HUD area
        RECT footer = { 0, 560, 580, 650 };
        FillRect(hdc, &footer, (HBRUSH)GetStockObject(GRAY_BRUSH));

        wchar_t msg[64];
        swprintf(msg, 64, L"PREDICTION: %d   (Press 'C' to Clear)", g_prediction);
        SetBkMode(hdc, TRANSPARENT);
        TextOut(hdc, 20, 580, msg, (int)wcslen(msg));

        EndPaint(hwnd, &ps);
    }
    return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    // 1. Initialize Network with a seed
    model_init(&g_model, 12345);

    // 2. Register Window
    const wchar_t CLASS_NAME[] = L"MNISTWinClass";
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClass(&wc);

    // 3. Create Window (560px for grid + 100px for text)
    HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"MNIST Real-Time Drawing", 
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 576, 650, NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) return 0;
    ShowWindow(hwnd, nCmdShow);

    // 4. Message Loop
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR szCmdLine, int nShow) {
    return wWinMain(hInst, hPrev, NULL, nShow);
}
