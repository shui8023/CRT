/*
 * =====================================================================================
 *
 *       Filename:  test_stdio.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年08月29日 00时52分13秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shui(dubingyang), dubingyangxiyou@gmail.com
 *        Company:  Class 1201 of software engineering
 *
 * =====================================================================================
 */

#include "stdio.h"
#include "string.h"
#include "malloc.h"
int crt_main(int argc, char *argv[])
{
	int ret;
	
	char message[] = "test the printf!\n";
	ret = strlen(message);
	char *ptr = (char *)malloc(10);
	int number = 19;

	printf("%d\n%d\n%s\n", ret, number, message);
	
	return 0;
}

