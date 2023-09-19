#include <iostream>
#include <array>
#include <random>
#include <string>
#include <time.h>
#include <vector>

using namespace std;
bool more(array<bool, 10> key, array<bool, 10> to_compare) {
    bool g = false, l = false;
    for (int sign = 9; sign != 0; sign--) {
        g = g || (!key[sign] && to_compare[sign] && !l);
        l = l || (key[sign] && !to_compare[sign] && !g);
    }
    return g > l;
}

array<array<bool, 10>, 10> filler() {
    array<array<bool, 10>, 10> result;
    srand(time_t(NULL));
    for (int first_iterator = 0; first_iterator < 10; first_iterator++) {
        for (int second_iterator = 0; second_iterator < 10; second_iterator++) {
            result[first_iterator][second_iterator] = rand() % 2;
        }
    }
    return result;
}

array<bool, 10> key_input() {
    array<bool, 10> key;
    bool current;
    for (int first_iterator = 0; first_iterator < 10; first_iterator++) {
        cin >> current;
        key[first_iterator] = current;
    }
    return key;
}

void search_between(array<bool, 10>  upper_limit, array<bool, 10> lower_limit, array<array<bool, 10>, 10> full_table) {
    array <bool, 10> check_box = { true, true, true, true, true, true, true, true, true, true };
    for (int iteration = 0; iteration < 10; iteration++) {
        if (more(upper_limit, full_table[iteration]) || more(full_table[iteration], lower_limit)) {
            check_box[iteration] = false;
        }
    }
    for (int row = 0; row < 10; row++) {
        if (check_box[row]) {
            for (int sign = 0; sign < 10; sign++)
                cout << full_table[row][sign] << " ";
            cout << endl;
        }
    }
}

bool xor_search(array<bool, 10> current) {
    bool current_condition = false;
    for (int sign = 0; sign < 10; sign++) {
        current_condition = current_condition ^ current[sign];
    }
    return current_condition;
}

bool or_search(array<bool, 10> current) {
    bool current_condition = false;
    for (int sign = 0; sign < 10; sign++) {
        current_condition = current_condition || current[sign];
    }
    return current_condition;
}

bool equal_search(array<bool, 10> current) {
    bool current_condition = false;
    for (int sign = 0; sign < 10; sign++) {
        current_condition = current_condition == current[sign];
    }
    return current_condition;
}

bool and_search(array<bool, 10> current) {
    bool current_condition = false;
    for (int sign = 0; sign < 10; sign++) {
        current_condition = current_condition == current[sign];
    }
    return current_condition;
}

void choise_interface(array<array<bool, 10>, 10> full_table) {
    int choise;
    vector<array<bool, 10>> result;
    cout << "Input which operation you chose:\n1)xor\n2)or\n3)and\n4)equal" << endl;
    cin >> choise;
    switch (choise)
    {
    case 1:for (int iteration = 0; iteration < 10; iteration++) {
        if (xor_search(full_table[iteration]))
            result.push_back(full_table[iteration]);
    } break;
    case 2:for (int iteration = 0; iteration < 10; iteration++) {
        if (or_search(full_table[iteration]))
            result.push_back(full_table[iteration]);
    } break;
    case 3:for (int iteration = 0; iteration < 10; iteration++) {
        if (and_search(full_table[iteration]))
            result.push_back(full_table[iteration]);
    } break;
    case 4:for (int iteration = 0; iteration < 10; iteration++) {
        if (equal_search(full_table[iteration]))
            result.push_back(full_table[iteration]);
    } break;
    default:
        break;
    }
    for (int variation = 0; variation < result.size(); variation++) {
        for (int sign = 0; sign < 10; sign++) {
            cout << result[variation][sign] << " ";
        }
        cout << endl;
    }
}

int main()
{
    string user_input;
    array<array<bool, 10>, 10> full_table = filler();
    array<bool, 10>  upper_limit, lower_limit;

    while (user_input != "Y")
    {
        cout << "Whole table" << endl;
        for (int variation = 0; variation < full_table.size(); variation++) {
            for (int sign = 0; sign < 10; sign++) {
                cout << full_table[variation][sign] << " ";
            }
            cout << endl;
        }
        cout << "Input first search key (10 numbers of 0 and 1)" << endl;
        upper_limit = key_input();
        cout << "Tnput second search key (10 numbers of 0 and 1)" << endl;
        lower_limit = key_input();
        search_between(upper_limit, lower_limit, full_table);
        choise_interface(full_table);
        cout << "Input Y if you want to exit" << endl;
    }
}

