#pragma warning(disable:4996)
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <Huffman.cpp>
#define nSIZE 256
#define ERROR  -1
using namespace std;

// �ļ�ͷ
struct HEAD
{
	char type[4];		// �ļ�����
	int length;		// ԭ�ļ�����
	int weight[nSIZE];	// Ȩֵ��ֵ
};

int InitHead(const char *pFilename, HEAD &sHead)   // ��ʼ���ļ�ͷ
{
	strcpy(sHead.type, "HUF");// �ļ�����
	sHead.length = 0;// ԭ�ļ�����
	for (int i = 0; i < nSIZE; i++)
	{
		sHead.weight[i] = 0;// Ȩֵ
	}
	// �Զ���������ʽ���ļ�
	FILE *fin = fopen(pFilename, "rb");
	int ch;
	// ɨ���ļ������Ȩ��
	while ((ch = fgetc(fin)) != EOF)
	{
		sHead.weight[ch]++;
		sHead.length++;
	}
	// �ر��ļ�
	fclose(fin);
	fin = NULL;

	return OK;
}

int WriteFile(const char *pFilename, const HEAD sHead, const char *pBuffer, const int nbuf)
{
	// �����ļ���
	char filename[nSIZE + 5] = { '\0' };
	strcpy(filename, pFilename);
	strcat(filename, ".huf");
	/*
	ofstream fout(filename,ios::binary);
	fout.write(&sHead, sizeof(HEAD));
	fout.write(pBuffer,sizeof(char) * nbuf);
	fout.close();*/
	
	// �Զ���������ʽ���ļ�
	FILE *fout = fopen(filename, "wb");
	// д�ļ�ͷ
	//fwrite(&sHead, sizeof(HEAD), 1, fout);
	// дѹ����ı���
	//fwrite(pBuffer, sizeof(char), nbuf, fout);
	// �ر��ļ����ͷ��ļ�ָ��
	fclose(fout);
	fout = NULL;
	
	cout << "����ѹ���ļ���" << filename << endl;
	int len = sizeof(HEAD) + strlen(pFilename) + 1 + nbuf;
	cout << "ѹ���ļ���СΪ��" << len << "B" << endl;
	double rate = len * 1.0 / sHead.length;
	cout.setf(ios::fixed);
	cout << "ѹ����Ϊ��" << setprecision(4) << rate << "%" << endl;

	return len;
}


char Str2byte(const char *pBinStr)  //�����硰01010101�����ַ���ת�����ֽ�
{
	char b = 0x00;
	for (int i = 0; i < 8; i++)
	{
		b = b << 1;// ����1λ
		if (pBinStr[i] == '1') {
			b = b | 0x01;
		}
	}
	return b;
}

int Encode(const char *pFilename, const HuffmanCode pHC, char *pBuffer, const int nbuf)
{
	// ���ٻ�����
	pBuffer = (char *)malloc(nbuf * sizeof(char));
	if (!pBuffer)
	{
		cerr << "���ٻ�����ʧ��!" << endl;
		return ERROR;
	}

	char cd[nSIZE] = { '\0' };  // ������
	int pos = 0;		// ������ָ��
	int ch;
	FILE *fin = fopen(pFilename, "rb");
	// ɨ���ļ�������Huffman�����������ѹ����ѹ������ݴ浽�������С�
	while ((ch = fgetc(fin)) != EOF)
	{
		strcat(cd, pHC[ch]);	// ��pHC���Ʊ��봮��cd
		// ѹ������
		while (strlen(cd) >= 8)
		{
			// ��ȡ�ַ�����ߵ�8���ַ���������ֽ�
			pBuffer[pos++] = Str2byte(cd);
			// �ַ�����������8�ֽ�
			for (int i = 0; i < nSIZE - 8; i++)
			{
				cd[i] = cd[i + 8];
			}
		}
	}
	fclose(fin);
	fin = NULL;
	if (strlen(cd) > 0)
	{
		pBuffer[pos++] = Str2byte(cd);
	}
	return OK;
}

int Compress(const char *pFilename, HuffmanCode &pHC, const HEAD sHead)
{
	//���㻺�����Ĵ�С  
	int nbuf = 0;
	for (int i = 0; i<nSIZE; i++)
	{
		nbuf += sHead.weight[i] * sizeof(pHC[i]);
	}
	nbuf = (nbuf % 8) ? nbuf / 8 + 1 : nbuf / 8;
	//cout<<"nbuf = "<<nbuf<<endl; 
	char *pBuffer = NULL;
	Encode(pFilename, pHC, pBuffer, nbuf);
	if (!pBuffer)
		return ERROR;
	int result = WriteFile(pFilename, sHead, pBuffer, nbuf);
	return result;
}