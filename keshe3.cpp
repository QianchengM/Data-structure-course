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

//�ɻ���
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
    Road() {//��ʼ���ܵ� 0Ϊ��
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
            cout << "�ӿ�" << endl;
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
            cout << "����" << endl;
            return false;
        }
        p[rear] = item;
        rear = (rear + 1) % mSize;
        return true;
    }
    bool deQueue(Plane& item) {
        if (front == rear) {
            cout << "�ӿ�" << endl;
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

    void deleteitem(int n) {//�Ӷ������Ƴ�ĳԪ��
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
    int QFcnt = 0, JLcnt = 0;//��ɼ��� �������
    int ALLcnt = 0;//ȫ���ɻ�����
    int fuel;//�����������
    int JLF;//JL���е�Front
    JLF = JL.front;
    char a, b;
    // srand((unsigned)time(NULL));
    while (1) {
        while (ALLNum > 0) {
            for (int i = 0; i < 4; i++) {
                way[i].NOTOCCUPY();//����ܵ�
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
                        cout << fj.PName << "������ɶ���" << endl;
                        QFcnt = QFcnt + 1;
                        cout << "��ɶ������У�" << endl;
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
                        cout << fj.PName << "���뽵�����" << endl;
                        JLcnt = JLcnt + 1;
                        cout << "����������У�" << endl;
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
                        cout << fj.PName << "�����������" << endl;
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
                //�н���
                if (!Jinji.isEmpty()) {

                    //����������
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
                    //ֻ��һ�ܽ����ɻ�ʱ
                    if (jinjinum == 1) {
                        way[3].ISOCCUPY();//ռ�ý����ܵ�
                        Plane fj;
                        Jinji.deQueue(fj);
                        cout << fj.PName << "�����ڽ����ܵ�" << endl;
                        cout << "����Ϊ" << fj.PFuel << endl;
                        ALLNum = ALLNum - 1;
                    }
                    //��ֹһ�ܽ���
                    else {
                        way[3].ISOCCUPY();
                        Plane fj;
                        Jinji.deQueue(fj);
                        cout << fj.PName << "�����ڽ����ܵ�" << endl;
                        cout << "����Ϊ" << fj.PFuel << endl;
                        ALLNum = ALLNum - 1;
                        jinjinum = jinjinum - 1;
                        int waynum = 2;
                        while (jinjinum != 0) {
                            if (waynum != 0) {
                                way[waynum].ISOCCUPY();
                                Plane temp;
                                Jinji.deQueue(temp);
                                cout << temp.PName << "�ڵ�" << waynum + 1 << "������" << endl;
                                cout << "����Ϊ" << temp.PFuel << endl;
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
                    //ѡʱ������ķɻ�
                    while (1) {



                        Plane qft;
                        Plane jlt;
                        //����� �޽���
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
                                cout << fj.PName << "�ڵ�" << n + 1 << "�������" << endl;
                            }
                            else
                                break;
                        }
                        //����� �н���
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
                                cout << fj.PName << "�ڵ�" << n + 1 << "������" << endl;
                                cout << "����Ϊ" << fj.PFuel << endl;
                            }
                            else
                                break;

                        }
                        //����� �н���
                        else if (!QF.isEmpty() && !JL.isEmpty()) {
                            //����ķɻ����������趨ֵʱ��������
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
                                //���ٵķɻ����Ƚ���
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
                                        cout << fj.PName << "�ڵ�" << n + 1 << "������" << endl;
                                        cout << "����Ϊ" << fj.PFuel << endl;
                                    }
                                    else
                                        break;
                                }
                                //����ɻ������ʼ���
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
                                        cout << fj.PName << "�ڵ�" << n + 1 << "�������" << endl;
                                    }
                                    else
                                        break;
                                }

                            }
                            //����ķɻ���û�дﵽ�趨ֵʱ��ʱ�����
                            else {
                                Plane qft, jlt;
                                QF.getFront(qft);
                                JL.getFront(jlt);
                                //�Ƚ����ʱ��ͽ���ʱ��

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
                                        cout << fj.PName << "�ڵ�" << n + 1 << "�������" << endl;
                                    }
                                    else
                                        break;
                                }
                                //��ʱ��˳������ɷɻ�
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
                                        cout << fj.PName << "�ڵ�" << n + 1 << "������" << endl;
                                        cout << "����Ϊ" << fj.PFuel << endl;
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
                //�޽���
                else {
                    while (1) {
                        Plane qft;
                        Plane jlt;
                        //����� �޽���
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
                                cout << fj.PName << "�ڵ�" << n + 1 << "�������" << endl;
                            }
                            else
                                break;
                        }
                        //����� �н���
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
                                cout << fj.PName << "�ڵ�" << n + 1 << "������" << endl;
                                cout << "����Ϊ" << fj.PFuel << endl;
                            }
                            else
                                break;

                        }
                        else if (!QF.isEmpty() && !JL.isEmpty()) {//����� �н���
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

                                if (!JL.isEmpty()) {//���Ƚ���
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
                                        cout << fj.PName << "�ڵ�" << n + 1 << "������" << endl;
                                        cout << "����Ϊ" << fj.PFuel << endl;
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
                                        cout << fj.PName << "�ڵ�" << n + 1 << "�������" << endl;
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
                                        cout << fj.PName << "�ڵ�" << n + 1 << "�������" << endl;
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
                                        cout << fj.PName << "�ڵ�" << n + 1 << "������" << endl;
                                        cout << "����Ϊ" << fj.PFuel << endl;
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
                    cout << "$$$$����Ϊ" << JL.p[n].PFuel << endl;
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
                cout << "####����Ϊ" << JL.p[n].PFuel << endl;
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
    if (!file.is_open())  //ͳ����ɽ���ɻ�����
    {
        cout << "can not open this file" << endl;
        return 0;
    }
    while (!file.eof()) {

      //  file >> f >> g >> Fnum >> c >>PQHtime >> a >>PQMtime >> d >>PAHtime >> b >> PAMtime >> e;
      //  cout<< f << g << Fnum << c << PQHtime << a << PQMtime << d << PAHtime << b << PAMtime <<endl;
        file >>PName>> PQHtime >> a >> PQMtime >> PAHtime >> b >> PAMtime;
        cout << PName<<" " << PQHtime << a << PQMtime <<" " << PAHtime << b << PAMtime << endl;
        //file.get(); // ��ȡ���Ļس���
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
    cout << "������Ϣ��ʾ���" << endl;

    Dispatch(ALLNum, QF, JL, Jinji, way);
    
    return  0;
}
