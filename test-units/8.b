declblock{
	int a, i, c;
}

codeblock{
	a = 5;
	p: a = 2;
	c = 2;
	goto p if c < 5;
	i = 2;
}