#pragma once
#include <queue>
// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� CREATDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// CREATDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#define CREATDLL_API __declspec(dllexport)
#pragma warning( disable: 4251 )

using namespace std;

typedef struct {
    int index, start, end, weight;
    bool visit;
} WordInfo;

extern "C" CREATDLL_API int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
extern "C" CREATDLL_API int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
