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


class CREATDLL_API Core {
private:

    int graph[30][30], words_index[30][30];
    int in_degree[30], length[30], last[30];
    queue<int> vertex;

    vector<WordInfo> start_words[26], end_words[26];
    deque<int> longest_word_chain, word_chain;
    int max_word_chain_length = 0;
    
    int get_last_vertex(char tail);
    void init_word_info(char* words[], int len, bool weighted);
    void dfs(int start, int depth);
    void dfs_with_end(int start, int depth, int end);
    void dfs_reverse(int end, int depth);
    
public:
    Core();
    int init_unweighted_graph(char* words[], int len);
    int init_weighted_graph(char* words[], int len);
    int topo_sort();
    void dp(char head, char tail);
    int gen_result(char* words[], char* result[], char head, char tail);
    int gen_loop_chain(char* words[], int len, char* result[], char head, char tail, bool weighted);
};

extern "C" CREATDLL_API int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
extern "C" CREATDLL_API int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop);
