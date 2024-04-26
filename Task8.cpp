#include <iostream>
#include <pthread.h>
using namespace std;

int arrayA[3][4] = {{100, 20, 3, 50}, {40, 33, 56, 2}, {150, 23, 17, 22}};
int arrayB[4][3] = {{56, 13, 9}, {22, 15, 55}, {19, 200, 27}, {100, 60, 14}};
int matC[3][3];

struct threadTask {
	int row, col;
};

void* multiplyMatrices(void* arg)
{
	threadTask* assignedData = (threadTask*) arg;
	for (int i = 0; i < 4; i++)
	{
		matC[assignedData->row][assignedData->col] += arrayA[assignedData->row][i] * arrayB[i][assignedData->col];
	}
	pthread_exit(NULL);
}

int main () {
	pthread_t pthreadsArr[9];
	threadTask threadRowColAssign[9];
	int x = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			threadRowColAssign[3*i+j].row = i;
			threadRowColAssign[3*i+j].col = j;
			pthread_create(&pthreadsArr[x], NULL, &multiplyMatrices, &threadRowColAssign[3*i+j]);
			x++;
		}
	}
	for (int i = 0; i < 9; i++) {
        pthread_join(pthreadsArr[i], NULL);
    }
    for (int i = 0; i < sizeof(matC)/sizeof(matC[0]); i++) {
        for (int j = 0; j < sizeof(matC[0])/sizeof(int); j++) {
			cout << matC[i][j] << ' ';
        }
        cout << endl;
    }
	return 0;
}