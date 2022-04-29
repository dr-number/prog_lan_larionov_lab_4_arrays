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
#include <random>

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
                cout << endl << xStr + " - не число!" << endl << endl;
            }
            else if (!isNegative && result <= 0) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << endl << "Число должно быть больше нуля!" << endl << endl;
            }
            else
                break;
        }

        return result;
    }

    int InputIndex(string text, int max) {

        string xStr = "";
        double x = 0, result = 0;
        bool isNumber = true;

        while (true) {

            SetConsoleTextAttribute(handleConsole, White);
            cout << text;

            xStr = GetLine();

            try {
                result = stoi(xStr.c_str());
                isNumber = true;
            }
            catch (...) {
                isNumber = false;
            }

            if (!isNumber) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << endl << xStr + " - не число!" << endl << endl;
            }
            else if (result < 0) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << endl << "Число не должно быть меньше нуля!" << endl << endl;
            }
            else if (result > max) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << endl << "Число должно лежать в промежутке [0; " << max << "]!" << endl << endl;
            }
            else
                break;
        }

        return result;
    }

    int InputIntData(string text, int min, int max, bool isNegative = false) {

        double result;

        while (true) {
            result = InputData(text);

            if (result != (int)result) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << endl << "Число должно быть целым!" << endl << endl;
            }
            else if (!isNegative && (result < min || result > max)) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << endl << "Число должно лежать в промежутке [" << min << "; " << max << "]!" << endl << endl;
            }
            else
                break;
        }

        return result;
    }

};

class MyQuestion {

public:
    const string QUESTION_RANDOM_DATA = "Сгенерировать данные случайным образом [y/n]?";
    const string QUESTION_IN_ORDER_DATA = "Взять числа по порядку [y/n]?";

    bool isQuestion(string textQuestion) {

        cout << textQuestion << endl;
        string answer = GetLine();

        transform(answer.begin(), answer.end(), answer.begin(), tolower);
        return answer == "y" || answer == "";
    }
};

class MyRandom {

public:
    const double MIN_RANDOM = 10, MAX_RANDOM = 1000;

    double GetRandom(int min, int max) {

        random_device random_device; // Источник энтропии.
        mt19937 generator(random_device()); // Генератор случайных чисел.

        // (Здесь берется одно инициализирующее значение, можно брать больше)
        uniform_int_distribution<> distribution(min, max); // Равномерное распределение [min, max]

        return distribution(generator); 
      
        //return rand() % (max - min) - min;
        //return rand() % max + min;
    }

};

class MyArray {
public:
    int const MIN_VALUE = -10000;
    int const MAX_VALUE = 10000;

    int const DEFAULT_COUNT_VALUE = 50;

    int const MIN_COUNT = 5;
    int const MAX_COUNT = 10000;

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
            arr.push_back(myInput.InputIntData("Введите целое число (" + to_string(i + 1) + " из " + to_string(n) + "): ", minValue, maxValue, true));

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

    vector <int> CreateArray() {
        MyInput myInput = *new MyInput();
        int size = myInput.InputIntData("Сколько элементов должно быть в массиве?: ", MIN_COUNT, MAX_COUNT);
        return CreateArray(size);
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

class MyMatrix {
public:
    int const MIN_VALUE = -10000;
    int const MAX_VALUE = 10000;

    int const DEFAULT_COUNT_VALUE = 50;

    int const MIN_COL = 5;
    int const MAX_COL = 10000;

    int const MIN_ROW = 5;
    int const MAX_ROW = 10000;

    int const STR_WIDTH = 8;

    struct coordinate {
        public:
            int n;
            int m;
    };

    struct interval {
    public:
        coordinate min;
        coordinate max;
    };

    bool isQual(coordinate a, coordinate b) {
        bool n = a.n == b.n;
        bool m = a.m == b.m;
        return n && m;
    }

    vector <vector <int>> CreateRandomArray(int n, int m, int minValue, int maxValue) {

        vector <vector <int>> arr(n, vector <int>(m));
        MyRandom myRandom = *new MyRandom();

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                arr[i][j] = myRandom.GetRandom(minValue, maxValue);

        return arr;
    }

    vector <vector <int>> CreateInputArray(int n, int m, int minValue, int maxValue) {

        vector <vector <int>> arr(n, vector <int>(m));
        MyInput myInput = *new MyInput();

        int size = m * n;
        int num = 1;

        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j) {
                arr[i][j] = myInput.InputIntData("Введите целое число (" + to_string(num) + " из " + to_string(size) + "): ", minValue, maxValue, true);
                ++num;
            }

        return arr;
    }

    vector <vector <int>> CreateArray(int n, int m, int minValue, int maxValue) {

        MyQuestion myQuestion = *new MyQuestion();

        bool isRandomData = myQuestion.isQuestion(myQuestion.QUESTION_RANDOM_DATA);

        if (isRandomData)
            return CreateRandomArray(n, m, minValue, maxValue);

        return CreateInputArray(n, m, minValue, maxValue);
    }

    vector <vector <int>> CreateArray(int n, int m) {
        return CreateArray(n, m, MIN_VALUE, MAX_VALUE);
    }

    vector <vector <int>> CreateArray() {

        MyInput myInput = *new MyInput();
        int n = myInput.InputIntData("Сколько строк должно быть в массиве?: ", MIN_ROW, MAX_ROW);
        int m = myInput.InputIntData("Сколько столбцов должно быть в массиве?: ", MIN_COL, MAX_COL);

        return CreateArray(n, m);
    }

    void printHeader(vector <vector <int>> arr) {

        int countCol = arr[0].size();
        cout << "   ";

        for (int j = 0; j < countCol; ++j)
            cout << setw(6) << "[" << j << "] ";

        cout << endl;
    }

    interval GetCoordinateMinMax(vector <vector <int>> matrix) {

        int col = matrix[0].size();
        int row = matrix.size();

        int min = matrix[0][0];
        int max = matrix[0][0];

        coordinate indexMin;
        indexMin.n = 0;
        indexMin.m = 0;

        coordinate indexMax;
        indexMax.n = 0;
        indexMax.m = 0;

        int item;


        for (int i = 0; i < row; ++i)
            for (int j = 0; j < col; ++j) {

                item = matrix[i][j];

                if (item < min) {
                    min = item;
                    indexMin.n = i;
                    indexMin.m = j;
                }

                if (item > max) {
                    max = item;
                    indexMax.n = i;
                    indexMax.m = j;
                }
            }



        interval result = *new interval();

        result.min = indexMin;
        result.max = indexMax;

        return result;
    }

};

class Task6 {

public:
    void Init() {

        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handleConsole, White);

        cout << "Поменять местали максимальный и минимальный элемент массива." << endl << endl;

        MyArray myArray = *new MyArray();
        vector<int> arr = myArray.CreateArray();

        int size = arr.size();

        int indexMinElem = myArray.GetIndexMinElem(arr);
        int indexMaxElem = myArray.GetIndexMaxElem(arr);

        bool isEqal = indexMinElem == indexMaxElem;

        if (isEqal) {
            SetConsoleTextAttribute(handleConsole, Blue);
            cout << "Все элементы массива одинаковы!" << endl << endl;
        }

        SetConsoleTextAttribute(handleConsole, Yellow);
        cout << "Исходный массив:" << endl;

        string info;

        for (int i = 0; i < size; ++i) {

            if (!isEqal) {
                if (i == indexMinElem) {
                    SetConsoleTextAttribute(handleConsole, Green);
                    info = " - минимальный элемент";
                }
                else if (i == indexMaxElem) {
                    SetConsoleTextAttribute(handleConsole, Green);
                    info = " - максимальный элемент";
                }
                else {
                    SetConsoleTextAttribute(handleConsole, Yellow);
                    info = "";
                }
            }

            cout << "[" << i << "] " << arr[i] << info << endl; //форматированный вывод
        }

        if (!isEqal) {

            int item = 0;
            SetConsoleTextAttribute(handleConsole, Blue);
            cout << endl << "Преобразованный массив:" << endl;

            for (int i = 0; i < size; ++i) {

                if (i == indexMinElem) {
                    SetConsoleTextAttribute(handleConsole, Green);
                    item = arr[indexMaxElem];
                    info = " - максимальный элемент";
                }
                else if (i == indexMaxElem) {
                    SetConsoleTextAttribute(handleConsole, Green);
                    item = arr[indexMinElem];
                    info = " - минимальный элемент";
                }
                else {
                    SetConsoleTextAttribute(handleConsole, Yellow);
                    info = "";
                    item = arr[i];
                }

                cout << "[" << i << "] " << item << info << endl;
            }
        }
 
    }

};

class Task26 {
public:
    void Init() {

        HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(handleConsole, White);

        cout << "Поменять местали указанные элементы массива." << endl << endl;

        MyArray myArray = *new MyArray();
        vector<int> arr = myArray.CreateArray();

        int size = arr.size();
        MyInput myInput = *new MyInput();

        int index1, index2;

        while (true) {

            index1 = myInput.InputIndex("Введите индекс №1: ", size - 1);
            index2 = myInput.InputIndex("Введите индекс №2: ", size - 1);

            if (index1 == index2) {
                SetConsoleTextAttribute(handleConsole, Red);
                cout << "Индексы не должны совпадать!" << endl << endl;
            }
            else {
                SetConsoleTextAttribute(handleConsole, White);
                break;
            }
            
        }

        SetConsoleTextAttribute(handleConsole, Yellow);
        cout << endl << "Исходный массив:" << endl;

        SetConsoleTextAttribute(handleConsole, White);

        for (int i = 0; i < size; ++i) {

            if (i == index1 || i == index2) 
                SetConsoleTextAttribute(handleConsole, Green);
            else
                SetConsoleTextAttribute(handleConsole, White);

            cout << "[" << i << "] " << arr[i] << endl; //форматированный вывод
        }


        SetConsoleTextAttribute(handleConsole, Yellow);
        cout << endl << "Поменять местали элементы массива под индексами " << index1 << " и " << index2 << endl << endl;
        cout << "Преобразованный массив:" << endl;

        SetConsoleTextAttribute(handleConsole, White);

        int item;

        for (int i = 0; i < size; ++i) {

            if (i == index1) {
                SetConsoleTextAttribute(handleConsole, Green);
                item = arr[index2];
            }
            else if (i == index2) {
                SetConsoleTextAttribute(handleConsole, Green);
                item = arr[index1];
            }
            else {
                SetConsoleTextAttribute(handleConsole, White);
                item = arr[i];
            }

            cout << "[" << i << "] " << item << endl; //форматированный вывод
        }

    }
};

class Task36 {
private:
    bool isNegativeMatrix(vector <vector <int>> matrix, bool isPrint = true) {

        int col = matrix[0].size();
        int row = matrix.size();

        int countNegative = 0;
        int countPositive = 0;

        int item;

        MyMatrix myMatrix = *new MyMatrix();

        if (isPrint)
            myMatrix.printHeader(matrix);

        for (int i = 0; i < row; ++i) {

            if (isPrint) {
                SetConsoleTextAttribute(handleConsole, Yellow);
                cout << "[" << i << "] " << setw(myMatrix.STR_WIDTH);
            }

            for (int j = 0; j < col; ++j) {

                item = matrix[i][j];

                if (item > 0) {
                    SetConsoleTextAttribute(handleConsole, Green);
                    ++countPositive;
                }
                else if (item < 0) {
                    SetConsoleTextAttribute(handleConsole, Red);
                    ++countNegative;
                }
                else
                    SetConsoleTextAttribute(handleConsole, White);

                if (isPrint)
                    cout << setw(myMatrix.STR_WIDTH) << item << " ";

            }

            if (isPrint)
                cout << endl;
        }

        if (isPrint) {
            SetConsoleTextAttribute(handleConsole, White);
            cout << "\nВсего элементов в массиве:         " << col * row << endl;

            SetConsoleTextAttribute(handleConsole, Green);
            cout << "Положительных элементов в массиве: " << countPositive << endl;

            SetConsoleTextAttribute(handleConsole, Red);
            cout << "Отрицательных элементов в массиве: " << countNegative << endl << endl;
        }

        return countNegative > countPositive;
    }

    vector <vector <int>> GetMatrixPositiveToZero(vector <vector <int>> matrix, bool isPrint = true) {

        int col = matrix[0].size();
        int row = matrix.size();

        MyMatrix myMatrix = *new MyMatrix();

        if (isPrint)
            myMatrix.printHeader(matrix);

        for (int i = 0; i < row; ++i) {

            if (isPrint) {
                SetConsoleTextAttribute(handleConsole, Yellow);
                cout << "[" << i << "] " << setw(myMatrix.STR_WIDTH);
            }

            for (int j = 0; j < col; ++j) {

                if (matrix[i][j] > 0)
                    SetConsoleTextAttribute(handleConsole, Green);
                else {
                    SetConsoleTextAttribute(handleConsole, White);
                    matrix[i][j] = 0;
                }
               
                if (isPrint)
                    cout << setw(myMatrix.STR_WIDTH) << matrix[i][j] << " ";

            }

            if (isPrint)
                cout << endl;
        }

        return matrix;
    }

public:
    void Init() {

        SetConsoleTextAttribute(handleConsole, White);
        cout << "В матрице заменить все положительные элементы нулями," << endl;
        cout << "если количество отрицательных элементов окажется больше, чем количество положительных элементов." << endl << endl;

        MyMatrix myMatrix = *new MyMatrix();
        vector <vector <int>> matrix = myMatrix.CreateArray();
        
        SetConsoleTextAttribute(handleConsole, Yellow);
        cout << "\nИсходная матрица:" << endl << endl;

      
        if(isNegativeMatrix(matrix, true)){

            SetConsoleTextAttribute(handleConsole, Yellow);
            cout << "Количество отрицательных элементов больше, чем количество положительных элементов." << endl;
            cout << "Заменяем все положительные элементы матрицы нулями." << endl << endl;

            cout << "Преобразованная матрица:" << endl << endl;

            GetMatrixPositiveToZero(matrix, true);
        }
        else {
            SetConsoleTextAttribute(handleConsole, Red);
            cout << "Условие не выполняется оставляем все как есть" << endl;
        }

    }
};

class Task46 {
public:
    void Init() {

        SetConsoleTextAttribute(handleConsole, White);
        cout << "Поменять местали максимальный и минимальный элементы матрицы." << endl;
      
        MyMatrix myMatrix = *new MyMatrix();
        vector <vector <int>> matrix = myMatrix.CreateArray();

        SetConsoleTextAttribute(handleConsole, Yellow);
        cout << "\nИсходная матрица:" << endl << endl;

        MyMatrix::interval coordMinMax = myMatrix.GetCoordinateMinMax(matrix);

        MyMatrix::coordinate coordMin = coordMinMax.min;
        MyMatrix::coordinate coordMax = coordMinMax.max;

        bool isEqal = myMatrix.isQual(coordMin, coordMax);

        if (isEqal) {
            SetConsoleTextAttribute(handleConsole, Blue);
            cout << "Все элементы массива одинаковы!" << endl << endl;
        }

        SetConsoleTextAttribute(handleConsole, Yellow);
        cout << "Исходный массив:" << endl;

        string info;

        myMatrix.printHeader(matrix);

        int col = matrix[0].size();
        int row = matrix.size();

        for (int i = 0; i < row; ++i) {

            SetConsoleTextAttribute(handleConsole, Yellow);
            cout << "[" << i << "] ";

            for (int j = 0; j < col; ++j) {

                if (!isEqal) {
                    if (i == coordMin.n && j == coordMin.m) {
                        SetConsoleTextAttribute(handleConsole, Red);
                    }
                    else if (i == coordMax.n && j == coordMax.m) {
                        SetConsoleTextAttribute(handleConsole, Green);
                    }
                    else
                        SetConsoleTextAttribute(handleConsole, White);
                }

                cout << setw(myMatrix.STR_WIDTH) << matrix[i][j] << " ";
            }

            cout << endl;
        
        }

        if (!isEqal) {



            SetConsoleTextAttribute(handleConsole, Red);
            cout << "\nМинимальный элемент массива:  [" << coordMin.n << "][" << coordMin.m << "] " << matrix[coordMin.n][coordMin.m] << endl;

            SetConsoleTextAttribute(handleConsole, Green);
            cout << "Максимальный элемент массива: [" << coordMax.n << "][" << coordMax.m << "] " << matrix[coordMax.n][coordMax.m] << endl;
        }

        
    }
};


int main()
{
    handleConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    setlocale(LC_ALL, "Russian");

    SetConsoleTextAttribute(handleConsole, White);

    cout << "Тема 4. Структурный тип данных \"массив\"" << endl;
    cout << "Ларионов Никита Юрьевич. гр. 110з" << endl;

    bool isGo = true;
    string select;

    while (isGo)
    {
        SetConsoleTextAttribute(handleConsole, White);

        cout << "\nВведите номер задачи" << endl;
        cout << "6)	Поменять местали максимальный и минимальный элементы массива." << endl << endl;

        cout << "26) Поменять местали указанные элементы массива." << endl << endl;

        cout << "36) В матрице заменить все положительные элементы нулями," << endl;
        cout << "если количество отрицательных элементов окажется больше, чем количество положительных элементов." << endl << endl;

        cout << "46) Поменять местали максимальный и минимальный элементы матрицы." << endl << endl;

        cout << endl << "Для выхода введите \"0\": ";

        select = GetLine();

        if (select == "6") {
            Task6 task6 = *new Task6();
            task6.Init();
        }/*
        else if (select == "16") {
            Task16 task16 = *new Task16();
            task16.Init();
        }*/
         else if (select == "26") {
            Task26 task26 = *new Task26();
            task26.Init();
        }
        else if (select == "36") {
            Task36 task36 = *new Task36();
            task36.Init();
        }
        else if (select == "46") {
            Task46 task46 = *new Task46();
            task46.Init();
        }
        else if (select == "0") {
            isGo = false;
        }
        else {
            SetConsoleTextAttribute(handleConsole, Red);
            cout << "\nНекорректные данные!" << endl;
            SetConsoleTextAttribute(handleConsole, White);
        }

    }
}

