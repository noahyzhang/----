#include<stdio.h>
#if 0
func(int b[][4], int m)
{
	int i, j, k;
	k = 0;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 4; j++)
			if (b[i][j] < m)
				k = k + b[i][j];
	return k;
}

void main()
{
	int a[3][4] = { {1,13,5,7},{2,4,26,8},{10,1,3,12} };
	int m = 10;
	printf("%d", func(a, m));
}
#endif

//void main()
//{
//	int x = 10;
//	void fun(int);
//	fun(x);
//	printf("%d", x);
//}
//void fun(x)
//{
//	x = 10;
//}


//int d = 1;
//fun(int p)
//{
//	static int d = 5;
//	d += p;
//	printf("%d", d);
//	return d;
//}
//
//void main()
//{
//	int a = 3;
//	printf("%d", fun(a + fun(d)));
//}


//int f(int a, int b)
//{
//	int c;
//	c = a;
//	if (a > b)
//		c = 1;
//	else if (a == b)
//		c = 0;
//	else
//		c = -1;
//	return c;
//}
//
//void main()
//{
//	int i = 2, p;
//	p = f(i, i + 1);
//	printf("%d", p);
//}

//long fun(int n)
//{
//	long s;
//	if (n == 1 || n == 2)
//		s = 2;
//	else
//		s = n + fun(n - 1);
//	return s;
//}
//
//void main()
//{
//	printf("%ld",fun(4));
//}