#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Fraction
{
private:
	int top;
	int bottom;
public:
	Fraction() {
		top = 0;
		bottom = 1;
	};

	Fraction(int a, int b) {
		if (b == 0) {
			cout << "Math error!" << endl;
		}
		top = a;
		bottom = b;
		int tmp = Maxf1ctor(this->top, this->bottom);
		this->top /= tmp;
		this->bottom /= tmp;
		if (this->bottom < 0) {
			this->top *= -1;
			this->bottom *= -1;
		}
	};

	Fraction(int a) {
		top = a;
		bottom = 1;
	};

	int getTop(){
		return top;
	}

	int getBottom(){
		return bottom;
	}

	void setTop(int i){
		top = i;
	}

	void setBottom(int i){
		bottom = i;
	}

	static int abs(int a) {
		return a > 0 ? a : -a;
	}

	static int Maxf1ctor(int a, int b) {
		if (a == 0 || b == 0) return 1;
		if (abs(a) > abs(b)) { int t = b; b = a; a = t; }
		a = abs(a);
		b = abs(b);
		for (int i = a; i <= b; --i) {
			if (a%i == 0 && b%i == 0)
				return i;
		}
		return 1;
	}

	friend Fraction operator+(Fraction &f1, Fraction &f2) {
		Fraction ft;
		ft.top = f1.top * f2.bottom + f1.bottom * f2.top;
		ft.bottom = f1.bottom * f2.bottom;
		int tmp = Maxf1ctor(ft.top, ft.bottom);
		ft.top /= tmp;
		ft.bottom /= tmp;
		return ft;
	}
	friend Fraction operator-(Fraction &f1, Fraction &f2) {
		Fraction ft;
		ft.top = f1.top * f2.bottom - f1.bottom * f2.top;
		ft.bottom = f1.bottom * f2.bottom;
		int tmp = Maxf1ctor(ft.top, ft.bottom);
		ft.top /= tmp;
		ft.bottom /= tmp;
		if (ft.bottom < 0) {
			ft.top *= -1;
			ft.bottom *= -1;
		}
		return ft;
	}

	friend Fraction operator*(Fraction &f1, Fraction &f2) {
		Fraction ft;
		ft.top = f1.top * f2.top;
		ft.bottom = f1.bottom * f2.bottom;
		int tmp = Maxf1ctor(ft.top, ft.bottom);
		ft.top /= tmp;
		ft.bottom /= tmp;
		return ft;
	}

	friend Fraction operator/(Fraction &f1, Fraction &f2) {
		Fraction ft;
		ft.top = f1.top * f2.bottom;
		ft.bottom = f1.bottom * f2.top;
		int tmp = Maxf1ctor(ft.top, ft.bottom);
		ft.top /= tmp;
		ft.bottom /= tmp;
		if (ft.bottom < 0) {
			ft.top *= -1;
			ft.bottom *= -1;
		}
		return ft;
	}

	Fraction operator=(const Fraction &f1) {
		Fraction ft;
		ft.top = f1.top;
		ft.bottom = f1.bottom;
		int tmp = Maxf1ctor(ft.top, ft.bottom);
		ft.top /= tmp;
		ft.bottom /= tmp;
		if (ft.bottom < 0) {
			ft.top *= -1;
			ft.bottom *= -1;
		}
		return ft;
	}

	friend bool operator<(Fraction &f1, Fraction &f2) {
		double a, b;
		double c, d, e, f;
		d = f1.top;
		c = f1.bottom;
		e = f2.top;
		f = f2.bottom;
		a = d / c;
		b = e / f;
		return a < b;
	}

	friend bool operator>(Fraction &f1, Fraction &f2) {
		double a, b;
		double c, d, e, f;
		d = f1.top;
		c = f1.bottom;
		e = f2.top;
		f = f2.bottom;
		a = d / c;
		b = e / f;
		return a > b;
	}

	friend bool operator <= (Fraction &f1, Fraction &f2) {
		double a, b;
		double c, d, e, f;
		d = f1.top;
		c = f1.bottom;
		e = f2.top;
		f = f2.bottom;
		a = d / c;
		b = e / f;
		return a <= b;
	}

	friend bool operator >= (Fraction &f1, Fraction &f2) {
		double a, b;
		double c, d, e, f;
		d = f1.top;
		c = f1.bottom;
		e = f2.top;
		f = f2.bottom;
		a = d / c;
		b = e / f;
		return a >= b;
	}

	friend bool operator == (Fraction &f1, Fraction &f2) {
		double a, b;
		double c, d, e, f;
		d = f1.top;
		c = f1.bottom;
		e = f2.top;
		f = f2.bottom;
		a = d / c;
		b = e / f;
		return a == b;
	}

	void convert_and_show() {
		cout << (double)top / bottom;
	}

	friend ostream & operator <<(ostream& output, Fraction &f1) {
		if (f1.bottom == 1) {
			output << f1.top;
		}
		else output << f1.top << '/' << f1.bottom;
		return output;
	}

	friend istream & operator >>(istream& input, Fraction &f1) {
		char string[30];
		int tag = 0;
		input >> string;
		int temp = 0, i;
		for (i = 0; i < 30; ++i)
		{
			if (string[i] == '-') {
				tag = 1;
			}
			if (string[i] == '/') {
				if (tag)
					f1.top = -temp;
				else
					f1.top = temp;
				break;
			}
			if (string[i] <= '9' && string[i] >= '0') {
				temp = temp * 10 + string[i] - '0';
			}
		}
		tag = 0;
		temp = 0;
		for (i++; i < 30; ++i)
		{
			if (string[i] == '-') {
				tag = 1;
			}
			else if (string[i] <= '9' && string[i] >= '0') {
				temp = temp * 10 + string[i] - '0';
			}
			else
				break;
		}
		if (!tag)
			f1.bottom = temp;
		else
			f1.bottom = -temp;
		int tmp = Maxf1ctor(f1.top, f1.bottom);
		f1.top /= tmp;
		f1.bottom /= tmp;
		if (f1.bottom < 0) {
			f1.top *= -1;
			f1.bottom *= -1;
		}
		return input;
	}

	~Fraction() {};
};

class iFraction:public Fraction
{
private:
	int base;
	int Top;
	int Bottom;
public:
	iFraction(){
		this->base = 0;
		this->Top = 0;
		this->Bottom = 0;
	}

	iFraction(int base, int top, int bottom){
		this->base = base;
		this->Top = top;
		this->Bottom = bottom;
	}

	void simpify(){
		if(Top > Bottom){
			base += Top / Bottom;
		}
		Top %= Bottom;
	}

	friend iFraction operator+(iFraction &if1, iFraction &if2) {
		iFraction ft;
		ft.Top = if1.Top * if2.Bottom - if1.Bottom * if2.Top;
		ft.Bottom = if1.Bottom * if2.Bottom;
		int tmp = Maxf1ctor(ft.Top, ft.Bottom);
		ft.Top /= tmp;
		ft.Bottom /= tmp;
		ft.base = if1.base + if2.base;
		ft.simpify();
		return ft;
	}

	friend Fraction operator-(iFraction &f1, iFraction &f2) {
		iFraction ft;
		ft.Top = f1.Top * f2.Bottom - f1.Bottom * f2.Top;
		ft.Bottom = f1.Bottom * f2.Bottom;
		int tmp = Maxf1ctor(ft.Top, ft.Bottom);
		ft.Top /= tmp;
		ft.Bottom /= tmp;
		if (ft.Bottom < 0) {
			ft.Top *= -1;
			ft.Bottom *= -1;
		}
		ft.simpify();
		return ft;
	}

	// friend Fraction operator*(Fraction &f1, Fraction &f2) {
	// 	Fraction ft;
	// 	ft.top = f1.top * f2.top;
	// 	ft.bottom = f1.bottom * f2.bottom;
	// 	int tmp = Maxf1ctor(ft.top, ft.bottom);
	// 	ft.top /= tmp;
	// 	ft.bottom /= tmp;
	// 	return ft;
	// }

	// friend Fraction operator/(Fraction &f1, Fraction &f2) {
	// 	Fraction ft;
	// 	ft.top = f1.top * f2.bottom;
	// 	ft.bottom = f1.bottom * f2.top;
	// 	int tmp = Maxf1ctor(ft.top, ft.bottom);
	// 	ft.top /= tmp;
	// 	ft.bottom /= tmp;
	// 	if (ft.bottom < 0) {
	// 		ft.top *= -1;
	// 		ft.bottom *= -1;
	// 	}
	// 	return ft;
	// }

	// Fraction operator=(const Fraction &f1) {
	// 	Fraction ft;
	// 	ft.top = f1.top;
	// 	ft.bottom = f1.bottom;
	// 	int tmp = Maxf1ctor(ft.top, ft.bottom);
	// 	ft.top /= tmp;
	// 	ft.bottom /= tmp;
	// 	if (ft.bottom < 0) {
	// 		ft.top *= -1;
	// 		ft.bottom *= -1;
	// 	}
	// 	return ft;
	// }

	// friend bool operator<(Fraction &f1, Fraction &f2) {
	// 	double a, b;
	// 	double c, d, e, f;
	// 	d = f1.top;
	// 	c = f1.bottom;
	// 	e = f2.top;
	// 	f = f2.bottom;
	// 	a = d / c;
	// 	b = e / f;
	// 	return a < b;
	// }

	// friend bool operator>(Fraction &f1, Fraction &f2) {
	// 	double a, b;
	// 	double c, d, e, f;
	// 	d = f1.top;
	// 	c = f1.bottom;
	// 	e = f2.top;
	// 	f = f2.bottom;
	// 	a = d / c;
	// 	b = e / f;
	// 	return a > b;
	// }

	// friend bool operator <= (Fraction &f1, Fraction &f2) {
	// 	double a, b;
	// 	double c, d, e, f;
	// 	d = f1.top;
	// 	c = f1.bottom;
	// 	e = f2.top;
	// 	f = f2.bottom;
	// 	a = d / c;
	// 	b = e / f;
	// 	return a <= b;
	// }

	// friend bool operator >= (Fraction &f1, Fraction &f2) {
	// 	double a, b;
	// 	double c, d, e, f;
	// 	d = f1.top;
	// 	c = f1.bottom;
	// 	e = f2.top;
	// 	f = f2.bottom;
	// 	a = d / c;
	// 	b = e / f;
	// 	return a >= b;
	// }

	// friend bool operator == (Fraction &f1, Fraction &f2) {
	// 	double a, b;
	// 	double c, d, e, f;
	// 	d = f1.top;
	// 	c = f1.bottom;
	// 	e = f2.top;
	// 	f = f2.bottom;
	// 	a = d / c;
	// 	b = e / f;
	// 	return a == b;
	// }

	// friend ostream & operator <<(ostream& output, Fraction &f1) {
	// 	if (f1.bottom == 1) {
	// 		output << f1.top;
	// 	}
	// 	else output << f1.top << '/' << f1.bottom;
	// 	return output;
	// }

	// friend istream & operator >>(istream& input, Fraction &f1) {
	// 	char string[30];
	// 	int tag = 0;
	// 	input >> string;
	// 	int temp = 0, i;
	// 	for (i = 0; i < 30; ++i)
	// 	{
	// 		if (string[i] == '-') {
	// 			tag = 1;
	// 		}
	// 		if (string[i] == '/') {
	// 			if (tag)
	// 				f1.top = -temp;
	// 			else
	// 				f1.top = temp;
	// 			break;
	// 		}
	// 		if (string[i] <= '9' && string[i] >= '0') {
	// 			temp = temp * 10 + string[i] - '0';
	// 		}
	// 	}
	// 	tag = 0;
	// 	temp = 0;
	// 	for (i++; i < 30; ++i)
	// 	{
	// 		if (string[i] == '-') {
	// 			tag = 1;
	// 		}
	// 		else if (string[i] <= '9' && string[i] >= '0') {
	// 			temp = temp * 10 + string[i] - '0';
	// 		}
	// 		else
	// 			break;
	// 	}
	// 	if (!tag)
	// 		f1.bottom = temp;
	// 	else
	// 		f1.bottom = -temp;
	// 	int tmp = Maxf1ctor(f1.top, f1.bottom);
	// 	f1.top /= tmp;
	// 	f1.bottom /= tmp;
	// 	if (f1.bottom < 0) {
	// 		f1.top *= -1;
	// 		f1.bottom *= -1;
	// 	}
	// 	return input;
	// }

	void Display(){
		cout << base << "+" << Top << "/"<< Bottom;
	}

	friend conevrtF(Fraction & f, iFraction & iF){
		if(f.getTop() > f.getBottom()){
			iF.base = f.getTop() / f.getBottom();
			iF.Top = f.getTop() % f.getBottom();
			iF.Bottom = f.getBottom();
		}
		else{
			iF.base = 0;
			iF.Top = f.getTop() % f.getBottom();
			iF.Bottom = f.getBottom();
		}
	}
};

int main(){
	
}