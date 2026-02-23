#ifndef UNICODE
#define UNICODE
#endif 

#include <windows.h>
#include <wchar.h>
#include <string.h>
#include <stdio.h>
#include "mnist_math.h"
#include "model.h"
#include "mnist_io.h"

// Global Variables
Model g_model;
float g_canvas[M_IN] = {0};
int g_prediction = -1;

void train_network() {
    printf("--- MNIST INTELLIGENCE BOOTSTRAP ---\n");
    
    MNISTImages imgs = load_mnist_images("training_data/train-images.idx3-ubyte");
    MNISTLabels lbls = load_mnist_labels("training_data/train-labels.idx1-ubyte");

    if (imgs.x == NULL || lbls.y == NULL) {
        printf("ERROR: Could not find MNIST files in 'training_data/' folder!\n");
        system("pause");
        return;
    }

    model_init(&g_model, 12345);
    
    // Improved Hyperparameters
    float lr = 0.05f; // Higher initial learning rate
    int epochs = 10;  // More laps through the data

    // Shuffling setup
    int* indices = (int*)malloc(imgs.n * sizeof(int));
    for (int i = 0; i < imgs.n; i++) indices[i] = i;

    printf("Training on %d images for %d epochs...\n", imgs.n, epochs);

    for (int e = 0; e < epochs; e++) {
        float total_loss = 0;
        
        // Shuffle indices using the xorshift32 from model.h
        for (int i = imgs.n - 1; i > 0; i--) {
            int j = xorshift32() % (i + 1);
            int temp = indices[i];
            indices[i] = indices[j];
            indices[j] = temp;
        }

        for (int i = 0; i < imgs.n; i++) {
            int idx = indices[i];
            float x[M_IN];
            mnist_u8_to_float(&imgs.x[idx * M_IN], x);
            total_loss += train_step_sgd(&g_model, x, lbls.y[idx], lr);
            
            if (i % 10000 == 0) printf("."); 
        }
        printf("\nEpoch %d complete. Avg Loss: %.4f\n", e + 1, total_loss / imgs.n);
        lr *= 0.85f; // Decay learning rate
    }

    model_save("model.bin", &g_model);
    printf("Success! Intelligence saved to 'model.bin'.\n");
    
    free(indices);
    free(imgs.x);
    free(lbls.y);
    Sleep(2000);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_MOUSEMOVE:
        if (wParam & MK_LBUTTON) {
            int x = LOWORD(lParam) / 20;
            int y = HIWORD(lParam) / 20;

            // Thick 3x3 brush - essential for MNIST recognition
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    int nx = x + dx, ny = y + dy;
                    if (nx >= 0 && nx < 28 && ny >= 0 && ny < 28) {
                        g_canvas[ny * 28 + nx] = 1.0f;
                    }
                }
            }

            float z1[M_H], a1[M_H], z2[M_OUT], p[M_OUT];
            forward(&g_model, g_canvas, z1, a1, z2, p);
            g_prediction = argmax(p, M_OUT);

            InvalidateRect(hwnd, NULL, FALSE);
        }
        return 0;

    case WM_KEYDOWN:
        if (wParam == 'C') { 
            memset(g_canvas, 0, sizeof(g_canvas));
            g_prediction = -1;
            InvalidateRect(hwnd, NULL, TRUE);
        }
        return 0;

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        
        for (int i = 0; i < M_IN; i++) {
            if (g_canvas[i] > 0.1f) {
                RECT rect = { (i % 28) * 20, (i / 28) * 20, ((i % 28) + 1) * 20, ((i / 28) + 1) * 20 };
                FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
            }
        }

        RECT footer = { 0, 560, 580, 650 };
        FillRect(hdc, &footer, (HBRUSH)GetStockObject(GRAY_BRUSH));

        wchar_t msg[64];
        swprintf(msg, 64, L"PREDICTION: %d   (Confidence: %d%%)", g_prediction, (g_prediction == -1 ? 0 : 90)); // Simplified confidence
        SetBkMode(hdc, TRANSPARENT);
        TextOut(hdc, 20, 580, msg, (int)wcslen(msg));
        TextOut(hdc, 400, 610, L"Press 'C' to Clear", 18);

        EndPaint(hwnd, &ps);
    }
    return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
    // Delete old model.bin to force a fresh, better training session
    // remove("model.bin"); 

    FILE* f = fopen("model.bin", "rb");
    if (f) {
        fclose(f);
        model_load("model.bin", &g_model);
    } else {
        AllocConsole();
        freopen("CONOUT$", "w", stdout);
        train_network();
        FreeConsole();
    }

    const wchar_t CLASS_NAME[] = L"MNISTWinClass";
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, L"MNIST Real-Time Recognizer", 
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 576, 650, NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) return 0;
    ShowWindow(hwnd, nCmdShow);

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