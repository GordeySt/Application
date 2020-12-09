#pragma once

#include <vector>
#include <string>

using namespace std;

string str_tolower(string str)
{
    vector <string> lc = { "à", "á", "â", "ã", "ä", "å", "¸", "æ", "ç", "è", "é", "ê", "ë", "ì", "í", "î", "ï", "ð", "ñ", "ò", "ó", "ô", "õ", "ö", "÷", "ø", "ù", "ý", "þ", "ÿ" };
    vector <char> uc = { 'À', 'Á', 'Â', 'Ã', 'Ä', 'Å', '¨', 'Æ', 'Ç', 'È', 'É', 'Ê', 'Ë', 'Ì', 'Í', 'Î', 'Ï', 'Ð', 'Ñ', 'Ò', 'Ó', 'Ô', 'Õ', 'Ö', '×', 'Ø', 'Ù', 'Ý', 'Þ', 'ß' };

    for (int i = 0; i <= str.length() - 1; i++) {
        for (int u = 0; u <= uc.size() - 1; u++) {
            if (str[i] == uc[u]) {
                str.replace(i, 1, lc[u]);
            }
        }
    }

    return str;
}