#pragma once
#pragma warning (disable:4290)
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


class WordGraph {
private:

public:
    int graph[30][30], index[30][30];
    int in_degree[30];
    deque<int> vertex_sorted;
    vector<WordInfo> start_words[26], end_words[26];

    WordGraph();
    int init_unweighted(char* words[], int len);
    int init_weighted(char* words[], int len);
    void init_word_info(char* words[], int len, bool weighted);
    int topo_sort();
};


class Compute {
private:
    WordGraph *word_graph;
    deque<int> longest_word_chain, word_chain;
    int max_word_chain_length = 0;
    int length[30], last[30];

    int get_last_vertex(char tail);
    void dfs(int start, int depth);
    void dfs_with_end(int start, int depth, int end);
    void dfs_reverse(int end, int depth);

public:
    Compute(WordGraph *word_graph);

    void dp(char head, char tail);
    int gen_result(char* words[], char* result[], char head, char tail);
    int gen_loop_chain(char* words[], int len, char* result[], char head, char tail, bool weighted);
};

extern "C" CREATDLL_API int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop) throw (const char *);
extern "C" CREATDLL_API int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop) throw (const char *);
