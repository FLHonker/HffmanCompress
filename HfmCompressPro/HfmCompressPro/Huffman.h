#pragma warning(disable:4996)
#include <iostream>
#include <stdlib.h>
#include <string.h>
#define OK 0
#define nSIZE 256
#define MAXVALUE 999999
using namespace std;

// Huffman���ڵ�
struct HTNode
{
	int weight;// Ȩֵ
	int parent;// ���ڵ�
	int lchild;// ����
	int rchild;// �Һ���
};

// Huffman��
typedef HTNode* HuffmanTree;	  // ��̬��������洢Huffman��
typedef char HuffmanCode[nSIZE][nSIZE];  //�ַ������飬��¼Huffman����

void CreateHuffmanTree(HuffmanTree &pHT, int weight[])
{
	/* i��j��ѭ��������m1��m2���������������ͬ������������СȨֵ����Ȩֵ��
	x1��x2���������������ͬ������������СȨֵ����������е���š�*/
	int i, j, m1, m2, x1, x2;
	HuffmanTree p;
	pHT = (HuffmanTree)malloc(2 * nSIZE * sizeof(HTNode));
	for (p = pHT, i = 0; i < nSIZE; ++i, ++p)
		*p = { weight[i], -1, -1, -1 };
	for (; i < 2 * nSIZE - 1; ++i, ++p)
		*p = { 0, -1, -1, -1 };
	/* ѭ������ Huffman �� */
	for (i = 0; i<nSIZE - 1; i++)
	{
		m1 = m2 = MAXVALUE;     /* m1��m2�д�������޸�����ҽ��Ȩֵ��С��������� */
		x1 = x2 = 0;
		/* �ҳ����н����Ȩֵ��С���޸�����������㣬���ϲ�֮Ϊһ�Ŷ����� */
		for (j = 0; j<nSIZE + i; j++)
		{
			if (pHT[j].weight < m1 && pHT[j].parent == -1)
			{
				m2 = m1;
				x2 = x1;
				m1 = pHT[j].weight;
				x1 = j;
			}
			else if (pHT[j].weight < m2 && pHT[j].parent == -1)
			{
				m2 = pHT[j].weight;
				x2 = j;
			}
		}
		/* �����ҵ��������ӽ�� x1��x2 �ĸ������Ϣ */
		pHT[x1].parent = nSIZE + i;
		pHT[x2].parent = nSIZE + i;
		pHT[nSIZE + i].weight = pHT[x1].weight + pHT[x2].weight;
		pHT[nSIZE + i].lchild = x1;
		pHT[nSIZE + i].rchild = x2;
	}
}

int HuffmanCoding(HuffmanCode &pHC, HuffmanTree &pHT)
{
	// ��ջ�ǵݹ����Huffman������Huffman����
	char cd[nSIZE] = { '\0' };// ��¼����·��
	int cdlen = 0;// ��¼��ǰ·������
	int i, c, p;
	for (i = 0; i < nSIZE; i++)
	{
		int start = 255;
		c = i;
		p = pHT[c].parent;
		while (p != -1)         /* ˫�׽����� */
		{
			if (pHT[p].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
			c = p;
			p = pHT[c].parent;    /* ������һѭ������ */
		}
		//cd[cdlen] = '\0';

		/* ���������ÿ��Ҷ���Ĺ��������� */
		strcpy(pHC[i], &cd[start]);
		//pHC[i] = (char*)malloc((cdlen + 1) * sizeof(char));
		//pHC[i] = cd;
	}
	return OK;
}


