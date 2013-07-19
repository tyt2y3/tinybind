#include <stdio.h>

template <class T>
class a_to_b
{
	public:
	void operator() ( int* a, int* b)
	{
		T obj=0;
		obj+=1;
		printf("converting a to b; obj=%d\n", obj);
	}
};

void binding( a_to_b<int>& fun1)
{
	int a=1; int b=2;
	fun1( &a, &b);
}

int main()
{
	int a=1; int b=2;
	a_to_b<int> fun1;
	fun1( &a, &b);

	binding( fun1);

	return 1;
}
