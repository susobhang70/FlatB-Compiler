declblock
{
	int i, n, p;
	int prime[1000001];
}
codeblock
{
	n = 1000000;

	for i = 0, n, 1
	{
		prime[i] = 1;
	}

	p = 2;

	while p*p <= n
	{
		if prime[p] == 1
		{
			for i = p*2, n, p
			{
                prime[i] = 0;
			}
		}
		p = p + 1;
	}

	for i = 2, n, 1
	{
		if prime[i] == 1
		{
			println i;
		}
	}
}