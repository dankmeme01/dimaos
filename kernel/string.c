#include "string.h"
#include "memory.h"

int strlen(const string s) {
	int i = 0;
	while (s[i] != '\0') {
		i++;
	}
	return i;
}

string int_to_str(int num) {
	unsigned int size = sizeof(char) * 11;
	string s = (string) malloc(size);
	zero_memory((void*)s, size);

	int i = 0;
	while (num != 0) {
		s[i] = num % 10 + '0';
		num /= 10;
		i++;
	}
	s[i] = '\0';

	string reversed = reverse_str(s);
	free(s);

	return reverse_str(s);
}

// convert a char array into a 32bit int
int str_to_int(const string num) {
	int out = 0;
	int i = 0;
	while (num[i] != '\0') {
		out *= 10;
		out += num[i] - '0';
		i++;
	}

	return out;
}

string reverse_str(const string str) {
	int len = strlen(str);
	string reversed = (string) malloc(sizeof(char) * len);
	int i = 0;
	while (str[i] != '\0') {
		reversed[len - i - 1] = str[i];
		i++;
	}
	reversed[len] = '\0';
	return reversed;
}

string rebase(unsigned int num, int base) {
	if (base <= 1 || base > 64)
		return NULL;

	int length = 0;
	unsigned int numcopy = num;

	while (num != 0) {
		num /= base;
		length += 1;
	}

	num = numcopy;

	string outbuf = (string)malloc(length + 1); // null byte 

	for (int i = 0; i < length; i++) {
		outbuf[i] = BASESTR[num % base];
		num /= 16;

	}

	outbuf[length] = '\0';
	string reversed = reverse_str(outbuf);
	free(outbuf);

	return reversed;
}

string hex(int num) {
	return rebase(num, 16);
}