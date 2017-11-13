declblock
{
	int i, j, range, range2;
	int a[10000], tmp;
}
codeblock
{
	range = 10000;
	for i = 0, range - 1, 1
	{
		a[i] = range - i;
	}

	for i = 0, range - 2, 1
	{
		range2 = range - i - 2;
		for j = 0, range2, 1
		{
			if a[j] > a[j + 1]
			{
				tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
			}
		}
	}
}