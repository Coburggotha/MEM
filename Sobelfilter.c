#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>   // sqrt ��� (�Һ� �ڵ忡 �ʿ�)

// BMP ���� ��� ����ü
#pragma pack(push, 1)
typedef struct {
    uint16_t type;        // ���� ���� (BM)
    uint32_t size;        // ���� ũ��
    uint16_t reserved1;   // ����� �ʵ�
    uint16_t reserved2;   // ����� �ʵ�
    uint32_t offset;      // �̹��� ������ ���� ��ġ
} BMPFileHeader;

typedef struct {
    uint32_t size;        // ��� ũ��
    int32_t width;        // �̹��� �ʺ�
    int32_t height;       // �̹��� ����
    uint16_t planes;      // ���� ��� ��
    uint16_t bitCount;    // �ȼ��� ��Ʈ ��
    uint32_t compression; // ���� ����
    uint32_t sizeImage;   // �̹��� ������ ũ��
    int32_t xPelsPerMeter;// ���� �ػ�
    int32_t yPelsPerMeter;// ���� �ػ�
    uint32_t clrUsed;     // ���� ���� ��
    uint32_t clrImportant;// �߿��� ���� ��
} BMPInfoHeader;

typedef struct {
    uint8_t blue;
    uint8_t green;
    uint8_t red;
} RGB;
#pragma pack(pop)

// RGB�� �׷��̽����Ϸ� ��ȯ�ϴ� �Լ�
uint8_t rgbToGrayscale(RGB pixel) {
    // ǥ�� luminance ����: Y = 0.299*R + 0.587*G + 0.114*B
    return (uint8_t)(0.299 * pixel.red + 0.587 * pixel.green + 0.114 * pixel.blue);
}

/* -------------------- �Һ� ���� (����� ���� �ڵ� �״��) -------------------- */
// �Һ� ����
int sobelX[3][3] = {
    {-1, 0, 1},
    {-2, 0, 2},
    {-1, 0, 1}
};
int sobelY[3][3] = {
    {-1, -2, -1},
    { 0,  0,  0},
    { 1,  2,  1}
};
// �����ϰ� �ȼ� �� ��������
unsigned char getPixel(unsigned char* image, int width, int height, int x, int y) {
    if (x < 0) x = 0;
    if (x >= width) x = width - 1;
    if (y < 0) y = 0;
    if (y >= height) y = height - 1;
    return image[y * width + x];
}
// �Һ� ���ͷ� ���� ã��
void findEdges(unsigned char* input, unsigned char* output, int width, int height) {
    printf("���� ���� ��...\n");
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int gx = 0, gy = 0;
            // �ֺ� 9�� �ȼ��� ���� ����
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    unsigned char pixel = getPixel(input, width, height, x + j, y + i);
                    gx += pixel * sobelX[i + 1][j + 1];
                    gy += pixel * sobelY[i + 1][j + 1];
                }
            }
            // ���� ���� ���
            int edge = (int)sqrt(gx * gx + gy * gy);
            if (edge > 255) edge = 255;
            output[y * width + x] = (unsigned char)edge;
        }
    }
}
/* ------------------------------------------------------------------------- */

int main() {
    const char* inputFile = "brainct_001.bmp";
    const char* outputFile = "output_grayscale.bmp";
    const char* edgeFile = "output_edge.bmp";     // (�߰�) ���� BMP
    const char* memFile = "output_image.mem";    // (�������� ���)

    const int IMAGE_WIDTH = 630;
    const int IMAGE_HEIGHT = 630;

    FILE* inFile = NULL;
    FILE* outFile = NULL;
    FILE* edgeOutFile = NULL;    // (�߰�) ���� BMP ���� ������
    FILE* memOutFile = NULL;     // (���� ����)

    // �Է� ���� ����
    if (fopen_s(&inFile, inputFile, "rb") != 0 || inFile == NULL) {
        printf("�Է� ������ �� �� �����ϴ�: %s\n", inputFile);
        return 1;
    }

    // BMP ��� �б�
    BMPFileHeader fileHeader;
    BMPInfoHeader infoHeader;

    fread(&fileHeader, sizeof(BMPFileHeader), 1, inFile);
    fread(&infoHeader, sizeof(BMPInfoHeader), 1, inFile);

    // BMP ���� ���� ����
    if (fileHeader.type != 0x4D42) { // "BM"
        printf("��ȿ���� ���� BMP �����Դϴ�.\n");
        fclose(inFile);
        return 1;
    }

    if (infoHeader.bitCount != 24) {
        printf("24��Ʈ BMP ������ �ƴմϴ�. (����: %d��Ʈ)\n", infoHeader.bitCount);
        fclose(inFile);
        return 1;
    }

    if (infoHeader.width != IMAGE_WIDTH || infoHeader.height != IMAGE_HEIGHT) {
        printf("�̹��� ũ�Ⱑ %dx%d�� �ƴմϴ�. (����: %dx%d)\n",
            IMAGE_WIDTH, IMAGE_HEIGHT, infoHeader.width, infoHeader.height);
        fclose(inFile);
        return 1;
    }

    printf("�Է� ���� ����:\n");
    printf("- ũ��: %dx%d\n", infoHeader.width, infoHeader.height);
    printf("- ��Ʈ ��: %d\n", infoHeader.bitCount);
    printf("- ���� ũ��: %u bytes\n", fileHeader.size);

    // �е� ��� (BMP�� �� ���� 4����Ʈ ��迡 ���ĵǾ�� ��)
    int padding = (4 - ((IMAGE_WIDTH * 3) % 4)) % 4;
    int rowSize = IMAGE_WIDTH * 3 + padding;

    // �̹��� ������ �޸� �Ҵ�
    RGB* imageData = (RGB*)malloc(IMAGE_WIDTH * IMAGE_HEIGHT * sizeof(RGB));
    if (imageData == NULL) {
        printf("�޸� �Ҵ� ����\n");
        fclose(inFile);
        return 1;
    }

    // �̹��� ������ �б� (BMP�� �Ʒ��ʺ��� �����)
    fseek(inFile, fileHeader.offset, SEEK_SET);

    for (int y = IMAGE_HEIGHT - 1; y >= 0; y--) {
        for (int x = 0; x < IMAGE_WIDTH; x++) {
            fread(&imageData[y * IMAGE_WIDTH + x], sizeof(RGB), 1, inFile);
        }
        // �е� �ǳʶٱ�
        fseek(inFile, padding, SEEK_CUR);
    }

    fclose(inFile);

    // �׷��̽����� ��ȯ
    uint8_t* grayscaleData = (uint8_t*)malloc(IMAGE_WIDTH * IMAGE_HEIGHT);
    if (grayscaleData == NULL) {
        printf("�޸� �˴� ����\n");
        free(imageData);
        return 1;
    }

    for (int i = 0; i < IMAGE_WIDTH * IMAGE_HEIGHT; i++) {
        grayscaleData[i] = rgbToGrayscale(imageData[i]);
    }

    // === (�߰�) �Һ� ���� ���� ===
    uint8_t* edgeData = (uint8_t*)malloc(IMAGE_WIDTH * IMAGE_HEIGHT);
    if (edgeData == NULL) {
        printf("���� ������ �޸� �Ҵ� ����\n");
        free(imageData);
        free(grayscaleData);
        return 1;
    }
    findEdges(grayscaleData, edgeData, IMAGE_WIDTH, IMAGE_HEIGHT);

    // ��� ���� ���� (�׷��̽����� BMP)
    if (fopen_s(&outFile, outputFile, "wb") != 0 || outFile == NULL) {
        printf("��� ������ ������ �� �����ϴ�: %s\n", outputFile);
        free(imageData);
        free(grayscaleData);
        free(edgeData);
        return 1;
    }

    // 8��Ʈ �׷��̽����� BMP ��� ����
    int newPadding = (4 - (IMAGE_WIDTH % 4)) % 4;
    int newRowSize = IMAGE_WIDTH + newPadding;
    int paletteSize = 256 * 4; // 256�� �ȷ�Ʈ (�� �׸��� 4����Ʈ)

    BMPFileHeader newFileHeader = fileHeader;
    BMPInfoHeader newInfoHeader = infoHeader;

    newFileHeader.size = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + paletteSize + (newRowSize * IMAGE_HEIGHT);
    newFileHeader.offset = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + paletteSize;

    newInfoHeader.bitCount = 8;
    newInfoHeader.sizeImage = newRowSize * IMAGE_HEIGHT;
    newInfoHeader.clrUsed = 256;
    newInfoHeader.clrImportant = 256;
    newInfoHeader.compression = 0;  // BI_RGB

    // ��� ���� (�׷��̽�����)
    fwrite(&newFileHeader, sizeof(BMPFileHeader), 1, outFile);
    fwrite(&newInfoHeader, sizeof(BMPInfoHeader), 1, outFile);

    // �׷��̽����� �ȷ�Ʈ ���� �� ����
    for (int i = 0; i < 256; i++) {
        uint8_t color[4] = { (uint8_t)i, (uint8_t)i, (uint8_t)i, 0 }; // B,G,R,Reserved
        fwrite(color, 4, 1, outFile);
    }

    // �׷��̽����� �̹��� ������ ���� (�Ʒ��ʺ���)
    uint8_t paddingBytes[4] = { 0 };

    for (int y = IMAGE_HEIGHT - 1; y >= 0; y--) {
        fwrite(&grayscaleData[y * IMAGE_WIDTH], 1, IMAGE_WIDTH, outFile);
        if (newPadding > 0) {
            fwrite(paddingBytes, newPadding, 1, outFile);
        }
    }
    fclose(outFile);

    // === (�߰�) ���� BMP ���� ===
    if (fopen_s(&edgeOutFile, edgeFile, "wb") != 0 || edgeOutFile == NULL) {
        printf("���� ��� ������ ������ �� �����ϴ�: %s\n", edgeFile);
        free(imageData);
        free(grayscaleData);
        free(edgeData);
        return 1;
    }

    // ��� ���� (������ ���� ���/�ȷ�Ʈ ���)
    fwrite(&newFileHeader, sizeof(BMPFileHeader), 1, edgeOutFile);
    fwrite(&newInfoHeader, sizeof(BMPInfoHeader), 1, edgeOutFile);

    for (int i = 0; i < 256; i++) {
        uint8_t color[4] = { (uint8_t)i, (uint8_t)i, (uint8_t)i, 0 };
        fwrite(color, 4, 1, edgeOutFile);
    }

    for (int y = IMAGE_HEIGHT - 1; y >= 0; y--) {
        fwrite(&edgeData[y * IMAGE_WIDTH], 1, IMAGE_WIDTH, edgeOutFile);
        if (newPadding > 0) {
            fwrite(paddingBytes, newPadding, 1, edgeOutFile);
        }
    }
    fclose(edgeOutFile);

    // �޸� ����
    free(imageData);
    free(grayscaleData);
    free(edgeData);

    printf("\n��ȯ �Ϸ�!\n");
    printf("�׷��̽����� BMP ����: %s\n", outputFile);
    printf("���� ���� BMP ����: %s\n", edgeFile);
    printf("�׷��̽����� MEM ����: %s\n", memFile);

    return 0;
}