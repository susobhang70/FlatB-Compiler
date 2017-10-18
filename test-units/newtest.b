declblock
{
	int k, dummy, i;
}

codeblock
{
	k = 0;

	L1: if k == 0
	{
		for i = 1, 100
		{
			k = k + 1;
		}
	}
	else
	{
		k = 200;
	}

	goto L1 if k < 100;
	println k;
}
