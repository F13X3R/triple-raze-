#include <iostream>
using namespace std;

template <typename T>
bool validInput(T& var) {
    if (!(cin >> var)) {
        cin.clear();
        cin.ignore(10000, '\n');
        return false;
    }
    return true;
}

void input(int X[100][100], int Y[100], int& n, int& m, int& k) {
    cout << "Введите размеры матрицы (n m): ";
    while (true) {
        if (validInput(n) && validInput(m) && n > 0 && m > 0) {
            break;
        }
        cout << "Неверный ввод. Попробуйте снова (n m): ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "Введите элементы матрицы X:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            while (true) {
                if (validInput(X[i][j])) {
                    break;
                }
                cout << "Неверный ввод. Попробуйте снова (элемент X[" << i << "][" << j << "]): ";
                cin.clear();
                cin.ignore(10000, '\n');
            }
        }
    }

    cout << "Введите размер массива Y (k): ";
    while (true) {
        if (validInput(k) && k > 0) {
            break;
        }
        cout << "Неверный ввод. Попробуйте снова (k): ";
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "Введите элементы массива Y:\n";
    for (int i = 0; i < k; i++) {
        while (true) {
            if (validInput(Y[i])) {
                break;
            }
            cout << "Неверный ввод. Попробуйте снова (элемент Y[" << i << "]): ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
    }
}

void findBounds(int row[], int m, int& firstEven, int& lastOdd) {
    firstEven = -1;
    lastOdd = -1;

    for (int i = 0; i < m; i++) {
        if (row[i] % 2 == 0) {
            firstEven = i;
            break;
        }
    }

    for (int i = m - 1; i >= 0; i--) {
        if (row[i] % 2 != 0) {
            lastOdd = i;
            break;
        }
    }
}

bool inArray(int val, int Y[], int k) {
    for (int i = 0; i < k; i++) {
        if (Y[i] == val) {
            return true;
        }
    }
    return false;
}

void collect(int row[], int m, int firstEven, int lastOdd, int Y[], int k, int Z[], int& ZIndex) {
    if (firstEven != -1 && lastOdd != -1 && firstEven < lastOdd) {
        for (int i = firstEven + 1; i < lastOdd; i++) {  // Элементы между первым четным и последним нечетным
            if (inArray(row[i], Y, k)) {
                Z[ZIndex++] = row[i];
            }
        }
    }
}

bool checkEO(int Y[], int k) {
    bool hasEven = false;
    bool hasOdd = false;
    
    for (int i = 0; i < k; i++) {
        if (Y[i] % 2 == 0) {
            hasEven = true;
        }
        if (Y[i] % 2 != 0) {
            hasOdd = true;
        }
    }

    return hasEven && hasOdd;
}

void calc(int X[100][100], int Y[100], int n, int m, int k, int Z[10000], int& ZIndex) {
    if (!checkEO(Y, k)) {
        cout << "Ошибка: В массиве Y должны быть и четные, и нечетные числа!" << endl;
        return;
    }

    ZIndex = 0;

    for (int i = 0; i < n; i++) {
        int firstEven, lastOdd;
        findBounds(X[i], m, firstEven, lastOdd);
        collect(X[i], m, firstEven, lastOdd, Y, k, Z, ZIndex);
    }
}

void output(int Z[], int ZIndex) {
    cout << "Результирующий массив Z:\n";
    if (ZIndex == 0) {
        cout << "Нет элементов, подходящих под критерии.\n";
    } else {
        for (int i = 0; i < ZIndex; i++) {
            cout << Z[i] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n, m, k;
    int X[100][100];
    int Y[100];
    int Z[10000];
    int ZIndex = 0;

    input(X, Y, n, m, k);
    calc(X, Y, n, m, k, Z, ZIndex);
    output(Z, ZIndex);

    return 0;
}
