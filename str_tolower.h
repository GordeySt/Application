#pragma once

#include <vector>
#include <string>

using namespace std;

string str_tolower(string str)
{
    vector <string> lc = { "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�", "�" };
    vector <char> uc = { '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�', '�' };

    for (int i = 0; i <= str.length() - 1; i++) {
        for (int u = 0; u <= uc.size() - 1; u++) {
            if (str[i] == uc[u]) {
                str.replace(i, 1, lc[u]);
            }
        }
    }

    return str;
}