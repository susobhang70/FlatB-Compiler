declblock{
	int a, i, c;
}

codeblock{
	c = 0;
	p: a = 2;
	c = c + a;
	println c;
	goto p if c < 5;
	i = 2;
}