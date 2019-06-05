#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *compute_prefix_function(char *pattern, int psize)
{
	int j = -1;
	int i = 1;
	int *pi = malloc(sizeof(int)*psize);
	if (!pi)
		return NULL;

	pi[0] = j;
	for (i = 1; i < psize; i++) {
		while (j > -1 && pattern[j+1] != pattern[i])
			j = pi[j];
		if (pattern[i] == pattern[j+1])
			j++;
		pi[i] = j;
	}
	return pi;
}

int kmp(char *target, int tsize, char *pattern, int psize)
{
	int i;
	int *pi = compute_prefix_function(pattern, psize);
	int k = -1;
	if (!pi)
		return -1;
	for (i = 0; i < tsize; i++) {
		while (k > -1 && pattern[k+1] != target[i])
			k = pi[k];
		if (target[i] == pattern[k+1])
			k++;
		if (k == psize - 1) {
			free(pi);
			return i-k;
		}
	}
	free(pi);
	return -1;
}

int main(int argc, const char *argv[])
{
	char target[] = "ABC ABCDAB ABCDABCDABDE";
	char *ch = target;
	char pattern[] = "ABCDABD";
	int i;

	i = kmp(target, strlen(target), pattern, strlen(pattern));
	if (i >= 0)
		printf("matched @: %s\n", ch + i);
	return 0;
}
