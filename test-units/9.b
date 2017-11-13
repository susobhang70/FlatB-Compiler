declblock{
	int a, i, c;
}

codeblock{
	c = 0;
	p: a = 2;
	c = c + a;
	if c < 5
	{
		println c;
		goto p;
	}

	print "Hello ", c;
}