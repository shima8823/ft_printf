#include "ft_printf.h"

int main()
{
	int c;
	ft_printf("aa%cvv%cggg%s--10\n\n%p\n\n%d\ni = %i\nu = %u\nx = %x\nX = %X", '2', '9', "Hello, World", SIZE_MAX, 10, INT_MIN, 12, 1967, 1967);
	ft_printf("\n");
	ft_printf(" NULL %s NULL ", NULL);
	// ft_printf("%%");
	ft_printf("\n");
	ft_printf("%");
	ft_printf("%a");
}