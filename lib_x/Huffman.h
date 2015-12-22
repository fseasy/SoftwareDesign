#ifndef HUFFMAN_H_INCLUDED
#define HUFFMAN_H_INCLUDED
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include "STACK_array.h"
/**
     **数据结构：哈夫曼相关
     *实现方式：静态链表
     **实现功能：构建哈夫曼树，编码，译码
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
    //huffman树部分
    void getWeight() ;
    void printHT() ;
    void selectMin(int maxExtent,int & min ,int & afterMin) ;
    void buildHuffmanTree() ;
    void buildHuffmanCode() ;
    void printHC() ;
    //哈夫曼编码部分
    void Encording() ;
    unsigned short binaryStrToNum(string binaryStr) ;
    //哈夫曼译码部分
    void Decording() ;
    string numToBinaryStr(unsigned short num) ;
private :
    int N ;
    HuffmanTreeNode* HuffmanTree ;
    string fileName ;//打开的文件名
    string xName ;//压缩文件名
    string rear ; //后缀
    string* bits ; //数组下标代表对应的char，值代表编码
    string buffer ;//缓存区
    int addedNum ; //字符串补零的个数

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
         cout <<"不存在该文件\n" ; 
         return ;
    }
}
void Huffman::getWeight()
{
    FILE * in ;
    in = fopen((fileName+rear).c_str(),"r") ;
    if(in == NULL)
    {
        cout <<"字符权值获取失败\n" ;
        return ;
    }
    unsigned short tmp ;
    while(!feof(in))
    {
        tmp = fgetc(in) ;
        if(tmp < N) //文件最后一个隐形字符范围诡异
            HuffmanTree[tmp].weight++ ;
    }
    cout <<"字符权值获取成功\n" ;
    fclose(in) ;
}
void Huffman::printHT()
{
    cout <<"字符\t权值\t父亲节点\t左孩子\t右孩子\n" ;
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
    //parent = -1 表示还没有被加入到树中
    for(int i =0 ; i < maxExtent ; i++)
    {
        if(HuffmanTree[i].parent == -1)
        {
            min = i ;//赋初值，第一个未加入树的节点
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
    cout <<"哈夫曼树建立完成\n" ;
}
void Huffman::buildHuffmanCode()//左子树为0，右子树为1
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
        bits[i] = tmp ;//变为从根到叶子节点的序列
        tmp = "" ;
    }
}
void Huffman::printHC()
{
    cout <<"字符\t编码\n" ;
    for(int i = 0 ; i < N ; i++)
    {
        cout <<(char)i<<"\t"<<bits[i]<<endl ;
    }
}
void Huffman::Encording()
{
    FILE * in ,* out ;
    in = fopen((fileName+rear).c_str(),"r") ;
    out = fopen(xName.c_str(),"wb") ;//创建文件或者清空存在的文件
    if(in == NULL)
    {
        cout <<"编码文件读入失败\n" ;
        return ;
    }
    fclose(out) ;
    out = fopen(xName.c_str(),"ab") ;//重新以附加的方式打开文件
    if(out == NULL)
    {
        cout <<"压缩文件创建失败\n" ;
        return ;
    }
    unsigned short tmp  ;
    string singleStr = "" ;
    while(!feof(in))
    {
        tmp = fgetc(in) ;
        if(tmp < N)
        {
            buffer+=bits[tmp] ;//重新编码
        }
        if(buffer.length()>= sizeof(char) * 8 * 10)//及时清空缓存
        {
            while(buffer.length() > sizeof(char) * 8)
            {
                singleStr = buffer.substr(0, sizeof(char)* 8) ;
                buffer.erase(0,sizeof(char) * 8) ;
                //将二进制型的字符串转换为对应二进制的数
                unsigned short m = binaryStrToNum(singleStr) ;
                fwrite(&m,sizeof(char),1,out) ;
            }
        }
    }
    //继续处理
    while(buffer.length() > sizeof(char) * 8)
    {
        singleStr = buffer.substr(0, sizeof(char) * 8) ;
        buffer.erase(0,sizeof(char) * 8) ;
        //将二进制型的字符串转换为对应二进制的数
        unsigned short m = binaryStrToNum(singleStr) ;
        fwrite(&m,sizeof(char),1,out) ;
    }
    //剩下不完全的编码,补零
    for(int i = buffer.length() ; i< sizeof(char) * 8 ; i++)
    {
        buffer+="0" ;
        addedNum++ ;//确定增加的字符个数
    }
    unsigned short m = binaryStrToNum(singleStr) ;
    fwrite(&m,sizeof(char),1,out) ;
    fclose(out) ;
    fclose(in) ;
    buffer = "" ;
    cout <<"\n压缩完成,已创建"<<xName<<"文件\n" ;
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
        cout <<"压缩文件打开失败\n" ;
        return  ;
    }
    string uncompressFile = fileName+"_unCom"+rear ;
    out = fopen(uncompressFile.c_str(),"w") ;
    fclose(out) ;
    out  = fopen(uncompressFile.c_str(),"a") ;
    if(out == NULL)
    {
        cout <<"解压缩文件创建失败\n" ;
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
            //将读入的字符转换为二进制型的字符串
            singleStr = numToBinaryStr(tmp) ;
        }
        buffer+=singleStr ;
        if(buffer.length() >= sizeof(char)*8 *10)
        {

            while(buffer.length()> 20)
            {
                //译码核心部分
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
    //处理剩余部分
    while(buffer.length()>addedNum)//增加的字符不能译码
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
    cout <<"\n解压缩完成，已创建"<<uncompressFile<<"文件\n" ;
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
