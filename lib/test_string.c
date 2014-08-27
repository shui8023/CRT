/*
 * =====================================================================================
 *
 *       Filename:  test_string.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2014年08月27日 20时15分31秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shui(dubingyang), dubingyangxiyou@gmail.com
 *        Company:  Class 1201 of software engineering
 *
 * =====================================================================================
 */

#include <stdio.h>
#include "string.h"
#include <stdlib.h>

#define N 100

int main(int argc, char *argv[])
{
	char s[N] = "test the string.h!";

	int ret = strlen(s);

	printf("%d\n", ret);
	return EXIT_SUCCESS;
}
