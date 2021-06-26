#define n 10
#define half_edge 120
#define edge 240
#define height 200
#define d 15
#define beta 0.4
#include <time.h>



LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char szProgName[]="Имя программы";
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
HWND hWnd;
MSG lpMsg;
WNDCLASS w;
w.lpszClassName=szProgName; //имя программы - объявлено выше
w.hInstance=hInstance; //идентификатор текущего приложения
w.lpfnWndProc=WndProc; //указатель на функцию окна
w.hCursor=LoadCursor(NULL, IDC_ARROW); //загружаем курсор
w.hIcon=0;
w.lpszMenuName=0;
w.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH); //цвет фона окна
w.style=CS_HREDRAW|CS_VREDRAW;
w.cbClsExtra=0;
w.cbWndExtra=0;
//Если не удалось зарегистрировать класс окна - выходим
if(!RegisterClass(&w))
return 0;
//Создадим окно в памяти, заполнив аргументы CreateWindow
hWnd=CreateWindow(szProgName, //Имя программы
                  "Грфические возможности Win32 API", //Заголовок окна
                  WS_OVERLAPPEDWINDOW, //Стиль окна - перекрывающееся
                  0, //положение окна на экране по х
                  0, //положение по у
                  1000, //ширина
                  1000, //высота
                  (HWND)NULL, //идентификатор родительского окна
(HMENU)NULL, //идентификатор меню
(HINSTANCE)hInstance, //идентификатор экземпляра программы
(HINSTANCE)NULL); //отсутствие дополнительных параметров

//Выводим окно из памяти на экран
ShowWindow(hWnd, nCmdShow);
//Обновим содержимое окна
UpdateWindow(hWnd);

//Цикл обработки сообщений

while(GetMessage(&lpMsg, NULL, 0, 0)) {
TranslateMessage(&lpMsg);
DispatchMessage(&lpMsg);
}
return(lpMsg.wParam);
}

//Функция рисования линии от точки к точке
BOOL Line(HDC hdc, int x1, int y1, int x2, int y2){
    MoveToEx(hdc, x1, y1, NULL);
    return LineTo(hdc, x2, y2);
}

//Функция дорисовки наконечника стрелок
void Arrowhead(HDC hdc, int x1, int y1, int x2, int y2){
    double fi;
    int rx, ry, lx, ly;
    if(x1 != x2){
        fi = atan((y1 - y2) / (x2 - x1));
        if (x1 < x2) {
            lx = x2 - 15 * cos(fi - 0.5);
            rx = x2 - 15 * cos(fi + 0.5);
            ly = y2 + 15 * sin(fi - 0.5);
            ry = y2 + 15 * sin(fi + 0.5);
        } else {
            lx = x2 + 15 * cos(fi - 0.5);
            rx = x2 + 15 * cos(fi + 0.5);
            ly = y2 - 15 * sin(fi - 0.5);
            ry = y2 - 15 * sin(fi + 0.5);
        }
    } else{
        lx = x2 - 15*sin(0.5);
        rx = x2 + 15*sin(0.5);
        if(y1 < y2){
            ly = y2 - 15*cos(0.5);
            ry = y2 - 15*cos(0.5);
        } else{
            ly = y2 + 15*cos(0.5);
            ry = y2 + 15*cos(0.5);
        }
    }
    Line(hdc, lx, ly, x2, y2);
    Line(hdc, x2, y2, rx, ry);
}

//Функция рисования стрелы
void Arrow(HDC hdc, int x1, int y1, int x2, int y2){
    double fi, dx, dy;
    int px, py;
    if(x1 != x2){
        if(y1 < y2) {
            fi = (atan((y1 - y2) / (x2 - x1)));
        } else{
            fi = (atan((y1 - y2) / (x1 - x2)));
        }
        dx = d * cos(fi);
        dy = d * sin(fi);
        if (x1 < x2) {
            px = x2 - dx;
            if (y1 < y2) {
                py = y2 + dy;
            } else {
                py = y2 - dy;
            }
        } else {
            px = x2 + dx;
            if (y1 < y2) {
                py = y2 - dy;
            } else {
                py = y2 + dy;
            }
        }
    } else{
        px = x2;
        if(y1 < y2){
            py = y2 - d;
        } else{
            py = y2 + d;
        }
    }
    Line(hdc, x1, y1, px, py);
}

//Функция рисования ломаной стрелки
void Broken_arrow(HDC hdc, int x1, int y1, int x2, int y2){
    int x, y, dx, dy, mid_x, mid_y;
    x = fabs(x1 - x2);
    y = fabs(y1 - y2);
    if (x1 == x2){
        dy = y / 2;
        dx = tan(beta/2) * dy;
        if(y1 < y2){
            mid_y = y1 + dy;
            mid_x = x1 + dx;
        } else{
            mid_y = y1 - dy;
            mid_x = x1 - dx;
        }
    } else if (x1 != x2){
        double alpha, fi;
        alpha = atan(y / x);
        dx = x / 2;
        if (y1 != y2){
            fi = alpha + beta;
            dy = tan(fi) * dx;
            if (x1 < x2) {
                mid_x = x1 + dx;
                if (y1 > y2) {
                    mid_y = y1 - dy;
                } else {
                    mid_y = y1 + dy;
                }
            } else {
                mid_x = x1 - x / 2;
                if (y1 > y2) {
                    mid_y = y1 - dy;
                } else {
                    mid_y = y1 + dy;
                }
            }
        } else{
            dy = tan(beta/2) * dx;
            if (x1 < x2){
                mid_x = x1 + dx;
                mid_y = y1 + dy;
            } else {
                mid_x = x1 - dx;
                mid_y = y1 - dy;
            }
        }
    }
    Line(hdc, x1, y1, mid_x, mid_y);
    Arrow(hdc, mid_x, mid_y, x2, y2);
}

void Vertex(HDC hdc, int x, int y, char* c){
    Ellipse(hdc, x-d, y-d, x+d, y+d);
    TextOut(hdc, x - 5, y - 8, c, 1);
}

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds)
        ;
}

