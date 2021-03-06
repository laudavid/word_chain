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

WordGraph::WordGraph() {}

Compute::Compute(WordGraph *word_graph)
{
    this->word_graph = word_graph;
}


int WordGraph::init_unweighted(char* words[], int len)
{
    char *word;
    int start, end;
    memset(graph, 0, sizeof(graph));
    memset(in_degree, 0, sizeof(in_degree));

    for (int i = 0; i < len; i++) {
        word = words[i];
        start = tolower(word[0]) - 'a';
        end = tolower(word[strlen(word) - 1]) - 'a';
        if (start < 0 || start > 25 || end < 0 || end > 25) {
            cout << "Error: the word contains illegal characters." << endl;
            exit(1);
        }
        if (start == end && graph[start][end] && strcmp(words[index[start][end]], words[i]) != 0) {
            return -1; //带多个自环，报错
        }
        if (!graph[start][end]) {
            graph[start][end] = 1;
            index[start][end] = i;
            if (start != end) { //对于自环，入度不增加
                in_degree[end]++;
            }
        }
    }
    return 0;
}


int WordGraph::init_weighted(char* words[], int len)
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
            cout << "Error: the word contains illegal characters." << endl;
            exit(1);
        }
        if (start == end && graph[start][end] && strcmp(words[index[start][end]], words[i]) != 0) {
            return -1; //带多个自环，报错
        }
        if (!graph[start][end]) {
            graph[start][end] = word_length;
            index[start][end] = i;
            if (start != end) { //对于自环，入度不增加
                in_degree[end]++;
            }
        }
        else if (graph[start][end] < word_length) {
            graph[start][end] = word_length;
            index[start][end] = i;
        }
    }
    return 0;
}


int WordGraph::topo_sort()
{
    int j;

    vertex_sorted.clear();

    for (int i = 0; i < 26; i++) {
        for (j = 0; j < 26 && in_degree[j] != 0; j++);
        if (j == 26) {
            return -1; //有环
        }
        in_degree[j] = -1;
        vertex_sorted.push_back(j);
        for (int k = 0; k < 26; k++) {
            if (j != k && graph[j][k]) {
                in_degree[k]--;
            }
        }
    }
    return 0;
}


void Compute::dp(char head, char tail)
{
    int v;

    memset(last, -1, sizeof(last));
    memset(length, 0, sizeof(length));
    if (head) {
        v = tolower(head) - 'a';
        while ((word_graph->vertex_sorted).front() != v) {
            (word_graph->vertex_sorted).pop_front();
        }
        (word_graph->vertex_sorted).pop_front();
    }

    while (!(word_graph->vertex_sorted).empty()) {
        v = (word_graph->vertex_sorted).front();
        (word_graph->vertex_sorted).pop_front();
        for (int j = 0; j < 26; j++) {
            if (j != v && (word_graph->graph)[j][v] && length[j] + (word_graph->graph)[j][v] > length[v]) {
                if (!head || j == tolower(head) - 'a' || length[j] > 0) {
                    length[v] = length[j] + (word_graph->graph)[j][v];
                    last[v] = j;
                }
            }
        }
        if ((word_graph->graph)[v][v]) {
            length[v] += (word_graph->graph)[v][v];
        }
        if (tail && v == tolower(tail) - 'a') {
            break;
        }
    }
}


int Compute::get_last_vertex(char tail)
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


int Compute::gen_result(char* words[], char* result[], char head, char tail)
{
    int v, count = 0;

    v = get_last_vertex(tail);
    while (last[v] != -1) {
        if ((word_graph->graph)[v][v]) {
            result[count++] = words[(word_graph->index)[v][v]];
        }
        result[count++] = words[(word_graph->index)[last[v]][v]];
        v = last[v];
    }
    if ((word_graph->graph)[v][v]) {
        result[count++] = words[(word_graph->index)[v][v]];
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


void Compute::dfs(int start, int depth)
{
    int length = (int)(word_graph->start_words)[start].size();
    bool flag = true;

    for (int j = 0; j < length; j++) {
        if (!(word_graph->start_words)[start][j].visit) {
            flag = false;
            (word_graph->start_words)[start][j].visit = true;
            word_chain.push_back((word_graph->start_words)[start][j].index);
            dfs((word_graph->start_words)[start][j].end, depth + (word_graph->start_words)[start][j].weight);
            word_chain.pop_back();
            (word_graph->start_words)[start][j].visit = false;
        }
    }

    if (flag && depth > max_word_chain_length) {
        max_word_chain_length = depth;
        longest_word_chain = word_chain;
    }
}


void Compute::dfs_with_end(int start, int depth, int end)
{
    int length = (int)(word_graph->start_words)[start].size();

    if (start == end && depth > max_word_chain_length) {
        max_word_chain_length = depth;
        longest_word_chain = word_chain;
    }

    for (int j = 0; j < length; j++) {
        if (!(word_graph->start_words)[start][j].visit) {
            (word_graph->start_words)[start][j].visit = true;
            word_chain.push_back((word_graph->start_words)[start][j].index);
            dfs_with_end((word_graph->start_words)[start][j].end, depth + (word_graph->start_words)[start][j].weight, end);
            word_chain.pop_back();
            (word_graph->start_words)[start][j].visit = false;
        }
    }
}


void Compute::dfs_reverse(int end, int depth)
{
    int length = (int)(word_graph->end_words)[end].size();
    bool flag = true;

    for (int j = 0; j < length; j++) {
        if (!(word_graph->end_words)[end][j].visit) {
            flag = false;
            (word_graph->end_words)[end][j].visit = true;
            word_chain.push_front((word_graph->end_words)[end][j].index);
            dfs_reverse((word_graph->end_words)[end][j].start, depth + (word_graph->end_words)[end][j].weight);
            word_chain.pop_front();
            (word_graph->end_words)[end][j].visit = false;
        }
    }

    if (flag && depth > max_word_chain_length) {
        max_word_chain_length = depth;
        longest_word_chain = word_chain;
    }
}


void WordGraph::init_word_info(char* words[], int len, bool weighted)
{
    char *word;
    int start, end, length;

    for (int i = 0; i < len; i++) {
        bool is_same = false;
        for (int j = 0; j < i; j++) {
            if (strcmp(words[i], words[j]) == 0) {
                is_same = true;
                break;
            }
        }
        if (is_same) {
            continue;
        }

        word = words[i];
        length = (int)strlen(word);
        start = tolower(word[0]) - 'a';
        end = tolower(word[length - 1]) - 'a';
        if (start < 0 || start > 25 || end < 0 || end > 25) {
            cout << "Error: the word contains illegal characters." << endl;
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



int Compute::gen_loop_chain(char* words[], int len, char* result[], char head, char tail, bool weighted)
{
    int start, end;

    word_graph->init_word_info(words, len, weighted);

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


int gen_chain_word(char* words[], int len, char* result[], char head, char tail, bool enable_loop) throw (const char*)
{
    if (words == NULL || result == NULL) {
        throw "Invalid parameter: 'words' or 'result' is null.";
    }
    if (len < 0) {
        throw "Invalid parameter: 'len' is less than 0.";
    }
    if (!isalpha(head) && head != '\0' || !isalpha(tail) && tail != '\0') {
        throw "Invalid parameter: 'head' or 'tail' is not a letter or 0.";
    }

    int ret;
    WordGraph* word_graph = new WordGraph();
    Compute* compute = new Compute(word_graph);

    if ((ret = word_graph->init_unweighted(words, len)) < 0) {
        if (enable_loop) {
            if ((ret = compute->gen_loop_chain(words, len, result, head, tail, false)) < 2) {
                throw "Error: no word chain meets the requirements.";
            }
            return ret;
        }
        else {
            throw "Error: word text implies word rings.";
        }
    }

    if ((ret = word_graph->topo_sort()) < 0) {
        if (enable_loop) {
            return compute->gen_loop_chain(words, len, result, head, tail, false);
        }
        else {
            throw "Error: word text implies word rings.";
        }
    }

    compute->dp(head, tail);
    if ((ret = compute->gen_result(words, result, head, tail)) < 2) {
        throw "Error: no word chain meets the requirements.";
    }
    return ret;
}


int gen_chain_char(char* words[], int len, char* result[], char head, char tail, bool enable_loop) throw (const char*)
{
    if (words == NULL || result == NULL) {
        throw "Invalid parameter: 'words' or 'result' is null.";
    }
    if (len < 0) {
        throw "Invalid parameter: 'len' is less than 0.";
    }
    if (!isalpha(head) && head != '\0' || !isalpha(tail) && tail != '\0') {
        throw "Invalid parameter: 'head' or 'tail' is not a letter or 0.";
    }

    int ret;
    WordGraph* word_graph = new WordGraph();
    Compute* compute = new Compute(word_graph);

    if ((ret = word_graph->init_weighted(words, len)) < 0) {
        if (enable_loop) {
            if ((ret = compute->gen_loop_chain(words, len, result, head, tail, true)) < 2) {
                throw "Error: no word chain meets the requirements.";
            }
            return ret;
        }
        else {
            throw "Error: word text implies word rings.";
        }
    }

    if ((ret = word_graph->topo_sort()) < 0) {
        if (enable_loop) {
            return compute->gen_loop_chain(words, len, result, head, tail, true);
        }
        else {
            throw "Error: word text implies word rings.";
        }
    }

    compute->dp(head, tail);
    if ((ret = compute->gen_result(words, result, head, tail)) < 2) {
        throw "Error: no word chain meets the requirements.";
    }
    return ret;
}


