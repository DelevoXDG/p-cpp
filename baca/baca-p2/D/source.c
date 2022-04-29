//Maksim Zdobnikau


#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// /usr/bin/gcc -fdiagnostics-color=always -std=gnu89 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment -g source.c -o source ; ./source < "tests/test.00.in"
#define nullptr NULL 

typedef unsigned short int uint16;
typedef enum
{
	false = (1 == 0),
	true = 1 == 1
} bool;

typedef enum {
	AFR = 0,
	ALR,
	AFC,
	ALC,
	IBR,
	IAR,
	IBC,
	IAC,
	SWR,
	SWC,
	DFR,
	DLR,
	DLC,
	RMR,
	RMC,
	RMB,
	ISB,
	WRF,
	RDF,
	PRT,

	END,
	undefined = 404
} Instruction;

Instruction opParse(const char* str) {
	if (strcmp(str, "AFR") == 0) return AFR;
	if (strcmp(str, "ALR") == 0) return ALR;
	if (strcmp(str, "ALR") == 0) return ALR;
	if (strcmp(str, "AFC") == 0) return AFC;
	if (strcmp(str, "ALC") == 0) return ALC;
	if (strcmp(str, "IBR") == 0) return IBR;
	if (strcmp(str, "IAR") == 0) return IAR;
	if (strcmp(str, "IBC") == 0) return IBC;
	if (strcmp(str, "IAC") == 0) return IAC;
	if (strcmp(str, "SWR") == 0) return SWR;
	if (strcmp(str, "SWC") == 0) return SWC;
	if (strcmp(str, "DFR") == 0) return DFR;
	if (strcmp(str, "DLR") == 0) return DLR;
	if (strcmp(str, "DLC") == 0) return DLC;
	if (strcmp(str, "RMR") == 0) return RMR;
	if (strcmp(str, "RMC") == 0) return RMC;
	if (strcmp(str, "RMB") == 0) return RMB;
	if (strcmp(str, "ISB") == 0) return ISB;
	if (strcmp(str, "WRF") == 0) return WRF;
	if (strcmp(str, "RDF") == 0) return RDF;
	if (strcmp(str, "PRT") == 0) return PRT;
	return END;
}


int cstr_length(const char* str) {
	int size = 0;
	int i = 0;
	for (i = 0; str[i] != 0;i++) {
		size++;
	}
	return size;
}
void cstr_copy(char* from, char* to) {
	int i = 0;
	for (i = 0; from[i] != 0;i++) {
		to[i] = from[i];
	}
	to[i] = '\0';

}
bool cstr_compare(const char* str1, const char* str2) {
	if (cstr_length(str1) != cstr_length(str2)) return false;
	int i = 0;
	for (i = 0; str1[i] != '\0'; i++) {
		if (str1[i] != str2[i]) return false;
	}

	return true; //cstrs are equal
}

int cstr_find(char* str, char key) {
	int i = 0;
	for (i = 0; str[i] != '\0'; i++) {
		if (str[i] == key) return i; //Return position of Character
	}
	return -1; //Returns -1 if position was not found
}

void cstr_substr(char* str, char* substr, int begin, int end) {
	int i = 0;
	int j = 0;
	for (i = begin; i < end; i++) {
		substr[j] = str[i];
		j++;
	}
	substr[j] = '\0';
}
int* readArrayStdin(int* arr, const uint16 rowLen) {
	int i = 0;
	for (i = 0; i < rowLen; i++) {
		int num;
		scanf("%d", &num);
		*(arr + i) = num;
	}
	return arr;
}
int** shiftDownMatrix(int** const matrix, const uint16 start, const uint16 end, const uint16 offset) {
	int i = 0;
	// for (i = end + 1; i > start; i--) {
	for (i = end; i > start; i--) {
		*(matrix + i - 1 + offset) = *(matrix + i - 1);
	}
	return matrix;
}
uint16* shiftDownArray(uint16* const arr, const uint16 start, const uint16 end, const uint16 offset) {
	int i = 0;
	for (i = end; i > start; i--) {
		*(arr + i - 1 + offset) = *(arr + i - 1);
	}
	return arr;
}
int* shiftRightArray(int* const arr, const uint16 start, const uint16 end, const uint16 offset) {
	int i = 0;
	for (i = end; i > start; i--) {
		// *(arr + i) = *(arr + i - 1);
		*(arr + i - 1 + offset) = *(arr + i - 1);
	}
	return arr;
}
// int* shiftUp(int * const arr, const uint16 start, const uint16 )

int** printMatrix(int** const matrix, const uint16 matrixHeight, uint16* const rowWidth) {
	printf("%d\n", matrixHeight);
	int i = 0;
	for (i = 0; i < matrixHeight; i++) {
		int rowLen = *(rowWidth + i);
		printf("%d", rowLen);
		int j = 0;
		for (j = 0; j < rowLen; j++) {
			printf(" %d", *(*(matrix + i) + j));
		}
		printf("\n");
	}
	return matrix;
}
void insertRowBefore(int*** matrix, uint16* matrixHeight, uint16** rowWidth, uint16 newRowWidth, uint16 offset) {
	if (*matrix == nullptr) {
		*matrix = malloc(((*matrixHeight) + 1) * sizeof(**matrix));
	}
	else {
		*matrix = realloc(*matrix, ((*matrixHeight) + 1) * sizeof(**matrix));
	}
	if (*rowWidth == nullptr) {
		*rowWidth = malloc((*matrixHeight + 1) * sizeof(**rowWidth));
	}
	else {
		*rowWidth = realloc(*rowWidth, (*matrixHeight + 1) * sizeof(**rowWidth));
	}


	int* newRow = malloc(newRowWidth * sizeof(*newRow));
	newRow = readArrayStdin(newRow, newRowWidth);

	*matrix = shiftDownMatrix(*matrix, offset, *matrixHeight, 1);
	*rowWidth = shiftDownArray(*rowWidth, offset, *matrixHeight, 1);
	*(*matrix + offset) = newRow;
	*(*rowWidth + offset) = newRowWidth;

	*matrixHeight = *matrixHeight + 1;
}
void insertArrayBefore(int** array, uint16* rowWidth, uint16 insertedWidth, uint16 before, int** insertedArr) {
	*array = realloc(*array, (*rowWidth + insertedWidth) * sizeof(**array));
	*array = shiftRightArray(*array, before, *rowWidth, insertedWidth);
	int i = 0;
	if (before >= *rowWidth) {
		before = *rowWidth;
	}
	for (i = 0; i < insertedWidth; i++) {
		*(*array + i + before) = *(*insertedArr + i);
	}

	*rowWidth += insertedWidth;
}

void insertRowBeforeFromArr(int*** matrix, uint16* matrixHeight, uint16** rowWidth, uint16 newRowWidth, uint16 offset, int** insertedArray) {
	if (*matrix == nullptr) {
		*matrix = malloc(((*matrixHeight) + 1) * sizeof(**matrix));
	}
	else {
		*matrix = realloc(*matrix, ((*matrixHeight) + 1) * sizeof(**matrix));
	}
	if (*rowWidth == nullptr) {
		*rowWidth = malloc((*matrixHeight + 1) * sizeof(**rowWidth));
	}
	else {
		*rowWidth = realloc(*rowWidth, (*matrixHeight + 1) * sizeof(**rowWidth));
	}


	int* newRow = malloc(newRowWidth * sizeof(*newRow));
	int i = 0;
	for (i = 0; i < newRowWidth; i++) {
		*(newRow + i) = *(*insertedArray + i);
	}

	*matrix = shiftDownMatrix(*matrix, offset, *matrixHeight, 1);
	*rowWidth = shiftDownArray(*rowWidth, offset, *matrixHeight, 1);
	*(*matrix + offset) = newRow;
	*(*rowWidth + offset) = newRowWidth;

	*matrixHeight = *matrixHeight + 1;
}


void cleanAll(int*** matrix, uint16* matrixHeight, uint16** rowWidth) {
	if (*matrixHeight == 0) {
		return;
	}
	int i;
	for (i = 0; i < *matrixHeight; i++) {
		free(*(*matrix + i));
	}
	free(*matrix);
	free(*rowWidth);
	*matrix = nullptr;
	*rowWidth = nullptr;
}


void insertBlock(int*** matrix, uint16* matrixHeight, uint16** rowWidth) {
	uint16 rowOffset = 0;
	uint16 colOffset = 0;
	uint16 blockHeight = 0;
	uint16 blockWidth = 0;


	scanf(" %hu %hu %hu %hu", &rowOffset, &colOffset, &blockHeight, &blockWidth);

	int** insertedBlock = nullptr;
	uint16* insertedBlockWidth = nullptr;
	uint16 curBlockHeight = 0;
	// insertedBlock = malloc((blockHeight * sizeof(**matrix)));
	// insertedBlockWidth = malloc((blockHeight * sizeof(**insertedBlock)));
	int i = 0;
	for (i = 0; i < blockHeight; i++) {
		// uint16 curRowLen = *(*rowWidth + i);
		// insertRowBefore(int*** matrix, uint16 * matrixHeight, uint16 * *rowWidth, uint16 newRowWidth, uint16 offset) {
		insertRowBefore(&insertedBlock, &curBlockHeight, &insertedBlockWidth, blockWidth, curBlockHeight);
	}
	printMatrix(insertedBlock, blockHeight, insertedBlockWidth);
	for (i = 0; i < blockHeight && i < *matrixHeight - rowOffset; i++) {
		// int j = 0;
		// for (j = 0; j < blockWidth; j++) {
		// }
		insertArrayBefore(&*(*matrix + i + rowOffset), &*(*rowWidth + i + rowOffset), blockWidth, colOffset, &*(insertedBlock + i));
	}
	while (i < blockHeight) {
		insertRowBeforeFromArr(matrix, matrixHeight, rowWidth, blockWidth, *matrixHeight, &*(insertedBlock + i));
		i++;
	}
	cleanAll(&insertedBlock, &curBlockHeight, &insertedBlockWidth);

	return;
}



int main(int argc, char const** argv)
{
	char* opStr = malloc(4 * sizeof(char));


	int** matrix = nullptr;							// Master array, contatins pointers to arrays of variable size
	unsigned short int  matrixHeight = 0;				// Master Array length a.k.a number of rows
	unsigned short int* rowWidth = nullptr;		// Array of row lengths a.k.a column count for each row

	Instruction OP;
	while (OP != END) {
		scanf("%s", opStr);
		*(opStr + 3) = '\0';
		OP = opParse(opStr);

		//  [ ] Isb
		// 	[ ] Ibr
		// 	[ ] Rmb
		// 	[ ] Swr
		// 	[ ] Swc
		// 	[ ] Pliki

		switch (OP) {
			case AFR: {
				printf("hello AFR\n");
				uint16 newRowWidth = 0;
				scanf("%hu", &newRowWidth);
				insertRowBefore(&matrix, &matrixHeight, &rowWidth, newRowWidth, 0);

				break;
			}
			case ALR: {
				printf("hello ALR\n");

				int rowLen = 0;
				scanf("%d", &rowLen);
				break;
			}
			case AFC: {
				printf("hello AFC\n");
				int rowLen = 0;
				scanf("%d", &rowLen);
				break;
			}
			case ALC: {
				printf("hello ALC\n");
				break;
			}
			case IBR: {
				printf("hello IBR\n");
				break;
			}
			case IAR: {
				printf("hello IAR\n");
				break;
			}
			case IBC: {
				printf("hello IBC\n");
				break;
			}
			case IAC: {
				printf("hello IAC\n");
				break;
			}
			case SWR: {
				printf("hello SWR\n");
				break;
			}
			case SWC: {
				printf("hello SWC\n");
				break;
			}
			case DFR: {
				printf("hello DFR\n");
				break;
			}
			case DLR: {
				printf("hello DLR\n");
				break;
			}
			case DLC: {
				printf("hello DLC\n");
				break;
			}
			case RMR: {
				printf("hello RMR\n");
				break;
			}
			case RMC: {
				printf("hello RMC\n");
				break;
			}
			case RMB: {
				printf("hello RMB\n");
				break;
			}
			case ISB: {
				printf("hello ISB\n");
				insertBlock(&matrix, &matrixHeight, &rowWidth);
				break;
			}
			case WRF: {
				printf("hello WRF\n");
				break;
			}
			case RDF: {
				printf("hello RDF\n");
				break;
			}
			case PRT: {
				printf("hello PRT\n");
				printMatrix(matrix, matrixHeight, rowWidth);
				break;
			}
			case END: {
				cleanAll(&matrix, &matrixHeight, &rowWidth);
				// if (matrixHeight == 0) {
				// 	break;
				// }
				// int i = 0;
				// for (i = 0; i < matrixHeight; i++) {
				// 	free(*(matrix + i));
				// }
				// printf("%p\n", &matrixHeight);

				// free(matrix);
				// free(rowWidth);
				// rowWidth = nullptr;
				break;
			}

		}
	}
	free(opStr);
	return 0;
}
