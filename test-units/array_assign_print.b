declblock{
	int a[100], b[100], c;
}

codeblock{
	a[0] = 5;
	c = 5;
	b[c] = a[0];
	println b[c];
}