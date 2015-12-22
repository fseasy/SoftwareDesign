#include "../lib_x/Huffman.h"
/**
     **�������ƣ���������ѹ��
     **���ݽṹ����̬��������
     **ʵ�ֹ��ܣ�ѹ���ı���һЩ����»���ʾ��This application has requested the Runtime to terminate it in an unusual way
Please contact the application's support team for more information.����֪Ϊ�Σ��ᵼ�½�ѹ��ȫ����ѹ����Ƶ��docx�ļ�ʧ��
*/
int main()
{ 
     Huffman *  x ;
    string menus = "\t\t\t��������ѹ��\n1.����ʾ��\n2.ѹ����ѹ���ļ�\n3.�˳�\n" ;
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
             cout <<"�������ļ���\n" ; 
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
