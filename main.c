#include <stdio.h>
#include<windows.h>
#include<math.h>
#include "generator.h"
#include "kruscal.h"
#include "draw.h"


//Функция окна
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc; //создаём контекст устройства
    PAINTSTRUCT ps; //создаём экземпляр структуры графического вывода
    LOGFONT lf;
    HFONT hFont;
    RECT r;
    HBRUSH hBrush;
    HPEN hPen;

    //Цикл обработки сообщений
    switch(message)
    {
        //сообщение рисования
        case WM_PAINT :
            hdc=BeginPaint(hWnd, &ps);

            int count = 0, floor = 1;
            int **A_cords = create_xy_array(10, 4);
            float x_cord = 500, y_cord = 50;
            while (count != size){
                for(int i = 0; i < floor; i++){
                    //Координата по x
                    if(i == 0){
                        int x = x_cord - half_edge * (floor - 1);
                        A_cords[count][0] = x;
                    } else{
                        A_cords[count][0] = A_cords[count-1][0] + edge;
                    }
                    //Координата по y
                    int y = y_cord;
                    A_cords[count][1] = y;
                    //Номер узла
                    A_cords[count][2] = count + 1;
                    count++;
                }
                floor++;
                y_cord += height;
            }
            double k1 = 1.0 - n3*0.01 - n4*0.005 - 0.05;
            srand(0304);
            int **A = get_matrix(size, k1);

            int **Wt = get_Wt_matrix(A, size);

            int **B = create_2Darray(size);
            for (int k = 0; k < size; ++k) {
                for (int l = 0; l < size; ++l) {
                    if (Wt[k][l] == 0){
                        B[k][l] = 0;
                    } else if (Wt[k][l] > 0){
                        B[k][l] = 1;
                    }
                }
            }

            int **C = create_2Darray(size);
            for (int k = 0; k < size; ++k) {
                for (int l = 0; l < size; ++l) {
                    if (B[k][l] != B[l][k]){
                        C[k][l] = 1;
                    } else {
                        C[k][l] = 0;
                    }
                }
            }

            int **D = create_2Darray(size);
            for (int k = 0; k < size; ++k) {
                for (int l = 0; l < size; ++l) {
                    if (B[k][l] == B[l][k] == 1){
                        D[k][l] = 1;
                    } else {
                        D[k][l] = 0;
                    }
                }
            }

            int **Tr = create_2Darray(size);
            for (int k = 0; k < size; ++k) {
                for (int l = 0; l < size; ++l) {
                    if (k < l){
                        Tr[k][l] = 1;
                    }
                }
            }

            int **W = create_2Darray(size);
            for (int k = 0; k < size; ++k) {
                for (int l = 0; l < size; ++l) {
                    W[k][l] = ((D[k][l] * Tr[k][l]) + C[k][l]) * Wt[k][l];
                }
            }

            for (int k = 0; k < size; ++k) {
                for (int l = 0; l < size; ++l) {
                    if (W[k][l] != W[l][k]){
                        W[k][l] = W[l][k] = max(W[k][l], W[l][k]);
                    }
                }
            }

            for (int k = 0; k < size; ++k) {
                for (int l = 0; l < size; ++l) {
                    Graph[k][l] = W[k][l];
                }
            }

            print_2Darray(W, size);

            kruskalAlgo();
            print();
            printf("\n_______________________________\n");

            char *nn[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};

            hPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
            SelectObject(hdc, hPen);

            for(int i = 0; i < size; i++){
                for(int j = 0; j < i; j++){
                    if(W[j][i] != 0){
                        Vertex(hdc, A_cords[i][0], A_cords[i][1], nn[i]);
                        if(i == j){
                            continue;
                        } else if (A_cords[i][1] == A_cords[j][1] && fabs(A_cords[i][0]-A_cords[j][0]) != edge){
                            Broken_arrow(hdc, A_cords[i][0], A_cords[i][1], A_cords[j][0], A_cords[j][1]);
                        } else if (fabs(A_cords[i][0]-A_cords[j][0]) == edge && fabs(A_cords[i][1]-A_cords[j][1]) > height){
                            Broken_arrow(hdc, A_cords[i][0], A_cords[i][1], A_cords[j][0], A_cords[j][1]);
                        } else if (fabs(A_cords[i][0]-A_cords[j][0]) == half_edge*3 && fabs(A_cords[i][1]-A_cords[j][1]) > height){
                            Broken_arrow(hdc, A_cords[i][0], A_cords[i][1], A_cords[j][0], A_cords[j][1]);
                        } else {
                            //normal
                            Arrow(hdc, A_cords[i][0], A_cords[i][1], A_cords[j][0], A_cords[j][1]);
                        }
                        Vertex(hdc, A_cords[j][0], A_cords[j][1], nn[j]);
                    }
                }
            }

            hBrush = CreateSolidBrush(RGB(255, 255, 255));
            hPen = CreatePen(PS_SOLID, 3, RGB(132, 56, 214));
            SelectObject(hdc, hPen);

            for(int k = 0; k < spanlist.c; k++){
                int i = spanlist.data[k].v;
                int j = spanlist.data[k].u;
                Vertex(hdc, A_cords[i][0], A_cords[i][1], nn[i]);
                if(i == j){
                    continue;
                } else if (A_cords[i][1] == A_cords[j][1] && fabs(A_cords[i][0]-A_cords[j][0]) != edge){
                    Broken_arrow(hdc, A_cords[i][0], A_cords[i][1], A_cords[j][0], A_cords[j][1]);
                } else if (fabs(A_cords[i][0]-A_cords[j][0]) == edge && fabs(A_cords[i][1]-A_cords[j][1]) > height){
                    Broken_arrow(hdc, A_cords[i][0], A_cords[i][1], A_cords[j][0], A_cords[j][1]);
                } else if (fabs(A_cords[i][0]-A_cords[j][0]) == half_edge*3 && fabs(A_cords[i][1]-A_cords[j][1]) > height){
                    Broken_arrow(hdc, A_cords[i][0], A_cords[i][1], A_cords[j][0], A_cords[j][1]);
                } else {
                    //normal
                    Arrow(hdc, A_cords[i][0], A_cords[i][1], A_cords[j][0], A_cords[j][1]);
                }
                Vertex(hdc, A_cords[j][0], A_cords[j][1], nn[j]);
                delay(1);
            }

            for(int i = 0; i < size; i++){
                Vertex(hdc, A_cords[i][0], A_cords[i][1], nn[i]);
            }

            ValidateRect(hWnd, NULL);
            EndPaint(hWnd, &ps);
            break;

            //сообщение выхода - разрушение окна
        case WM_DESTROY:
            PostQuitMessage(0); //Посылаем сообщение выхода с кодом 0 - нормальное завершение
            DeleteObject(hPen);
            DeleteObject(hBrush);
            break;

        default:
            return(DefWindowProc(hWnd, message, wParam, lParam)); //освобождаем очередь приложения от нераспознаных
    }
    return 0;
}