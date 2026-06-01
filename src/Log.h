#pragma once
#include <string>

int LogSectionTitle(const char *message);
int Log(const char *message);
int Log(int value);
int Log(const std::string &message);