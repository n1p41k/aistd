#include <iostream>
#include <vector>
using std::cin;
using std::cout;
using std::vector;
using std::string;
using std::endl;

int* TAB_generate(string text, string substring) {
    int len_t = text.length(), len_s = substring.length();
    int* TAB = new int[256];
    for (int i = 0; i < len_t; i++) TAB[text[i]] = len_s;
    for (int i = 0; i < len_s; i++) TAB[substring[i]] = len_s - i - 1;
    return TAB;
}

int BM_search(string text, string substring, int* TAB, int start = 0, int end = -1) {
    if (end == -1) end = text.length();
    int len_s = substring.length();
    int i, j, k = 0;
    for (i = start + len_s - 1, j = len_s - 1; i <= end; i = k + TAB[text[k]]) {
        for (k = i, j = len_s - 1; j >= 0 && text[k] == substring[j];) {
            k--;
            j--;
        }
        if (j < 0) return k + 1;
        if (k >= end) return -1;
    }
    if (i >= end && j < 0) return k + 1;
    else return -1;
}

vector<int> BM_search_in_range(string text, string substring, int* TAB, int start, int end) {
    vector<int> Entrance;
    int  entrance = BM_search(text, substring, TAB, start, end);
    if (entrance < 0) return Entrance;
    while (entrance >= 0)
    {
        Entrance.push_back(entrance);
        start = entrance + 1;
        entrance = BM_search(text, substring, TAB, start, end);
    }
    return Entrance;
}

    vector<int> BM_search_all(string text, string substring, int* TAB) {
    return BM_search_in_range(text, substring, TAB, 0, text.length());
}

int main() {
    string text = "std::move_iterator is an iterator adaptor which behaves exactly like the underlying iterator", substring = "tor";
    cout << "Text: " << text << ", substring: " << substring << endl;
    int* TAB = TAB_generate(text, substring);
    int first = BM_search(text, substring, TAB);
    if (first < 0) cout << "No entrance";
    else cout << "First entrance index: " << first << endl;
    int start, end;
    cout << "Enter the begining of search: ";
    cin >> start;
    cout << ". Enter the ending of search: ";
    cin >> end;
    vector<int> Entrance = BM_search_in_range(text, substring, TAB, start, end);
    if (Entrance.size() == 0) cout << "No entrance in range(" << start << ";" << end << ")." << endl;
    else {
        cout << "Indexes of all entrance in range(" << start << ";" << end << "): ";
        for (int el : Entrance)
            cout << el << " ";
        cout << "\n";
    }
    Entrance = BM_search_all(text, substring, TAB);
    if (Entrance.size() == 0) cout << "No entrance in al text";
    else {
        cout << "Indexes of all entrance: ";
        for (int el : Entrance)
            cout << el << " ";
        cout << "\n";
    }
    delete[] TAB;
}