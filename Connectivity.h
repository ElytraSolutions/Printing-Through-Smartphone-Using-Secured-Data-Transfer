#pragma once
#pragma once
#pragma once
#include <Windows.h>
#pragma once

#include "Credentials.h"
#include <urlmon.h>
#include <fstream>
#include <iostream>
#include <shellapi.h>
#include <io.h>
#include <future>
#include <wininet.h>
#include <string>
#include <tchar.h>
#include <random>
#include <Shlwapi.h>

#pragma comment(lib, "shlwapi.lib")
#pragma comment(lib, "wininet.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "urlmon.lib")



std::string Query(std::string Url,
	std::string query, INTERNET_PORT securityType);

void DisplayQR(std::string Location);

void Print(std::string File);