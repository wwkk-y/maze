#pragma once
#ifndef WIN_H
#define WIN_H

#include <Windows.h>

namespace win {
    inline void setFont(int size = 16);//设置字体大小(窗口缩放比),16为原始值
    inline void setSize(int w, int h);//设置窗口宽高，有侧边滑动条
    inline void gotoxy(int x, int y);//设置光标位置
    inline void setCursor(bool mode = false);//设置光标显示(隐藏或者显示)
    inline void setColor(WORD color = 0x7);
}

namespace win {
    enum {
        back,
        blue,
        green,
        greenLight1,

        red,
        purple,
        yellow,
        white,

        grey,
        blueLight,
        greeLight2,
        greenLightLight,

        redLight,
        purpleLight,
        yellowLight,
        whiteLight
    };
    struct Color {
        WORD front;
        WORD back;

        Color(WORD color = 0x07) {
            front = color % 16;
            back = color / 16;
        }

        Color(WORD front, WORD back) :front(front), back(back) {};

        Color& operator=(WORD color) {
            front = color % 16;
            back = color / 16;
            return *this;
        }

        operator WORD() const{ return back * 16 + front; }
    };
}

namespace win {
    void win::setFont(int size) {//设置字体大小
        CONSOLE_FONT_INFOEX cfi;
        cfi.cbSize = sizeof cfi;
        cfi.nFont = 0;
        cfi.dwFontSize.X = 0;
        cfi.dwFontSize.Y = size;  //设置字体大小
        cfi.FontFamily = FF_DONTCARE;
        cfi.FontWeight = FW_NORMAL; //字体粗细 FW_BOLD
        SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
    }

    void win::setSize(int w, int h)//设置窗口大小
    {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD size = { w, h };
        SetConsoleScreenBufferSize(hOut, size);
        SMALL_RECT rc = { 1,1, w, h };
        SetConsoleWindowInfo(hOut, 1, &rc);
        return;
    }

    void win::gotoxy(int x, int y) {
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD pos;
        pos.X = x;
        pos.Y = y;//COORD pos = {x,y}; 
        SetConsoleCursorPosition(handle, pos);
    }

    void win::setCursor(bool mode)
    {
        CONSOLE_CURSOR_INFO cursor;
        cursor.bVisible = mode;
        cursor.dwSize = sizeof(cursor);
        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorInfo(handle, &cursor);
    }

    void win::setColor(WORD color)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    }
}
#endif