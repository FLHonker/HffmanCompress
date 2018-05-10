#include <iostream>
#include <Huffman.h>
#include <Compress.h>
using namespace std;


int main()
{
	char tmpfile[nSIZE];
	cout << "============ Huffman�ļ�ѹ�� ============" << endl;
	cout << "�������ļ�����·����: ";
	cin >> tmpfile;
	char *filename = tmpfile;
	HEAD shead;
	HuffmanTree pHT;
	HuffmanCode pHC;
	char *pBuffer = NULL;
	InitHead(filename, shead);
	CreateHuffmanTree(pHT, shead.weight); //����HuffmanTree

	/*����HuffmanTree�����Ϣ*/
	//cout<<"���ɵ�Huffman�������ϢΪ��"<<endl;
	//cout<<"pHT[i]  \t"<<"weight\t"<<"parent\t"<<"lchild\t"<<"rchild\t"<<endl;
	//for(int i=0;i<2*nSIZE-1;i++)
	//cout<<"pHT["<<i<<"]  \t"<<pHT[i].weight<<'\t'<<pHT[i].parent<<'\t'<<pHT[i].lchild<<'\t'<<pHT[i].rchild<<'\t'<<endl;

	HuffmanCoding(pHC, pHT);    //����Huffman����

	/*�������ɵ�Huffman����*/
	//cout<<" *���ɵ�Huffman����Ϊ��"<<endl;
	//for(int i=0;i<nSIZE;i++)
	//cout<<"pHC["<<setfill('0')<<setw(2)<<i<<"] = "<<pHC[i]<<endl;

	/*����ѹ���ļ�������ѹ����*/
	int nbuf = 0;
	for (int i = 0; i<nSIZE; i++)
	{
		nbuf += shead.weight[i] * sizeof(pHC[i]);
	}
	nbuf = (nbuf % 8) ? nbuf / 8 + 1 : nbuf / 8;
	Encode(filename, pHC, pBuffer, nbuf);
	int result = WriteFile(filename, shead, pBuffer, nbuf);

	//Compress(filename, pHC, shead);   //ѹ�������ļ�
	return 0;
}
