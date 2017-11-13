declblock{
	int a, i, c;
}

codeblock{
	a = 5;
	goto p;
	i = 3;
	c = 2;
	println i;
	p: i = 5;
	print i;
}