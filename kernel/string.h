#ifndef DIMAOS_STRING_H
#define DIMAOS_STRING_H

#define string char *
#define BASESTR "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+/"

int strlen(const string s);
string int_to_str(int num);
int str_to_int(const string num);

string reverse_str(const string str);
string rebase(unsigned int num, int base);
string hex(int num);

#endif