#pragma once
#include "stdafx.h"

#define MAX_SUBJECT_WIDTH 128
#define MAX_ID_WIDTH 64
#define MAX_NAME_WIDTH 64
#define MAX_GENDER_WIDTH 32


enum ErrorType {
	SUCCEEDED,
	FILE_ERROR,
	INCORRECT_PASSWORD
};

struct FileHeader {
	int nStudent;
	int nSubject;
	char PasswordDigest[48];
};

struct StudentInfo {
	char id[MAX_ID_WIDTH];
	char name[MAX_NAME_WIDTH];
	char gender[MAX_GENDER_WIDTH];
};