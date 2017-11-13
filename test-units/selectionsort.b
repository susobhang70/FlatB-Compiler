declblock
{
	int i, j, range, min;
	int A[10000], tmp;
}
codeblock
{
	range = 10000;

	for i = 0, range - 1, 1
	{
		A[i] = range - i;
	}

	for j = 0, range - 2, 1
	{
		min = j;
		for i = j + 1, range - 1, 1
		{
			if A[i] < A[min]
			{
				min = i;
			}
		}

		if min != j
		{
			tmp = A[j];
			A[j] = A[min];
			A[min] = tmp;
		}
	}
}