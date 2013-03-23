// RomTxtExporter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "RomTxtExporter.h"
#include "NDSFileParser.h"
#include "RomImageExportImporter.h"
#include "Mini4WDTexFile.h"

#include <iostream>
#include <fstream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{           
//     if ( argc < 4 )
//     {        
//         wcout << L"usage: RomTxtExporter codeTable romFile exportFile" << endl;
// 
//         return -1;
//     }
//    
//     const wchar_t* codeTableFileName = argv[1];
    const wchar_t* srcFileName = argv[1];
//     const wchar_t* destFileName = argv[3];
//     const wchar_t* targetImageFileName = L"allinone.bmp";
    
    ifstream f( srcFileName, ios::binary );
    if ( !f )
    {
        cout << "û���ҵ�ROM�ļ�" << endl;
        return -1;
    }

    cout << "�����У����Ե�" << endl;
    NDSFileParser ndsFile;
    if ( !ndsFile.Load(f) )
    {
        cout << "ֻ����������ROM���Խ�����" << endl;
        return -1;
    }

//     RomTxtExporter exporter;
//     if ( !exporter.LoadCodeTable( codeTableFileName ) )
//     {
//         wcout << L"û���ṩ���" << endl;
//         return -1;
//     }

//     if ( !exporter.Import( L"���Ը�.txt", ndsFile, L"�����.txt" ) )
//     {
//         wcout << L"�ı�����ʧ�ܣ�" << endl;
//         return -1;
//     }

//     if ( !exporter.Export( ndsFile, destFileName ) )
//     {
//         wcout << L"�ı��������ִ���" << endl;
//         return -1;
//     }

//     Mini4WDTexFile file( L"b2_mark.tex" );
//     file.SaveAsBmp( L"b2_mark.bmp");

    RomImageExporterImporter imageExporter;
//     if ( !imageExporter.ExportToSingleBMP( ndsFile, NULL ) )
//     {
//         cout << "ͼƬ�������ִ���" << endl;
//         return -1;
//     }
//     if ( !imageExporter.ImportFromBmpBatch(ndsFile, L"Tex") )
//     {
//         cout << "ͼƬ�������" << endl;
//         return -1;
//     }

    if ( !imageExporter.ImportFromBmp(ndsFile, L"logo/copy_t.tex", L"Tex", L"logo/copy_t.bmp") )
        return -1;

    ndsFile.SaveAs( L"bmp_imported.nds" );

    cout << "ͼƬ������ɣ�" << endl;

	return 0;
}

