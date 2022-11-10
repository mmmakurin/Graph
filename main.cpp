//������ �����:
//n - ���������� ������� (������� ���� ������)
//���_1 ����1 ����2 ����3 - ��� �������� � ����� ��� ������ ��� ������������
//���_2 ����1 ����2
//...
//���_n ����1 ����2 ����n

//������ ������: ������ ��� ���, ��� ������� ����������� �������.


#include <iostream>
#include <vector>
#include <string>
#include <limits>

#include "MatrixGraph.h"

// ���� �����
// ������� ������� ����� �������������� ����� � ���������� ������, ���� ���� �� ����� ����������
int inputNumber() {
    const string ERROR_MSG = "The number must be an integer and greater than zero";
    const string INPUT_MSG = "Enter the number of people (positive integer): ";
    int number;
    while (true) {
        cout << INPUT_MSG;
        string number_str;
        cin >> number_str;
        try {
            number = stoi(number_str);
            if (number > 0) {
                break;
            }
        } catch (exception e) {
            cout << ERROR_MSG << endl;
        }
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return number;
}

// ������� ������� ����� ������ ����, ������������ �������� delim,
// � ���������� �����, ���������� � ������
vector<string> inputStrings(const string& delim = " ") {
    string str;
    getline(cin, str);
    size_t pos;
    string token;
    vector<string> strings;
    while ((pos = str.find(delim)) != string::npos) {
        token = str.substr(0, pos);
        strings.push_back(token);
        str.erase(0, pos + delim.length());
    }
    strings.push_back(str);
    return strings;
}

// ������� ������� ������ ������� �������� � �������
// ��� -1, ���� ������� �� ������
int findIndexByValue(const vector<string>& vec, const string& value) {
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i] == value) {
            return i;
        }
    }
    return -1;
}


int main() {
    const string INPUT_LIST_MSG = "Now for each person you need to enter a list of his friends. For each person, the input begins with a new line.";
    const string INPUT_FORMAT_MSG = "The input format: Name1 FriendName1 FriendName2 ... FriendName_n";
    const string INPUT_EXAMPLE_MSG = "Example: Ivan Tosha Dasha (where Ivan - name of person, Tosha and Dasha - his friends)"; // ��� ������ �� �����

    int people_number = inputNumber(); // ������ ���������� �����
    vector<string> persons;
    auto* graph_matrix = new CMatrixGraph(people_number); // ������ ������ ���� ��� �������� ����������

    cout << INPUT_LIST_MSG << endl;
    cout << INPUT_FORMAT_MSG << endl;
    cout << INPUT_EXAMPLE_MSG << endl;
    for (int i = 0; i < people_number; i++) {
        vector<string> names = inputStrings(); // �������� ������ ���
        if (names.size() < 2) { // ���������� ������, ���� ���� ��������
            cout << "Wrong input: " << INPUT_FORMAT_MSG  << endl;
            continue;
        }
        string new_person_name = names.front(); // ���� ������ ������� - ��� ��������
        names.erase(names.begin());
        // ���������� ����� �������, �������������� ������� �����
        int new_person_index = findIndexByValue(persons, new_person_name);
        if (new_person_index == -1) {
            persons.push_back(new_person_name);
            new_person_index = persons.size() - 1;
        }
        // ���������� ������ ������, �������������� ������ ��� ������
        for (auto & person_friend : names) {
            int person_friend_index = findIndexByValue(persons, person_friend);
            if (person_friend_index == -1) {
                persons.push_back(person_friend);
                person_friend_index = persons.size() - 1;
            }
            // ��������� ����� �������-���� � ����
            graph_matrix->AddEdge(new_person_index, person_friend_index);
            graph_matrix->AddEdge(person_friend_index, new_person_index);
        }
    }

    // ������� ���������� ���������� ����� ����� ��������� �����
    int** distance_matrix = graph_matrix->getShortestDistanceMatrix();
    int max_distance = 3; // ������������ ���������� = 3
    for (int i = 0; i < people_number; i++) {
        for (int j = i + 1; j < people_number; j++) {
            if (distance_matrix[i][j] <= max_distance) {
                cout << persons[i] << " " << persons[j] << endl; // ������� ���� �������������� ���
            }
        }
    }
    delete graph_matrix;
    delete distance_matrix;
    return 0;
}
