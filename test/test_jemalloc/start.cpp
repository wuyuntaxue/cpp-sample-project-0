
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <list>

extern "C" {
	#include "jemalloc/jemalloc.h"
}

int main()
{
	int i = 0;
	int iCount = 500;
	int iSize = 1000;

	std::list<int*> pMemBuf;

	for (i = 0; i < iCount; i++)
	{
		int* pMem = (int *)malloc(iSize);
		pMemBuf.push_back(pMem);
	}

	malloc_stats_print(NULL, NULL, "gbxem");


	for (i = 0; i < iCount; i++)
	{
		free(pMemBuf.front());
		pMemBuf.pop_front();
	}

	// malloc_message(NULL, NULL);


	printf("press any key exit......\r\n");
	getchar();
	return 0;
}
