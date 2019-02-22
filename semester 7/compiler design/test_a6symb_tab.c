

int main()
{
	int i, j, k, l, n;
	char a, b;
	j=1;
	k=2;
	l=3;
	n=3;

	float f;
	f = 2.980;

	if(((j<2)||(k>2))&&(l==n))
	{
		int m;
		m=9;
		m = (2/m);
		l = k++;
	}
	else
	{
		f = 0.01;
		n = --j;
	}
	j = k;
	
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
		case 1: int x;
				x=2;
				break;
		case 2: int y;
				y = 12;
				break;
		default:int z;
				z = 0;
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
		float w, p;
	}while(i<=3);
	return 0;
}


