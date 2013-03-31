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

void help()
{
	cout << "usage: RomTxtExporter -i romFile translatedRomFile jisCodeTable newCodeTable translatedText translatedImagePath[option]" << endl; 
	cout << "usage: RomTxtExporter -e romFile jisCodeTable exportTextFile exportImagePath[option]" << endl; 
	cout << "����ģʽ -e��ʾ������-i��ʾ����\n"
		<< "***��-iģʽʱ����������\n"
		<< "\tromFile	rom�ļ�·��\n"
		<< "\ttranslatedRomFile	������rom�ļ���·��\n"
		<< "\tjisCodeTable	Shift-JIS����ļ�·��\n"
		<< "\tnewCodeTable	������ı����ɵ�������ļ�����·��\n"
		<< "\ttranslatedText	��������ı��ļ�·��\n"
		<< "\ttranslatedImagePath	�������ͼƬĿ¼·������ѡ������û���򲻵���ͼƬ\n"
		<< "***��-eģʽʱ����������\n"
		<< "\tromFile	rom�ļ�·��\n"				
		<< "\tjisCodeTable	Shift-JIS����ļ�·��\n"
		<< "\texportTextFile	�ı������ļ���\n"	
		<< "\texportImagePath	������ͼƬĿ¼·������ѡ������û���򲻵���ͼƬ\n"
		<< "\n" << endl;
}

int _tmain(int argc, _TCHAR* argv[])
{           
	if ( argc < 2 )
	{        
		help();
		return -1;
	}

	const wchar_t* mode = argv[1];		
	const wchar_t* srcFileName = argv[2];

	if ( wstring(mode) == L"-i" )
	{
		if ( argc < 6 )
		{
			help();
			return -1;
		}		
	}
	else if ( wstring(mode) == L"-e" )
	{
		if ( argc < 4 )
		{
			help();
			return -1;
		}		
	}
	else
	{
		help();
		return -1;
	}

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

	RomTxtExporter exporter;
	RomImageExporterImporter imageExporter;

	if ( wstring(mode) == L"-e" )
	{
		//cout << "usage: RomTxtExporter -e romFile jisCodeTable exportTextFile exportImagePath[option]" << endl; 
		const wchar_t* destFileName = argv[3];
		const wchar_t* codeTableFileName = argv[4];		 
		const wchar_t* translatedTextFile = argv[5];
		const wchar_t* translatedImagePath = argv[6];

		cout << "��ʼ�����ı���" << destFileName << endl;
		if ( !exporter.Export( ndsFile, destFileName ) )
		{
			cout << "�ı��������ִ���" << endl;
			return -1;
		}
		cout << "�ı�������ϣ�" << endl;

		if ( translatedImagePath && translatedImagePath[0] )
		{
			cout << "��ʼ����ͼƬ��" << destFileName << endl;
			if ( !imageExporter.ExportToSingleBMP( ndsFile, translatedImagePath ) )
			{
				cout << "����ͼƬ����" << endl;
				return -1;
			}
			cout << "����ͼƬ���!" << destFileName << endl;
		}

		cout << "�������" << endl;
		return 0;
	}
	else if ( wstring(mode) == L"-i" )
	{
		//"usage: RomTxtExporter -i romFile translatedRomFile jisCodeTable newCodeTable translatedText translatedImagePath[option]
		const wchar_t* destFileName = argv[3];
		const wchar_t* codeTableFileName = argv[4];
		const wchar_t* newCodeTableFileName = argv[5];
		const wchar_t* translatedTextFile = argv[6];
		const wchar_t* translatedImagePath = argv[7];

		cout << "��ȡԭʼ���" << endl;
		if ( !exporter.LoadCodeTable( codeTableFileName ) )
		{
			cout << "û���ṩ���" << endl;
			return -1;
		}

		if ( translatedTextFile && translatedTextFile[0] )
		{
			if ( !exporter.Import( translatedTextFile, ndsFile, newCodeTableFileName ) )
			{
				cout << "�ı�����ʧ�ܣ�" << endl;
				return -1;
			}
			else
				cout << "�����ı�����ɹ�!" << endl;
		}

		if ( translatedImagePath && translatedImagePath[0] )
		{
			if ( !imageExporter.ImportFromBmpBatch(ndsFile, translatedImagePath ) )
			{
				cout << "ͼƬ�������" << endl;
				return -1;
			}
			else
				cout << "ͼƬ����ɹ�" << endl;
		}		 

		cout << "����rom�ļ�" << endl;
		if ( !ndsFile.SaveAs( destFileName ) )
		{
			cout << "�����rom����" << endl;
			return -1;
		}

		cout << "rom����滻��ɣ�����CrystalTile���滻�ֿ⣨�Ժ�Ὣ�ù��ܼ��ɵ��������" << endl;
		return 0;
	}

	return 0;
}

