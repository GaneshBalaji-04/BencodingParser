#ifndef __BENCODER_H_INCLUDED__
#define __BENCODER_H_INCLUDED__

#include <vector>
#include <any>
#include <string>
#include <map>
#include <typeinfo>

using namespace std;

string bencode(int &a){
    string val = to_string(a);
    string res = 'i' + val + 'e';

    return res;
}

string bencodehelper(string &a){
    return to_string(a.size()) + ':' + a;
}

string bencode(string &s){
    string digit = "", strs = "";
    string ans;
    for(int i=0; i<a.size(); i++){
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
    return ans;
}

string bencode(vector<any> &list){
    int n = list.size();
    string result = "l";
    for(int i=0; i<n; i++){
        if(typeid(list[i]) == typeid(int)){
            int value = any_cast<int>(list[i]);
            result.append(bencode(value));
        }
        else if(typeid(list[i]) == typeid(string)){
            string str = any_cast<string>(list[i]);
            result.append(bencode(str));
        }
    }
    result.push_back('e');
    return result;
}

string bencode(map<string, any> &mp){
    if(mp.empty()){
        return "de";
    }
    string result;
    result.push_back('d');
    for(auto &p:mp){
        if(typeid(p.second) == typeid(int)){
            int value = any_cast<int>(p.second);
            result.append(bencode(value));
        }
        else if(typeid(p.second) == typeid(string)){
            string str = any_cast<string>(p.second);
            result.append(bencode(str));
        }
    }
    result.push_back('e');
    return result;
}

#endif