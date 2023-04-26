#include "includes/Assistance.h"                    // 辅助软件包
#include "includes/AdjListDirNetwork.h"        // 邻接表有向网
#include <stdlib.h>

int main(void) {
    try                                    // 用try封装可能出现异常的代码
    {
        srand(1);
        int infity = DEFAULT_INFINITY;
        char vexs[] = {'A', 'B', 'C', 'D'};
        /*int m[4][4] = {
                {infity, 2,      3,      4},
                {2,      infity, 5,      6},
                {3,      5,      infity, 7},
                {4,      6,      7,      infity}
        };*/
        char c = 'a', e, e1, e2;
        int n = 4, v, v1, v2, w;
        bool flag;
        int ori[510];
        int sum;
        AdjListDirNetwork<char, int> net(vexs, n);

        for (int v = 0; v < n; v++)
            for (int u = v + 1; u < n; u++)
                net.InsertArc(v, u, rand());

        while (c != 'Z') {
            cout << endl << "1. 无向网清空.";
            cout << endl << "2. 显示无向网.";
            cout << endl << "3. 取指定顶点的值.";
            cout << endl << "4. 设置指定顶点的值.";
            cout << endl << "5. 删除顶点.";
            cout << endl << "6. 插入顶点.";
            cout << endl << "7. 删除边.";
            cout << endl << "8. 插入边.";
            cout << endl << "9. 设置指定边的权.";
            cout << endl << "A. 显示节点的度";
            cout << endl << "B. 显示图的连通分量数";
            cout << endl << "C. 验证Kruska最小生成树算法";
            cout << endl << "D. 验证Prim最小生成树算法";
            cout << endl << "E. 判断无向网是否存在唯一的最小生成树";
            cout << endl << "F. Boruvka求最小生成树";
            cout << endl << "G. 超级源点问题";
            cout << endl << "H. 次小生成树";
            cout << endl << "选择功能(0~G):";
            cin >> c;
            switch (c) {
                case '1':
                    net.Clear();
                    break;
                case '2':
                    if (net.IsEmpty())
                        cout << "该有向网为空。" << endl;
                    else
                        net.Display();
                    break;
                case '3':
                    cout << endl << "输入顶点序号（有向网的顶点序号从0开始）:";
                    cin >> v;
                    net.GetElem(v, e);
                    cout << "序号为" << v << "的顶点为" << e;
                    break;
                case '4':
                    cout << endl << "输入顶点序号（有向网的顶点序号从0开始）:";
                    cin >> v;
                    cout << endl << "输入" << v << "号顶点的值:";
                    cin >> e;
                    net.SetElem(v, e);
                    break;
                case '5':
                    cout << endl << "输入被删除顶点的值:";
                    cin >> e;
                    net.DeleteVex(e);
                    break;
                case '6':
                    cout << endl << "输入插入顶点的值:";
                    cin >> e;
                    net.InsertVex(e);
                    break;
                case '7':
                    cout << endl << "输入与被删除边关联的两个顶点值:";
                    cin >> e1 >> e2;
                    v1 = net.GetOrder(e1);
                    v2 = net.GetOrder(e2);
                    net.DeleteArc(v1, v2);
                    break;
                case '8':
                    cout << endl << "输入与插入边关联的两个顶点值和边的权值:";
                    cin >> e1 >> e2 >> w;
                    v1 = net.GetOrder(e1);
                    v2 = net.GetOrder(e2);
                    net.InsertArc(v1, v2, w);
                    break;
                case '9':
                    cout << endl << "输入与插入边关联的两个顶点值和边的权值:";
                    cin >> e1 >> e2 >> w;
                    v1 = net.GetOrder(e1);
                    v2 = net.GetOrder(e2);
                    net.SetWeight(v1, v2, w);
                    break;
                case 'A':
                    cout << endl << "输入节点的下标:";
                    cin >> v;
                    cout << net.CountDegree(v) << endl;
                    break;
                case 'B':
                    cout << "图的连通分量数为:" << net.ConnectedComponent() << endl;
                    break;
                case 'C':
                    cout << "Kruskal最小生成树:" << endl;
                    net.MiniSpanTreeKruskal();
                    break;
                case 'D':
                    cout << "指定起点顶点值:";
                    cin >> e;
                    cout << "Prim最小生成树:" << endl;
                    net.MiniSpanTreePrim(net.GetOrder(e));
                    break;
                case 'E':
                    flag = net.HasUniqueMinTree();
                    if (flag)
                        cout << "存在唯一最小生成树";
                    else
                        cout << "最小生成树不唯一";
                    cout << endl;
                    break;
                case 'F':
                    net.Boruvka();
                    break;
                case 'G':
                    cout << "请按顺序输入(" << net.GetVexNum() << ")个源点值:" << endl;
                    for (int i = 1; i <= net.GetVexNum(); i++) {
                        cin >> ori[i];
                    }
                    sum = net.superorigin(ori);
                    cout << "总权值： " << sum << endl;
                    break;
                case 'H':
                    cout << endl;
                    sum = net.SecondMiniSpanTreeKruskal();
                    break;
            }

        }
    }
    catch (Error err)                    // 捕捉并处理异常
    {
        err.Show();                        // 显示异常信息
    }
    system("PAUSE");                    // 调用库函数system()
    return 0;                            // 返回值0, 返回操作系统
}

