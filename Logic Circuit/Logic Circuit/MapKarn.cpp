#include "Classes.h"


void MapKarn::Draw(Graphics& graphics, const Pen& pen, const Font& font, const SolidBrush& brush)
{
	const int letterDisFromY = 17;
	const int letterSpace = 11;
	const int letterDis = 4;
	const int intDis = 7;
	const int lYOverSpac = 1;

	if (szExpVars % 2 == 0)
	{
		int repSz = 1;
		for (size_t i = 0; i < szExpVars / 2; i++) {
			repSz *= 2;
		} repSz--;

		int textSeg1 = 0, textSeg2 = 0;
		const int x = this->x, y = this->y;
		const int resX = this->szTable / this->szExpVars;
		const int resY = this->szTable / (this->szExpVars*2);
		int xR = 0, yR = 0;

		for (size_t i = 0; i <= repSz; i++)
		{

			xR = x + resX * (i + 1);
			yR = y + resY * (i + 1);
			graphics.DrawLine(&pen, xR, y, xR, y + resY * (repSz+2));
			graphics.DrawLine(&pen, x, yR, x + resX * (repSz + 2), yR);

			//Draw lettters
			for (size_t z = 0; z < szExpVars / 2; z++)
			{
				int letterX = xR + (z * letterSpace);
				if (textVars1[textSeg1 + 1] == L'\u0305')
				{
					graphics.DrawString(&textVars1[textSeg1], 2, &font,
						PointF(letterX + (z ? 1.5F : 0),
							 y + resY - letterDisFromY + lYOverSpac), &brush);
					textSeg1 += 2;
				}
				else
				{
					graphics.DrawString(&textVars1[textSeg1], 1, &font,
						PointF(letterX, y + resY - letterDisFromY ), &brush);
					textSeg1++;
				}
			}
			for (size_t z = 0; z < szExpVars / 2; z++)
			{
				int letterX = x + (z * letterSpace);
				if (textVars2[textSeg2 + 1] == L'\u0305')
				{
					graphics.DrawString(&textVars2[textSeg2], 2, &font,
						PointF(letterX + (z ? 1.2F : 0),
							yR + resY - letterDisFromY + lYOverSpac), &brush);
					textSeg2 += 2;
				}
				else
				{
					graphics.DrawString(&textVars2[textSeg2], 1, &font,
						PointF(letterX, yR + resY - letterDisFromY), &brush);
					textSeg2++;
				}
			}
		}
		DrawTable(graphics, pen, font, brush, repSz, x, y);
		graphics.DrawLine(&pen, (xR + resX), y, (xR + resX), y + resY * (repSz + 2));
		graphics.DrawLine(&pen, x, (yR + resY), x + resX * (repSz + 2), (yR + resY));
		size_t szResExp = 1;
		for (size_t i = 0; resolvedExpression[i] != NULL; i++)
			++szResExp;
		wchar_t* textShow = new wchar_t[szResExp + 9];
		wcscpy_s(textShow, 9, L"Result: ");
		wcscat_s(textShow, szResExp + 9, resolvedExpression);
		graphics.DrawString(textShow, -1, &font, PointF(x, yR + resY + intDis), &brush);
	}
}

void MapKarn::DrawTable(Graphics& graphics, const Pen& pen,
	const Font& font, const SolidBrush& brush, const int& repSz, const int& x, const int& y)
{
	std::vector<int> expVec;
	GetExpressionFromText(textVars1, expVec);
	wchar_t outVal[2] = { L'0', L'1' };

	const int letterDisFromY = 17;
	const int intDis = 7, intDisY = 15;
	const int resX = this->szTable / this->szExpVars;
	const int resY = this->szTable / (this->szExpVars * 2);
	int xR, yR;
	for (size_t i = 0; i <= repSz; i++)
	{
		yR = y + resY * (i + 1);
		for (size_t z = 0; z <= repSz; z++)
		{
			bool drawZero = true;
			for (size_t w = 0; w < expression.size(); w++)
			{
				for (size_t j = 0; j < szExpVars / 2; j++)
				{
					int expEle = (expVec[z] << (szExpVars / 2));
					if (expression[w] == expEle + expVec[i])
					{
						drawZero = false;
					}
				}

			}
			xR = x + resX * (z + 1);
			int xDraw = x + resX * (z + 1);
			if (drawZero)
				graphics.DrawString(&outVal[0], 1, &font,
					PointF(xDraw + (resX / 2) - intDis,  yR + resY - letterDisFromY), &brush);
			else
				graphics.DrawString(&outVal[1], 1, &font,
					PointF(xDraw + (resX / 2) - intDis, yR + resY - letterDisFromY), &brush);
		}
	}
}


const int& MapKarn::RemoveEqualExpression(char text[], const size_t& szText, const size_t& szVars)
{
	int equals = 0, indEnd = szVars, removed = 0;
	int index = 0;

	while( index < szText-szVars)
	{
		for (size_t z = 0; z < szVars; z++)
		{
			if (text[z + index] == text[z + indEnd] && text[z + index] != 'r') 
				equals++;
			
			if (equals == szVars)
			{
				for (size_t j = 0; j < szVars; j++)
					text[indEnd + z - j] = 'r';
				removed += szVars;

			}
		}
		equals = 0;
		indEnd += szVars;
		if (indEnd == szText) {
			index += szVars;
			indEnd = index + szVars;
		}
	}

	bool keepRemove = true;
	int count = 0, varSeg = 0, nRem = 0;
	while (keepRemove)
	{
		if (varSeg >= szText) {
			varSeg = 0;
			count++;
			keepRemove = count > szVars ? false : true;
		}
		for (size_t i = varSeg; i < varSeg + szVars; i++) {
			if (text[i] == 'r') {
				if (i + szVars < szText) {
					text[i] = text[i + szVars];
					text[i + szVars] = 'r';
				}
				else
					text[i] = '\0';
				nRem += szVars;
				keepRemove = true;
				count = 0;
			}
		}
		varSeg += szVars;
	}
	return removed;
}


//Man seriosly i thought that before(bellow) was crazy but it's 
//the most complex loop that i did in my entire life :0
void MapKarn::ResolveExpression(wchar_t expResolve[],
	const std::vector<int>& expression, const size_t& szExpVars)
{
	auto checkInList = [](std::vector<int>& list, const int& offset) {
		bool Inlist = false;
		for (int it : list)
			if (offset == it)
				Inlist = true;
		return Inlist;
	};


	auto checkLastExpression = [](char exWorking[], const int& exSize, const int& szExpVars)
	{
		int segEnd = 0, binSeg = exSize - szExpVars;
		bool hasExpression = false;
		while (segEnd < exSize * (szExpVars - 1)) {
			int notEqual = 0;
			for (size_t j = binSeg; j < binSeg + szExpVars; j++)
			{
				if (exWorking[j] != exWorking[segEnd])
					notEqual++;


				if (j == (binSeg + szExpVars - 1) && notEqual == 1)
					hasExpression = true;
				segEnd++;
			}
		}
	};

	auto getTextFormat = [](char expText[], wchar_t endText[], const size_t& szExpression, const size_t& szVars)
	{
		size_t textSeg = 0, binSeg = 0, countX = 0;
		for (int j = 0; j < szExpression; j++) {
			for (int i = 0; i < szVars; i++)
			{
				if (expText[binSeg] == '1') {
					endText[textSeg] = nameVar[i];
					textSeg++;
				}
				else if (expText[binSeg] != 'x')
				{
					endText[textSeg] = nameVar[i];
					endText[textSeg + 1] = L'\u0305';
					textSeg += 2;
				}
				else
					countX++;
				binSeg++;
			}

			if (j < szExpression - 1) {
				endText[textSeg] = L'+';
				textSeg++;
			}
		}
		if (countX >= szExpression * szVars)
		{
			endText[0] = L'1';
			textSeg++;
		}
		endText[textSeg] = NULL;
	};


	int varMul = 1;
	for (size_t i = 1; i < szExpVars; i++)
		varMul *= 2;
	char* binaryExpression;
	{
		int arraySz = expression.size() * szExpVars;
		binaryExpression = new char[arraySz + 1];
		int binSeg = 0;
		for (size_t i = 0; i < expression.size(); i++) {
			int mul = varMul;
			for (size_t j = 0; j < szExpVars; j++)
			{
				if (expression[i] & mul)
					binaryExpression[binSeg] = '1';
				else
					binaryExpression[binSeg] = '0';
				binSeg++;
				mul /= 2;
			}
		}
		binaryExpression[binSeg] = '\0';
	}

	int removeds = RemoveEqualExpression(binaryExpression, expression.size() * szExpVars, szExpVars);
	removeds /= szExpVars;
	size_t resultSz = szExpVars * szExpVars * (expression.size() - removeds);

	bool keepLoop = true;
	char* exWorking = binaryExpression;
	size_t exSize = expression.size() - removeds;
	while (keepLoop)
	{
		keepLoop = false;
		char* result = new char[resultSz + 1];
		int resCounter = 0;
		std::vector <int> simpList;
		for (size_t mainCounter = 0; mainCounter < exSize; mainCounter++)
		{
			int binSeg = szExpVars * mainCounter;
			int sCounter = binSeg;
			int remVars = 0;
			bool findEx = false;


			if (sCounter == (exSize - 1) * (szExpVars))
			{

				if (!checkInList(simpList, binSeg)) {
					for (size_t j = binSeg; j < binSeg + szExpVars; j++)
					{
						result[resCounter] = exWorking[j];
						resCounter++;
					}
				}
			}
			else
			{
				for (size_t i = 0; i < exSize - mainCounter - 1; i++)
				{
					int notEqual = 0;
					int xPos = -1;
					int inteJ = binSeg + szExpVars * 2;
					int counter = sCounter;

					for (size_t j = binSeg + szExpVars; j < inteJ; j++)
					{

						if (exWorking[counter] != exWorking[j]) {
							notEqual++;
							if (exWorking[counter] != 'x')
								xPos = counter;
						}

						if (j == inteJ - 1 && notEqual == 1)
						{
							findEx = true;
							simpList.push_back(j - (szExpVars - 1));
							for (size_t z = counter - (szExpVars - 1); z <= counter; z++) {
								if (z == xPos)
									result[resCounter] = 'x';
								else
									result[resCounter] = (char)exWorking[z];
								resCounter++;
							}
						}
						else if (i == exSize - 2 - mainCounter && j == inteJ - 1 && !findEx)
						{
							if (!checkInList(simpList, counter - (szExpVars - 1)))
								for (size_t z = counter - (szExpVars - 1); z <= counter; z++) {
									result[resCounter] = (char)exWorking[z];
									resCounter++;
								}
						}
						binSeg++;
						counter++;
					}
				}
			}
		}

		for (size_t i = 0; i < resCounter; i++)
			if (result[i] != exWorking[i]) {
				keepLoop = true;
				break;
			}

		result[resCounter] = '\0';
		if (keepLoop)
		{
			delete[] exWorking;
			exWorking = result;
			exSize = resCounter / szExpVars;
		}
	}

	removeds = RemoveEqualExpression(exWorking, exSize * szExpVars, szExpVars) / szExpVars;
	exSize = exSize - removeds;
	getTextFormat(exWorking, expResolve, exSize, szExpVars);
	delete[] exWorking;
}


///Is very crazy I don't know which one is more crazy(Edit1 I know that's for sure) :/ Good lucky again2
//FU** i did it again2 
void MapKarn::GetTextFromExpression(const std::vector<int>& expression, wchar_t expText[],
	const size_t& szExpVar, const bool& wOperator)
{
	const size_t szExpression = expression.size();
	int varBinaryInt = 1;
	for (size_t i = 1; i < szExpVar; i++)
		varBinaryInt *= 2;

	size_t textSeg = 0;
	int var = varBinaryInt;
	for (int j = 0; j < szExpression; j++) {
		for (int i = 0; i < szExpVar; i++)
		{
			if (expression[j] & var) {
				expText[textSeg] = nameVar[i];
				textSeg++;
			}
			else
			{
				expText[textSeg] = nameVar[i];
				expText[textSeg + 1] = L'\u0305';
				textSeg += 2;
			}
			var /= 2;
		}
		var = varBinaryInt;
		if (j < szExpression - 1 && wOperator) {
			expText[textSeg] = L'+';
			textSeg++;
		}
	}
	expText[textSeg] = NULL;
}

size_t MapKarn::GetTextFromExpCalc(const std::vector<int>& expression,
	const size_t& szExpVar, const bool& wOperator)
{
	const size_t szExpression = expression.size();
	int varBinaryInt = 1;
	for (size_t i = 1; i < szExpVar; i++)
		varBinaryInt *= 2;

	size_t counter = 0;
	int var = varBinaryInt;
	for (int j = 0; j < szExpression; j++) {
		for (int i = 0; i < szExpVar; i++)
		{
			if (expression[j] & var)
				counter++;
			else
				counter += 2;
			var /= 2;
		}
		var = varBinaryInt;
		if (j < szExpression - 1 && wOperator)
			counter++;
	}
	return counter + 1;
}


///Man this sh** is crazy again1 :[] i did it just need to say that again1. Good lucky
//FU** i did it again1
void MapKarn::GetExpressionFromText(wchar_t text[], std::vector<int>& intVars)
{
	size_t varSz = 0, overcounter = 0, edSz;
	bool doMath = false;
	for (int i = 0; text[i] != NULL; i++)
	{
		if (text[i] == L'\u0305')
			overcounter++;
		else if (text[i] != L'+' && text[i] != L'\u0305')
			varSz++;


		if (text[i + 1] == L'+' || text[i + 1] == NULL || text[i + 1] == text[0])
		{
			edSz = varSz;
			doMath = true;
		}

		if (doMath) {
			int varBinaryInt = 1;
			for (size_t i = 1; i < edSz; i++)
				varBinaryInt *= 2;

			int result = 0;
			for (size_t z = 0; z < edSz + overcounter; z++)
			{
				int CalcT = (i + 1) + z - overcounter - varSz;
				if (text[CalcT + 1] != L'\u0305')
					result += varBinaryInt;
				else
					z++;
				varBinaryInt /= 2;
			}
			intVars.push_back(result);
			doMath = false;
			overcounter = 0;
			varSz = 0;
			if (text[i + 1] == L'+')
				i++;
		}
	}
}



///Man this sh** is crazy :3 i did it just need say that. Good lucky
//FU** i did it
void MapKarn::GetText(wchar_t textVars1[], wchar_t textVars2[])
{
	auto func = [](wchar_t text[], const wchar_t& label, const bool& overline, size_t& i) {
		if (overline) {
			text[i] = label;
			text[i + 1] = L'\u0305';
			i = i + 2;
		}
		else {
			text[i] = label;
			i++;
		}

	};

	int varExp = 1, sVarBin = 1;
	{
		for (size_t i = 0; i < szExpVars / 2; i++) {
			if (i > 0)
				sVarBin *= 2;
			varExp *= 2;
		} varExp--;
	}

	size_t twoPart = 0;
	wchar_t* text = textVars1;
	for (size_t twoTimes = 0; twoTimes < 2; twoTimes++)
	{
		size_t textSeg = 0, seg = 0, szVs = varExp;
		for (size_t i = 0; i <= varExp; i++)
		{
			int varBin = sVarBin;
			for (size_t z = 0; z < szExpVars / 2; z++)
			{
				if (szVs & varBin)
					func(text, nameVar[z + twoPart], false, textSeg);
				else
					func(text, nameVar[z + twoPart], true, textSeg);
				varBin /= 2;
			}
			szVs--;
		}
		text[textSeg] = L'\0';
		text = textVars2;
		twoPart = szExpVars / 2;
	}
	/*First Version missing some expressions
	wchar_t* text = textVars1;
	size_t twoPart = 0;
	for (size_t twoTimes = 0; twoTimes < 2; twoTimes++)
	{
		size_t seg = 0, textSeg = 0, repetition = 0, repCounter = 0;
		while (repetition <= szExpVars / 2) {
			for (size_t i = 0; i < szExpVars / 2; i++)
			{
				if ((repetition - repCounter) && (i >= seg)) {

						func(text, nameVar[i + twoPart], true, textSeg);
						repCounter++;
				}
				else
					func(text, nameVar[i + twoPart], false, textSeg);
			}

			seg++;
			repCounter = 0;
			if ((seg > szExpVars / 2 - repetition) || !repetition) {
				repetition++;
				seg = 0;
			}

		}
		text[textSeg] = L'\0';
		text = textVars2;
		twoPart = szExpVars / 2;
	}*/
}


const size_t& MapKarn::CalcArraySize() {

	int varExp = 1, sVarBin = 1;
	{
		for (size_t i = 0; i < szExpVars / 2; i++) {
			if (i > 0)
				sVarBin *= 2;
			varExp *= 2;
		} varExp--;
	}

	size_t twoPart = 0, counter = 0;
	size_t textSeg = 0, seg = 0, szVs = varExp;
	for (size_t i = 0; i <= varExp; i++)
	{
		int varBin = sVarBin;
		for (size_t z = 0; z < szExpVars / 2; z++)
		{
			if (szVs & varBin)
				counter++;
			else
				counter += 2;
			varBin /= 2;
		}
		szVs--;
	}
	return counter + 1;


	/*To first version
	size_t counter = 0, seg = 0, repetition = 0, repCounter = 0;
	while (repetition <= szExpVars / 2) {
		for (size_t i = 0; i < szExpVars / 2; i++)
			if ((repetition - repCounter) && (i >= seg)) {
				counter += 2;
				repCounter++;
			}
			else
				counter++;
		seg++;
		repCounter = 0;
		if ((seg > szExpVars / 2 - repetition) || !repetition) {
			repetition++;
			seg = 0;
		}

	}
	return counter + 1;                   //Counter + null
	*/
}
