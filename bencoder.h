#ifndef BENCODER_H
#define BENCODER_H

#include <vector>
#include <variant>
#include <string>
#include <map>
#include <typeinfo>

using namespace std;

string bencode(int &a){
    string val = to_string(a);

    string result;
    result.push_back('i');
    result.append(val);
    result.push_back('e');

    return result;
}

string bencodehelper(string &a){
    string result;
    result.append(to_string(a.size()));
    result.push_back(':');
    result.append(a);
    return result;
}

string bencode(string &s){
    string digit = "", strs = "";
    string ans;
    for(int i=0; i<s.size(); i++){
        if(isdigit(s[i]) and strs == ""){
            digit+=s[i];
        }
        else if(isdigit(s[i]) and strs != ""){
            string strans = bencodehelper(strs);
            ans+=strans;
            strs = "";
            digit+=s[i];
        }
        else if(!isdigit(s[i]) and digit == ""){
            strs+=s[i];
        }
        else if(!isdigit(s[i]) and digit != ""){
            int value = stoi(digit);
            string intans = bencode(value);
            ans+=intans;
            digit = "";
            strs+=s[i];
        }
    }
    return bencodehelper(ans);
}

string bencode(vector<variant<int, string>> &list){
    if(list.size() == 0){
        return "le";
    }
    int n = list.size();
    string result;
    result.push_back('l');
    for(int i=0; i<n; i++){
        if(holds_alternative<int>(list[i])){
            int value = get<int>(list[i]);
            result.append(bencode(value));
        }
        else if(holds_alternative<string>(list[i])){
            string value = get<string>(list[i]);
            result.append(bencode(value));
        }
    }
    result.push_back('e');
    return result;
}

string bencode(map<string, variant<int, string>> &mp){
    if(mp.empty()){
        return "de";
    }
    string result;
    result.push_back('d');
    for(auto &p:mp){
        string s = p.first;
        result.append(bencode(s));
        if(holds_alternative<int>(p.second)){
            int value = get<int>(p.second);
            result.append(bencode(value));
        }
        else if(holds_alternative<string>(p.second)){
            string value = get<string>(p.second);
            result.append(bencode(value));
        }
    }
    result.push_back('e');
    return result;
}

#endif