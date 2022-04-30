//Maksim Zdobnikau
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// /usr/bin/gcc -fdiagnostics-color=always -std=gnu89 -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment -g source.c -o source ; ./source < "tests/test.00.in"
#define nullptr NULL 

typedef unsigned short int uint16;
typedef enum {
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
	DFC,
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
} Operation;

Operation opParse(const char* str) {
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
	if (strcmp(str, "DFC") == 0) return DFC;
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
void insertRowBefore(int*** matrix, uint16* const rowCount, uint16** rowWidth, uint16 newRowWidth, const uint16 offset) {
	if (newRowWidth <= 0) {
		return;
	}
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

void insertColsBefore(int** array, uint16* rowWidth, const uint16 insertedWidth, uint16 before, int** insertedArr) {
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


void cleanAll(int*** matrix, uint16* const rowCount, uint16** rowWidth) {
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
	*rowCount = 0;
}



void insertBlock(int*** matrix, uint16* const rowCount, uint16** rowWidth, const uint16 rowOffset, const uint16 colOffset, const uint16 blockHeight, const uint16 blockWidth) {
	int** insertedBlock = nullptr;
	uint16* insertedBlockWidth = nullptr;
	uint16 curBlockHeight = 0;

	int i = 0;
	for (i = 0; i < blockHeight; i++) {

		insertRowBefore(&insertedBlock, &curBlockHeight, &insertedBlockWidth, blockWidth, curBlockHeight);
	}
	// printMatrix(insertedBlock, blockHeight, insertedBlockWidth);
	for (i = 0; i < blockHeight && i < *rowCount - rowOffset; i++) {
		insertColsBefore(&*(*matrix + i + rowOffset), &*(*rowWidth + i + rowOffset), blockWidth, colOffset, &*(insertedBlock + i));
	}
	while (i < blockHeight) {
		insertRowBeforeFromArr(matrix, rowCount, rowWidth, blockWidth, *rowCount, &*(insertedBlock + i));
		i++;
	}
	cleanAll(&insertedBlock, &curBlockHeight, &insertedBlockWidth);
}


void skipLine(const uint16 skipCount) {
	int dummy = 0;
	int i = 0;
	for (i = 0; i < skipCount; i++) {
		scanf("%d", &dummy);
	}
}

void removeRowAt(int*** matrix, uint16* const rowCount, uint16** rowWidth, const uint16 removedAt) {
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
void removeBlock(int*** matrix, uint16* const rowCount, uint16** colCount, const uint16 rowStart, const uint16 rowOffset, const uint16 columnStart, const uint16 colOffset) {
	uint16 rowEnd = rowStart + rowOffset;
	if (rowEnd > *rowCount) {
		rowEnd = *rowCount;
	}
	int rowChanges = rowStart;
	int i = 0;
	for (i = rowStart; rowChanges < rowEnd; i++, rowChanges++) {
		uint16 curColCount = *(*colCount + i);
		if (columnStart >= curColCount) {
			continue;
		}
		int columnEnd = columnStart + colOffset;
		if (columnEnd > curColCount) {
			columnEnd = curColCount;
		}
		int removedColsCount = columnEnd - columnStart;
		if (curColCount <= removedColsCount) {
			removeRowAt(matrix, rowCount, colCount, i);
			i--;
			continue;
		}
		// int* newRow = *(matrix + i);
		shiftLeftArray(*(*matrix + i), columnStart, curColCount, removedColsCount);
		*(*matrix + i) = realloc(*(*matrix + i), (curColCount - removedColsCount) * sizeof(**matrix));
		*(*colCount + i) = curColCount - removedColsCount;

	}
}

void removeLastColumn(int*** matrix, uint16* const rowCount, uint16** colCount) {
	uint16 rowStart = 0;
	uint16 rowOffset = *rowCount;

	uint16 rowEnd = rowStart + rowOffset;
	if (rowEnd > *rowCount) {
		rowEnd = *rowCount;
	}
	int rowChanges = rowStart;
	int i = 0;
	for (i = rowStart; rowChanges < rowEnd; i++, rowChanges++) {
		uint16 curColCount = *(*colCount + i);

		if (curColCount <= 1) {
			removeRowAt(matrix, rowCount, colCount, i);
			i--;
			continue;
		}
		shiftLeftArray(*(*matrix + i), curColCount - 1, curColCount, 1);
		*(*matrix + i) = realloc(*(*matrix + i), (curColCount - 1) * sizeof(**matrix));
		*(*colCount + i) = curColCount - 1;
	}
}
void scanemptyRows(uint16* const rowCount, uint16** const colCount, const char* OP) {
	int i = 0;
	for (i = 0; i < *rowCount; i++) {
		if (*(*colCount + i) == 0) {
			printf("%s caused illegal state\n", OP);
			return;
		}
	}
}

void switchRows(int*** matrix, uint16* const rowCount, uint16** colCount, const uint16 rowA, const uint16 rowB) {
	if (rowA >= *rowCount || rowB >= *rowCount) {
		return;
	}
	int* tmp = *(*matrix + rowA);
	*(*matrix + rowA) = *(*matrix + rowB);
	*(*matrix + rowB) = tmp;

	uint16 tmp1 = *(*colCount + rowA);
	*(*colCount + rowA) = *(*colCount + rowB);
	*(*colCount + rowB) = tmp1;
}
void switchCols(int*** matrix, uint16* const rowCount, uint16** colCount, const uint16 colA, const uint16 colB) {
	int i = 0;
	for (i = 0; i < *rowCount; i++) {
		uint16 curColCount = *(*colCount + i);
		if (colA < curColCount && colB < curColCount) {
			int tmp = *(*(*matrix + i) + colA);
			*(*(*matrix + i) + colA) = *(*(*matrix + i) + colB);
			*(*(*matrix + i) + colB) = tmp;
		}
	}
}

int bigEndianInt(const int num) {
	return ((num >> 24) & 0xff) | ((num << 8) & 0xff0000) | ((num >> 8) & 0xff00) | ((num << 24) & 0xff000000);
}
uint16 bigEndianUS(const uint16 num) {
	return (num >> 8) | (num << 8);
}

void writeToFile(int*** matrix, uint16* const rowCount, uint16** rowWidth, const char* fileName) {
	FILE* destFile = fopen(fileName, "wb");
	fprintf(destFile, "%hu\n", *rowCount);
	int i = 0;
	for (i = 0; i < *rowCount; i++) {
		uint16 curRowWidth = bigEndianUS(*(*rowWidth + i));
		fwrite(&curRowWidth, sizeof(uint16), 1, destFile);
		curRowWidth = *(*rowWidth + i);
		int j = 0;
		for (j = 0; j < curRowWidth; j++) {
			int curValue = bigEndianInt(*(*(*matrix + i) + j));
			// int element = *(*(*matrix + i) + j);
			// int tmp = 0;
			// tmp = element >> 24;
			// fwrite(&tmp, 1, 1, destFile);
			// tmp = (element >> 16) & 0xff;
			// fwrite(&tmp, 1, 1, destFile);
			// tmp = (element >> 8) & 0xff;
			// fwrite(&tmp, 1, 1, destFile);
			// tmp = (element) & 0xff;
			// fwrite(&tmp, 1, 1, destFile);
			fwrite(&curValue, sizeof(int), 1, destFile);
		}
	}
	fclose(destFile);
}
void readFromFile(int*** matrix, uint16* const rowCount, uint16** colCount, const char* fileName) {
	FILE* sourceFile = fopen(fileName, "rb");
	cleanAll(matrix, rowCount, colCount);
	uint16 newRowCount = 0;
	fscanf(sourceFile, "%hu\n", &newRowCount);
	int i = 0;
	for (i = 0; i < newRowCount; i++) {
		uint16 curRowWidth = 0;
		fread(&curRowWidth, sizeof(uint16), 1, sourceFile);
		curRowWidth = bigEndianUS(curRowWidth);
		int j = 0;
		int* newRow = malloc(curRowWidth * sizeof(newRow));
		for (j = 0; j < curRowWidth; j++) {
			int curValue = 0;
			fread(&curValue, sizeof(int), 1, sourceFile);
			curValue = bigEndianInt(curValue);
			// unsigned char tmp = 0;
			// int curValue = 0;
			// fread(&tmp, 1, 1, sourceFile);
			// curValue |= tmp << 24;
			// fread(&tmp, 1, 1, sourceFile);
			// curValue |= tmp << 16;
			// fread(&tmp, 1, 1, sourceFile);
			// curValue |= tmp << 8;
			// fread(&tmp, 1, 1, sourceFile);
			// curValue |= tmp;
			* (newRow + j) = curValue;
		}
		insertRowBeforeFromArr(matrix, rowCount, colCount, curRowWidth, *rowCount, &newRow);
		free(newRow);
	}
	fclose(sourceFile);
}

int main() {
	char* opStr = malloc(4 * sizeof(*opStr));

	int** matrix = nullptr;							// Master array, contatins pointers to arrays of variable size
	uint16  rowCount = 0;				// length a.k.a number of rows
	uint16* colCount = nullptr;			// Array of row lengths a.k.a column count for each row

	Operation OP;
	while (OP != END) {
		// scanemptyRows(&rowCount, &colCount, opStr);
		scanf("%s", opStr);
		*(opStr + 3) = '\0';
		OP = opParse(opStr);
		uint16 rowOStart = 0;
		uint16 colStart = 0;
		uint16 blockHeight = 0;
		uint16 blockWidth = 0;


		switch (OP) {
			case AFR: {
				//printf("hello AFR\n");
				scanf("%hu", &blockWidth);

				insertRowBefore(&matrix, &rowCount, &colCount, blockWidth, 0);
				break;
			}
			case ALR: {
				//printf("hello ALR\n");
				scanf(" %hu", &blockWidth);

				insertRowBefore(&matrix, &rowCount, &colCount, blockWidth, rowCount);
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
				scanf(" %hu %hu", &rowOStart, &blockWidth);
				if (rowOStart >= rowCount) {
					skipLine(blockWidth);
					break;
				}

				insertRowBefore(&matrix, &rowCount, &colCount, blockWidth, rowOStart);
				break;
			}
			case IAR: {
				//printf("hello IAR\n");
				scanf(" %hu %hu", &rowOStart, &blockWidth);
				if (rowOStart >= rowCount) {
					skipLine(blockWidth);
					break;
				}

				insertRowBefore(&matrix, &rowCount, &colCount, blockWidth, rowOStart + 1);
				break;
			}
			case IBC: {
				//printf("hello IBC\n");
				scanf(" %hu %hu", &colStart, &blockHeight);
				insertBlock(&matrix, &rowCount, &colCount, 0, colStart, blockHeight, 1);
				break;
			}
			case IAC: {
				//printf("hello IAC\n");
				scanf(" %hu %hu", &colStart, &blockHeight);
				insertBlock(&matrix, &rowCount, &colCount, 0, colStart + 1, blockHeight, 1);
				break;
			}
			case SWR: {
				//printf("hello SWR\n");
				uint16 rowA;
				uint16 rowB;

				scanf(" %hu %hu", &rowA, &rowB);
				switchRows(&matrix, &rowCount, &colCount, rowA, rowB);
				break;
			}
			case SWC: {
				//printf("hello SWC\n");
				uint16 colA;
				uint16 colB;

				scanf(" %hu %hu", &colA, &colB);
				switchCols(&matrix, &rowCount, &colCount, colA, colB);
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
			case DFC: {
				removeBlock(&matrix, &rowCount, &colCount, 0, rowCount, 0, 1);
				break;
			}
			case DLC: {
				//printf("hello DLC\n");
				removeLastColumn(&matrix, &rowCount, &colCount);
				break;
			}
			case RMR: {
				//printf("hello RMR\n");
				scanf(" %hu", &rowOStart);
				removeRowAt(&matrix, &rowCount, &colCount, rowOStart);
				break;
			}
			case RMC: {
				//printf("hello RMC\n");
				scanf(" %hu", &colStart);
				removeBlock(&matrix, &rowCount, &colCount, 0, rowCount, colStart, 1);
				break;
			}
			case RMB: {
				//printf("hello RMB\n");
				scanf(" %hu %hu %hu %hu", &rowOStart, &blockHeight, &colStart, &blockWidth);

				removeBlock(&matrix, &rowCount, &colCount, rowOStart, blockHeight, colStart, blockWidth);
				break;
			}
			case ISB: {
				//printf("hello ISB\n");
				scanf(" %hu %hu %hu %hu", &rowOStart, &colStart, &blockHeight, &blockWidth);

				insertBlock(&matrix, &rowCount, &colCount, rowOStart, colStart, blockHeight, blockWidth);
				break;
			}
			case WRF: {
				char* fileName = malloc(16 * sizeof(fileName));
				scanf(" %s", fileName);
				writeToFile(&matrix, &rowCount, &colCount, fileName);
				//printf("hello RDF\n");
				free(fileName);
				break;
				break;
			}
			case RDF: {
				char* fileName = malloc(16 * sizeof(fileName));
				scanf(" %s", fileName);
				readFromFile(&matrix, &rowCount, &colCount, fileName);
				//printf("hello RDF\n");
				free(fileName);
				break;
			}
			case PRT: {
				//printf("hello PRT\n");
				printMatrix(matrix, rowCount, colCount);
				break;
			}
			case END: {
				cleanAll(&matrix, &rowCount, &colCount);
				break;
			}
			case undefined:
				break;
		}

	}
	free(opStr);
	return 0;
}
