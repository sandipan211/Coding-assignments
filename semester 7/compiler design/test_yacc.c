int calsum(int x, int y)
{
	int sum;
	sum = x+y;
	return sum;
}

int x=10;
float pi=3.1416;

int main()
{
	int i;
	char a, b;
	int j=1, k=2, l=3, n=3;

	float f = 2.980;

	if(((j<2)||(k>2))&&(l==n))
	{
		int m;
		m=9;
		m = 2+(396-(9*8)/m)%3;
		l = k++;
	}
	else
	{
		f = 0.01;
		n = --j;
	}
	j = k;
	
	float f1, f2, f3, f4;
	f1 = 1.0||f;
	f2 = 0.0&&f;
	f3 = f^6;
	f4 = !f;

	if(j>3)
	{
		k = 2;
	}
	else if(j<3)
	{
		k = 3;
	}
	else
	{
		k = 1;
	}

	switch(k)
	{
		case 1: int x = 2;
				break;
		case 2: int y = 3;
				break;
		default:int z=1;
				break;
	}

	for(i=0;i<3;i++)
	{
		j = j*2;
	}

	i=3;
	while(i>0)
	{
		j = j/2;
		i--;
	}

	do
	{
		j = j+2;
		++i;
	}while(i<=3);

	int val = calsum(2,j);
	return 0;
}


