declblock{
	int a, i, c;
}

codeblock{
	a = 5;
	c = 7;
	while c >= 6 {
		a = a + 1;
		c = c - 1;
	}

	println a;
	println c;
}