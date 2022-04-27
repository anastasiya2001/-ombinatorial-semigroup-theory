#include <iostream>
#include <vector>  
#include <set>
#include <map>
#include <string>
#include <algorithm> 
#include <iomanip>


using namespace std;

int Find1(int k, vector <int> bunch, int n) {
    for (int j = 0; j < n; j++) {
        if (k == bunch[j])
            return j;
    }
}

bool Chek_ass(vector<pair<int, int>> res, vector<pair<int, int>> prov) {
    if (res.size() == prov.size()) {
        int c = 0;
        for (int i = 0; i < res.size(); i++) {
            for (int j = 0; j < prov.size(); j++) {
                if (res[i].first == prov[j].first)
                    c++;
            }
        }
        if (res.size() == c)
            return false;
        else return true;
    }
    return true;
}

vector<pair<int, int>> Obed(vector<pair<int, int>> res, vector<pair<int, int>> resSt, int el1, int el2) {
    vector < pair <int, int>> res1;
    for (int i = 0; i < el1; i++)
        res1.push_back(res[i]);
    for (int i = 0; i < el2; i++) {
        int c = 0;
        for (int j = 0; j < res1.size(); j++) {
            if (resSt[i].first == res1[j].first && resSt[i].second == res1[j].second)
                c++;
        }
        if (c == 0)
            res1.push_back(resSt[i]);
    }
    return res1;
}

vector<pair<int, int>> Podpul(vector<vector<int>> Kel, vector<pair<int, int>> subset, vector <int> bunch, int n) {
    vector<pair<int, int>> res = subset;
    vector<pair<int, int>> chek;
    do {
        vector<pair<int, int>> resSt;
        for (int i = 0; i < subset.size(); i++) {
            for (int j = 0; j < res.size(); j++) {
                int k = Kel[subset[i].second][res[j].second];
                resSt.push_back(make_pair(k, Find1(k, bunch, n)));
            }
        }
        chek = res;
        res = Obed(res, resSt, res.size(), resSt.size());
    } while (Chek_ass(res, chek));
    return res;
}

void Zad1() {
    int n, m, el;
    cout << "Введите количество элементов полугруппы S: ";
    cin >> n;
    vector <int> bunch;
    cout << "Введите элементы полугруппы: ";
    for (int i = 0; i < n; i++) {
        cin >> el;
        bunch.push_back(el);
    }
    vector <vector <int>> Kel;
    Kel.resize(n);
    cout << "Введите таблицу Кэлли:\n";
    for (int i = 0; i < n; i++) {
        Kel[i].resize(n);
        for (int j = 0; j < n; j++)
            cin >> Kel[i][j];
    }

    cout << "Введите количество элементов в подмножестве: ";
    cin >> m;
    vector <pair <int, int>> subset;
    cout << "Введите элементы подмножества: ";
    for (int i = 0; i < m; i++) {
        cin >> el;
        int e = Find1(el, bunch, n);
        subset.push_back(make_pair(el, e));
    }

    vector<pair<int, int>> res;
    res = Podpul(Kel, subset, bunch, n);
    sort(res.begin(), res.end());
    cout << "Подполугруппа: {";
    for (int i = 0; i < res.size(); i++)
        if (i != res.size() - 1)
            cout << res[i].first << ", ";
        else cout << res[i].first << "}\n";
}

/*--------*/

vector <vector <int>> MultyMatr(vector <vector <int>> sets, vector <vector <int>> res, int n) {
    vector <vector <int>> res1;
    res1.resize(n);
    for (int i = 0; i < n; i++)
        res1[i].resize(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                if (sets[i][k] == 1 && res[k][j] == 1) {
                    res1[i][j] = 1;
                    break;
                }
                else res1[i][j] = 0;
            }
        }
    }
    return res1;
}

set <vector <vector <int>>> InsMat(set <vector <vector <int>>> sets, int n) {
    for (vector <vector <int>> sets1 : sets)
        for (vector <vector <int>> sets2 : sets) {
            sets.insert(MultyMatr(sets1, sets2, n));
        }
    return sets;
}

void Zad2() {
    int n, m;
    cout << "Введите количество элементов на множестве: ";
    cin >> n;
    cout << "Введите количество матриц в порождающем множестве: ";
    cin >> m;

    vector <vector <int>> matrix;
    map <char, vector <vector <int>>> in_m;
    map <vector <vector <int>>, char> out_m;
    matrix.resize(n);
    set <vector <vector <int>>> sets;
    int k = 0;
    for (int i = 1; i <= m; i++) {
        cout << "Введите матрицу " << char(65 + k) << "\n";
        for (int e = 0; e < n; e++) {
            matrix[e].resize(n);
            for (int j = 0; j < n; j++)
                cin >> matrix[e][j];
        }
        sets.insert(matrix);
        in_m.insert(make_pair(char(65 + k), matrix));
        out_m.insert(make_pair(matrix, char(65 + k++)));
    }

    set <vector <vector <int>>> group;
    group = sets;
    int kout = 0;
    while (true) {
        for (auto i = sets.begin(); i != sets.end(); i++) {
            for (auto j = sets.begin(); j != sets.end(); j++) {
                vector <vector <int>> newMatrix = MultyMatr(*i, *j, n);

                if (group.find(newMatrix) == group.end()) {
                    in_m.insert(make_pair(char(65 + k + kout), newMatrix));
                    out_m.insert(make_pair(newMatrix, char(65 + k + kout++)));
                    group.insert(newMatrix);
                }
            }
        }

        if (group == sets) {
            group = sets;
            sets = InsMat(sets, n);
            cout << endl;
            cout << "Полученная полугруппа:\n";

            for (vector <vector <int>> res1 : sets) {
                cout << "\n" << out_m[res1] << endl;
                for (int i = 0; i < res1.size(); i++) {
                    cout << "\n";
                    for (int j = 0; j < res1.size(); j++)
                        cout << res1[i][j] << " ";
                }
                cout << endl;
            }

            cout << endl << "Таблица Кэли: \n";
            cout << " ";
            for (int i = 0; i < out_m.size(); i++)
                cout << setw(4) << char(65 + i);
            cout << endl;
            for (int i = 0; i < out_m.size(); i++) {
                cout << char(65 + i) << setw(4);
                for (int j = 0; j < out_m.size(); j++)
                    cout << setw(4) << out_m[MultyMatr(in_m[char(65 + i)], in_m[char(65 + j)], n)];
                cout << endl;
            }
            return;
        }
        else sets = group;
    }

}
/*-------*/

set<string> s, sss, s_1, s_2;
int maksimal = 0;
map<string, string> slowar;
int counter;
string word_2;
vector <vector <string>> kali;

vector<string> Sl(string word) {
    vector<string> new_word;
    for (int i = 0; i < word.size(); ++i)
        new_word.push_back(word.substr(i, 1));
    return(new_word);
}

void New(string word, bool flag, int row, int size) {
    if (sss.find(word) != sss.end() && !flag)
        return;
    vector<string> word_3 = Sl(word);

    int len = 2;
    while (len <= maksimal) {
        for (int i = word_3.size() - 1; i > -1; --i) {
            string probe = "";
            if (len > word.size() || len > i + 1)
                break;
            int j;
            for (j = i; j > i - len; --j)
                probe = word_3[j] + probe;

            if (slowar.find(probe) != slowar.end()) {
                word_2 = "";
                vector<string> probe_ = Sl(slowar[probe]);
                for (int k = 0; k < j; ++k)
                    word_2 = word_2 + word_3[k];
                word_2 = word_2 + slowar[probe];
                for (int k = i + 1; k < word_3.size(); ++k)
                    word_2 = word_2 + word_3[k];

                if (word_2.size() < word.size() && !flag) {
                    sss.insert(word);
                    sss.insert(word_2);
                    return;
                }
                else if (sss.find(word_2) != sss.end() && !flag)
                    return;
                else if (flag && s.find(word_2) != s.end()) {
                    if (kali[row].size() < size)
                        kali[row].push_back(word_2);
                    return;
                }
                else {
                    int check = kali[row].size();
                    New(word_2, flag, row, size);
                    if (flag && kali[row].size() > check)
                        return;
                }
            }
            if (sss.find(word) != sss.end() && !flag)
                return;

            if (flag && s.find(word) != s.end()) {
                if (kali[row].size() <= size)
                    kali[row].push_back(word);
                return;
            }
        }
        ++len;
    }

    if (word_2.size() == word.size() && word_2 < word && sss.find(word) == sss.end() && sss.find(word_2) == sss.end() && !flag) {
        s.insert(word_2);
        s_2.insert(word_2);
        sss.insert(word);
        sss.insert(word_2);
    }
    else if (!flag) {
        s.insert(word);
        s_2.insert(word_2);
        sss.insert(word);
        sss.insert(word_2);
    }
}

void Zad3() {
    maksimal = 0;
    slowar.clear();
    s.clear();
    sss.clear();

    int n, m;
    cout << "Введите количество элементов алфавита: ";
    cin >> n;
    cout << "Введите алфавит: ";
    set<string> alf;
    for (int i = 0; i < n; ++i) {
        string a;
        cin >> a;
        alf.insert(a);
        s.insert(a);
        sss.insert(a);
    }
    cout << "Введите количество определяющих соотношений: ";
    cin >> m;
    cout << "Введите определяющие соотношения (через пробел):\n";
    for (int i = 0; i < m; ++i) {
        string l, r;
        cin >> l;
        cin >> r;
        if (l.size() > maksimal)
            maksimal = l.size();
        if (r.size() > maksimal)
            maksimal = r.size();
        if (l.size() < r.size())
            slowar[r] = l;
        else if (l.size() > r.size())
            slowar[l] = r;
        else {
            if (l < r)
                slowar[r] = l;
            else
                slowar[l] = r;
        }
    }

    int count = 1;
    s_1 = alf;
    while (!s_1.empty()) {
        ++count;
        s_2.clear();
        for (string sit : s_1) {
            for (string buc : alf) {
                string sit_1 = sit + buc;
                word_2 = "";
                New(sit_1, false, 0, -1);
            }
        }
        s_1.clear();
        for (auto str : s)
            if (str.size() == count)
                s_1.insert(str);
    }
    cout << endl;
    cout << "Полученная полугруппа: {";
    for (string res : s)
        cout << res << " ";
    cout << "}\n";
    cout << endl;

    vector <string> gr;
    for (string str : s)
        gr.push_back(str);
    sort(gr.begin(), gr.end());
    int sizes = gr.size();

    kali.resize(sizes);
    for (int i = 0; i < sizes; i++)
        for (int j = 0; j < sizes; j++)
            New(gr[i] + gr[j], true, i, sizes);

    cout << endl << "Таблица Кэли: \n";
    cout << "    ";
    for (int i = 0; i < sizes; i++)
        cout << setw(4) << gr[i];
    cout << endl;
    for (int i = 0; i < sizes; i++) {
        cout << setw(4) << gr[i] << setw(4);
        for (int j = 0; j < sizes; j++)
            cout << kali[i][j] << setw(4);
        cout << endl;
    }
    cout << endl;

}

int main() {
    setlocale(LC_ALL, "Russian");
    for (;;) {
        cout << "1 - Построить подполугруппу по таблице Кэли\n2 - Построить полугруппы бинарных отношений по заданному порождающему множеству\n";
        cout << "3 - Построить полугруппы по порождающему множеству и определяющим соотношениям\n";
        int x;
        cin >> x;
        switch (x) {
        case 1:
            Zad1();
            cout << endl;
            break;
        case 2:
            Zad2();
            cout << endl;
            break;
        case 3:
            Zad3();
            cout << endl;
            break;
        case 4:
            break;
        }
    }

}
