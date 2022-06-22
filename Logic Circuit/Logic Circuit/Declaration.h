#pragma once
#include "Var.h"
#include "VarIn.h"
#include "Cable.h"

//Functions
void DrawVariables(const int& spacing, const VarIn<Var>& vars, int& spacHeight, Graphics& graphics);
void DrawComponent(const bool& energized, const GateType& type, const int& x, const int& y, Graphics& graphics);
void DrawCable(Pen& pen, const int& x, const int& y, const int& xF, const int& yF, Graphics& graphics);
void DrawConnection(const int&, const int&, const int&, Brush&, Graphics&);
