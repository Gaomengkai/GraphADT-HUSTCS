#pragma once

// C std library
#include <cstdio>
#include <cstdlib>
#include <cstring>
// C++ std library
#include <iostream>
#include <algorithm>
// STL library
#include <queue>

// Problem Macro and Definitions
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20

const int stNoVertex = -2;
const int stNoFirstAdj = -3;

typedef int status;
typedef int KeyType;
typedef enum { DG, DN, UDG, UDN } GraphKind;
typedef struct {
    KeyType  key;
    char others[20];
} VertexType; //顶点类型定义


typedef struct ArcNode {         //表结点类型定义
    int adjvex;              //顶点位置编号 
    struct ArcNode* nextarc;	   //下一个表结点指针
} ArcNode;
typedef struct VNode {				//头结点及其数组类型定义
    VertexType data;       	//顶点信息
    ArcNode* firstarc;      	 //指向第一条弧
} VNode, AdjList[MAX_VERTEX_NUM];
typedef  struct {  //邻接表的类型定义
    AdjList vertices;     	 //头结点数组
    int vexnum, arcnum;   	  //顶点数、弧数
    GraphKind  kind;        //图的类型
} ALGraph;
typedef struct QUEUE {
    int* elem;
    int front, tail;
    int length;
}QUEUE;
typedef struct {  //图的集合类型定义
    struct {
        char name[30];
        ALGraph G;
    } elem[10];
    int length;
}GRAPHS;


status CreateGraph(ALGraph& G, VertexType V[], KeyType VR[][2]);
status DestroyGraph(ALGraph& G);
int LocateVex(ALGraph G, KeyType u);
status PutVex(ALGraph& G, KeyType u, VertexType v_a_l_v_e);
int FirstAdjVex(ALGraph G, KeyType u);
int NextAdjVex(ALGraph G, KeyType v, KeyType w);
status InsertVex(ALGraph& G, VertexType v);
status DeleteVex(ALGraph& G, KeyType v);
status InsertArc(ALGraph& G, KeyType v, KeyType w);
status DeleteArc(ALGraph& G, KeyType v, KeyType w);
void visit(VertexType v);
void DFSDriver(ALGraph& G, int v, void (*visit)(VertexType), KeyType vst[]);
status DFSTraverse(ALGraph& G, void (*visit)(VertexType));
status BFSTraverse(ALGraph& G, void (*visit)(VertexType));
status SaveGraph(ALGraph G, char FileName[]);
status LoadGraph(ALGraph& G, char FileName[]);
status AddGraph(GRAPHS& graphs, char ListName[]);
status RemoveGraph(GRAPHS& graphs, char ListName[]);
int LocateGraph(GRAPHS graphs, char ListName[]);
bool isEmpty(ALGraph& G);