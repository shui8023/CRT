/*
 * =====================================================================================
 *
 *       Filename:  crt_entry.c
 *
 *    Description:  crt的入口函数
 *
 *        Version:  1.0
 *        Created:  2014年08月25日 21时08分19秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shui(dubingyang), dubingyangxiyou@gmail.com
 *        Company:  Class 1201 of software engineering
 *
 * =====================================================================================
 */

extern int crt_main(int argc, char *argv[]);

void exit(int exitcode);

void _start(void)
{
	int ret;

	int argc;
	char **argv;
	char *ebp_reg;

	asm __volatile__ ("movl %%ebp,%0\n":"=r"(ebp_reg));
	
	argc = *(int *)(ebp_reg + 4);
	argv = (char **)(ebp_reg + 8);

	ret = crt_main(argc,  argv);
	
	exit(ret);
}

void exit(int exitcode)
{
	asm ("movl %0, %%ebx \n\t"
	     "movl $1, %%eax \n\t"
	     "int $0x80 \n\t"
	     "hlt \t\n"
	     ::"m"(exitcode));

}
