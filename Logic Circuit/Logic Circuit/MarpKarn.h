#pragma once
class MapKarn
{
public:
    int x, y;

    MapKarn(const std::vector<int>& expression,
        const size_t& szExpVars, const int& x, const int& y)
        : 
        x(x), y(y),
        expression(expression), szExpVars(szExpVars),
        szTable(50 * szExpVars)
   
    {
        size_t szTextVars = CalcArraySize();
        wchar_t* text1 = new wchar_t[szTextVars];
        wchar_t* text2 = new wchar_t[szTextVars];
        GetText(text1, text2);
        
        textVars1 = text1;
        textVars2 = text2;
       
        size_t szExpression = szExpVars * expression.size() * 2 + 1;        //numberVar * numExpressions ->
        resolvedExpression = new wchar_t[szExpression];                     //-> * maxPossible overlines + null
        ResolveExpression(resolvedExpression, this->expression, szExpVars);
    }


    void GetTextFromExpression(const std::vector<int>& expression, wchar_t expText[],
        const size_t& szExpVar, const bool& wOperator=true);

    size_t GetTextFromExpCalc(const std::vector<int>& expression,
        const size_t& szExpVar, const bool& wOperator=true);

    void GetExpressionFromText(wchar_t text[], std::vector<int>& intVars);

    
    MapKarn operator=(const MapKarn& other) = delete;

    MapKarn() = delete;

    ~MapKarn() 
    {
        delete[] textVars1;
        delete[] textVars2;
        delete[] resolvedExpression;
    }

    void Draw(Graphics&, const Pen&, const Font&, const SolidBrush&);

private:
    size_t szTable; 
    size_t szExpVars;
    std::vector<int> expression;

    wchar_t* textVars1;
    wchar_t* textVars2;
    wchar_t* resolvedExpression;
    

    void ResolveExpression(wchar_t[], const std::vector<int>&, const size_t&);

    const size_t& CalcArraySize();

    void GetText(wchar_t[], wchar_t[]);

    void DrawTable(Graphics&, const Pen&, const Font&,
        const SolidBrush&, const int&, const int&, const int&);

    const int& RemoveEqualExpression(char[], const size_t&, const size_t&);
};