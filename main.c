#include<stdio.h>
#include<stdlib.h>
#include<math.h>

float* allocateMatrix(int rows, int cols);
float* getMatrixWithoutLines(float* matrix, int rows, int cols, int rowToRemove, int colToRemove);
void printMatrix(float* matrix, int rows, int cols);
void fillMatrix(float* matrix, int rows, int cols, unsigned int autoFill);
float calculateDeterminant(float* matrix, int rows, int cols);


int main(){
	int rows, cols;
	float* matrix;
	printf("Inserisci il numero di righe: ");
	scanf("%d", &rows);
	printf("Inserisci il numero di colonne: ");
	scanf("%d", &cols);
	
	matrix = allocateMatrix(rows, cols);
	fillMatrix(matrix, rows, cols, 0);//0 to autofill
	printMatrix(matrix, rows, cols);
	
	float determinante = calculateDeterminant(matrix, rows, cols);
	printf("Determinante: %-5.2f\n", determinante);
	//in the end...
	free(matrix);
	return 0;
}

float* allocateMatrix(int rows, int cols){
	return (float*)malloc(rows * cols * sizeof(float));
	
}

void fillMatrix(float* matrix, int rows, int cols, unsigned int autoFill){
	//0-->autoFills, 1--> must be filled
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			if(autoFill==0){
				matrix[cols*i+j] = cols*i+j+1;
			}else{
				printf("Inserisci elemento %d,%d: ", i+1, j+1);
				scanf("%f", &matrix[cols*i+j]);
			}
			
		}
	}
}

void printMatrix(float* matrix, int rows, int cols){
	printf("\n");	
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			printf("%6.1f", matrix[cols*i+j]);
		}
		printf("\n");
	}
	printf("\n");
}

float* getMatrixWithoutLines(float* matrix, int rows, int cols, int rowToRemove, int colToRemove){
	float* out = allocateMatrix(rows-1, cols-1);
	int index = 0;
	for(int i=0;i<rows;i++){
		if(i!=rowToRemove){
			for(int j=0;j<cols;j++){
				if(j!=colToRemove){
					out[index] = matrix[cols*i+j];
					index++;
				}
				
			}
		}
			
	}
	return out;
}

float calculateDeterminant(float* matrix, int rows, int cols){
	if(rows==2 && cols==2){
		return matrix[0] * matrix[3] - matrix[1] * matrix[2];
	}else{
		int result = 0;
		for(int j=0;j<cols;j++){
			float* littleMatrix = getMatrixWithoutLines(matrix, rows, cols, 0, j);
			result += matrix[j] * pow(-1, j) * calculateDeterminant(littleMatrix, rows-1, cols-1);
			free(littleMatrix);
		}
	}
}
