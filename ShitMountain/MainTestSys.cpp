#include "MainTestSys.h"
using namespace std;

int main()
{
    GRAPHS graphs;
    graphs.length = 0;
    char errMsg[] = { 0x4d,0x65,0x72,0x6b,0x79,0x20,0x55,
        0x32,0x30,0x32,0x30,0x31,0x35,0x34,0x39,0x30,0x00 };
    ALGraph G;
    char graphname[20];
    int result;
    int op = 1;
    while (op) {
        _CLEAR;
        _SCREEN_WHITE;
        printf("                     菜单选项 \n");
        printf("-----------------------------------------------------------------\n");
        printf("1. + 增加图                                     2. X 删除图\n");
        printf("3. ~ 查找图                                     4. ` 选中图\n");
        printf("0. 输入0可退出系统\n");
        printf("-----------------------------------------------------------------\n");
        printf("请选择你的操作[0~4]:");
        cin >> op;
        switch (op) {
        case 1:
            printf("Name of New Graph：");
            cin >> graphname;
            if (LocateGraph(graphs, graphname) != 0){
                printf("已存在!\n");
                _SCREEN_RED;
            }
            else
            {
                AddGraph(graphs, graphname);
                printf("[+] Success！\n");
                _SCREEN_GREEN;
            }
            _PW;
            break;
        case 2:
            printf("Name of Graph to be deleted：");
            cin >> graphname;
            result = RemoveGraph(graphs, graphname);
            if (result == ERROR) {
                printf("[-] No Such Graph！");
                _SCREEN_RED;
            }
            else {
                printf("[+] Success！\n");
                _SCREEN_GREEN;
            }
            _PW;
            break;
        case 3:
            printf("Name of Graph to be found：");
            cin >> graphname;
            result = LocateGraph(graphs, graphname);
            if (result == 0) {
                printf("[-] No Such Graph！");
                _SCREEN_RED;
            }
            else { printf("AT [ %d ]\n", result); }
            _PW;
            break;
        case 4:
            printf("Graph to be Selected：");
            cin >> graphname;
            result = LocateGraph(graphs, graphname);
            if (result != 0)
            {
                G = graphs.elem[result - 1].G;
                graphs.elem[result - 1].G = Second_menu(G);
            }
            else {
                printf("[-] No Such Graph！");
                _SCREEN_RED;
            }
            _PW;
            break;
        case 0:
            break;
        default:
            printf("Merky Gao 高盟凯 U202015490 计算机2007\n");
            puts(errMsg);
            _SCREEN_GREEN;
            _PW;
            break;
        }
    }
    _CLEAR;
    printf("Thx.\n");
    _SCREEN_GREEN;
    return 0;
}

ALGraph Second_menu(ALGraph& G)
{
    int op = 1, u, v;
    int st;
    VertexType value;
    char errMsg[] = { 0x4d,0x65,0x72,0x6b,0x79,0x20,0x55,
    0x32,0x30,0x32,0x30,0x31,0x35,0x34,0x39,0x30,0x00};
    VertexType V[MaxV+11];
    int VR[MaxVR][2];
    while (op) {
        _CLEAR
        printf("-----------------------------------------------------------------\n");
        printf("                     SubMenu \n");
        printf("-----------------------------------------------------------------\n");
        printf(" 1. 创建图 Create Graph               2. 销毁图 Destroy\n");
        printf(" 3. 查找顶点  Locate                  4. 顶点赋值 PutVex\n");
        printf(" 5. 获得第一邻接点 FirstAdjVex         6. 获得下一邻接点NextAdjVex\n");
        printf(" 7. 插入顶点 InsertVex                8. 删除顶点DeleteVex\n");
        printf(" 9. 插入弧 InsertArc                  10. 删除弧DelArc\n");
        printf("11. 深度优先搜索遍历 DFS                12. 广度优先搜索遍历 BFS\n");
        printf("13. 将图中的数据读入文件  SaveToFile     14. 将文件数据传入图LoadFromFile\n");
        printf(" 0. 输入0可返回上一级菜单 Back\n");
        printf("-----------------------------------------------------------------\n");
        printf("请选择你的操作[0~14]:");
        cin >> op;
        switch (op) {
        case 1:
            printf("Vertex and Arc, ends at -1：\n");
            for (int i = 0;i<=MaxV; ++i)
            {
                cin >> V[i].key >> V[i].others;
                if (V[i].key == -1)
                    break;
            }
            for (int i = 0;i<=MaxVR; i++)
            {
                cin >> VR[i][0] >> VR[i][1];
                if (VR[i][0] == -1)
                    break;
            }
            st = CreateGraph(G, V, VR);
            if (st == OK) {
                printf("[+] Success！\n");
                _SCREEN_GREEN;
            }
            else if (st == INFEASIBLE) {
                printf("图已存在！\n");
                _SCREEN_RED;
            }
            else {
                printf("创建失败！\n");
                _SCREEN_RED;
            }
            _PW;
            break;
        case 2:
            st = DestroyGraph(G);
            if (st == OK) {
                printf("[+] Success！\n");
                _SCREEN_GREEN
            }
            else {
                printf("[-] No Such Graph！\n");
                _SCREEN_RED;
            }
            _PW;
            break;
        case 3:
            printf("请输入你想查找的顶点的关键字：");
            cin >> u;
            st = LocateVex(G, u);
            if (st == INFEASIBLE) {
                printf("[-] No Such Graph！\n");
                _SCREEN_RED
            }
            else if (st == -2) {
                printf("顶点不存在！\n");
                _SCREEN_RED
            }
            else {
                printf("顶点的序号为%d。", st);
                _SCREEN_GREEN
            }
            _PW;
            break;
        case 4:
            printf("请输入你想修改的顶点的关键字：");
            cin >> u;
            printf("请输入替换后的数据：");
            cin >> value.key >> value.others;
            st = PutVex(G, u, value);
            if (st == INFEASIBLE) {
                printf("图不存在。\n");
                _SCREEN_RED;
            }
            else if (st == OK) printf("[+] Success！\n");
            else printf("赋值失败！\n");
            _PW;
            break;
        case 5:
            printf("请输入顶点的关键字：");
            scanf("%d", &u);
            st = FirstAdjVex(G, u);
            if (st == INFEASIBLE) printf("图不存在\n");
            else if (st == -2) printf("不存在该顶点！\n");
            else if (st == -3) printf("第一邻接点不存在！\n");
            else printf("第一邻接点的位序为%d！\n", st);
            _PW;
            break;
        case 6:
            printf("请输入两个顶点的关键字：");
            scanf("%d%d", &u, &v);
            st = NextAdjVex(G, u, v);
            if (st == INFEASIBLE) printf("图不存在\n");
            else if (st == -2) printf("查找失败！\n");
            else printf("下一邻接点的位序为%d！\n", st);
            _PW;
            break;
        case 7:
            printf("请输入你想插入的顶点的数据：");
            scanf("%d%s", &value.key, value.others);
            st = InsertVex(G, value);
            if (st == INFEASIBLE) printf("图不存在！\n");
            else if (st == ERROR) printf("插入失败！\n");
            else printf("[+] Success！\n");
            _PW;
            break;
        case 8:
            printf("请输入你想删除的顶点的关键字：");
            scanf("%d", &u);
            st = DeleteVex(G, u);
            if (st == INFEASIBLE) printf("图不存在\n");
            else if (st == ERROR) printf("删除失败！\n");
            else printf("[+] Success！\n");
            _PW;
            break;
        case 9:
            printf("请输入弧的两个顶点的关键字：");
            scanf("%d%d", &u, &v);
            st = InsertArc(G, u, v);
            if (st == INFEASIBLE) printf("图不存在\n");
            else if (st == ERROR) printf("插入失败！\n");
            else printf("[+] Success！\n");
            _PW;
            break;
        case 10:
            printf("请输入弧的两个顶点的关键字：");
            scanf("%d%d", &u, &v);
            st = DeleteArc(G, u, v);
            if (st == INFEASIBLE) printf("图不存在\n");
            else if (st == ERROR) printf("删除失败！\n");
            else printf("[+] Success！\n");
            _PW;
            break;
        case 11:
            st = DFSTraverse(G, visit);
            if (st == INFEASIBLE) printf("图不存在！\n");
            _PW;
            break;
        case 12:
            st = BFSTraverse(G, visit);
            if (st == INFEASIBLE) printf("图不存在！\n");
            _PW;
            break;
        case 13:
            char FileName[20];
            printf("请输入文件名称：");
            scanf("%s", FileName);
            st = SaveGraph(G, FileName);
            if (st == ERROR) printf("打开文件失败！\n");
            else printf("[+] Success！\n");
            _PW;
            break;
        case 14:
            printf("请输入文件名称：");
            scanf("%s", FileName);
            st = LoadGraph(G, FileName);
            if (st == ERROR) printf("打开文件失败！\n");
            else printf("[+] Success！\n");
            _PW;
            break;
        case 0:
            break;
        default:
            puts(errMsg);
            _PW;
            break;
        }//end of switch
    }//end of while
    return G;
}
