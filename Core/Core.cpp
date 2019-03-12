// Core.cpp : 定义 DLL 应用程序的导出函数。

#include "stdafx.h"
#include <cstdio>
#include <cstring>
#include <cctype>
#include <queue>
#include <deque>
#include <vector>
#include <iostream>
#include "Core.h"

using namespace std;

int graph[30][30], words_index[30][30];
int in_degree[30], length[30], last[30];
queue<int> vertex;

vector<WordInfo> start_words[26], end_words[26];
deque<int> longest_word_chain, word_chain;
int max_word_chain_length = 0;


int init_unweighted_graph(char* words[], int len)
{
    char *word;
    int start, end;
    memset(graph, 0, sizeof(graph));
    memset(in_degree, 0, sizeof(in_degree));

    for (int i = 0; i < len; i++) {
        word = words[i];
        start = tolower(word[0]) - 'a';
        end = tolower(word[strlen(word) - 1]) - 'a';
        if (start < 0 || start>25 || end < 0 || end >25) {
            cout << "The word contains illegal characters." << endl;
            exit(1);
        }
        if (start == end && graph[start][end]) {
            return -1; //带多个自环，报错
        }
        if (!graph[start][end]) {
            graph[start][end] = 1;
            words_index[start][end] = i;
            if (start != end) { //对于自环，入度不增加
                in_degree[end]++;
            }
        }
    }
    return 0;
}


int init_weighted_graph(char* words[], int len)
{
    char *word;
    int start, end, word_length;
    
    memset(graph, 0, sizeof(graph));
    memset(in_degree, 0, sizeof(in_degree));

    for (int i = 0; i < len; i++) {
        word = words[i];
        word_length = (int)strlen(word);
        start = tolower(word[0]) - 'a';
        end = tolower(word[word_length - 1]) - 'a';
        if (start < 0 || start>25 || end < 0 || end >25) {
            cout << "The word contains illegal characters." << endl;
            exit(1);
        }
        if (start == end && graph[start][end]) {
            return -1; //带多个自环，报错
        }
        if (!graph[start][end]) {
            graph[start][end] = word_length;
            words_index[start][end] = i;
            if (start != end) { //对于自环，入度不增加
                in_degree[end]++;
            }
        }
        else if (graph[start][end] < word_length) {
            graph[start][end] = word_length;
            words_index[start][end] = i;
        }
    }
    return 0;
}


int topo_sort()
{
    int j;

    for (int i = 0; i < 26; i++) {
        for (j = 0; j < 26 && in_degree[j] != 0; j++);
        if (j == 26) {
            return -1; //有环
        }
        in_degree[j] = -1;
        vertex.push(j);
        for (int k = 0; k < 26; k++) {
            if (j != k && graph[j][k]) {
                in_degree[k]--;
            }
        }
    }
    return 0;
}


void dp(char head, char tail)
{
    int v;

    memset(last, -1, sizeof(last));
    memset(length, 0, sizeof(length));
    if (head) {
        v = tolower(head) - 'a';
        while (vertex.front() != v) {
            vertex.pop();
        }
        vertex.pop();
    }

    while (!vertex.empty()) {
        v = vertex.front();
        vertex.pop();
        for (int j = 0; j < 26; j++) {
            if (j != v && graph[j][v] && length[j] + graph[j][v] > length[v]) {
                if (!head || j == tolower(head) - 'a' || length[j] > 0) {
                    length[v] = length[j] + graph[j][v];
                    last[v] = j;
                }
            }
        }
        if (graph[v][v]) {
            length[v] += graph[v][v];
        }
        if (tail && v == tolower(tail) - 'a') {
            break;
        }
    }
}


int get_last_vertex(char tail)
{
    int max_length = -1, last_v;

    if (tail) {
        return tolower(tail) - 'a';
    }

    for (int i = 0; i < 26; i++) {
        if (length[i] > max_length) {
            max_length = length[i];
            last_v = i;
        }
    }
    return last_v;
}


int gen_result(char* words[], char* result[], char head, char tail)
{
    int v, count = 0;

    v = get_last_vertex(tail);
    while (last[v] != -1) {
        if (graph[v][v]) {
            result[count++] = words[words_index[v][v]];
        }
        result[count++] = words[words_index[last[v]][v]];
        v = last[v];
    }
    if (graph[v][v]) {
        result[count++] = words[words_index[v][v]];
    }

    if (head && tolower(head) - 'a' != v) {
        return 0;
    }

    for (int i = 0, j = count - 1; i < j; i++, j--) {
        char *tmp;
        tmp = result[i];
        result[i] = result[j];
        result[j] = tmp;
    }
    return count;
}


void dfs(int start, int depth)
{
    int length = (int)start_words[start].size();
    bool flag = true;

    for (int j = 0; j < length; j++) {
        if (!start_words[start][j].visit) {
            flag = false;
            start_words[start][j].visit = true;
            word_chain.push_back(start_words[start][j].index);
            dfs(start_words[start][j].end, depth + start_words[start][j].weight);
            word_chain.pop_back();
            start_words[start][j].visit = false;
        }
    }

    if (flag && depth > max_word_chain_length) {
        max_word_chain_length = depth;
        longest_word_chain = word_chain;
    }
}


void dfs_with_end(int start, int depth, int end)
{
    int length = (int)start_words[start].size();

    if (start == end && depth > max_word_chain_length) {
        max_word_chain_length = depth;
        longest_word_chain = word_chain;
    }

    for (int j = 0; j < length; j++) {
        if (!start_words[start][j].visit) {
            start_words[start][j].visit = true;
            word_chain.push_back(start_words[start][j].index);
            dfs_with_end(start_words[start][j].end, depth + start_words[start][j].weight, end);
            word_chain.pop_back();
            start_words[start][j].visit = false;
        }
    }
}


void dfs_reverse(int end, int depth)
{
    int length = (int)end_words[end].size();
    bool flag = true;

    for (int j = 0; j < length; j++) {
        if (!end_words[end][j].visit) {
            flag = false;
            end_words[end][j].visit = true;
            word_chain.push_front(end_words[end][j].index);
            dfs_reverse(end_words[end][j].start, depth + end_words[end][j].weight);
            word_chain.pop_front();
            end_words[end][j].visit = false;
        }
    }

    if (flag && depth > max_word_chain_length) {
        max_word_chain_length = depth;
        longest_word_chain = word_chain;
    }
}


void init_word_info(char* words[], int len, bool weighted)
{
    char *word;
    int start, end, length;

    for (int i = 0; i < len; i++) {
        word = words[i];
        length = (int)strlen(word);
        start = tolower(word[0]) - 'a';
        end = tolower(word[length - 1]) - 'a';
        if (start < 0 || start>25 || end < 0 || end >25) {
            cout << "The word contains illegal characters." << endl;
            exit(1);
        }
        WordInfo word_info;
        word_info.start = start;
        word_info.end = end;
        word_info.weight = weighted ? length : 1;
        word_info.index = i;
        word_info.visit = false;
        start_words[start].push_back(word_info);
        end_words[end].push_back(word_info);
    }
}



int gen_loop_chain(char* words[], int len, char* result[], char head, char tail, bool weighted)
{
    int start, end;

    init_word_info(words, len, weighted);

    if (head && tail) {
        start = tolower(head) - 'a';
        end = tolower(tail) - 'a';
        dfs_with_end(start, 0, end);
    }
    else if (head) {
        start = tolower(head) - 'a';
        dfs(start, 0);
    }
    else if (tail) {
        end = tolower(tail) - 'a';
        dfs_reverse(end, 0);
    }
    else {
        for (int i = 0; i < 26; i++) {
            dfs(i, 0);
        }
    }

    int count = (int)longest_word_chain.size();
    for (int i = 0; i < count; i++) {
        result[i] = words[longest_word_chain[i]];
    }
    return count;
}


int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop)
{
    int ret;

    if ((ret = init_unweighted_graph(words, len)) < 0) {
        if (enable_loop) {
            return gen_loop_chain(words, len, result, head, tail, false);
        }
        else {
            return ret;
        }
    }
    else if ((ret = topo_sort()) < 0) {
        if (enable_loop) {
            return gen_loop_chain(words, len, result, head, tail, false);
        }
        else {
            return ret;
        }
    }
    else {
        dp(head, tail);
        return gen_result(words, result, head, tail);
    }
}


int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop)
{
    int ret;

    if ((ret = init_weighted_graph(words, len)) < 0) {
        if (enable_loop) {
            return gen_loop_chain(words, len, result, head, tail, true);
        }
        else {
            return ret;
        }
    }
    else if ((ret = topo_sort()) < 0) {
        if (enable_loop) {
            return gen_loop_chain(words, len, result, head, tail, true);
        }
        else {
            return ret;
        }
    }
    else {
        dp(head, tail);
        return gen_result(words, result, head, tail);
    }
}


