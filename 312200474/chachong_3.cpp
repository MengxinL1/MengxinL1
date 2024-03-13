#define _CRT_SECURE_NO_WARNINGS


#define MAX_CHAR 256
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h> 
// 去除标点符号和空格
void removePunctuationAndSpace(char* str) {
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		if (ispunct(str[i]) || isspace(str[i])) {
			str[i] = ' ';
		}
	}
}

// 转换为小写字母
void toLowerCase(char* str) {
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		str[i] = tolower(str[i]);
	}
}

// 计算余弦相似度
float cosineSimilarity(char* str1, char* str2) {
	int vec1[MAX_CHAR] = { 0 };
	int vec2[MAX_CHAR] = { 0 };

	int len1 = strlen(str1);
	int len2 = strlen(str2);

	for (int i = 0; i < len1; i++) {
		vec1[(int)str1[i]]++;
	}

	for (int i = 0; i < len2; i++) {
		vec2[(int)str2[i]]++;
	}

	float dotProduct = 0.0;
	float normVec1 = 0.0;
	float normVec2 = 0.0;

	for (int i = 0; i < MAX_CHAR; i++) {
		dotProduct += vec1[i] * vec2[i];
		normVec1 += vec1[i] * vec1[i];
		normVec2 += vec2[i] * vec2[i];
	}

	normVec1 = sqrt(normVec1);
	normVec2 = sqrt(normVec2);

	if (normVec1 == 0 || normVec2 == 0) {
		return 0.0;
	}

	return dotProduct / (normVec1 * normVec2);
}

void writeAnswer(float overlap, const char *answerPath) {
	FILE *answerFile = fopen(answerPath, "w");
	if (answerFile == NULL) {
		perror("Error opening answer file");
		exit(EXIT_FAILURE);
	}

	// 将重复率格式化为两位小数的字符串  
	char overlapStr[10];
	snprintf(overlapStr, sizeof(overlapStr), "%.2f", overlap);

	// 写入答案文件  
	fprintf(answerFile, "%s\n", overlapStr);

	// 关闭文件  
	fclose(answerFile);
}

int main() {
	FILE* file1 = fopen("C:\\wx\\WeChat Files\\wxid_8c49z6a9b7u622\\FileStorage\\File\\2024-03\\测试文本\\orig.txt", "r");
	FILE* file2 = fopen("C:\\wx\\WeChat Files\\wxid_8c49z6a9b7u622\\FileStorage\\File\\2024-03\\测试文本\\orig_0.8_add.txt", "r");

	char str1[11000];
	char str2[11000];
	const char *answerPath = { "answer.txt" };
	fgets(str1, sizeof(str1), file1);
	fgets(str2, sizeof(str2), file2);

	fclose(file1);
	fclose(file2);

	removePunctuationAndSpace(str1);
	removePunctuationAndSpace(str2);

	toLowerCase(str1);
	toLowerCase(str2);

	float similarity = cosineSimilarity(str1, str2);
	writeAnswer(similarity, answerPath);
	printf("相似度：%.2f\n", similarity);

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
