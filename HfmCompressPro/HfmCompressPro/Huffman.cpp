//#include <Huffman.h>
#include <stdio.h>
#include <iomanip>

//�ڿ���̨���Huffman��ÿ���ڵ����Ϣ
void TestHufTree(HuffmanTree pHT)
{
	for (int i = 0; i < 2 * nSIZE - 1; i++)
	{
		cout << "HuffmanTree�Ľ����ϢΪ��" << endl;
		cout << "pHT[i]  \t" << "weight\t" << "parent\t" << "lchild\t" << "rchild\t" << endl;
		cout << "pHT[" << i << "]  \t" << pHT[i].weight << "\t" << pHT[i].parent
			<< "\t" << pHT[i].lchild << "\t" << pHT[i].rchild << endl;
	}
}

//������������ķ������ڿ���̨���Huffman��ÿ��������Ϣ
void TestHufTreeN(HuffmanTree pHT, int root)
{
	cout << pHT[root].weight << " ";
	if (pHT[root].lchild != -1)
	{
		TestHufTreeN(pHT, pHT[root].lchild);
	}
	if (pHT[root].rchild != -1)
	{
		TestHufTreeN(pHT, pHT[root].rchild);
	}
}

//����������ɵĸ�������Huffman����
void TestHufCode(HuffmanCode pHC)
{
	cout << " *���ɵ�Huffman����Ϊ��" << endl;
	for (int i = 0; i<nSIZE; i++)
		cout << "pHC[" << setfill('0') << setw(2) << i << "] = " << pHC[i] << endl;
}


