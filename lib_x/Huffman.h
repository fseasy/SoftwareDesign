#ifndef HUFFMAN_H_INCLUDED
#define HUFFMAN_H_INCLUDED
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include "STACK_array.h"
/**
     **���ݽṹ�����������
     *ʵ�ַ�ʽ����̬����
     **ʵ�ֹ��ܣ������������������룬����
*/
using namespace std ;

class HuffmanTreeNode
{
public :
    int weight ;
    int parent ;
    int lChild ;
    int rChild ;
} ;
class Huffman
{
public :
    Huffman() ;
    Huffman(string fileName) ;
    //huffman������
    void getWeight() ;
    void printHT() ;
    void selectMin(int maxExtent,int & min ,int & afterMin) ;
    void buildHuffmanTree() ;
    void buildHuffmanCode() ;
    void printHC() ;
    //���������벿��
    void Encording() ;
    unsigned short binaryStrToNum(string binaryStr) ;
    //���������벿��
    void Decording() ;
    string numToBinaryStr(unsigned short num) ;
private :
    int N ;
    HuffmanTreeNode* HuffmanTree ;
    string fileName ;//�򿪵��ļ���
    string xName ;//ѹ���ļ���
    string rear ; //��׺
    string* bits ; //�����±�����Ӧ��char��ֵ�������
    string buffer ;//������
    int addedNum ; //�ַ�������ĸ���

} ;
Huffman::Huffman()
{
    N = 256 ;
    HuffmanTree = new HuffmanTreeNode[2*N-1] ;
    for(int i = 0 ; i < 2*N-1 ; i++)
    {
        HuffmanTree[i].weight = 0 ;
        HuffmanTree[i].parent = -1 ;
        HuffmanTree[i].lChild = -1 ;
        HuffmanTree[i].rChild = -1 ;
    }
    bits = new string[N] ;
    for(int i = 0 ; i < N ; i++)
    {
        bits[i] = "" ;
    }
    buffer  = "" ;
    addedNum = 0 ;
    fileName = "sample.txt" ;
    int pos = fileName.length() -1 ;
    for( ; pos>= 0 ; pos -- )
    {
        if(fileName.at(pos) == '.')
            break ;
    }
    rear = "" ;
    for(int i = pos ; i < fileName.length() ; i++)
    {
        rear+=fileName.at(i) ;
    }
    fileName.erase(pos) ;
    xName = fileName+".hfmX" ;
}
Huffman::Huffman(string Name)
{
    FILE * in ; 
    N = 256 ;
    HuffmanTree = new HuffmanTreeNode[2*N-1] ;
    for(int i = 0 ; i < 2*N-1 ; i++)
    {
        HuffmanTree[i].weight = 0 ;
        HuffmanTree[i].parent = -1 ;
        HuffmanTree[i].lChild = -1 ;
        HuffmanTree[i].rChild = -1 ;
    }
    bits = new string[N] ;
    for(int i = 0 ; i < N ; i++)
    {
        bits[i] = "" ;
    }
    buffer  = "" ;
    addedNum = 0 ;
    fileName = Name ;
    int pos = fileName.length() -1 ;
    for( ; pos>= 0 ; pos -- )
    {
        if(fileName.at(pos) == '.')
            break ;
    }
    rear = "" ;
    for(int i = pos ; i < fileName.length() ; i++)
    {
        rear+=fileName.at(i) ;
    }
    fileName.erase(pos) ;
    xName = fileName+".hfmX" ;
    in = fopen((fileName+rear).c_str(),"r") ; 
    if(in == NULL)
    {
         cout <<"�����ڸ��ļ�\n" ; 
         return ;
    }
}
void Huffman::getWeight()
{
    FILE * in ;
    in = fopen((fileName+rear).c_str(),"r") ;
    if(in == NULL)
    {
        cout <<"�ַ�Ȩֵ��ȡʧ��\n" ;
        return ;
    }
    unsigned short tmp ;
    while(!feof(in))
    {
        tmp = fgetc(in) ;
        if(tmp < N) //�ļ����һ�������ַ���Χ����
            HuffmanTree[tmp].weight++ ;
    }
    cout <<"�ַ�Ȩֵ��ȡ�ɹ�\n" ;
    fclose(in) ;
}
void Huffman::printHT()
{
    cout <<"�ַ�\tȨֵ\t���׽ڵ�\t����\t�Һ���\n" ;
    for(int i = 0 ; i < N ; i++)
    {
        if(HuffmanTree[i].weight>0)
        {
            cout <<(char)i<<"\t" ;
            cout <<HuffmanTree[i].weight <<"\t" ;
            cout <<HuffmanTree[i].parent <<"\t" ;
            cout <<HuffmanTree[i].lChild <<"\t" ;
            cout <<HuffmanTree[i].rChild <<"\t" ;
            cout <<"\n" ;
        }

    }
}
void Huffman::selectMin(int maxExtent,int & min , int & afterMin)
{
    //parent = -1 ��ʾ��û�б����뵽����
    for(int i =0 ; i < maxExtent ; i++)
    {
        if(HuffmanTree[i].parent == -1)
        {
            min = i ;//����ֵ����һ��δ�������Ľڵ�
            break ;
        }
    }
    for(int i = min+1 ; i < maxExtent ; i++)
    {
        if(HuffmanTree[i].parent == -1)
        {
            afterMin = i ;
            break ;
        }
    }
    for(int i = min+1 ; i < maxExtent ; i++ )
    {
        if(HuffmanTree[i].parent == -1 && HuffmanTree[i].weight <HuffmanTree[min].weight && i != afterMin)
        {
            min = i ;
        }
    }
    for(int i = afterMin+1 ; i< maxExtent ; i++)
    {
        if(HuffmanTree[i].parent == -1 && HuffmanTree[i].weight < HuffmanTree[afterMin].weight && i != min)
        {
            afterMin = i ;
        }
    }
    if(min > afterMin)
    {
        int tmp = min ;
        min = afterMin ;
        afterMin = tmp ;
    }

}
void Huffman::buildHuffmanTree()
{
    for(int i = N ; i < 2*N -1 ; i++)
    {
        int min,afterMin ;
        selectMin(i,min,afterMin) ;
        HuffmanTree[i].lChild = min ;
        HuffmanTree[i].rChild = afterMin ;
        HuffmanTree[i].weight = HuffmanTree[min].weight+HuffmanTree[afterMin].weight ;
        HuffmanTree[min].parent = i ;
        HuffmanTree[afterMin].parent = i ;
    }
    cout <<"���������������\n" ;
}
void Huffman::buildHuffmanCode()//������Ϊ0��������Ϊ1
{
    string tmp = "" ;
    for(int i = 0 ; i < N ; i++)
    {
        int parent = HuffmanTree[i].parent ;
        int current = i ;
        while(parent != -1)
        {
            if(HuffmanTree[parent].lChild == current)
            {
                bits[i]+="0" ;
            }
            else
            {
                bits[i]+="1" ;
            }
            current = parent ;
            parent = HuffmanTree[current].parent ;
        }
        for(int k = bits[i].length()-1 ; k >= 0 ; k-- )
        {
            tmp+=bits[i].at(k) ;
        }
        bits[i] = tmp ;//��Ϊ�Ӹ���Ҷ�ӽڵ������
        tmp = "" ;
    }
}
void Huffman::printHC()
{
    cout <<"�ַ�\t����\n" ;
    for(int i = 0 ; i < N ; i++)
    {
        cout <<(char)i<<"\t"<<bits[i]<<endl ;
    }
}
void Huffman::Encording()
{
    FILE * in ,* out ;
    in = fopen((fileName+rear).c_str(),"r") ;
    out = fopen(xName.c_str(),"wb") ;//�����ļ�������մ��ڵ��ļ�
    if(in == NULL)
    {
        cout <<"�����ļ�����ʧ��\n" ;
        return ;
    }
    fclose(out) ;
    out = fopen(xName.c_str(),"ab") ;//�����Ը��ӵķ�ʽ���ļ�
    if(out == NULL)
    {
        cout <<"ѹ���ļ�����ʧ��\n" ;
        return ;
    }
    unsigned short tmp  ;
    string singleStr = "" ;
    while(!feof(in))
    {
        tmp = fgetc(in) ;
        if(tmp < N)
        {
            buffer+=bits[tmp] ;//���±���
        }
        if(buffer.length()>= sizeof(char) * 8 * 10)//��ʱ��ջ���
        {
            while(buffer.length() > sizeof(char) * 8)
            {
                singleStr = buffer.substr(0, sizeof(char)* 8) ;
                buffer.erase(0,sizeof(char) * 8) ;
                //���������͵��ַ���ת��Ϊ��Ӧ�����Ƶ���
                unsigned short m = binaryStrToNum(singleStr) ;
                fwrite(&m,sizeof(char),1,out) ;
            }
        }
    }
    //��������
    while(buffer.length() > sizeof(char) * 8)
    {
        singleStr = buffer.substr(0, sizeof(char) * 8) ;
        buffer.erase(0,sizeof(char) * 8) ;
        //���������͵��ַ���ת��Ϊ��Ӧ�����Ƶ���
        unsigned short m = binaryStrToNum(singleStr) ;
        fwrite(&m,sizeof(char),1,out) ;
    }
    //ʣ�²���ȫ�ı���,����
    for(int i = buffer.length() ; i< sizeof(char) * 8 ; i++)
    {
        buffer+="0" ;
        addedNum++ ;//ȷ�����ӵ��ַ�����
    }
    unsigned short m = binaryStrToNum(singleStr) ;
    fwrite(&m,sizeof(char),1,out) ;
    fclose(out) ;
    fclose(in) ;
    buffer = "" ;
    cout <<"\nѹ�����,�Ѵ���"<<xName<<"�ļ�\n" ;
}
unsigned short Huffman::binaryStrToNum(string binaryStr)
{
    unsigned short tmp = 0 ;
    int weight = 1 ;
    for(int i = binaryStr.length() -1 ; i >= 0 ; i-- )
    {
        int k = (binaryStr.at(i) - '0')*weight ;
        tmp+=k ;
        weight*= 2 ;
    }
    return tmp ;
}
void Huffman::Decording()
{
    FILE* in,* out ;
    in = fopen(xName.c_str(),"rb") ;
    if(in == NULL)
    {
        cout <<"ѹ���ļ���ʧ��\n" ;
        return  ;
    }
    string uncompressFile = fileName+"_unCom"+rear ;
    out = fopen(uncompressFile.c_str(),"w") ;
    fclose(out) ;
    out  = fopen(uncompressFile.c_str(),"a") ;
    if(out == NULL)
    {
        cout <<"��ѹ���ļ�����ʧ��\n" ;
        return ;
    }
    unsigned short tmp ;
    string singleStr = "" ;
    while(!feof(in))
    {
        fread(&tmp,sizeof(char),1,in) ;
        singleStr = "" ;
        if(tmp < N)
        {
            //��������ַ�ת��Ϊ�������͵��ַ���
            singleStr = numToBinaryStr(tmp) ;
        }
        buffer+=singleStr ;
        if(buffer.length() >= sizeof(char)*8 *10)
        {

            while(buffer.length()> 20)
            {
                //������Ĳ���
                //------------------------------------------------
                int pos = 2*N-2 ;
                while(pos >= N)
                {
                    if(buffer.at(0) == '0')
                    {
                        pos = HuffmanTree[pos].lChild ;
                    }
                    else
                    {
                        pos = HuffmanTree[pos].rChild ;
                    }
                    buffer.erase(0,1) ;
                }
                fputc(pos,out) ;
                //---------------------------------------------------
            }

        }

    }
    //����ʣ�ಿ��
    while(buffer.length()>addedNum)//���ӵ��ַ���������
    {
        int pos = 2*N-2 ;
        while(pos >= N)
        {
            if(buffer.at(0) == '0')
            {
                pos = HuffmanTree[pos].lChild ;
            }
            else
            {
                pos = HuffmanTree[pos].rChild ;
            }
            buffer.erase(0,1) ;
        }
        fputc(pos,out) ;
    }
    fclose(out) ;
    fclose(in) ;
    cout <<"\n��ѹ����ɣ��Ѵ���"<<uncompressFile<<"�ļ�\n" ;
}
string Huffman:: numToBinaryStr(unsigned short num)
{
    Stack<int> s ;
    s.makeNull() ;
    string singleStr = "" ;
    int counter = 0 ;
    while(num != 0)
    {
        s.push(num%2) ;
        num/=2 ;
        counter++ ;
    }
    for(int i = counter ; i< sizeof(char)*8 ; i++)
    {
        s.push(0) ;
    }
    while(!s.isEmpty())
    {
        char tmp = s.pop()+'0' ;
        singleStr+=tmp ;
    }
    return singleStr ;
}
#endif // HUFFMAN_H_INCLUDED
