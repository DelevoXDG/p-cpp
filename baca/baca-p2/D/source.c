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
	for (i = end; i > start; i--) {
		*(matrix + i - 1 + offset) = *(matrix + i - 1);
	}
	return matrix;
}
int** shiftUpMatrix(int** const matrix, const uint16 start, const uint16 end, const uint16 offset) {
	int i = 0;
	for (i = start; i < end - offset; i++) {
		*(matrix + i) = *(matrix + i + offset);
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
uint16* shiftUpArray(uint16* const arr, const uint16 start, const uint16 end, const uint16 offset) {
	int i = 0;
	for (i = start; i < end - offset; i++) {
		*(arr + i) = *(arr + i + offset);
	}
	return arr;
}
int* shiftRightArray(int* const arr, const uint16 start, const uint16 end, const uint16 offset) {
	int i = 0;
	for (i = end; i > start; i--) {
		*(arr + i - 1 + offset) = *(arr + i - 1);
	}
	return arr;
}
int* shiftLeftArray(int* const arr, const uint16 start, const uint16 end, const uint16 offset) {
	int i = 0;
	for (i = start; i < end - offset; i++) {
		*(arr + i) = *(arr + i + offset);
	}
	return arr;
}

int** printMatrix(int** const matrix, const uint16 rowCount, uint16* const rowWidth) {
	printf("%d\n", rowCount);
	int i = 0;
	for (i = 0; i < rowCount; i++) {
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
void insertRowBefore(int*** matrix, uint16* rowCount, uint16** rowWidth, uint16 newRowWidth, uint16 offset) {
	if (*matrix == nullptr) {
		*matrix = malloc(((*rowCount) + 1) * sizeof(**matrix));
	}
	else {
		*matrix = realloc(*matrix, ((*rowCount) + 1) * sizeof(**matrix));
	}
	if (*rowWidth == nullptr) {
		*rowWidth = malloc((*rowCount + 1) * sizeof(**rowWidth));
	}
	else {
		*rowWidth = realloc(*rowWidth, (*rowCount + 1) * sizeof(**rowWidth));
	}


	int* newRow = malloc(newRowWidth * sizeof(*newRow));
	newRow = readArrayStdin(newRow, newRowWidth);

	*matrix = shiftDownMatrix(*matrix, offset, *rowCount, 1);
	*rowWidth = shiftDownArray(*rowWidth, offset, *rowCount, 1);
	*(*matrix + offset) = newRow;
	*(*rowWidth + offset) = newRowWidth;

	*rowCount = *rowCount + 1;
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

void insertRowBeforeFromArr(int*** matrix, uint16* rowCount, uint16** rowWidth, uint16 newRowWidth, uint16 offset, int** insertedArray) {
	if (*matrix == nullptr) {
		*matrix = malloc(((*rowCount) + 1) * sizeof(**matrix));
	}
	else {
		*matrix = realloc(*matrix, ((*rowCount) + 1) * sizeof(**matrix));
	}
	if (*rowWidth == nullptr) {
		*rowWidth = malloc((*rowCount + 1) * sizeof(**rowWidth));
	}
	else {
		*rowWidth = realloc(*rowWidth, (*rowCount + 1) * sizeof(**rowWidth));
	}


	int* newRow = malloc(newRowWidth * sizeof(*newRow));
	int i = 0;
	for (i = 0; i < newRowWidth; i++) {
		*(newRow + i) = *(*insertedArray + i);
	}

	*matrix = shiftDownMatrix(*matrix, offset, *rowCount, 1);
	*rowWidth = shiftDownArray(*rowWidth, offset, *rowCount, 1);
	*(*matrix + offset) = newRow;
	*(*rowWidth + offset) = newRowWidth;

	*rowCount = *rowCount + 1;
}


void cleanAll(int*** matrix, uint16* rowCount, uint16** rowWidth) {
	if (*rowCount == 0) {
		return;
	}
	int i;
	for (i = 0; i < *rowCount; i++) {
		free(*(*matrix + i));
	}
	free(*matrix);
	free(*rowWidth);
	*matrix = nullptr;
	*rowWidth = nullptr;
}


void insertBlock(int*** matrix, uint16* rowCount, uint16** rowWidth, uint16 rowOffset, uint16 colOffset, uint16 blockHeight, uint16 blockWidth) {
	int** insertedBlock = nullptr;
	uint16* insertedBlockWidth = nullptr;
	uint16 curBlockHeight = 0;
	// insertedBlock = malloc((blockHeight * sizeof(**matrix)));
	// insertedBlockWidth = malloc((blockHeight * sizeof(**insertedBlock)));
	int i = 0;
	for (i = 0; i < blockHeight; i++) {
		// uint16 curRowLen = *(*rowWidth + i);
		// insertRowBefore(int*** matrix, uint16 * rowCount, uint16 * *rowWidth, uint16 newRowWidth, uint16 offset) {
		insertRowBefore(&insertedBlock, &curBlockHeight, &insertedBlockWidth, blockWidth, curBlockHeight);
	}
	// printMatrix(insertedBlock, blockHeight, insertedBlockWidth);
	for (i = 0; i < blockHeight && i < *rowCount - rowOffset; i++) {
		// int j = 0;
		// for (j = 0; j < blockWidth; j++) {
		// }
		insertArrayBefore(&*(*matrix + i + rowOffset), &*(*rowWidth + i + rowOffset), blockWidth, colOffset, &*(insertedBlock + i));
	}
	while (i < blockHeight) {
		insertRowBeforeFromArr(matrix, rowCount, rowWidth, blockWidth, *rowCount, &*(insertedBlock + i));
		i++;
	}
	cleanAll(&insertedBlock, &curBlockHeight, &insertedBlockWidth);

}


void skipLine(uint16 skipCount) {
	int dummy = 0;
	int i = 0;
	for (i = 0; i < skipCount; i++) {
		scanf("%d", &dummy);
	}
}

void removeRowAt(int*** matrix, uint16* rowCount, uint16** rowWidth, uint16 removedAt) {
	if (removedAt >= *rowCount) {
		return;
	}
	free(*(*matrix + removedAt));
	*matrix = shiftUpMatrix(*matrix, removedAt, *rowCount, 1);
	*rowWidth = shiftUpArray(*rowWidth, removedAt, *rowCount, 1);

	*matrix = realloc(*matrix, (*rowCount - 1) * sizeof(**matrix));
	*rowWidth = realloc(*rowWidth, (*rowCount - 1) * sizeof(**rowWidth));

	*rowCount = *rowCount - 1;
}
void removeBlock(int*** matrix, uint16* rowCount, uint16** colCount, uint16 rowStart, uint16 columnStart, uint16 rowOffset, uint16 colOffset) {
	uint16 rowEnd = rowStart + rowOffset;
	if (rowEnd > *rowCount) {
		rowEnd = *rowCount;
	}
	int rowChanges = rowStart;
	int i = 0;
	for (i = rowStart; rowChanges < rowEnd; i++, rowChanges++) {
		uint16 curColLength = *(*colCount + i);
		if (columnStart >= curColLength) {
			continue;
		}
		int columnEnd = columnStart + colOffset;
		if (columnEnd > curColLength) {
			columnEnd = curColLength;
		}
		int removedColsCount = columnEnd - columnStart;
		if (curColLength <= removedColsCount) {
			removeRowAt(matrix, rowCount, colCount, i);
			i--;
			continue;
		}
		// int* newRow = *(matrix + i);
		shiftLeftArray(*(*matrix + i), columnStart, curColLength, removedColsCount);
		// *(*matrix + i) = realloc(*matrix, (*rowCount - 1) * sizeof(**matrix));
		*(*colCount + i) = curColLength - removedColsCount;

	}
	// for ()
}

int main()
{
	char* opStr = malloc(4 * sizeof(char));


	int** matrix = nullptr;							// Master array, contatins pointers to arrays of variable size
	unsigned short int  rowCount = 0;				// Master Array length a.k.a number of rows
	unsigned short int* colCount = nullptr;		// Array of row lengths a.k.a column count for each row

	Instruction OP;
	while (OP != END) {
		scanf("%s", opStr);
		*(opStr + 3) = '\0';
		OP = opParse(opStr);
		uint16 rowOffset = 0;
		uint16 colOffset = 0;
		uint16 blockHeight = 0;
		uint16 blockWidth = 0;

		//  [x] Isb
		// 	[x] Ibr
		// 	[ ] Rmb
		// 	[x] Swr
		// 	[x] Swc
		// 	[ ] Pliki

		switch (OP) {
			case AFR: {
				//printf("hello AFR\n");
				uint16 newRowWidth = 0;
				scanf("%hu", &newRowWidth);
				insertRowBefore(&matrix, &rowCount, &colCount, newRowWidth, 0);

				break;
			}
			case ALR: {
				//printf("hello ALR\n");

				uint16 newRowWidth = 0;
				scanf(" %hu", &newRowWidth);
				insertRowBefore(&matrix, &rowCount, &colCount, newRowWidth, rowCount);
				break;
			}
			case AFC: {
				scanf(" %hu", &blockHeight);

				insertBlock(&matrix, &rowCount, &colCount, 0, 0, blockHeight, 1);
				break;
			}
			case ALC: {
				//printf("hello ALC\n");
				scanf(" %hu", &blockHeight);

				insertBlock(&matrix, &rowCount, &colCount, 0, 65535, blockHeight, 1);
				break;
			}
			case IBR: {
				//printf("hello IBR\n");
				scanf(" %hu %hu", &rowOffset, &blockWidth);
				if (rowOffset >= rowCount) {
					skipLine(blockWidth);
					break;
				}

				insertRowBefore(&matrix, &rowCount, &colCount, blockWidth, rowOffset);
				break;
			}
			case IAR: {
				//printf("hello IAR\n");
				scanf(" %hu %hu", &rowOffset, &blockWidth);
				if (rowOffset >= rowCount) {
					skipLine(blockWidth);
					break;
				}

				insertRowBefore(&matrix, &rowCount, &colCount, blockWidth, rowOffset + 1);
				break;
			}
			case IBC: {
				//printf("hello IBC\n");
				scanf(" %hu %hu", &colOffset, &blockHeight);
				insertBlock(&matrix, &rowCount, &colCount, 0, colOffset, blockHeight, 1);
				break;
			}
			case IAC: {
				//printf("hello IAC\n");
				scanf(" %hu %hu", &colOffset, &blockHeight);
				insertBlock(&matrix, &rowCount, &colCount, 0, colOffset + 1, blockHeight, 1);
				break;
			}
			case SWR: {
				//printf("hello SWR\n");
				uint16 rowA;
				uint16 rowB;
				scanf(" %hu %hu", &rowA, &rowB);
				if (rowA >= rowCount || rowB >= rowCount) {
					break;
				}
				int* tmp = *(matrix + rowA);
				*(matrix + rowA) = *(matrix + rowB);
				*(matrix + rowB) = tmp;

				uint16 tmp1 = *(colCount + rowA);
				*(colCount + rowA) = *(colCount + rowB);
				*(colCount + rowB) = tmp1;

				break;
			}
			case SWC: {
				//printf("hello SWC\n");
				uint16 colA;
				uint16 colB;

				scanf(" %hu %hu", &colA, &colB);
				int i = 0;
				for (i = 0; i < rowCount; i++) {
					uint16 curColCount = *(colCount + i);
					if (colA < curColCount && colB < curColCount) {
						int tmp = *(*(matrix + i) + colA);
						*(*(matrix + i) + colA) = *(*(matrix + i) + colB);
						*(*(matrix + i) + colB) = tmp;
					}
				}
				break;
			}
			case DFR: {
				//printf("hello DFR\n");
				removeRowAt(&matrix, &rowCount, &colCount, 0);

				break;
			}
			case DLR: {
				//printf("hello DLR\n");
				if (rowCount <= 0) {
					break;
				}
				removeRowAt(&matrix, &rowCount, &colCount, rowCount - 1);
				break;
			}
			case DLC: {
				//printf("hello DLC\n");
				break;
			}
			case RMR: {
				//printf("hello RMR\n");
				scanf(" %hu", &rowOffset);
				removeRowAt(&matrix, &rowCount, &colCount, rowOffset);
				break;
			}
			case RMC: {
				//printf("hello RMC\n");
				break;
			}
			case RMB: {
				//printf("hello RMB\n");
				scanf(" %hu %hu %hu %hu", &rowOffset, &colOffset, &blockHeight, &blockWidth);
				removeBlock(&matrix, &rowCount, &colCount, rowOffset, blockHeight, colOffset, blockWidth);
				break;
			}
			case ISB: {
				//printf("hello ISB\n");


				scanf(" %hu %hu %hu %hu", &rowOffset, &colOffset, &blockHeight, &blockWidth);
				insertBlock(&matrix, &rowCount, &colCount, rowOffset, colOffset, blockHeight, blockWidth);
				break;
			}
			case WRF: {
				//printf("hello WRF\n");
				break;
			}
			case RDF: {
				//printf("hello RDF\n");
				break;
			}
			case PRT: {
				//printf("hello PRT\n");
				printMatrix(matrix, rowCount, colCount);
				break;
			}
			case END: {
				cleanAll(&matrix, &rowCount, &colCount);
				// if (rowCount == 0) {
				// 	break;
				// }
				// int i = 0;
				// for (i = 0; i < rowCount; i++) {
				// 	free(*(matrix + i));
				// }
				// printf("%p\n", &rowCount);

				// free(matrix);
				// free(rowWidth);
				// rowWidth = nullptr;
				break;
			}
			case undefined:
				break;
		}
	}
	free(opStr);
	return 0;
}
