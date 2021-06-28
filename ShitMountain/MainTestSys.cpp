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
    char fileName[20];
    memset(graphname, 0, sizeof(graphname));
    memset(fileName, 0, sizeof(fileName));

    int result = -1;
    int res2 = -1;
    int op = 1;
    while (op) {
        _CLEAR;
        _SCREEN_WHITE;
        printf("                     菜单选项 \n");
        printf("-----------------------------------------------------------------\n");
        printf("1. + 增加图                                     2. X 删除图\n");
        printf("3. ~ 查找图                                     4. ` 选中图\n");
        printf("\n5. 读文件\n");
        printf("0. 输入0可退出系统\n");
        printf("-----------------------------------------------------------------\n");
        printf("Your choice [0~5]: ");
        cin >> op;
        switch (op) {
        case 1:
            printf("Name of New Graph：");
            cin >> graphname;
            if (LocateGraph(graphs, graphname) != 0){
                printf("[-] Graph %s Exists!\n",graphname);
                _SCREEN_RED;
            }
            else
            {
                AddGraph(graphs, graphname);
                printf("[+] Succeeded to create %s！\n",graphname);
                _SCREEN_GREEN;
            }
            _PW;
            break;
        case 2:
            printf("Name of Graph to be deleted：");
            cin >> graphname;
            result = RemoveGraph(graphs, graphname);
            if (result == ERROR) {
                printf("[-] No Such Graph named %s！",graphname);
                _SCREEN_RED;
            }
            else {
                printf("[+] Succeeded to remove %s！\n",graphname);
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
        case 5:
            cout << "Name of Graph:(string)";
            cin >> graphname;
            result = LocateGraph(graphs, graphname);
            if (result == 0) {
                printf("[-] No Such Graph！\n");
                printf("    You must create a new graph before.\n");
                _SCREEN_RED;
                _PW;
                break;
            }
            else if (!isEmpty(graphs.elem[result - 1].G)) {
                printf("[-] Graph is not empty！\n");
                _SCREEN_RED;
                _PW;
                break;
            }
            cout << "Name of File:(string)";
            cin >> fileName;
            res2 = LoadGraph(graphs.elem[result - 1].G, fileName);
            if (OK == res2) {
                cout << "[+] Successs!\n";
                _SCREEN_GREEN;
            }
            else {
                cout << "[-] Load Error!\n";
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
        printf(" 1. 创建图 Create Graph                2. 销毁图 Destroy\n");
        printf(" 3. 查找顶点  Locate                   4. 顶点赋值 PutVex\n");
        printf(" 5. 获得第一邻接点 FirstAdjVex         6. 获得下一邻接点NextAdjVex\n");
        printf(" 7. 插入顶点 InsertVex                8. 删除顶点DeleteVex\n");
        printf(" 9. 插入弧 InsertArc                  10. 删除弧DelArc\n");
        printf("11. 深度优先搜索遍历 DFS                12. 广度优先搜索遍历 BFS\n\n--[文件操作]\n");
        printf("13. 将图中的数据读入文件  SaveToFile     14. 将文件数据传入图LoadFromFile\n");
        printf(" 0. 输入0可返回上一级菜单 Back\n");
        printf("-----------------------------------------------------------------\n");
        printf("请选择你的操作[0~14]:");
        cin >> op;
        switch (op) {
        case 1:
            if (!isEmpty(G)) {
                printf("[-] Already has a Graph！\n");
                _SCREEN_RED;
                _PW;
                break;
            }
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
                printf("图已经存在\nAlready has a Graph！\n");
                _SCREEN_RED;
            }
            else {
                printf("[-] ERROR！\n");
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
            if (isEmpty(G)) {
                printf("[-] No Such Graph！\n");
                _SCREEN_RED;
                _PW;
                break;
            }
            printf("Key to Find:(key):\t");
            cin >> u;
            st = LocateVex(G, u);
            if (st == INFEASIBLE) {
                printf("[-] No Such Graph！\n");
                _SCREEN_RED
            }
            else if (st == -2) {
                printf("[-] No Such Vertex！\n");
                _SCREEN_RED
            }
            else {
                printf("Vertex AT  [ %d ]。", st);
                _SCREEN_GREEN
            }
            _PW;
            break;
        case 4:
            if (isEmpty(G)) {
                printf("[-] No Such Graph！\n");
                _SCREEN_RED;
                _PW;
                break;
            }
            printf("key to replace:(key): \t");
            cin >> u;
            printf("请输入替换后的数据(key, others)：");
            cin >> value.key >> value.others;
            st = PutVex(G, u, value);
            if (st == OK) {
                printf("[+] Success！\n");
                _SCREEN_GREEN;
            }
            else {
                printf("[-] Fail！\n");
                _SCREEN_RED;
            }
            _PW;
            break;
        case 5:
            if (isEmpty(G)) {
                printf("[-] No Such Graph！\n");
                _SCREEN_RED;
                _PW;
                break;
            }
            printf("FirstAdjVex: (key): \t");
            scanf("%d", &u);
            st = FirstAdjVex(G, u);
            if (st == stNoVertex) {
                printf("[-] No Such Vertex！\n");
                _SCREEN_RED;
            }
            else if (st == stNoFirstAdj) {
                printf("[-] 1st Adj Not Found! \n");
                _SCREEN_RED;
            }
            else {
                printf("1st Adj is [%d] -> [ %d ]！\n", u, st);
                _SCREEN_GREEN;
            }
            _PW;
            break;
        case 6:
            if (isEmpty(G)) {
                printf("[-] No Such Graph！\n");
                _SCREEN_RED;
                _PW;
                break;
            }
            printf(" NextAdjVex: (key => key)：\t");
            cin >> u >> v;
            st = NextAdjVex(G, u, v);
            if (st == -2) {
                printf("[-] Nothing Found！\n");
                _SCREEN_RED;
            }
            else {
                printf("NextAdj AT  [ %d ]\n", st);
                _SCREEN_GREEN;
            }
            _PW;
            break;
        case 7:
            if (isEmpty(G)) {
                printf("[-] No Such Graph！\n");
                _SCREEN_RED;
                _PW;
                break;
            }
            printf("Insert a Vertex: (key, others): \t");
            cin >> value.key >> value.others;
            st = InsertVex(G, value);
            if (st == ERROR) {
                printf("[-] ERROR on InsertVex()\n");
                _SCREEN_RED;
            }
            else {
                printf("[+] Success！\n");
                _SCREEN_GREEN;
            }
            _PW;
            break;
        case 8:
            if (isEmpty(G)) {
                printf("[-] No Such Graph！\n");
                _SCREEN_RED;
                _PW;
                break;
            }
            printf("v.key to delete: (key)：");
            cin >> u;
            st = DeleteVex(G, u);
            if (st == ERROR) {
                printf("[-] ERROR on DeleteVertex()！\n");
                _SCREEN_RED;
            }
            else {
                printf("[+] Success！\n");
                _SCREEN_GREEN;
            }
            _PW;
            break;
        case 9:
            if (isEmpty(G)) {
                printf("[-] No Such Graph！\n");
                _SCREEN_RED;
                _PW;
                break;
            }
            printf("AddArc: (u.key <-> v.key):\t");
            cin >> u >> v;
            st = InsertArc(G, u, v);
            if (st == ERROR) {
                printf("[-] ERROR on InsertArc()！\n"); _SCREEN_RED;
            }
            else {
                printf("[+] Success！\n"); _SCREEN_GREEN;
            }
            _PW;
            break;
        case 10:
            if (isEmpty(G)) {
                printf("[-] No Such Graph！\n");
                _SCREEN_RED;
                _PW;
                break;
            }
            printf("Delete: (u.key <-> v.key):\t");
            cin >> u >> v;
            st = DeleteArc(G, u, v);
            if (st != OK) {
                printf("[-] ERROR on DeleteArc()！\n"); _SCREEN_RED;
            }
            else {
                printf("[+] Success！\n"); _SCREEN_GREEN;
            }
            _PW;
            break;
        case 11:
            if (isEmpty(G)) {
                printf("[-] No Such Graph！\n");
                _SCREEN_RED;
                _PW;
                break;
            }
            st = DFSTraverse(G, visit);
            _SCREEN_GREEN;
            _PW;
            break;
        case 12:
            if (isEmpty(G)) {
                printf("[-] No Such Graph！\n");
                _SCREEN_RED;
                _PW;
                break;
            }
            st = BFSTraverse(G, visit);
            _SCREEN_GREEN;
            _PW;
            break;
        case 13:
            if (isEmpty(G)) {
                printf("[-] No Such Graph！\n");
                _SCREEN_RED;
                _PW;
                break;
            }
            char FileName[20];
            printf("请输入文件名称/ FILENAME：");
            cin >> FileName;
            st = SaveGraph(G, FileName);
            if (st == ERROR) {
                printf("FILE_ERROR！\n"); _SCREEN_RED;
            }
            else {
                printf("[+] Success！\n"); _SCREEN_GREEN;
            }
            _PW;
            break;
        case 14:
            if (!isEmpty(G)) {
                printf("[-] Already Exist Such Graph！\n");
                _SCREEN_RED;
                _PW;
                break;
            }
            printf("请输入文件名称 / FILENAME：");
            scanf("%s", FileName);
            st = LoadGraph(G, FileName);
            if (st == ERROR) {
                printf("FILE_ERROR！\n"); _SCREEN_RED;
            }
            else {
                printf("[+] Success！\n"); _SCREEN_GREEN;
            }
            _PW;
            break;
        case 0:
            puts(errMsg);
            break;
        default:
            puts(errMsg);
            _PW;
            break;
        }//end of switch
    }//end of while
    return G;
}
