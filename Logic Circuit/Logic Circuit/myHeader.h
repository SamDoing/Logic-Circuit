#pragma once
#include <windows.h>
#include <objidl.h>
#include <gdiplus.h>
#include <iostream>
#include <vector>

using namespace Gdiplus;
#pragma comment (lib,"Gdiplus.lib")

//Enums
enum GateType { AND, OR, NOT };

//Goblal Variables
extern const WCHAR* nameVar;
const Size szComponent(20, 20);




