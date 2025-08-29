 // 1. ======== 파일 생성 추가 ========
 const char* memFile = "output_image.mem";  // MEM 파일 이름 추가
 FILE* memOutFile = NULL;  // MEM 파일 포인터 추가

 // 2. ======== MEM 파일 생성 부분 (추가) ========

 // MEM 파일 생성
 if (fopen_s(&memOutFile, memFile, "w") != 0 || memOutFile == NULL) {
     printf("MEM 파일을 생성할 수 없습니다: %s\n", memFile);
     free(imageData);
     free(grayscaleData);
     return 1;
 }

 // MEM 파일에 그레이스케일 데이터를 16진수로 쓰기
 // 각 픽셀값을 2자리 16진수로 변환하고 줄바꿈(0x0D 0x0A)으로 구분
 for (int i = 0; i < IMAGE_WIDTH * IMAGE_HEIGHT; i++) {
     fprintf(memOutFile, "%02X\r\n", grayscaleData[i]);
 }

 fclose(memOutFile);

MEM 파일 생성 코드 추가

cmd 
C:\Users\62>fc image_data.mem image_data2.mem 
명령어 이용 두 개의 파일 비교 


//키보드 방향키 인식 코드 2025.8.29





소벨 필터 적용 이미지




![output_edge.bmp](https://github.com/user-attachments/files/22039110/output_edge.bmp)



소벨 필터 코드를 BMP to Gray 코드에 추가

// 소벨 필터
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
// 안전하게 픽셀 값 가져오기
unsigned char getPixel(unsigned char* image, int width, int height, int x, int y) {
    if (x < 0) x = 0;
    if (x >= width) x = width - 1;
    if (y < 0) y = 0;
    if (y >= height) y = height - 1;
    return image[y * width + x];
}
// 소벨 필터로 엣지 찾기
void findEdges(unsigned char* input, unsigned char* output, int width, int height) {
    printf("엣지 검출 중...\n");
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int gx = 0, gy = 0;
            // 주변 9개 픽셀에 필터 적용
            for (int i = -1; i <= 1; i++) {
                for (int j = -1; j <= 1; j++) {
                    unsigned char pixel = getPixel(input, width, height, x + j, y + i);
                    gx += pixel * sobelX[i + 1][j + 1];
                    gy += pixel * sobelY[i + 1][j + 1];
                }
            }
            // 엣지 강도 계산
            int edge = (int)sqrt(gx * gx + gy * gy);
            if (edge > 255) edge = 255;
            output[y * width + x] = edge;
        }
    }
}
