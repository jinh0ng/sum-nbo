// main.cpp
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "sum-nbo.h"

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		fprintf(stderr, "Usage: %s <file1> [<file2> ...]\n", argv[0]);
		return 1;
	}

	uint32_t total = 0;
	int first = 1;

	// 모든 파일에 대해 처리
	for (int i = 1; i < argc; i++)
	{
		FILE *fp = fopen(argv[i], "rb");
		if (!fp)
		{
			fprintf(stderr, "Error: 파일 '%s'을 열 수 없음음.\n", argv[i]);
			return 1;
		}

		uint32_t num;
		if (fread(&num, sizeof(uint32_t), 1, fp) != 1)
		{
			fprintf(stderr, "Error: 파일 '%s'에서 4바이트를 읽지 못함함.\n", argv[i]);
			fclose(fp);
			return 1;
		}
		fclose(fp);

		// network byte order -> host byte order 변환
		num = ntohl(num);

		if (first)
		{
			printf("%u(0x%x)", num, num);
			first = 0;
		}
		else
		{
			printf(" + %u(0x%x)", num, num);
		}

		total += num;
	}

	printf(" = %u(0x%x)\n", total, total);
	return 0;
}