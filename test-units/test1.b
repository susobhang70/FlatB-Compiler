declblock{
	int data[100] ;
	int i, sum ;
}

codeblock{
	for i = 1, 100 {
		data[i] = i ; 
	}
	

	sum = 0;
	for i = 1, 100 {
		sum = sum + data[i] ;
		for i = 100, 1, -1 {
			sum = 0;
		}
 	}

	print "Sum value: ", sum ;
}

