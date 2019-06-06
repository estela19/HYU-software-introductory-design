#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
void print_matrix(int** matrix, int angle);
int** rotate(int** matrix);
int** newmat(int row, int col);

int main() {
	int row, col;
	
	// ����� ũ�⸦ �Է¹���
	printf("Input row size of the matrix : ");
	scanf("%d", &row);
	printf("Input column size of the matrix : ");
	scanf("%d", &col);

	//ũ�⿡ �´� ���ο� ����� ����
	int** mat = newmat(row, col);
	
	//n�� ����
	int n = 0;
	while (n < 4) {
		print_matrix(mat, n * 90);
		//���� ����� ȸ��
		mat = rotate(mat);
		n++;
	}

	//�޸� ����
	for (int i = 0; i < row; i++) {
		free(mat[i]);
		mat[i] = 0;
	}
	free(mat);
	mat = 0;

	return 0;
}

//���ο� ����� ����� �Լ�
int** newmat(int row, int col) {
	//ũ�⿡ �´� ������ ������ ���� �� �����Ҵ�
	int** mat = NULL;
	mat = (int**)malloc((row) * sizeof(int*));

	//���� ������ �����͹迭�� ������ ������ �迭�� ����
	int num = 0;
	for (int i = 0; i < row; i++) {
		mat[i] = (int*)malloc((col) * sizeof(int));
		
		//��Ŀ� ���ڸ� ä�� ����
		for (int j = 0; j < col; j++)
		{
			num++;
			mat[i][j] = num;
		}
	}
	return mat;
}


int** rotate(int** matrix) {
	int rowsize, colsize;
	
	//���ο� ������ ũ�⸦ ����
	rowsize = _msize(matrix) / sizeof(int*);
	colsize = _msize(matrix[0]) / sizeof(int);

	//ȸ���ϸ� ���ο� ������ ũ�Ⱑ ���ϹǷ� ���μ��� �ݴ�� ��� ����
	int** new_matrix;
	new_matrix = newmat(colsize, rowsize);

	//���� ����� 90�� ȸ��
	for (int i = 0; i < rowsize; i++) {
		for (int j = 0; j < colsize; j++) {
			new_matrix[j][rowsize - i - 1] = matrix[i][j];
		}
	}

	//���� �ִ� ��� �Ҵ�����
	for (int i = 0; i < rowsize; i++) {
		free(matrix[i]);
		matrix[i] = 0;
	}
	free(matrix);
	matrix = 0;
	return new_matrix;
}

//��� ����Լ�
void print_matrix(int** matrix, int angle) {
	int rowsize, colsize;
	
	//����� ���� ���� ũ�⸦ ����
	rowsize = _msize(matrix) / sizeof(int*);
	colsize = _msize(matrix[0]) / sizeof(int);

	//���� ũ�⸦ �������� ������ ĭ ���
	printf("< degree : %d >\n", angle);
	for (int i = 0; i < rowsize; i++) {
		for (int j = 0; j < colsize; j++) {
			printf("%4d", matrix[i][j]);
		}
		printf("\n");
	}
}