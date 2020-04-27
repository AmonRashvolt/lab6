#define NMAX 1000

#include<iostream>
#include<cmath>
#include<cstdio>
#include <fstream>

using namespace std;

//Собственно здесь записывается наша функция
double f(double x, double y) {
	return 4*x*x-20*x+y*y-28*y+222;
	
}

//Это первая производная по dx
double f_dx(double x, double y) {
	return (8*x-20);
	
}

//Это первая производная по dy
double f_dy(double x, double y) {
	return (2*y-28);
	
}

double f_sc(double* x1, double a, double* p) {
	double x_new[] = { x1[0] + a * p[0], x1[1] + a * p[1] };
	return f(x_new[0], x_new[1]);
}

double mso(double* x1, double* p) { // metod skolz. okna
	double a = 0;
	double h = 0.025;
	while (1) {
		if (f_sc(x1, a - h, p) > f_sc(x1, a, p) && f_sc(x1, a, p) < f_sc(x1, a + h, p)) {
			break;
		}
		else if (f_sc(x1, a - h, p) > f_sc(x1, a + h, p)) {
			a += h / 2;
		}
		else if (a > -h / 2) {
			a -= h / 2;
		}
	}
	return a;
}



//Это функция g d методе наискорейшего (градиентного) спуска
double g(double x, double y, double alpha) {
	return f(x - alpha * f_dx(x, y), y - alpha * f_dy(x, y));
}

//двумерная норма
double norma(double x, double y) {
	return sqrt((f_dx(x, y)) * (f_dx(x, y)) + (f_dy(x, y)) * (f_dy(x, y)));
}

//Метод половинного деления для нахождения минимума в градиентном спуске
double Dihotomia(double a0, double b0, double epsilon, double x, double y)
{
	//Номер шага
	int k;
	//Отклонени от середины отрезка влево, вправо
	double lk, mk;
	//Величина на которую мы отклонимся от середины отрезка
	double delta = 0.5 * epsilon;
	//Точка минимума
	double x_;
	//Отрезок локализации минимума
	double ak = a0, bk = b0;
	k = 1;
	//Пока длина отрезка больше заданной точности
	do {
		//Берем середину (ну почти середину - +\- некоторое дельта в частности у нас delta=0.5*epsilon)
		lk = (ak + bk - delta) / 2;
		mk = (ak + bk + delta) / 2;

		k++;
		//Проверяем в какую часть попадает точка минимума слева от разбиения или справа и выбираем соответствующую точку
		if (g(x, y, lk) <= g(x, y, mk)) {
			//Теперь правая граница отрезка локализации равна mk
			bk = mk;
		}
		else {
			//Теперь левая граница отрезка локализации равна mk
			ak = lk;
		}
	} while ((bk - ak) >= epsilon);

	x_ = (ak + bk) / 2; //minimum point

	return x_;
}


// метод наискорейшего спуска
void GreatDescent(  double bx, double by, double epsilon) {
	double x[NMAX];
	double y[NMAX];
	double alpha[NMAX];
	int k,gh;
	double u;
	double x1[5];
	double p[5];
	ofstream out;
	out.open("ans1.txt");
	//Начальное приближение u[0]
	x[0] = bx;
	y[0] = by;
	gh = 0;
	cout << "RES:" << endl << "x(" << 0 << "): (" << x[0] << ", " << y[0] << ")" << endl;
	out << x[0] << " " << y[0] << " " << f(x[0], y[0]) << endl;
	for (k = 0; ; k++) {
		x1[k] = x[0];
		x1[k+1] = y[0];
		p[k] = -f_dx(x[0],y[0]);
		p[k+1] = -f_dx(x[0], y[0]);
		u = mso(x1, p);
		gh++;
		//cout << "++++++++ " << u << "+++++++" << endl;


		//Находим alpha_k как минимум функции g на отрезке -10000,100000
		alpha[k] = Dihotomia(u-0.025, u+0.025, epsilon, x[k], y[k]);
		//Вычисляем u[k]
		x[k + 1] = x[k] - alpha[k] * f_dx(x[k], y[k]);
		y[k + 1] = y[k] - alpha[k] * f_dy(x[k], y[k]);

		cout << "x(" << k + 1 << "): " << "(" << x[k + 1] << ", " << y[k + 1] << ")" << endl
			<< "f(" << x[k + 1] << ", " << y[k + 1] << ") = " << f(x[k + 1], y[k + 1]) << endl;
		out  << x[k + 1] << " " << y[k + 1] <<  " " << f(x[k + 1], y[k + 1]) << endl;
		//cout <<"gg "<< norma(x[k + 1] - x[k], y[k + 1] - y[k])<<" "<<x[k]<<" "<<y[k]<<"dfs "<<alpha[k] << endl;
		//if (k > 1) {
			//Проверяем условие остановки
			if (norma(x[k + 1] - x[k], y[k + 1] - y[k]) <= epsilon) {
			break;
			}
			if (((x[k + 1] - x[k])<=epsilon) && ((y[k + 1] - y[k]) <= epsilon)) {
				break;
			}
			
		//}
		x[k] = x[k + 1];
		y[k] = y[k + 1];
		k = 0;
	}
	out.close();
	cout << "Tochka min (epsilon=" << epsilon << ")" << endl
		<< "f(" << x[k + 1] << ", " << y[k + 1] << ") = " << f(x[k + 1], y[k + 1]) << " gh= "<<gh<< endl;
	//return f(x[k + 1], y[k + 1]);
}

int main() {
	double x, y, epsilon,olk;
	cout << "x=-1\n";
	x = -1;
	cout << "y=-13;\n"; 
	y = -13;
	cout << "epsilon=0.001\n";epsilon=0.001;
	GreatDescent(x, y, epsilon);

	system("pause");
	return 0;
}
