﻿// ShitMountain.cpp: 定义应用程序的入口点。
//

#include <string.h>
#include "stdio.h"
#include "stdlib.h"
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20
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
GRAPHS graphs;
int visited[20];
int visited1[20];

status CreateGraph(ALGraph& G, VertexType V[], KeyType VR[][2]) //创建无向图
{
    if (G.vexnum != 0) return INFEASIBLE;
    int Vnumber, VRnumber, tmpVtx[30]; //temp1用来记录头结点在数组中的序号
    KeyType hasNode[30];  //用来判断V VR是否正确
    memset(tmpVtx, 0, sizeof(tmpVtx));
    memset(hasNode, 0, sizeof(hasNode));
    for (int i = 0; V[i].key != -1; i++) //判断V是否正确
    {
        if (hasNode[V[i].key] == 0)
            hasNode[V[i].key] = 1;
        else
            return ERROR;
    }
    for (int j = 0; VR[j][0] != -1; j++)                   //判断VR是否正确
        if (hasNode[VR[j][0]] == 0 || hasNode[VR[j][1]] == 0)
            return ERROR;

    for (Vnumber = 0; V[Vnumber].key != -1; Vnumber++);    //求顶点个数
    if (Vnumber > 20) return ERROR;                        //超过最大值
    for (VRnumber = 0; VR[VRnumber][0] != -1; VRnumber++); //求边个数
    G.vexnum = Vnumber; G.arcnum = VRnumber; G.kind = DG;
    for (int k = 0; k < Vnumber; k++)                      //构建头结点数组
    {
        G.vertices[k].data.key = V[k].key;
        strcpy(G.vertices[k].data.others, V[k].others);
        tmpVtx[V[k].key] = k;
        G.vertices[k].firstarc = NULL;
    }
    for (int l = 0; l < VRnumber; l++)                 //插入表结点
    {
        ArcNode* r1 = (ArcNode*)malloc(sizeof(ArcNode));
        ArcNode* r2 = (ArcNode*)malloc(sizeof(ArcNode));
        r1->adjvex = tmpVtx[VR[l][0]]; r2->adjvex = tmpVtx[VR[l][1]];
        r1->nextarc = G.vertices[tmpVtx[VR[l][1]]].firstarc;
        G.vertices[tmpVtx[VR[l][1]]].firstarc = r1;
        r2->nextarc = G.vertices[tmpVtx[VR[l][0]]].firstarc;
        G.vertices[tmpVtx[VR[l][0]]].firstarc = r2;
    }
    return OK;
}

status DestroyGraph(ALGraph& G)       //销毁无向图G
{
    if (!G.vexnum) return INFEASIBLE; //图G不存在
    for (int i = 0; i < G.vexnum; i++)
    {
        ArcNode* p = G.vertices[i].firstarc;
        while (p)  //销毁表结点
        {
            ArcNode* q = p;
            p = p->nextarc;
            free(q);
        }
    }
    G.vexnum = 0; G.arcnum = 0;
    return OK;
}

int LocateVex(ALGraph G, KeyType u)  //查找顶点
{
    if (!G.vexnum) return INFEASIBLE;  //图不存在
    for (int i = 0; i < G.vexnum; i++)
        if (G.vertices[i].data.key == u)
            return i;
    return -2;
}

//status FindRepetition(ALGraph& G, KeyType u)  //查找是否有重复
//{
//    for (int i = 0; i < G.vexnum; i++)
//        if (G.vertices[i].data.key == u)   //关键字重复
//            return 1;
//    return 0;
//}

status PutVex(ALGraph& G, KeyType u, VertexType v_a_l_v_e)   //根据u在图G中查找顶点，查找成功将该顶点值修改成value
{
    if (!G.vexnum) return INFEASIBLE;
    if (u != v_a_l_v_e.key)
    {
        if (LocateVex(G, v_a_l_v_e.key) == -1)return ERROR;
    }
    int b = LocateVex(G, u);     //b为顶点的下标
    if (b == -2) return ERROR;   //不存在关键字为u的顶点
    G.vertices[b].data.key = v_a_l_v_e.key;
    strcpy(G.vertices[b].data.others, v_a_l_v_e.others);
    return OK;
}

int FirstAdjVex(ALGraph G, KeyType u)   //根据u在图G中查找顶点，查找成功返回顶点u的第一邻接顶点位序
{
    if (!G.vexnum) return INFEASIBLE;
    int a = LocateVex(G, u);  //a为顶点的位序
    if (a == -2) return -2;   //未找到顶点u
    else
    {
        if (G.vertices[a].firstarc != NULL)
            return (G.vertices[a].firstarc)->adjvex;  //返回第一邻接点的位序
        else
            return -3;
    }

}

int NextAdjVex(ALGraph G, KeyType v, KeyType w)
//根据u在图G中查找顶点，查找成功返回顶点v的邻接顶点相对于w的下一邻接顶点的位序
{
    if (!G.vexnum) return INFEASIBLE;
    int loc_v = LocateVex(G, v), loc_w = LocateVex(G, w);  //loc_v是v顶点的位序   loc_w是w顶点的位序
    if (loc_v == -2 || loc_w == -2) return -2;   //v或w顶点不存在
    ArcNode* p = G.vertices[loc_v].firstarc;
    if (!p) return -2;   //v顶点为独立顶点
    ArcNode* q = p->nextarc;
    while (p && q)
    {
        if (G.vertices[p->adjvex].data.key == w)
            return q->adjvex;  //返回下一邻接点的位序
        p = p->nextarc;
        q = q->nextarc;
    }
    return -2;
}

status InsertVex(ALGraph& G, VertexType v)
//在图G中插入顶点v
{
    if (G.vexnum == MAX_VERTEX_NUM) return ERROR;  //图的顶点个数达到最大
    if (LocateVex(G, v.key)!=-1) return ERROR;   //图中已有关键字为v的顶点
    G.vertices[G.vexnum].data.key = v.key;
    strcpy(G.vertices[G.vexnum].data.others, v.others);
    G.vertices[G.vexnum].firstarc = NULL;
    G.vexnum++;
    return OK;
}

status DeleteVex(ALGraph& G, KeyType v) {//在图G中删除关键字v对应的顶点以及相关的弧
    if (!G.vexnum) return INFEASIBLE;
    if (G.vexnum == 1) return ERROR;
    // debug
    int nFree = 0;
    // Cannot del the graph with only one vertex...
    int viSelVertex = LocateVex(G, v);
    if (viSelVertex == -1)return ERROR;
    ArcNode* eEdgeRelatedToSelectedVertex = G.vertices[viSelVertex].firstarc;

    while (eEdgeRelatedToSelectedVertex) {//找出与将要删除结点相关联的结点 
        int viDestOfSelEdge = eEdgeRelatedToSelectedVertex->adjvex;
        VNode* vDestOfSelEdge = &G.vertices[viDestOfSelEdge];
        ArcNode* eSecondaryRelatedEdge = vDestOfSelEdge->firstarc, * s = NULL;
        while (eSecondaryRelatedEdge) {//删除adjvex为i的表结点
            if (eSecondaryRelatedEdge->adjvex == viSelVertex) {
                // this situation is that whether I need to lcoate the pre arc
                if (eSecondaryRelatedEdge == G.vertices[viDestOfSelEdge].firstarc) {
                    vDestOfSelEdge->firstarc = eSecondaryRelatedEdge->nextarc;
                    free(eSecondaryRelatedEdge);
                }
                else {
                    s->nextarc = eSecondaryRelatedEdge->nextarc;
                    free(eSecondaryRelatedEdge);
                }
                G.arcnum -= 1;
                nFree += 1;
                break;
            }
            s = eSecondaryRelatedEdge;
            eSecondaryRelatedEdge = s->nextarc;
        }
        auto t = eEdgeRelatedToSelectedVertex;
        eEdgeRelatedToSelectedVertex = eEdgeRelatedToSelectedVertex->nextarc;
        free(t);
    }
    for (int j = viSelVertex; j < G.vexnum - 1; j++) { // Move forward the last vertex
        G.vertices[j].data.key = G.vertices[j + 1].data.key;
        strcpy(G.vertices[j].data.others, G.vertices[j + 1].data.others);
        G.vertices[j].firstarc = G.vertices[j + 1].firstarc;
    }
    G.vexnum--;
    for (int j = 0; j < G.vexnum; j++) {
        ArcNode* ptr = G.vertices[j].firstarc;
        while (ptr) { // fix the vex turned to far vex
            if (ptr->adjvex > viSelVertex)
                ptr->adjvex--;
            ptr = ptr->nextarc;
        }
    }
    //printf("Edge: %d\tVertex: %d\tnFree: %d\n",G.arcnum, G.vexnum, nFree);
    return OK;
}

status InsertArc(ALGraph& G, KeyType v, KeyType w)
//在图G中增加弧<v,w>
{
    if (!G.vexnum) return INFEASIBLE;  //图不存在
    int nums[30] = { 0 };   //用来标记已存在的顶点
    for (int i = 0; i < G.vexnum; i++)
    {
        if (nums[G.vertices[i].data.key] == 0)
            nums[G.vertices[i].data.key] = 1;
        else
            return ERROR;
    }
    if (!nums[v] || !nums[w]) return ERROR; //不存在相应结点
    int loc_v = LocateVex(G, v), loc_w = LocateVex(G, w);   //存在相应结点并求出结点的下标
    ArcNode* p = G.vertices[loc_v].firstarc;
    while (p)
    {
        if (p->adjvex == loc_w)
            return ERROR;  //边已存在
        p = p->nextarc;
    }
    ArcNode* ptr2 = (ArcNode*)malloc(sizeof(ArcNode));   //添加两个表结点
    ArcNode* ptr1 = (ArcNode*)malloc(sizeof(ArcNode));
    ptr1->adjvex = loc_w;
    ptr1->nextarc = G.vertices[loc_v].firstarc;
    G.vertices[loc_v].firstarc = ptr1;
    ptr2->adjvex = loc_v;
    ptr2->nextarc = G.vertices[loc_w].firstarc;
    G.vertices[loc_w].firstarc = ptr2;
    G.arcnum++;
    return OK;
}

status DeleteArc(ALGraph& G, KeyType v, KeyType w)
//在图G中删除弧<v,w>
{
    if (!G.vexnum) return INFEASIBLE;
    int nums[30] = { 0 }, num = 0;
    for (int i = 0; i < G.vexnum; i++)
    {
        if (nums[G.vertices[i].data.key] == 0)
            nums[G.vertices[i].data.key] = 1;
        else
            return ERROR;
    }
    if (!nums[v] || !nums[w]) return ERROR; //不存在相应结点
    int loc_v = LocateVex(G, v), loc_w = LocateVex(G, w); //结点的下标
    ArcNode* p = G.vertices[loc_v].firstarc;
    if (!p) return ERROR; //关键字为v的结点不含有弧
    ArcNode* q = p;
    while (p) //删除（v,w）
    {
        if (p->adjvex == loc_w && !num)
        {
            G.vertices[loc_v].firstarc = p->nextarc;
            free(p);
            if (G.kind == DG) return OK;
            break;
        }
        else if (p->adjvex == loc_w && num)
        {
            q->nextarc = p->nextarc;
            free(p);
            if (G.kind == DG) return OK;
            break;
        }
        q = p;
        num++;
        p = q->nextarc;
    }
    if (!p) return ERROR; //未找到对应弧
    int num1 = 0;
    ArcNode* p1 = G.vertices[loc_w].firstarc;
    ArcNode* q1 = p1;
    while (p1) //删除<w,v>
    {
        if (p1->adjvex == loc_v && !num1)
        {
            G.vertices[loc_w].firstarc = p1->nextarc;
            free(p1);
        }
        else if (p1->adjvex == loc_v && num1)
        {
            q1->nextarc = p1->nextarc;
            free(p1);
        }
        q1 = p1;
        num1++;
        p1 = q1->nextarc;
    }
    return OK;
}

void visit(VertexType v)
{
    printf(" %d %s", v.key, v.others);
}
void DFS(ALGraph& G, int v, void (*visit)(VertexType))
{
    visited[v] = 1;
    visit(G.vertices[v].data);
    for (ArcNode* p = G.vertices[v].firstarc; p; p = p->nextarc)
        if (!visited[p->adjvex])  //顶未访问
            DFS(G, p->adjvex, visit);
}
status DFSTraverse(ALGraph& G, void (*visit)(VertexType))
//对图G进行深度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    if (!G.vexnum) return INFEASIBLE;
    for (int k = 0; k < 20; k++)
        visited[k] = 0;       //将visited元素初始化为0
    if (!G.vexnum) return INFEASIBLE;
    for (int i = 0; i < G.vexnum; i++)
        if (!visited[i])  //未访问过
            DFS(G, i, visit);
    return OK;
}

status BFSTraverse(ALGraph& G, void (*visit)(VertexType))
//对图G进行广度优先搜索遍历，依次对图中的每一个顶点使用函数visit访问一次，且仅访问一次
{
    if (!G.vexnum) return INFEASIBLE;
    for (int k = 0; k < 20; k++)
        visited1[k] = 0;       //将visited1元素初始化为0
    QUEUE queue;
    queue.elem = (int*)malloc(sizeof(int) * MAX_VERTEX_NUM);
    queue.front = 0; queue.tail = 0; queue.length = 0;  //初始化队列
    for (int i = 0; i < G.vexnum; i++)
        if (!visited1[i])
        {
            visit(G.vertices[i].data);
            visited1[i] = 1;  //访问过后做标记
            *(queue.elem + queue.tail) = i;
            queue.length++;    //将顶点位序入队列
            queue.tail = (queue.tail + MAX_VERTEX_NUM) % MAX_VERTEX_NUM;
            if (queue.length != 0)
            {
                int a = *(queue.elem + queue.front);  //访问队列第一个元素
                queue.front = (queue.front + MAX_VERTEX_NUM) % MAX_VERTEX_NUM;  //将第一个元素出队列
                queue.length--;
                for (ArcNode* p = G.vertices[a].firstarc; p; p = p->nextarc)  //每访问队列中的一个元素，将与其连接的顶点的位序入队列
                {
                    if (!visited1[p->adjvex])
                    {
                        visited1[p->adjvex] = 1;
                        visit(G.vertices[p->adjvex].data);
                        *(queue.elem + queue.tail) = p->adjvex;  //与其连接的顶点的位序入队列
                        queue.length++;
                        queue.tail = (queue.tail + MAX_VERTEX_NUM) % MAX_VERTEX_NUM;
                    }
                }
            }
        }
    return OK;
}

status SaveGraph(ALGraph G, char FileName[])
//将图的数据写入到文件FileName中
{
    int nums[20] = { 0 };
    FILE* fp = fopen(FileName, "w");
    if (!fp) return ERROR;;
    for (int i = 0; i < G.vexnum; i++)  //将顶点的信息存入文件
    {
        fprintf(fp, "%d %s ", G.vertices[i].data.key, G.vertices[i].data.others);
    }
    fprintf(fp, "-1 nil ");  //打印结束标志
    for (int j = 0; j < G.vexnum; j++)  //遍历每个顶点
    {
        ArcNode* p = G.vertices[j].firstarc;
        while (p)  //将每个没保存的弧存入文件
        {
            if (!nums[G.vertices[p->adjvex].data.key])
                fprintf(fp, "%d %d ", G.vertices[j].data.key, G.vertices[p->adjvex].data.key);
            p = p->nextarc;
        }
        if (!nums[G.vertices[j].data.key])
            nums[G.vertices[j].data.key] = 1;
    }
    fprintf(fp, "-1 -1");
    fclose(fp);
    return OK;
}
status LoadGraph(ALGraph& G, char FileName[])
//读入文件FileName的图数据，创建图的邻接表
{
    VertexType V[20];
    int VR[20][2];
    FILE* fp = fopen(FileName, "r");
    if (!fp) return ERROR;
    for (int i = 0;; i++)  //用V储存顶点数据
    {
        fscanf(fp, "%d%s", &V[i].key, V[i].others);
        if (V[i].key == -1)
            break;
    }
    for (int j = 0;; j++)  //用VR储存弧数据
    {
        fscanf(fp, "%d%d", &VR[j][0], &VR[j][1]);
        if (VR[j][0] == -1)
            break;
    }
    fclose(fp);
    CreateGraph(G, V, VR);  //使用既有函数构建图
    return OK;
}

status AddGraph(GRAPHS& graphs, char ListName[])
// 在Lists中增加一个名称为ListName的空单链表。
{
    strcpy(graphs.elem[graphs.length].name, ListName);
    graphs.length++;
    return 0;
}
status RemoveGraph(GRAPHS& graphs, char ListName[])
// Lists中删除一个名称为ListName的线性表
{
    for (int i = 0; i < graphs.length; i++)
    {
        if (!strcmp(ListName, graphs.elem[i].name))
        {
            DestroyGraph(graphs.elem[i].G);
            for (int j = i; j < graphs.length; j++)
            {
                graphs.elem[j].G = graphs.elem[j + 1].G;
                strcpy(graphs.elem[j].name, graphs.elem[j + 1].name);
            }
            graphs.length--;
            return OK;
        }
    }
    return ERROR;
}
int LocateGraph(GRAPHS graphs, char ListName[])
// 在Lists中查找一个名称为ListName的线性表
{
    for (int i = 0; i < graphs.length; i++)
    {
        if (!strcmp(ListName, graphs.elem[i].name))
            return i + 1;

    }
    return 0;
}

ALGraph Second_menu(ALGraph& G)
{
    int op = 1, u, v;
    int result;
    VertexType value;
    while (op) {
        system("cls");	printf("\n\n");
        printf("                     菜单选项 \n");
        printf("-----------------------------------------------------------------\n");
        printf(" 1. 创建图                              2. 销毁图\n");
        printf(" 3. 查找顶点                            4. 顶点赋值\n");
        printf(" 5. 获得第一邻接点                      6. 获得下一邻接点\n");
        printf(" 7. 插入顶点                            8. 删除顶点\n");
        printf(" 9. 插入弧                             10. 删除弧\n");
        printf("11. 深度优先搜索遍历                   12. 广度优先搜索遍历\n");
        printf("13. 将图中的数据读入文件               14. 将文件数据传入图\n");
        printf(" 0. 输入0可返回上一级菜单\n");
        printf("-----------------------------------------------------------------\n");
        printf("请选择你的操作[0~14]:");
        scanf("%d", &op);
        switch (op) {
        case 1:
            VertexType V[20];
            int VR[20][2];
            printf("请输入顶点的数据和弧的数据：\n");
            for (int i = 0;; i++)  //用V储存顶点数据
            {
                scanf("%d%s", &V[i].key, V[i].others);
                if (V[i].key == -1)
                    break;
            }
            for (int j = 0;; j++)  //用VR储存弧数据
            {
                scanf("%d%d", &VR[j][0], &VR[j][1]);
                if (VR[j][0] == -1)
                    break;
            }
            result = CreateGraph(G, V, VR);
            if (result == OK) printf("创建成功！\n");
            else if (result == INFEASIBLE) printf("图已存在！\n");
            else printf("创建失败！\n");
            getchar(); getchar();
            break;
        case 2:
            result = DestroyGraph(G);
            if (result == OK) printf("图销毁成功！\n");
            else printf("图不存在！\n");
            getchar(); getchar();
            break;
        case 3:
            printf("请输入你想查找的顶点的关键字：");
            scanf("%d", &u);
            result = LocateVex(G, u);
            if (result == INFEASIBLE) printf("图不存在！\n");
            else if (result == -2) printf("顶点不存在！\n");
            else printf("顶点的序号为%d。", result);
            getchar(); getchar();
            break;
        case 4:
            printf("请输入你想修改的顶点的关键字：");
            scanf("%d", &u);
            printf("请输入替换后的数据：");
            scanf("%d%s", &value.key, value.others);
            result = PutVex(G, u, value);
            if (result == INFEASIBLE) printf("图不存在。\n");
            else if (result == OK) printf("赋值成功。\n");
            else printf("赋值失败！\n");
            getchar(); getchar();
            break;
        case 5:
            printf("请输入顶点的关键字：");
            scanf("%d", &u);
            result = FirstAdjVex(G, u);
            if (result == INFEASIBLE) printf("图不存在\n");
            else if (result == -2) printf("不存在该顶点！\n");
            else if (result == -3) printf("第一邻接点不存在！\n");
            else printf("第一邻接点的位序为%d！\n", result);
            getchar(); getchar();
            break;
        case 6:
            printf("请输入两个顶点的关键字：");
            scanf("%d%d", &u, &v);
            result = NextAdjVex(G, u, v);
            if (result == INFEASIBLE) printf("图不存在\n");
            else if (result == -2) printf("查找失败！\n");
            else printf("下一邻接点的位序为%d！\n", result);
            getchar(); getchar();
            break;
        case 7:
            printf("请输入你想插入的顶点的数据：");
            scanf("%d%s", &value.key, value.others);
            result = InsertVex(G, value);
            if (result == INFEASIBLE) printf("图不存在！\n");
            else if (result == ERROR) printf("插入失败！\n");
            else printf("插入成功！\n");
            getchar(); getchar();
            break;
        case 8:
            printf("请输入你想删除的顶点的关键字：");
            scanf("%d", &u);
            result = DeleteVex(G, u);
            if (result == INFEASIBLE) printf("图不存在\n");
            else if (result == ERROR) printf("删除失败！\n");
            else printf("删除成功！");
            getchar(); getchar();
            break;
        case 9:
            printf("请输入弧的两个顶点的关键字：");
            scanf("%d%d", &u, &v);
            result = InsertArc(G, u, v);
            if (result == INFEASIBLE) printf("图不存在\n");
            else if (result == ERROR) printf("插入失败！\n");
            else printf("插入成功！");
            getchar(); getchar();
            break;
        case 10:
            printf("请输入弧的两个顶点的关键字：");
            scanf("%d%d", &u, &v);
            result = DeleteArc(G, u, v);
            if (result == INFEASIBLE) printf("图不存在\n");
            else if (result == ERROR) printf("删除失败！\n");
            else printf("删除成功！");
            getchar(); getchar();
            break;
        case 11:
            result = DFSTraverse(G, visit);
            if (result == INFEASIBLE) printf("图不存在！\n");
            getchar(); getchar();
            break;
        case 12:
            result = BFSTraverse(G, visit);
            if (result == INFEASIBLE) printf("图不存在！\n");
            getchar(); getchar();
            break;
        case 13:
            char FileName[20];
            printf("请输入文件名称：");
            scanf("%s", FileName);
            result = SaveGraph(G, FileName);
            if (result == ERROR) printf("打开文件失败！\n");
            else printf("保存成功！\n");
            getchar(); getchar();
            break;
        case 14:
            printf("请输入文件名称：");
            scanf("%s", FileName);
            result = LoadGraph(G, FileName);
            if (result == ERROR) printf("打开文件失败！\n");
            else printf("传入成功！\n");
            getchar(); getchar();
            break;
        case 0:
            break;
        default:
            printf("输入错误！\n");
            getchar(); getchar();
            break;
        }//end of switch
    }//end of while
    return G;
}

int main()
{
    graphs.length = 0;
    ALGraph G;
    char graphname[20];
    int result;
    int op = 1;
    while (op) {
        system("cls");	printf("\n\n");
        printf("                     菜单选项 \n");
        printf("-----------------------------------------------------------------\n");
        printf("1. 增加图                                     2. 删除图\n");
        printf("3. 查找图                                     4. 选中图\n");
        printf("0. 输入0可退出系统\n");
        printf("-----------------------------------------------------------------\n");
        printf("请选择你的操作[0~4]:");
        scanf("%d", &op);
        switch (op) {
        case 1:
            printf("请输入你想添加的图的名称：");
            scanf("%s", graphname);
            if (LocateGraph(graphs, graphname) != 0)
                printf("图已存在!\n");
            else
            {
                AddGraph(graphs, graphname);
                printf("添加成功！\n");
            }
            getchar(); getchar();
            break;
        case 2:
            printf("请输入你想删除的图的名称：");
            scanf("%s", graphname);
            result = RemoveGraph(graphs, graphname);
            if (result == ERROR) printf("图不存在！");
            else printf("删除成功！\n");
            getchar(); getchar();
            break;
        case 3:
            printf("请输入你想查找的图的名称：");
            scanf("%s", graphname);
            result = LocateGraph(graphs, graphname);
            if (result == 0) printf("未找到该图！\n");
            else printf("该图在第%d个。", result);
            getchar(); getchar();
            break;
        case 4:
            printf("请输入你想选中的图的名称：");
            scanf("%s", graphname);
            result = LocateGraph(graphs, graphname);
            if (result != 0)
            {
                G = graphs.elem[result - 1].G;
                graphs.elem[result - 1].G = Second_menu(G);
            }
            else  printf("不存在！");
            getchar(); getchar();
            break;
        case 0:
            break;
        default:
            printf("输入错误！");
            getchar(); getchar();
            break;
        }//end of switch
    }//end of while
    printf("欢迎下次再使用本系统！\n");
    return 0;
}
