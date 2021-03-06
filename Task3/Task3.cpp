#define _CRT_SECURE_NO_WARNINGS
#include<time.h>
#include<iostream>
#include<cstdio>
#include<string.h>
#include"pch.h"

int main(int argc, char *argv[]) {
	time_t timeSA = 0;
	time_t t1 = 0, t2 = 0;
	char oper_code = 0;
	if (argc != 4) {
		printf("You haven't entered enough arguments \n");
		return -1;
	}
	for (int i = 0; i < argc; i++) { //Цикл считывает каждую переданный аргумент поочередно 
		if (!strcmp(argv[i], "add") || !strcmp(argv[i], "sub")) {
			if (!strcmp(argv[i], "add")) oper_code = 'a';
			else oper_code = 's';
			i++;
			if (!strcmp(argv[i], "min") || !strcmp(argv[i], "hour") || !strcmp(argv[i], "day") || !strcmp(argv[i], "sec")) {
				timeSA = atoi(argv[i + 1]);
				if (!strcmp(argv[i], "min")) timeSA *= 60;
				else if (!strcmp(argv[i], "hour")) timeSA *= 60 * 60;
				else if (!strcmp(argv[i], "day")) timeSA *= 60 * 60 * 24;
			}
			else {
				printf("Warning! You've entered a wrong value");
				return -1;
			}
		}
		else if (!strcmp(argv[i], "diff")) {
			oper_code = 'd';
			for (++i; i < argc; i++) {
				int hour = 0;
				int min = 0;
				int sec = 0;
				if (sscanf(argv[i], "%2d:%2d:%2d", &hour, &min, &sec) != 3 || strlen(argv[i]) != 8 || argv[i][7]<'0' ||
					argv[i][7] > '9' || hour > 23 || min > 59 || sec > 59 || hour < 0 || min < 0 || sec < 0) {
					printf("Please, enter date in format HH:MM:SS");
					return -1;
				}
				int ti = hour * 60 * 60 + min * 60 + sec;
				if (i == 2) t1 = ti; //Время1
				else t2 = ti; //Время2
			}
		}
	}

	if (!oper_code) {
		printf("You lose \n");
		return -1;
	}
	time_t timer = 0;
	struct tm *rawtime;
	switch (oper_code) {
	case 'a':
		time(&timer);
		timer += timeSA;
		break;
	case 's':
		time(&timer);
		timer -= timeSA;
		break;
	case 'd':
		timer = abs(t1 - t2);
		printf("%ld\n", timer);
		break;
	}
	if (timer < 0) { //Если меньше, чем 00 1 января 1970 года - выход
		printf("Can't get result\n");
		return -1;
	}
	rawtime = localtime(&timer);
	printf("%s \n", asctime(rawtime));
	return 0;
}