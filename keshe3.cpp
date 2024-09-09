#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <time.h>
#include <ctime>
#include <Windows.h>

using namespace std;


static int NHour = 7;
static int NMinute = 0;

//飞机类
class Plane {

public:
    string PName;
   // Time PTime;
    int PQHtime;
    int PQMtime;
    int PAHtime;
    int PAMtime;
    int PType;
    int PDuration;
    int PFuel;

public:
    Plane()
    {

    }
    Plane(string PName, int PQHtime, int PQMtime, int PAHtime, int PAMtime, int PFuel) {
        this->PName = PName;
        this->PQHtime = PQHtime;
        this->PQMtime = PQMtime;
        this->PAHtime = PAHtime;
        this->PAMtime = PAMtime;
        this->PFuel = PFuel;

    }
    virtual ~Plane() {

    }
public:

    bool everyTime() {
        PFuel = PFuel - 5;
        return true;
    }
    //
    //    Time getTime()  {
     //       return PTime;
     //   }
      //int getType() {
     //     return PType;
     // }   
      //int getDuration() {
      //    return PDuration;
      //}
      //  void increaseDuration() {
    //        ++PDuration;
       // }
};



class Road {
public:
    int Rflag;
    Road() {//初始化跑道 0为空
        Rflag = 0;
    }
    bool ISOCCUPY() {
        Rflag = 1;
        return true;
    }
    bool NOTOCCUPY() {
        Rflag = 0;
        return true;
    }
};


class Queue{
public:
    bool getFront(Plane & item);
    bool clear();
    bool deQueue(Plane & item);
    bool enQueue(const Plane & item);
    bool isEmpty();
    bool isFull();
    bool deleteitem(int n);
};

class PQueue :public Queue {
public:
    int mSize, front, rear;
    Plane* p;

    PQueue() {
    }
    PQueue(int size) {
        mSize = size + 1;
        p = new Plane[mSize];
        front = rear = 0;
    }
    ~PQueue() {
        delete[] p;
    }

    bool getFront(Plane& item) {
        if (front == rear) {
            cout << "队空" << endl;
            return false;
        }
        item = p[front];
        return true;
    }

    void clear() {
        front = rear;
    }

    bool enQueue(const Plane item)
    {
        if (((rear + 1) % mSize) == front) {
            cout << "队满" << endl;
            return false;
        }
        p[rear] = item;
        rear = (rear + 1) % mSize;
        return true;
    }
    bool deQueue(Plane& item) {
        if (front == rear) {
            cout << "队空" << endl;
            return false;
        }
        item = p[front];
        front = (front + 1) % mSize;
        return true;
    }


    bool isEmpty() {
        if (front == rear)
            return true;
        else
            return false;
    }

    void deleteitem(int n) {//从队列中移除某元素
        for (int i = n; i < rear - 1; i = (i + 1) % mSize) {
            p[i] = p[i + 1];
        }
        rear = (rear - 1) % mSize;
    }
};
int Dispatch(int& ALLNum, PQueue& QF, PQueue& JL, PQueue& Jinji, Road* way);
int Dispatch(int& ALLNum, PQueue& QF, PQueue& JL, PQueue& Jinji, Road* way) {
    int i;
    int  PQHtime, PQMtime, PAHtime, PAMtime;
    int PFuel;
    string PName;
    int QFcnt = 0, JLcnt = 0;//起飞计数 降落计数
    int ALLcnt = 0;//全部飞机计数
    int fuel;//随机生成油量
    int JLF;//JL队列的Front
    JLF = JL.front;
    char a, b;
    // srand((unsigned)time(NULL));
    while (1) {
        while (ALLNum > 0) {
            for (int i = 0; i < 4; i++) {
                way[i].NOTOCCUPY();//清空跑道
            }
            QFcnt = 0;
            JLcnt = 0;
            cout << "kkkkkkkkkk" << ALLNum << "kkkkkkkkkk" << endl;
            ifstream file("C:\\Users\\23854\\Desktop\\test.txt");
            if (!file.is_open())
            {
                cout << "can not open file !" << endl;
                return 0;
            }
            while (!file.eof()) {
                file >> PName >> PQHtime >> a >> PQMtime >> PAHtime >> b >> PAMtime;
                cout << "  " << NHour << ":" << NMinute << endl;
                if ((PAHtime == 0 && PAMtime == 0) && (PQHtime == NHour && PQMtime >= NMinute && PQMtime < NMinute + 15)) {
                    Plane fj(PName, PQHtime, PQMtime, PAHtime, PAMtime, 100);
                    // cout << "qifei mSize" << QF.mSize << endl;
                    if (QFcnt <= 4) {
                        QF.enQueue(fj);
                        // cout << "*********" << endl;
                        cout << fj.PName << "进入起飞队列" << endl;
                        QFcnt = QFcnt + 1;
                        cout << "起飞队列中有：" << endl;
                        for (int i = QF.front; i < QF.rear; i = (i + 1) % QF.mSize) {
                            cout << QF.p[i].PName << endl;
                        }
                    }
                    else
                        break;
                }
                else if ((PQHtime == 0 && PQMtime == 0) && (PAHtime == NHour && PAMtime >= NMinute && PAMtime < NMinute + 15)) {
                    //  srand((unsigned)time(NULL));
                    fuel = rand() % 100 + 1;

                    Plane fj(PName, PQHtime, PQMtime, PAHtime, PAMtime, fuel);
                    if (JLcnt <= 4) {
                        JL.enQueue(fj);
                        // cout << "!!!!!!!!!!" << endl;
                        cout << fj.PName << "进入降落队列" << endl;
                        JLcnt = JLcnt + 1;
                        cout << "降落队列中有：" << endl;
                        for (int i = JL.front; i < JL.rear; i = (i + 1) % JL.mSize) {
                            cout << JL.p[i].PName << endl;
                        }

                    }
                    else
                        break;
                }
            }
            file.close();
            int t;
            int c = JL.front;
            int v = JL.rear;
            ALLcnt = 0;
            cout << "mmmmmmmm" << c << "    " << v << "mmmmmmmmmm" << endl;

            if (JL.rear >= JL.front) {
                t = JL.rear - JL.front;
            }
            else {
                t = JL.rear - JL.front + JL.mSize;
            }

            while (ALLcnt != t) {
                cout << "(((((((((" << "    " << ALLcnt << "     " << ")))))))))" << endl;
                for (JLF = JL.front; JLF < JL.rear; JLF = (JLF + 1) % JL.mSize) {
                    if (JL.p[JLF].PFuel < 10) {
                        Plane fj;
                        fj = JL.p[JLF];
                        JL.deleteitem(JLF);
                        cout << fj.PName << "进入紧急队列" << endl;
                        Jinji.enQueue(fj);
                        JLF = JL.front;
                        ALLcnt = 0;
                        break;

                    }
                    else {
                        ALLcnt = ALLcnt + 1;
                    }
                }
            }


            if (!QF.isEmpty() || !JL.isEmpty() || !Jinji.isEmpty()) {
                //有紧急
                if (!Jinji.isEmpty()) {

                    //按油量排序
                    for (int m = Jinji.front; m < Jinji.rear - 1; m = (m + 1) % Jinji.mSize) {
                        for (int n = m; n < Jinji.rear; n = (n + 1) % Jinji.mSize) {
                            if (Jinji.p[m].PFuel > Jinji.p[n].PFuel) {
                                Plane tmp;
                                tmp = Jinji.p[m];
                                Jinji.p[m] = Jinji.p[n];
                                Jinji.p[n] = tmp;
                            }
                        }
                    }
                    int jinjinum = 0;
                    for (int i = Jinji.front; i < Jinji.rear; i = (i + 1) % Jinji.mSize) {
                        jinjinum = jinjinum + 1;
                    }
                    //只有一架紧急飞机时
                    if (jinjinum == 1) {
                        way[3].ISOCCUPY();//占用紧急跑道
                        Plane fj;
                        Jinji.deQueue(fj);
                        cout << fj.PName << "降落在紧急跑道" << endl;
                        cout << "油量为" << fj.PFuel << endl;
                        ALLNum = ALLNum - 1;
                    }
                    //不止一架紧急
                    else {
                        way[3].ISOCCUPY();
                        Plane fj;
                        Jinji.deQueue(fj);
                        cout << fj.PName << "降落在紧急跑道" << endl;
                        cout << "油量为" << fj.PFuel << endl;
                        ALLNum = ALLNum - 1;
                        jinjinum = jinjinum - 1;
                        int waynum = 2;
                        while (jinjinum != 0) {
                            if (waynum != 0) {
                                way[waynum].ISOCCUPY();
                                Plane temp;
                                Jinji.deQueue(temp);
                                cout << temp.PName << "在第" << waynum + 1 << "道降落" << endl;
                                cout << "油量为" << temp.PFuel << endl;
                                ALLNum--;
                                jinjinum--;
                                waynum--;
                            }
                        }
                    }


                    int jlnum = 0;
                    for (int i = JL.front; i < JL.rear; i = (i + 1) % JL.mSize) {
                        jlnum = jlnum + 1;
                    }
                    //选时间最早的飞机
                    while (1) {



                        Plane qft;
                        Plane jlt;
                        //有起飞 无降落
                        if (!QF.isEmpty() && JL.isEmpty()) {
                            int n = 0;
                            int flag = 0;
                            for (n = 0; n <= 3; n++) {
                                if (way[n].Rflag == 0) {
                                    way[n].ISOCCUPY();
                                    flag = 1;
                                    break;
                                }
                            }
                            if (flag == 1) {
                                Plane fj;
                                QF.deQueue(fj);
                                ALLNum--;
                                cout << fj.PName << "在第" << n + 1 << "道上起飞" << endl;
                            }
                            else
                                break;
                        }
                        //无起飞 有降落
                        else if (QF.isEmpty() && !JL.isEmpty()) {
                            int n = 0;
                            int flag = 0;
                            for (n = 0; n <= 2; n++) {
                                if (way[n].Rflag == 0) {
                                    way[n].ISOCCUPY();
                                    flag = 1;
                                    break;
                                }

                            }
                            if (flag == 1) {
                                Plane fj;
                                JL.deQueue(fj);
                                ALLNum--;
                                cout << fj.PName << "在第" << n + 1 << "道降落" << endl;
                                cout << "油量为" << fj.PFuel << endl;
                            }
                            else
                                break;

                        }
                        //有起飞 有降落
                        else if (!QF.isEmpty() && !JL.isEmpty()) {
                            //降落的飞机数量大于设定值时降落优先
                            if (jlnum > 5) {
                                for (int m = JL.front; m < JL.rear - 1; m = (m + 1) % JL.mSize) {
                                    for (int n = m; n < JL.rear; n = (n + 1) % JL.mSize) {
                                        if (JL.p[m].PFuel > JL.p[n].PFuel) {
                                            Plane tmp;
                                            tmp = JL.p[m];
                                            JL.p[m] = JL.p[n];
                                            JL.p[n] = tmp;
                                        }
                                    }
                                }
                                //油少的飞机优先降落
                                if (!JL.isEmpty()) {
                                    int n = 0;
                                    int flag = 0;
                                    for (n = 0; n <= 2; n++)
                                    {
                                        if (way[n].Rflag == 0) {
                                            way[n].ISOCCUPY();
                                            flag = 1;
                                            break;
                                        }
                                    }
                                    if (flag == 1) {
                                        Plane fj;
                                        JL.deQueue(fj);
                                        ALLNum--;
                                        cout << fj.PName << "在第" << n + 1 << "道降落" << endl;
                                        cout << "油量为" << fj.PFuel << endl;
                                    }
                                    else
                                        break;
                                }
                                //降落飞机降落后开始起飞
                                else if (!QF.isEmpty()) {
                                    int n = 0;
                                    int flag = 0;
                                    for (n = 0; n <= 3; n++) {
                                        if (way[n].Rflag == 0) {
                                            way[n].ISOCCUPY();
                                            flag = 1;
                                            break;
                                        }

                                    }
                                    if (flag == 1) {
                                        Plane fj;
                                        QF.deQueue(fj);
                                        ALLNum--;
                                        cout << fj.PName << "在第" << n + 1 << "道上起飞" << endl;
                                    }
                                    else
                                        break;
                                }

                            }
                            //降落的飞机数没有达到设定值时按时间进行
                            else {
                                Plane qft, jlt;
                                QF.getFront(qft);
                                JL.getFront(jlt);
                                //比较起飞时间和降落时间

                                if ((qft.PQHtime < jlt.PAHtime) || ((qft.PQHtime = jlt.PAHtime) && (qft.PQMtime < jlt.PAMtime)))
                                {
                                    int n = 0;
                                    int flag = 0;
                                    for (n = 0; n <= 3; n++) {
                                        if (way[n].Rflag == 0) {
                                            way[n].ISOCCUPY();
                                            flag = 1;
                                            break;
                                        }

                                    }
                                    if (flag == 1) {
                                        Plane fj;
                                        QF.deQueue(fj);
                                        ALLNum--;
                                        cout << fj.PName << "在第" << n + 1 << "道上起飞" << endl;
                                    }
                                    else
                                        break;
                                }
                                //按时间顺序无起飞飞机
                                else {
                                    int n = 0;
                                    int flag = 0;
                                    for (n = 0; n <= 2; n++)
                                    {
                                        if (way[n].Rflag == 0) {
                                            way[n].ISOCCUPY();
                                            flag = 1;
                                            break;
                                        }
                                    }
                                    if (flag == 1) {
                                        Plane fj;
                                        JL.deQueue(fj);
                                        ALLNum--;
                                        cout << fj.PName << "在第" << n + 1 << "道降落" << endl;
                                        cout << "油量为" << fj.PFuel << endl;
                                    }
                                    else
                                        break;
                                }
                            }
                        }
                        else {
                            break;
                        }
                    }
                }
                //无紧急
                else {
                    while (1) {
                        Plane qft;
                        Plane jlt;
                        //有起飞 无降落
                        if (!QF.isEmpty() && JL.isEmpty()) {
                            int n = 0;
                            int flag = 0;
                            for (n = 0; n <= 3; n++) {
                                if (way[n].Rflag == 0) {
                                    way[n].ISOCCUPY();
                                    flag = 1;
                                    break;
                                }
                            }
                            if (flag == 1) {
                                Plane fj;
                                QF.deQueue(fj);
                                ALLNum--;
                                cout << fj.PName << "在第" << n + 1 << "道上起飞" << endl;
                            }
                            else
                                break;
                        }
                        //无起飞 有降落
                        else if (QF.isEmpty() && !JL.isEmpty()) {
                            int n = 0;
                            int flag = 0;
                            for (n = 0; n <= 2; n++) {
                                if (way[n].Rflag == 0) {
                                    way[n].ISOCCUPY();
                                    flag = 1;
                                    break;
                                }

                            }
                            if (flag == 1) {
                                Plane fj;
                                JL.deQueue(fj);
                                ALLNum--;
                                cout << fj.PName << "在第" << n + 1 << "道降落" << endl;
                                cout << "油量为" << fj.PFuel << endl;
                            }
                            else
                                break;

                        }
                        else if (!QF.isEmpty() && !JL.isEmpty()) {//有起飞 有降落
                            int jlnum = 0;
                            if (jlnum > 5) {
                                for (int m = JL.front; m < JL.rear - 1; m = (m + 1) % JL.mSize) {
                                    for (int n = m; n < JL.rear; n = (n + 1) % JL.mSize) {
                                        if (JL.p[m].PFuel > JL.p[n].PFuel) {
                                            Plane tmp;
                                            tmp = JL.p[m];
                                            JL.p[m] = JL.p[n];
                                            JL.p[n] = tmp;
                                        }
                                    }
                                }

                                if (!JL.isEmpty()) {//优先降落
                                    int n = 0;
                                    int flag = 0;
                                    for (n = 0; n <= 2; n++)
                                    {
                                        if (way[n].Rflag == 0) {
                                            way[n].ISOCCUPY();
                                            flag = 1;
                                            break;
                                        }
                                    }
                                    if (flag == 1) {
                                        Plane fj;
                                        JL.deQueue(fj);
                                        ALLNum--;
                                        cout << fj.PName << "在第" << n + 1 << "道降落" << endl;
                                        cout << "油量为" << fj.PFuel << endl;
                                    }
                                    else
                                        break;
                                }
                                else if (!QF.isEmpty()) {
                                    int n = 0;
                                    int flag = 0;
                                    for (n = 0; n <= 3; n++) {
                                        if (way[n].Rflag == 0) {
                                            way[n].ISOCCUPY();
                                            flag = 1;
                                            break;
                                        }

                                    }
                                    if (flag == 1) {
                                        Plane fj;
                                        QF.deQueue(fj);
                                        ALLNum--;
                                        cout << fj.PName << "在第" << n + 1 << "道上起飞" << endl;
                                    }
                                    else
                                        break;
                                }

                            }
                            else {
                                Plane qft, jlt;
                                QF.getFront(qft);
                                JL.getFront(jlt);
                                if ((qft.PQHtime < jlt.PAHtime) || ((qft.PQHtime = jlt.PAHtime) && (qft.PQMtime < jlt.PAMtime)))
                                {
                                    int n = 0;
                                    int flag = 0;
                                    for (n = 0; n <= 3; n++) {
                                        if (way[n].Rflag == 0) {
                                            way[n].ISOCCUPY();
                                            flag = 1;
                                            break;
                                        }

                                    }
                                    if (flag == 1) {
                                        Plane fj;
                                        QF.deQueue(fj);
                                        ALLNum--;
                                        cout << fj.PName << "在第" << n + 1 << "道上起飞" << endl;
                                    }
                                    else
                                        break;
                                }
                                else {
                                    int n = 0;
                                    int flag = 0;
                                    for (n = 0; n <= 2; n++)
                                    {
                                        if (way[n].Rflag == 0) {
                                            way[n].ISOCCUPY();
                                            flag = 1;
                                            break;
                                        }
                                    }
                                    if (flag == 1) {
                                        Plane fj;
                                        JL.deQueue(fj);
                                        ALLNum--;
                                        cout << fj.PName << "在第" << n + 1 << "道降落" << endl;
                                        cout << "油量为" << fj.PFuel << endl;
                                    }
                                    else
                                        break;
                                }
                            }
                        }
                        else {
                            break;
                        }
                    }
                }
                NMinute = NMinute + 15;
                cout << "!!!!!!!!!!" << endl;
                if (NMinute == 60) {
                    NHour++;
                    NMinute = 0;
                    if (NHour == 24) {
                        NHour = 0;
                    }
                }
                Sleep(1000);
                int k = JL.front;
                int w = JL.rear;
                cout << "^^^^^^^^^^^" << JL.front << JL.rear << "^^^^^^^^^^^^" << endl;
                for (int n = JL.front; n < JL.rear; n++) {
                    JL.p[n].everyTime();
                    cout << "FLAGFLAGFLAGFLAG" << endl;
                    cout << "$$$$油量为" << JL.p[n].PFuel << endl;
                }
                continue;
            }
            NMinute = NMinute + 15;
            cout << "!!!!!!!!!!" << endl;
            if (NMinute == 60) {
                NHour++;
                NMinute = 0;
                if (NHour == 24) {
                    NHour = 0;
                }
            }
            // srand((unsigned)time(NULL));
            Sleep(1000);
            for (int n = JL.front; n < JL.rear; n = (n + 1) % JL.mSize) {
                JL.p[n].everyTime();
                cout << "####油量为" << JL.p[n].PFuel << endl;
            }
        }
        
    }
    return 1;
}

int  main() {
    int QPNum = 0;
    int APNum = 0;
    int ALLNum = 0;
    char a,b,c,d,e,f,g;

    string PName;
    int PQHtime, PQMtime, PAHtime, PAMtime, Fnum;
    ifstream file("C:\\Users\\23854\\Desktop\\test.txt");
    if (!file.is_open())  //统计起飞降落飞机数量
    {
        cout << "can not open this file" << endl;
        return 0;
    }
    while (!file.eof()) {

      //  file >> f >> g >> Fnum >> c >>PQHtime >> a >>PQMtime >> d >>PAHtime >> b >> PAMtime >> e;
      //  cout<< f << g << Fnum << c << PQHtime << a << PQMtime << d << PAHtime << b << PAMtime <<endl;
        file >>PName>> PQHtime >> a >> PQMtime >> PAHtime >> b >> PAMtime;
        cout << PName<<" " << PQHtime << a << PQMtime <<" " << PAHtime << b << PAMtime << endl;
        //file.get(); // 读取最后的回车符
        //if (file.peek() == '\n') break;
        if (PAHtime == 0 && PAMtime == 0) {
           // cout << "file was opened" << endl;
            APNum++;
           // cout << "111" << endl;
        }
        else if (PQHtime == 0 && PQMtime == 0) {
        //    cout << "file was opened" << endl;
            QPNum++;
           // cout << "222" << endl;
        }
    }
    file.close();
    ALLNum = QPNum + APNum;
    PQueue QF(QPNum);
    PQueue JL(APNum);
    PQueue Jinji(ALLNum);
    Road way[4];
    int FLAG = 0;
    //cout << "*********" << endl;
    cout << "航班信息显示完毕" << endl;

    Dispatch(ALLNum, QF, JL, Jinji, way);
    
    return  0;
}
