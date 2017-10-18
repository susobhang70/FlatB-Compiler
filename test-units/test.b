declblock{
	int data[100], sumy;
	int i, sum;
}

codeblock{
	for i = 1, 100 {
		data[i] = i ; 
	}

	sum = 0;
	for i = 1, 100 {
		sum = sum + data[i] ;
 	}

	println "Sum value: ", sum ;
}

