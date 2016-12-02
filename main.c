#include<stdio.h>
#include<stdlib.h>
#include<math.h>

float* allocateMatrix(int rows, int cols);
float* getMatrixWithoutLines(float* matrix, int rows, int cols, int rowToRemove, int colToRemove);
void printMatrix(float* matrix, int rows, int cols);
void fillMatrix(float* matrix, int rows, int cols, unsigned int autoFill);
float calculateDeterminant(float* matrix, int rows, int cols);
int calculateRank(float* matrix, int rows, int cols);
float* getSubMatrix(float* matrix, int rows, int cols, int offsetRow, int offsetCol, int lengthRows, int lengthCols);
float* getAggiunta(float* matrix, int rows, int cols);
float* prodottoPerScalare(float* matrix, int rows, int cols, int x);

int main(){
	int rows, cols;
	float* matrix;
	printf("Inserisci il numero di righe: ");
	scanf("%d", &rows);
	printf("Inserisci il numero di colonne: ");
	scanf("%d", &cols);
	
	matrix = allocateMatrix(rows, cols);
	fillMatrix(matrix, rows, cols, 1);//0 to autofill
	printMatrix(matrix, rows, cols);
	float determinante;
	if(rows==cols){
		determinante = calculateDeterminant(matrix, rows, cols);
		printf("Determinante: %-5.2f\n", determinante);
	}
	
	int rango = calculateRank(matrix, rows, cols);
	printf("rango: %d\n", rango);

	float* aggiunta = getAggiunta(matrix, rows, cols);
	printf("Matrice inversa:");
	printMatrix(aggiunta, cols, rows);
	
	if(rows==cols && determinante!=0){
		printf("Matrice inversa:");
		float* inversa = prodottoPerScalare(aggiunta, rows, cols, 1/determinante);
		printMatrix(inversa, rows, cols);
	}


	//in the end...
	free(matrix);
	return 0;
}

int calculateRank(float* matrix, int rows, int cols){
	float det = 0;
	int offset = 0;
	float* littleMatrix;
	int Max=(rows>=cols) ? cols : rows;
	int n=Max;
	while(n>0){
		littleMatrix = (float*)malloc(sizeof(float) *pow(n,2));
		for(int i=0;i<=rows-n && det==0;i++){
			for(int j=0;j<=cols-n && det==0;j++){
				littleMatrix = getSubMatrix(matrix, rows, cols, i, j, n,n);
				if(n==1 && littleMatrix[0]!=0)return 1;
				det = calculateDeterminant(littleMatrix, n,n);
			}
		}
		
		if(det==0){
			n--;
		}
		else{
			printf("Maggiore sottomatrice quadrata non singolare:\n");
			printMatrix(littleMatrix,n,n);
			return n;
		}	
	}
	return 0;
}

float* getSubMatrix(float* matrix, int rows, int cols, int offsetRow, int offsetCol, int lengthRows, int lengthCols){
	float* littleMatrix = allocateMatrix(lengthRows,lengthCols);
	int littleOffset = 0;
	for(int i=offsetRow; i<offsetRow+lengthRows;i++){
		for(int j=offsetCol; j<offsetCol+lengthCols;j++){
			int offset = i*cols+j;
			littleMatrix[littleOffset++] = matrix[offset];
		}
	}
	return littleMatrix;
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
		float result = 0.0;
		for(int j=0;j<cols;j++){
			if(matrix[j]!=0){
				float* littleMatrix = getMatrixWithoutLines(matrix, rows, cols, 0, j);
				result += matrix[j] * pow(-1, j) * calculateDeterminant(littleMatrix, rows-1, cols-1);
				free(littleMatrix);
			}
		}
		return result;
	}
}

float* getAggiunta(float* matrix, int rows, int cols){
	float* out = (float*)malloc(sizeof(float)*rows*cols);
	for(int i=0;i<rows;i++){
		for(int j=0;j<cols;j++){
			int offset = i*cols+j;
			float* littleMatrix = getMatrixWithoutLines(matrix, rows, cols, j, i);
			float det = calculateDeterminant(littleMatrix, rows-1, cols-1);
			out[offset] = pow(-1, i+j) * det;
			free(littleMatrix);
		}
		
	}
	return out;
}

float* prodottoPerScalare(float* matrix, int rows, int cols, int x){
	float* out = (float*)malloc(sizeof(float)*rows*cols);
	for(int i=0;i<rows*cols;i++){
		out[i] = out[i]*x;
	}
	return out;
}
