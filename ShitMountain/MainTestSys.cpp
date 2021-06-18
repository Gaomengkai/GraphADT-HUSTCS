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
        printf("                     �˵�ѡ�� \n");
        printf("-----------------------------------------------------------------\n");
        printf("1. + ����ͼ                                     2. X ɾ��ͼ\n");
        printf("3. ~ ����ͼ                                     4. ` ѡ��ͼ\n");
        printf("\n5. ���ļ�\n");
        printf("0. ����0���˳�ϵͳ\n");
        printf("-----------------------------------------------------------------\n");
        printf("��ѡ����Ĳ���[0~4]:");
        cin >> op;
        switch (op) {
        case 1:
            printf("Name of New Graph��");
            cin >> graphname;
            if (LocateGraph(graphs, graphname) != 0){
                printf("[-] Graph %s Exists!\n",graphname);
                _SCREEN_RED;
            }
            else
            {
                AddGraph(graphs, graphname);
                printf("[+] Succeeded to create %s��\n",graphname);
                _SCREEN_GREEN;
            }
            _PW;
            break;
        case 2:
            printf("Name of Graph to be deleted��");
            cin >> graphname;
            result = RemoveGraph(graphs, graphname);
            if (result == ERROR) {
                printf("[-] No Such Graph named %s��",graphname);
                _SCREEN_RED;
            }
            else {
                printf("[+] Succeeded to remove %s��\n",graphname);
                _SCREEN_GREEN;
            }
            _PW;
            break;
        case 3:
            printf("Name of Graph to be found��");
            cin >> graphname;
            result = LocateGraph(graphs, graphname);
            if (result == 0) {
                printf("[-] No Such Graph��");
                _SCREEN_RED;
            }
            else { printf("AT [ %d ]\n", result); }
            _PW;
            break;
        case 4:
            printf("Graph to be Selected��");
            cin >> graphname;
            result = LocateGraph(graphs, graphname);
            if (result != 0)
            {
                G = graphs.elem[result - 1].G;
                graphs.elem[result - 1].G = Second_menu(G);
            }
            else {
                printf("[-] No Such Graph��");
                _SCREEN_RED;
            }
            _PW;
            break;
        case 5:
            cout << "Name of Graph:(string)";
            cin >> graphname;
            result = LocateGraph(graphs, graphname);
            if (result == 0) {
                printf("[-] No Such Graph��\n");
                printf("    You must create a new graph before.\n");
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
            printf("Merky Gao ���˿� U202015490 �����2007\n");
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
        printf(" 1. ����ͼ Create Graph                2. ����ͼ Destroy\n");
        printf(" 3. ���Ҷ���  Locate                   4. ���㸳ֵ PutVex\n");
        printf(" 5. ��õ�һ�ڽӵ� FirstAdjVex         6. �����һ�ڽӵ�NextAdjVex\n");
        printf(" 7. ���붥�� InsertVex                8. ɾ������DeleteVex\n");
        printf(" 9. ���뻡 InsertArc                  10. ɾ����DelArc\n");
        printf("11. ��������������� DFS                12. ��������������� BFS\n\n�ļ�����\n");
        printf("13. ��ͼ�е����ݶ����ļ�  SaveToFile     14. ���ļ����ݴ���ͼLoadFromFile\n");
        printf(" 0. ����0�ɷ�����һ���˵� Back\n");
        printf("-----------------------------------------------------------------\n");
        printf("��ѡ����Ĳ���[0~14]:");
        cin >> op;
        switch (op) {
        case 1:
            if (!isEmpty(G)) {
                printf("[-] Already has a Graph��\n");
                _SCREEN_RED;
                _PW;
                break;
            }
            printf("Vertex and Arc, ends at -1��\n");
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
                printf("[+] Success��\n");
                _SCREEN_GREEN;
            }
            else if (st == INFEASIBLE) {
                printf("ͼ�Ѿ�����\nAlready has a Graph��\n");
                _SCREEN_RED;
            }
            else {
                printf("[-] ERROR��\n");
                _SCREEN_RED;
            }
            _PW;
            break;
        case 2:
            st = DestroyGraph(G);
            if (st == OK) {
                printf("[+] Success��\n");
                _SCREEN_GREEN
            }
            else {
                printf("[-] No Such Graph��\n");
                _SCREEN_RED;
            }
            _PW;
            break;
        case 3:
            if (isEmpty(G)) {
                printf("[-] No Such Graph��\n");
                _SCREEN_RED;
                _PW;
                break;
            }
            printf("Key to Find:(key):\t");
            cin >> u;
            st = LocateVex(G, u);
            if (st == INFEASIBLE) {
                printf("[-] No Such Graph��\n");
                _SCREEN_RED
            }
            else if (st == -2) {
                printf("[-] No Such Vertex��\n");
                _SCREEN_RED
            }
            else {
                printf("Vertex AT  [ %d ]��", st);
                _SCREEN_GREEN
            }
            _PW;
            break;
        case 4:
            if (isEmpty(G)) {
                printf("[-] No Such Graph��\n");
                _SCREEN_RED;
                _PW;
                break;
            }
            printf("key to replace:(key): \t");
            cin >> u;
            printf("�������滻�������(key, others)��");
            cin >> value.key >> value.others;
            st = PutVex(G, u, value);
            if (st == OK) {
                printf("[+] Success��\n");
                _SCREEN_GREEN;
            }
            else {
                printf("[-] Fail��\n");
                _SCREEN_RED;
            }
            _PW;
            break;
        case 5:
            if (isEmpty(G)) {
                printf("[-] No Such Graph��\n");
                _SCREEN_RED;
                _PW;
                break;
            }
            printf("FirstAdjVex: (key): \t");
            scanf("%d", &u);
            st = FirstAdjVex(G, u);
            if (st == stNoVertex) {
                printf("[-] No Such Vertex��\n");
                _SCREEN_RED;
            }
            else if (st == stNoFirstAdj) {
                printf("[-] 1st Adj Not Found! \n");
                _SCREEN_RED;
            }
            else {
                printf("1st Adj is [%d] -> [ %d ]��\n", u, st);
                _SCREEN_GREEN;
            }
            _PW;
            break;
        case 6:
            if (isEmpty(G)) {
                printf("[-] No Such Graph��\n");
                _SCREEN_RED;
                _PW;
                break;
            }
            printf(" NextAdjVex: (key => key)��\t");
            cin >> u >> v;
            st = NextAdjVex(G, u, v);
            if (st == -2) {
                printf("[-] Nothins Found��\n");
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
                printf("[-] No Such Graph��\n");
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
                printf("[+] Success��\n");
                _SCREEN_GREEN;
            }
            _PW;
            break;
        case 8:
            if (isEmpty(G)) {
                printf("[-] No Such Graph��\n");
                _SCREEN_RED;
                _PW;
                break;
            }
            printf("v.key to delete: (key)��");
            cin >> u;
            st = DeleteVex(G, u);
            if (st == ERROR) {
                printf("[-] ERROR on DeleteVertex()��\n");
                _SCREEN_RED;
            }
            else {
                printf("[+] Success��\n");
                _SCREEN_GREEN;
            }
            _PW;
            break;
        case 9:
            if (isEmpty(G)) {
                printf("[-] No Such Graph��\n");
                _SCREEN_RED;
                _PW;
                break;
            }
            printf("AddArc: (u.key <-> v.key):\t");
            cin >> u >> v;
            st = InsertArc(G, u, v);
            if (st == ERROR) {
                printf("[-] ERROR on InsertArc()��\n"); _SCREEN_RED;
            }
            else {
                printf("[+] Success��\n"); _SCREEN_GREEN;
            }
            _PW;
            break;
        case 10:
            if (isEmpty(G)) {
                printf("[-] No Such Graph��\n");
                _SCREEN_RED;
                _PW;
                break;
            }
            printf("Delete: (u.key <-> v.key):\t");
            cin >> u >> v;
            st = DeleteArc(G, u, v);
            if (st != OK) {
                printf("[-] ERROR on DeleteArc()��\n"); _SCREEN_RED;
            }
            else {
                printf("[+] Success��\n"); _SCREEN_GREEN;
            }
            _PW;
            break;
        case 11:
            if (isEmpty(G)) {
                printf("[-] No Such Graph��\n");
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
                printf("[-] No Such Graph��\n");
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
                printf("[-] No Such Graph��\n");
                _SCREEN_RED;
                _PW;
                break;
            }
            char FileName[20];
            printf("�������ļ�����/ FILENAME��");
            cin >> FileName;
            st = SaveGraph(G, FileName);
            if (st == ERROR) {
                printf("FILE_ERROR��\n"); _SCREEN_RED;
            }
            else {
                printf("[+] Success��\n"); _SCREEN_GREEN;
            }
            _PW;
            break;
        case 14:
            if (!isEmpty(G)) {
                printf("[-] Already Exist Such Graph��\n");
                _SCREEN_RED;
                _PW;
                break;
            }
            printf("�������ļ����� / FILENAME��");
            scanf("%s", FileName);
            st = LoadGraph(G, FileName);
            if (st == ERROR) {
                printf("FILE_ERROR��\n"); _SCREEN_RED;
            }
            else {
                printf("[+] Success��\n"); _SCREEN_GREEN;
            }
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
