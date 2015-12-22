#include "../lib_x/Huffman.h"
/**
     **程序名称：哈夫曼解压缩
     **数据结构：静态三叉链表
     **实现功能：压缩文本（一些情况下会提示“This application has requested the Runtime to terminate it in an unusual way
Please contact the application's support team for more information.”不知为何，会导致解压不全），压缩音频，docx文件失败
*/
int main()
{ 
     Huffman *  x ;
    string menus = "\t\t\t哈夫曼解压缩\n1.运行示例\n2.压缩解压缩文件\n3.退出\n" ;
    char choice ;
    while(cout <<menus)
    {
         cin >> choice ; 
        switch(choice)
        {
        case '1' :
        {
              x = new Huffman() ; 
            x->getWeight() ;

            x->buildHuffmanTree() ;
            //x->printHT() ;
            x->buildHuffmanCode() ;
            // x->printHC() ;
            x->Encording() ;
            x->Decording() ;
            delete x ; 
            break ; 
        }
        case '2' :
        {
             cout <<"请输入文件名\n" ; 
             string fileName ;  
             cin.ignore(80,'\n') ;
             cin >> fileName ; 
            
             x = new Huffman(fileName) ;
             x->getWeight() ;

            x->buildHuffmanTree() ;
            //x->printHT() ;
            x->buildHuffmanCode() ;
            // x->printHC() ;
            x->Encording() ;
            x->Decording() ;
            delete x ; 
            break ;      
        }
        case '3' :
        return 0 ; 
        default :
        cout <<"INVALID CHOICE\n" ;   
        }
    }

    return 0;
}
