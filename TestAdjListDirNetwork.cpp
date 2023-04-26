#include "includes/Assistance.h"                    // ���������
#include "includes/AdjListDirNetwork.h"        // �ڽӱ�������
#include <stdlib.h>

int main(void) {
    try                                    // ��try��װ���ܳ����쳣�Ĵ���
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
            cout << endl << "1. ���������.";
            cout << endl << "2. ��ʾ������.";
            cout << endl << "3. ȡָ�������ֵ.";
            cout << endl << "4. ����ָ�������ֵ.";
            cout << endl << "5. ɾ������.";
            cout << endl << "6. ���붥��.";
            cout << endl << "7. ɾ����.";
            cout << endl << "8. �����.";
            cout << endl << "9. ����ָ���ߵ�Ȩ.";
            cout << endl << "A. ��ʾ�ڵ�Ķ�";
            cout << endl << "B. ��ʾͼ����ͨ������";
            cout << endl << "C. ��֤Kruska��С�������㷨";
            cout << endl << "D. ��֤Prim��С�������㷨";
            cout << endl << "E. �ж��������Ƿ����Ψһ����С������";
            cout << endl << "F. Boruvka����С������";
            cout << endl << "G. ����Դ������";
            cout << endl << "H. ��С������";
            cout << endl << "ѡ����(0~G):";
            cin >> c;
            switch (c) {
                case '1':
                    net.Clear();
                    break;
                case '2':
                    if (net.IsEmpty())
                        cout << "��������Ϊ�ա�" << endl;
                    else
                        net.Display();
                    break;
                case '3':
                    cout << endl << "���붥����ţ��������Ķ�����Ŵ�0��ʼ��:";
                    cin >> v;
                    net.GetElem(v, e);
                    cout << "���Ϊ" << v << "�Ķ���Ϊ" << e;
                    break;
                case '4':
                    cout << endl << "���붥����ţ��������Ķ�����Ŵ�0��ʼ��:";
                    cin >> v;
                    cout << endl << "����" << v << "�Ŷ����ֵ:";
                    cin >> e;
                    net.SetElem(v, e);
                    break;
                case '5':
                    cout << endl << "���뱻ɾ�������ֵ:";
                    cin >> e;
                    net.DeleteVex(e);
                    break;
                case '6':
                    cout << endl << "������붥���ֵ:";
                    cin >> e;
                    net.InsertVex(e);
                    break;
                case '7':
                    cout << endl << "�����뱻ɾ���߹�������������ֵ:";
                    cin >> e1 >> e2;
                    v1 = net.GetOrder(e1);
                    v2 = net.GetOrder(e2);
                    net.DeleteArc(v1, v2);
                    break;
                case '8':
                    cout << endl << "���������߹�������������ֵ�ͱߵ�Ȩֵ:";
                    cin >> e1 >> e2 >> w;
                    v1 = net.GetOrder(e1);
                    v2 = net.GetOrder(e2);
                    net.InsertArc(v1, v2, w);
                    break;
                case '9':
                    cout << endl << "���������߹�������������ֵ�ͱߵ�Ȩֵ:";
                    cin >> e1 >> e2 >> w;
                    v1 = net.GetOrder(e1);
                    v2 = net.GetOrder(e2);
                    net.SetWeight(v1, v2, w);
                    break;
                case 'A':
                    cout << endl << "����ڵ���±�:";
                    cin >> v;
                    cout << net.CountDegree(v) << endl;
                    break;
                case 'B':
                    cout << "ͼ����ͨ������Ϊ:" << net.ConnectedComponent() << endl;
                    break;
                case 'C':
                    cout << "Kruskal��С������:" << endl;
                    net.MiniSpanTreeKruskal();
                    break;
                case 'D':
                    cout << "ָ����㶥��ֵ:";
                    cin >> e;
                    cout << "Prim��С������:" << endl;
                    net.MiniSpanTreePrim(net.GetOrder(e));
                    break;
                case 'E':
                    flag = net.HasUniqueMinTree();
                    if (flag)
                        cout << "����Ψһ��С������";
                    else
                        cout << "��С��������Ψһ";
                    cout << endl;
                    break;
                case 'F':
                    net.Boruvka();
                    break;
                case 'G':
                    cout << "�밴˳������(" << net.GetVexNum() << ")��Դ��ֵ:" << endl;
                    for (int i = 1; i <= net.GetVexNum(); i++) {
                        cin >> ori[i];
                    }
                    sum = net.superorigin(ori);
                    cout << "��Ȩֵ�� " << sum << endl;
                    break;
                case 'H':
                    cout << endl;
                    sum = net.SecondMiniSpanTreeKruskal();
                    break;
            }

        }
    }
    catch (Error err)                    // ��׽�������쳣
    {
        err.Show();                        // ��ʾ�쳣��Ϣ
    }
    system("PAUSE");                    // ���ÿ⺯��system()
    return 0;                            // ����ֵ0, ���ز���ϵͳ
}

