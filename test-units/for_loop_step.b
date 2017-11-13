declblock{
	int a, i, c;
}

codeblock{
	a = 5;
	c = 2;
	for i = 1, 10, 2 {
		a = a + c;
	}

	println a;
}