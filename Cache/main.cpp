#include <iostream>
#include <Windows.h>

using namespace std;

int buffer[10000][10000];

int main(void) {
	memset(buffer, 0, sizeof(buffer));

	// Cache - Spacial Locality 수행 속도 테스트
	// 배열의 메모리 구조
	// [0,0][0,1][][][]... [1,0][1,1][][][]... [2,0][2,1][][][]...
	{
		int64_t sum = 0;
		uint64_t start = GetTickCount64();

		for (int i = 0; i < 10000; i++) {
			for (int j = 0; j < 10000; j++) {
				sum += buffer[j][i];	// 이게 더 느림
			}
		}

		uint64_t end = GetTickCount64();

		cout << "Elapsed Time : " << end - start << endl;
	}
	{
		int64_t sum = 0;
		uint64_t start = GetTickCount64();

		for (int i = 0; i < 10000; i++) {
			for (int j = 0; j < 10000; j++) {
				sum += buffer[i][j];
			}
		}

		uint64_t end = GetTickCount64();

		cout << "Elapsed Time : " << end - start << endl;
	}

	return 0;
}