#ifndef __BENCODER_H_INCLUDED__
#define __BENCODER_H_INCLUDED__

#include<bits/stdc++.h>

string bencode(int &a){
    string val = to_string(a);
    string res = 'i' + val + 'e';

    return res;
}

string bencodehelper(string &a){
    return to_string(a.size()) + ':' + a;
}

string bencode(string &a){
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



#endif