#include "myHeader.h"
#include "VarIn.h"
#include "Var.h"

void DrawConnection(const int& x, const int& y, const int& diameter, Brush& brush, Graphics& graphics)
{
	int midX(x - diameter / 2), midY(y - diameter / 2);
	graphics.FillEllipse(&brush, midX, midY, diameter, diameter);
}

void DrawCable(Pen& pen, const int& x, const int& y, const int& xF, const int& yF, Graphics& graphics)
{
	graphics.DrawLine(&pen, x, y, xF, yF);
}

void DrawComponent(const bool& energized, const GateType& type, const int& x, const int& y, Graphics& graphics)
{
	Pen pen(Color(energized ? 255 : 0, 0, 0), (REAL)3);
	const int xR = x - (szComponent.Width / 2);
	switch (type)
	{
	case AND:
		
		break;
	case OR:
		break;

	case NOT: 
	{
		const int diaCir = (int)szComponent.Height*0.4F;
		Point dPos[] = {
			Point(xR, y),
			Point(xR + szComponent.Width, y),
			Point(x, y + szComponent.Height-8),
			Point(xR, y)
		};
		graphics.DrawLines(&pen, dPos, 4);
		graphics.DrawEllipse(
			&pen, (x- diaCir/2), y + szComponent.Height - diaCir,
			szComponent.Height - (szComponent.Height - diaCir),
			szComponent.Height - (szComponent.Height - diaCir));
	}
		break;

	default:
		break;
	}
}

void DrawVariables(const int& spacing, const VarIn<Var>& vars, int& spacHeight, Graphics& graphics)
{
	const int spacLine = spacing * 2;

	Font font(L"Comic-Sans", 12, FontStyleBold);
	Pen newPen(Color(0, 0, 0), 3.F);
	for (size_t i = 0; i < vars.size(); i++) {
		SolidBrush newBrush(Color(vars[i].energized ? 255 : 0, 0, 0));
		graphics.DrawString(
			&nameVar[i], 1,
			&font, PointF((REAL)spacLine * (i + 1) - 8, 0),
			&newBrush);
		graphics.DrawRectangle(&newPen, vars[i].rect);
	}
}