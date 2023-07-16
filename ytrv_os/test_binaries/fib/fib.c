int fib(int i){
	if (i > 2){
		return fib(i - 1) + fib (i - 2);
	}
	else{
		return 1;
	}
}

int main(){
	return fib(5) - 5;
}
