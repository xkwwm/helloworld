// Calculator.h: interface for the CCalculator class.
//
//////////////////////////////////////////////////////////////////////


typedef struct _sPoint
{
	float x;
	float y;
}sPoint;	

class CCalculator  
{
public:
	CCalculator();
	virtual ~CCalculator();
	
public:
	float CalcDistance(sPoint* p1, int p, sPoint* p2, int q);

private:
	float Cal(float** ca, int i, int j);
	float dis(int i, int j);
	float min3(float f1, float f2, float f3);
public:
	sPoint* p1;
	sPoint* p2;
	int p;
	int q;
};

