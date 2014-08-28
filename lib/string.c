/*
 * =====================================================================================
 *
 *       Filename:  string.c
 *
 *    Description:  字符串函数的实现
 *
 *        Version:  1.0
 *        Created:  2014年08月26日 22时14分15秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Shui(dubingyang), dubingyangxiyou@gmail.com
 *        Company:  Class 1201 of software engineering
 *
 * =====================================================================================
 */

#include "string.h"


/*概述： 函数strlen计算s指向的串的长度
 *返回值：返回空字符前面的字符的数目
 */
size_t strlen(const char *s)
{
	const char *sc;

	for (sc = s; *sc != '\0'; ++sc) {
		;
	}

	return (sc - s);
}

/*
 *概述：将s2指向的串包括终止的空字符串复制给s1指向的数组
 *返回值：返回s1的值,这就是为什么要在s1的最后一位加上字符结束符
 */
char *strcpy(char *s1, const char *s2)
{
	char *s  = s1;

	for (s = s1; (*s++ = *s2++) != '\0';) {
		;
	}

	return s1;
}

/*
 *概述：将s2指向字符串中复制最多n个字符（不复制空字符后面的字符）到s1指向的数组中，
 *如果s2指向的字符串是一个长度比n短的字符串，则在s1指向的数组后面添加空字符，直到写入了n个字符
 *返回值：返回s1的值
 */
char *strncpy(char *s1, const char *s2, size_t n)
{
	char *s = s1;

	for (s = s1; n > 0 && *s2 != '\0'; --n) {
		*s++ = *s2++;
	}

	for (; 0 < n; --n) {
		*s++ = '\0';
	}

	return s1;
}

/*
 *概述：从s2指向的对象中复制n个字符到s1指向的对象中
 *返回值：返回s1的值
 */
void *memcpy(void *s1, const void *s2, size_t n)
{
	 char *s = s1;
	 char *sc = s2;
	 for (s = s1; n > 0; --n) {
	 	*s++ = *sc++;
	 }
	 return s1;
}

/*
 *概述：将s1中指向的对象赋值为0,
 *返回值：返回s1的值
 */
void *bzero(char *s1)
{
	return memset(s1, 0, strlen(s1));
}

/*
 *概述：将s指向的n个字符用c填充
 *返回值：返回s的值
 */
void *memset(void *s, int c, size_t n)
{
	char *sc = s;

	for (sc = s; n > 0; --n) {
		*sc++ = c;
	}

	return s;
}

/*
 *概述：对s1指向的串和s2指向的串进行比较
 *返回值：当s1指向的串大于，等于或者小于s2指向的串是，返回一个大于，等于或者小于零的整数
 */
int strcmp(const char *s1, const char *s2)
{
	for (; *s1 == *s2; ++s1, ++s2) {
		if (*s1 == '\0') {
			return 0;
		}
	}

	return (*(unsigned char *)s1 < *(unsigned char *)s2)? -1: 1;
}
