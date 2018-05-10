//#include <Compress.h>
//#include <Huffman.cpp>

void CompressPro(const char *pFilename)
{
	HuffmanTree pHT;
	HuffmanCode pHC;
	HEAD sHead;
	InitHead(pFilename, sHead);      //��ʼ���ļ�ͷ,���Ȩ��
	Compress(pFilename, pHT, pHC, sHead.weight, sHead);   //����Compress()ʵ��ѹ�����������ļ�.huf
}

/*
int main()
{
HEAD shead;
char filename[nSIZE];
InitHead(filename,shead);
int i;
for(i=0;i<nSIZE;i++)
cout<<shead.weight[i]<<" ";
}*/
