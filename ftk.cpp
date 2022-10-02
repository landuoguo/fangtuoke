#include <windows.h>
#include <iostream>
#include <cstdio>
#include <time.h>

#pragma warning(disable:4996);
using namespace std;
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)


struct nowdate
{
    int sec;
    int min;
    int hour;
    int daysec;
};

nowdate timelist[100];
int line;
int delaytimes=0, delaytime=0, warninginterval=50;


nowdate gettime() {
    nowdate now;
    time_t curtime;
    time(&curtime);
    tm* nowtime = localtime(&curtime);
    now.sec = nowtime->tm_sec;
    now.min = nowtime->tm_min;
    now.hour = nowtime->tm_hour;
    now.daysec = now.sec + 60 * now.min + 3600 * now.hour;
    return now;
}

int pd(int s) {
    nowdate now = gettime();
    for (int i = 0; i <= line; i += 2) {
        if (timelist[i].daysec + delaytime <= now.daysec && timelist[i + 1].daysec >= now.daysec) {
            for (int j = 0; j <= 10; j++) {
                if (KEY_DOWN(MOUSE_MOVED)) {
                    if (s < delaytimes) {//判断延时次数
                        cout << "防拖课警告已触发 time=> " << now.hour << ":" << now.min << ":" << now.sec << " s=>" << s << endl;
                        Sleep(200);
                        MessageBox(GetForegroundWindow(),L"-------下课时间到!-------",L"防拖课系统",MB_OK);
                    }
                    else {
                        cout << "防拖课锁定已触发 time=> " << now.hour << ":" << now.min << ":" << now.sec << " s=>" << s << endl;
                        system("rundll32.exe user32.dll, LockWorkStation");//锁屏
                        MessageBox(GetForegroundWindow(), L"-------下课时间到!-------", L"防拖课系统", MB_OK);
                    }
                    s++;//计数器累加
                    Sleep(warninginterval*1000);//警告间隔时间
                    break;
                }
                Sleep(100);//延迟0.1s
            }
            pd(s);
        }
    }
    s = 0;//清空计数器
    return 0;
}


int main()
{
    freopen("time.conf", "r", stdin);
    int a, b, c;
    cin >> delaytimes >> warninginterval;
    cin >> line;
    line = 2*line - 1;

    cout << "fqyz研究性学习课题" << endl;
    cout << "《如何防止老师拖课，提高学生上课精神》" << endl;
    cout << "@Auther:landuoguo" << endl;
    cout << "Github: github.com/landuoguo/fangtuoke" << endl;
    cout << "防拖课触发时间表：" << endl;


    for (int i = 0; i <= line; i++) {
        scanf("%d:%d:%d", &a, &b, &c);
        timelist[i].hour = a;
        timelist[i].min = b;
        timelist[i].sec = c;
        timelist[i].daysec = a * 3600 + b * 60 + c;
        if (i % 2 == 0) {
            cout <<"from " << a << ":" << b << ":" << c;
        }
        else {
            cout <<" to " << a << ":" << b << ":" << c <<endl;
        }
        
    }
    
    cout << "程序运行中……" << endl;

    while (1) {
        pd(0);
        Sleep(15000);//延迟15秒
        
    }
    
}
