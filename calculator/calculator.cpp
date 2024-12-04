#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//Функция для вычисления арктангенса или арккотангенса
vector<double> calculate(const string& operation, const vector<double>& operands, bool radians) {
    vector<double> results;
    if (operation == "arctan") {
        for (double operand : operands) {
            double result = atan(operand);
            results.push_back(radians ? result : result * 180 / M_PI);
        }
    } else if (operation == "arccot") {
        for (double operand : operands) {
            if (operand == 0) {
                return {}; //возвращаем пустой вектор в случае деления на 0
            }
            double result = atan(1.0 / operand);
            results.push_back(radians ? result : result * 180 / M_PI);
        }
    }
    return results;
}


int main(int argc, char* argv[]) {
    if (argc < 3) {
        cerr << "Использование: " << argv[0] << " {arctan|arccot} <число1> [число2] ... [-r]" << endl;
        cerr << " -r: Использовать радианы (по умолчанию градусы)" << endl;
        return 1;
    }

    string operation = argv[1];
    if (operation != "arctan" && operation != "arccot") {
        cerr << "Неверная операция. Используйте 'arctan' или 'arccot'." << endl;
        return 1;
    }

    vector<double> operands;
    bool radians = false;

    for (int i = 2; i < argc; ++i) {
        string arg = argv[i];
        if (arg == "-r") {
            radians = true;
        } else {
            try {
                operands.push_back(stod(arg));
            } catch (const invalid_argument& e) {
                cerr << "Ошибка: Неверный операнд: " << arg << endl;
                return 1;
            }
        }
    }
    if (operands.empty()) {
      cerr << "Ошибка: Не указаны операнды." << endl;
      return 1;
    }

    vector<double> results = calculate(operation, operands, radians);
    if (results.empty()){
        cerr << "Ошибка вычислений (возможно, деление на ноль)." << endl;
        return 1;
    }

    for (double result : results) {
        cout << result << " ";
    }
    cout << endl;

    return 0;
}

