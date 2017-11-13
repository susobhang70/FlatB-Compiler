declblock{
	int data[100] ;
	int i, j, sum, other;
}

codeblock{
	for i = 1, 100 {
		data[i] = i ; 
	}
	

	sum = 0;
	other = 0;
	for i = 1, 100 {
		sum = sum + data[i] ;
		for j = 1, 100, 1 
		{
			sum = sum - 1;
		}
 	}

	println "Sum value: ", sum ;
}

