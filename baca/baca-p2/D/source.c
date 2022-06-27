//Maksim Zdobnikau
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define nullptr NULL 

typedef unsigned short int uint16;

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
	for (i = end - 1; i > start - 1; i--) {
		*(arr + i + offset) = *(arr + i);
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

void printMatrix(int** const matrix, const uint16 rowCount, uint16* const rowWidth) {
	printf("%hu\n", rowCount);
	int i = 0;
	for (i = 0; i < rowCount; i++) {
		int rowLen = *(rowWidth + i);
		printf("%hu", rowLen);
		int j = 0;
		for (j = 0; j < rowLen; j++) {
			printf(" %d", *(*(matrix + i) + j));
		}
		printf("\n");
	}
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
	int i = 0;
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
		*(*matrix + i) = shiftLeftArray(*(*matrix + i), columnStart, curColCount, removedColsCount);
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

		*(*matrix + i) = shiftLeftArray(*(*matrix + i), curColCount - 1, curColCount, 1);
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
		int* newRow = malloc(curRowWidth * sizeof(*newRow));

		int j = 0;
		for (j = 0; j < curRowWidth; j++) {
			int curValue = 0;
			fread(&curValue, sizeof(int), 1, sourceFile);
			curValue = bigEndianInt(curValue);
			*(newRow + j) = curValue;
		}

		insertRowBeforeFromArr(matrix, rowCount, colCount, curRowWidth, *rowCount, &newRow);
		free(newRow);
	}
	fclose(sourceFile);
}

int main() {
	char* opStr = malloc(4 * sizeof(*opStr));

	int** matrix = nullptr;				// Master array, contatins pointers to arrays of variable size
	uint16  rowCount = 0;				// length a.k.a number of rows
	uint16* colCount = nullptr;			// Array of row lengths a.k.a column count for each row

	Operation OP = undefined;
	while (OP != END) {
		scanf("%s", opStr);
		*(opStr + 3) = '\0';
		OP = opParse(opStr);

		uint16 rowOStart = 0;
		uint16 colStart = 0;
		uint16 blockHeight = 0;
		uint16 blockWidth = 0;

		switch (OP) {
			case AFR: {
				scanf("%hu", &blockWidth);

				insertRowBefore(&matrix, &rowCount, &colCount, blockWidth, 0);
				break;
			}
			case ALR: {
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
				scanf(" %hu", &blockHeight);

				insertBlock(&matrix, &rowCount, &colCount, 0, 65535, blockHeight, 1);
				break;
			}
			case IBR: {
				scanf(" %hu %hu", &rowOStart, &blockWidth);
				if (rowOStart >= rowCount) {
					skipLine(blockWidth);
					break;
				}

				insertRowBefore(&matrix, &rowCount, &colCount, blockWidth, rowOStart);
				break;
			}
			case IAR: {
				scanf(" %hu %hu", &rowOStart, &blockWidth);
				if (rowOStart >= rowCount) {
					skipLine(blockWidth);
					break;
				}

				insertRowBefore(&matrix, &rowCount, &colCount, blockWidth, rowOStart + 1);
				break;
			}
			case IBC: {
				scanf(" %hu %hu", &colStart, &blockHeight);
				insertBlock(&matrix, &rowCount, &colCount, 0, colStart, blockHeight, 1);
				break;
			}
			case IAC: {
				scanf(" %hu %hu", &colStart, &blockHeight);
				insertBlock(&matrix, &rowCount, &colCount, 0, colStart + 1, blockHeight, 1);
				break;
			}
			case SWR: {
				uint16 rowA;
				uint16 rowB;

				scanf(" %hu %hu", &rowA, &rowB);
				switchRows(&matrix, &rowCount, &colCount, rowA, rowB);
				break;
			}
			case SWC: {
				uint16 colA;
				uint16 colB;

				scanf(" %hu %hu", &colA, &colB);
				switchCols(&matrix, &rowCount, &colCount, colA, colB);
				break;
			}
			case DFR: {
				removeRowAt(&matrix, &rowCount, &colCount, 0);

				break;
			}
			case DLR: {
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
				removeLastColumn(&matrix, &rowCount, &colCount);
				break;
			}
			case RMR: {
				scanf(" %hu", &rowOStart);
				removeRowAt(&matrix, &rowCount, &colCount, rowOStart);
				break;
			}
			case RMC: {
				scanf(" %hu", &colStart);
				removeBlock(&matrix, &rowCount, &colCount, 0, rowCount, colStart, 1);
				break;
			}
			case RMB: {
				scanf(" %hu %hu %hu %hu", &rowOStart, &blockHeight, &colStart, &blockWidth);

				removeBlock(&matrix, &rowCount, &colCount, rowOStart, blockHeight, colStart, blockWidth);
				break;
			}
			case ISB: {
				scanf(" %hu %hu %hu %hu", &rowOStart, &colStart, &blockHeight, &blockWidth);

				insertBlock(&matrix, &rowCount, &colCount, rowOStart, colStart, blockHeight, blockWidth);
				break;
			}
			case WRF: {
				char* fileName = malloc(16 * sizeof(*fileName));
				scanf(" %s", fileName);

				writeToFile(&matrix, &rowCount, &colCount, fileName);
				free(fileName);
				break;
			}
			case RDF: {
				char* fileName = malloc(16 * sizeof(*fileName));
				scanf(" %s", fileName);
				readFromFile(&matrix, &rowCount, &colCount, fileName);

				free(fileName);
				break;
			}
			case PRT: {
				printMatrix(matrix, rowCount, colCount);
				break;
			}
			case END: {
				break;
			}
			case undefined:
				break;
		}

	}
	cleanAll(&matrix, &rowCount, &colCount);
	free(opStr);
	return 0;
}
