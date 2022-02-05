#include "magic.h"

int main()
{
	int n;
	printf("请输入幻方的阶数n: ");
	scanf("%d", &n);
	GetMagic(n);
	ShowMagic(n);
	system("pause");
	return 0;
}
