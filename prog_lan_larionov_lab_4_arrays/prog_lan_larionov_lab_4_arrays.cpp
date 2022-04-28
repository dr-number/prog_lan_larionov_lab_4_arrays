#include <iostream>
#include <Windows.h>
#include <string>
#include <stdlib.h>
#include <cctype>
#include <conio.h>
#include <random>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <vector>

#define PI 3.14159265

using namespace std;
HANDLE handleConsole;

enum ConsoleColor
{
    Blue = 1,
    Green = 2,
    Red = 4,
    Yellow = 14,
    White = 15
};

string GetLine() {
    string line;
    getline(cin, line);
    cin.clear();
    return line;
}

class MyInput {

public:

    double InputData(string text, bool isNegative = true) {

        string xStr = "";
        double x = 0, result = 0;
        bool isNumber = true;

        while (true) {

            SetConsoleTextAttribute(handleConsole, White);
            cout << text;

            xStr = GetLine();

            try {
                result = stod(xStr.c_str());
                isNumber = true;
            }
            catch (...) {
                isNumber = false;
            }

            if (!isNumber) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << endl << xStr + " - �� �����!" << endl << endl;
            }
            else if (isNegative && result <= 0) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << endl << "����� ������ ���� ������ ����!" << endl << endl;
            }
            else
                break;
        }

        return result;
    }

    int InputIntData(string text, int min, int max, bool isNegative) {

        double result;

        while (true) {
            result = InputData(text);

            if (result != (int)result) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << endl << "����� ������ ���� �����!" << endl << endl;
            }
            else if (result < min || result > max) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << endl << "����� ������ ������ � ���������� [" << min << "; " << max << "]!" << endl << endl;
            }
            else
                break;
        }

        return result;
    }

    int InputIntData(string text, int min, int max, int defaultValue, bool isNegative) {

        string str = GetLine();

        if (str == "\n")
            return defaultValue;

        return InputIntData(text, min, max, isNegative);
    }



};

class MyQuestion {

public:
    const string QUESTION_RANDOM_DATA = "������������� ������ ��������� ������� [y/n]?";
    const string QUESTION_IN_ORDER_DATA = "����� ����� �� ������� [y/n]?";

    bool isQuestion(string textQuestion) {

        cout << textQuestion << endl;
        string answer = GetLine();

        transform(answer.begin(), answer.end(), answer.begin(), tolower);
        return answer == "y" || answer == "";
    }
};

class MyRandom {

public:
    double MIN_RANDOM = 10, MAX_RANDOM = 1000;

    double GetRandom(int min, int max) {
        return rand() % (max - min) - min;
    }

};

class MyArray {
public:
    int const MIN_VALUE = -10000;
    int const MAX_VALUE = 10000;

    int const DEFAULT_COUNT_VALUE = 50;

    vector <int> CreateRandomArray(int n, int minValue, int maxValue) {
        
        vector <int> arr;
        MyRandom myRandom = *new MyRandom();

        for(int i = 0; i < n; ++i)
            arr.push_back(myRandom.GetRandom(minValue, maxValue));

        return arr;
    }

    vector <int> CreateInputArray(int n, int minValue, int maxValue) {

        vector <int> arr;
        MyInput myInput = *new MyInput();

        for (int i = 0; i < n; ++i)
            arr.push_back(myInput.InputIntData("������� ����� ����� (" + to_string(i + 1) + "��" + to_string(n) + "): ", minValue, maxValue, true));

        return arr;
    }

    vector <int> CreateArray(int n, int minValue, int maxValue) {

        MyQuestion myQuestion = *new MyQuestion();

        bool isRandomData = myQuestion.isQuestion(myQuestion.QUESTION_RANDOM_DATA);

        if (isRandomData)
            return CreateRandomArray(n, minValue, maxValue);

        return CreateInputArray(n, minValue, maxValue);
    }

    vector <int> CreateArray(int n) {
        return CreateArray(n, MIN_VALUE, MAX_VALUE);
    }

    void PrintArray(vector <int> arr) {
        
        int size = arr.size();

        for (int i = 0; i < size; ++i)
            cout << "[" << i << "] " << arr[i] << endl;
    }

    int GetIndexMinElem(vector<int> arr) {

        int index = 0;
        int min = arr[0];
        int size = arr.size();

        for (int i = 1; i < size; ++i)
            if (arr[i] < min) {
                min = arr[i];
                index = i;
            }

        return index;
    }

    int GetIndexMaxElem(vector<int> arr) {

        int index = 0;
        int max = arr[0];
        int size = arr.size();

        for (int i = 1; i < size; ++i)
            if (arr[i] > max) {
                max = arr[i];
                index = i;
            }

        return index;
    }

};

class Task6 {

public:
    void Init() {

        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handleConsole, White);

        cout << "������ ������ ������ ��������������� ������ ��������� �� ������ �� 3 �������." << endl;
        cout << "���������, ������� ������� ������ ��������� ���� �������." << endl << endl;

        MyArray myArray = *new MyArray();
        MyInput myInput = *new MyInput();

        int size = myInput.InputIntData("������� ��������� ������ ���� � �������? :", myArray.MIN_VALUE, myArray.MAX_VALUE, myArray.DEFAULT_COUNT_VALUE);

        vector<int> arr = myArray.CreateArray(size);

        int indexMinElem = myArray.GetIndexMinElem(arr);
        int indexMaxElem = myArray.GetIndexMaxElem(arr);

        bool isEqal = indexMinElem == indexMaxElem;

        if (isEqal) {
            SetConsoleTextAttribute(handleConsole, Blue);
            cout << "��� �������� ������� ���������!" << endl;
        }

        SetConsoleTextAttribute(handleConsole, Yellow);
        cout << "�������� ������:" << endl;

        string info;

        for (int i = 0; i < size; ++i) {

            if (!isEqal) {
                if (i == indexMinElem) {
                    SetConsoleTextAttribute(handleConsole, Green);
                    info = " - ����������� �������";
                }
                else if (i == indexMaxElem) {
                    SetConsoleTextAttribute(handleConsole, Green);
                    info = " - ������������ �������";
                }
                else {
                    SetConsoleTextAttribute(handleConsole, Yellow);
                    info = "";
                }
            }

            cout << "[" << i << "] " << arr[i] << info << endl;
        }


        
        
    }

};


int main()
{
    handleConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    setlocale(LC_ALL, "Russian");

    SetConsoleTextAttribute(handleConsole, White);

    cout << "���� 4. ����������� ��� ������ \"������\"" << endl;
    cout << "�������� ������ �������. ��. 110�" << endl;

    bool isGo = true;
    string select;

    while (isGo)
    {
        SetConsoleTextAttribute(handleConsole, White);

        cout << "\n������� ����� ������" << endl;
        cout << "6)	�������� ������� ������������ � ����������� ������� �������." << endl << endl;


        cout << endl << "��� ������ ������� \"0\": ";

        select = GetLine();

        if (select == "6") {
            Task6 task6 = *new Task6();
            task6.Init();
        }/*
        else if (select == "16") {
            Task16 task16 = *new Task16();
            task16.Init();
        }
        else if (select == "36") {
            Task36 task36 = *new Task36();
            task36.Init();
        }
        else if (select == "46") {
            Task46 task46 = *new Task46();
            task46.Init();
        }*/
        else if (select == "0") {
            isGo = false;
        }
        else {
            SetConsoleTextAttribute(handleConsole, Red);
            cout << "\n������������ ������!" << endl;
            SetConsoleTextAttribute(handleConsole, White);
        }

    }
}

