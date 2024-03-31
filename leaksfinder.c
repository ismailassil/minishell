/*header file*/

/*==== LEAKS FINDER ==*/
#include <libc.h>
FILE    *gfp;
static void *__malloc(size_t size, int line, const char *file)
{
    void    *ptr;
    ptr = malloc(size);
    fprintf(gfp, "dct[%p] = ['malloc', '%p', %i, '%s']\n", 
        ptr, ptr, line, file);
    fflush(gfp);
    return (ptr);
}
static void    __free(void *ptr, int line, const char *file)
{
    fprintf(gfp, "dct[%p] = ['free', '%p', %i, '%s']\n",
        ptr, ptr, line, file);
    fflush(gfp);
    free(ptr);
}
#define malloc(x) __malloc(x, __LINE__, __FILE__)
#define free(x) __free(x, __LINE__, __FILE__)
/**/

/*source file*/
void    leaks()
{
  fclose(gfp);
  system("leaks minishell");
  usleep(1000 * 100 *10000);
}

int	main(void)
{
	gfp = fopen("leaks.t", "w");
	atexit(leaks);
}
