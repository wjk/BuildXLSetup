#pragma once

#ifndef WINVER
#define WINVER 0x0A00
#endif

#ifndef _WIN32_MSI
#define _WIN32_MSI 500
#endif

#define WIN32_LEAN_AND_MEAN
// Windows Header Files:
#include <windows.h>
#include <strsafe.h>
#include <msiquery.h>
#include <ShObjIdl.h>

// WiX Header Files:
#include <wcautil.h>

// ATL Header Files:
#include <atlcomcli.h>
#include <atlstr.h>
