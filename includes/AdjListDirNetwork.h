#ifndef __ADJ_LIST_GRAPH_H__
#define __ADJ_LIST_GRAPH_H__

#include "AdjListDirNetworkArc.h"            // �����ڽӱ�ı߽����
#include "AdjListDirNetworkVex.h"            // �����ڽӱ�Ķ�������
#include "UFSets.h"
#include "MineHeap.h"

// ���������ڽӱ���
template<class ElemType, class WeightType>
class AdjListDirNetwork {
protected:
// �ڽӱ�����ݳ�Ա:
    int vexNum, vexMaxNum, arcNum;                  // ������Ŀ������Ķ��������Ŀ�ͱ���
    AdjListNetWorkVex<ElemType, WeightType> *vexTable;    // �����
    mutable Status *tag;                            // ��־����
    WeightType infinity;                            // ������ֵ
    void ConnectedComponent_dfs(int v);

public:
// �����������ͷ������������ر���ϵͳĬ�Ϸ�������:
    AdjListDirNetwork(ElemType es[], int vertexNum, int vertexMaxNum = DEFAULT_SIZE,
                      WeightType infinit = (WeightType) DEFAULT_INFINITY);

    AdjListDirNetwork(int vertexMaxNum = DEFAULT_SIZE,
                      WeightType infinit = (WeightType) DEFAULT_INFINITY);

    ~AdjListDirNetwork();                         // ��������

    void Clear();                                 // ���������
    bool IsEmpty();                              // �ж��������Ƿ�Ϊ��
    int GetOrder(ElemType &d) const;             // �󶥵�����
    Status GetElem(int v, ElemType &d) const;    // �󶥵��Ԫ��ֵ
    Status SetElem(int v, const ElemType &d);    // ���ö����Ԫ��ֵ
    WeightType GetInfinity() const;                 // ȡ������ֵ
    int GetVexNum() const;                         // ���������Ķ������
    int GetArcNum() const;                         // ���������ı�������
    int FirstAdjVex(int v) const;                 // ���������ж���v�ĵ�һ���ڽӵ�
    int NextAdjVex(int v1, int v2) const;         // ���������ж���v1�������v2����һ���ڽӵ�
    void InsertVex(const ElemType &d);             // ����Ԫ��ֵΪd�Ķ���
    void InsertArc(int v1, int v2, WeightType w);// ����Ӷ���Ϊv1��v2��ȨΪw�ı�
    void DeleteVex(const ElemType &d);             // ɾ��Ԫ��ֵΪd�Ķ���
    void DeleteArc(int v1, int v2);                 // ɾ���Ӷ���Ϊv1��v2�ı�
    void DeleteArc(WeightType w);

    WeightType GetWeight(int v1, int v2) const;     // ��Ӷ���Ϊv1��v2�ıߵ�Ȩֵ
    void SetWeight(int v1, int v2, WeightType w);// ���ôӶ���Ϊv1��v2�ıߵ�Ȩֵ
    Status GetTag(int v) const;                     // �󶥵�v�ı�־
    void SetTag(int v, Status tag) const;         // ���ö���v�ı�־Ϊtag
    AdjListDirNetwork(const AdjListDirNetwork<ElemType, WeightType> &copy);    // ���ƹ��캯��
    AdjListDirNetwork<ElemType, WeightType> &operator=
            (const AdjListDirNetwork<ElemType, WeightType> &copy); // ���ظ�ֵ�����
    void Display();    // ��ʾ�������ڽӱ�

    int CountDegree(int v);
    int ConnectedComponent();
    int MiniSpanTreeKruskal();
    int MiniSpanTreeKruskal(WeightType *wt, bool &no_unsigned);
    void MiniSpanTreePrim(int u0);
    void MiniSpanTreeBoruvka();
    bool HasUniqueMinTree();
    int SuperOrigin(WeightType *origin);
};

// ���������ڽӱ����ʵ�ֲ���
template<class ElemType, class WeightType>
AdjListDirNetwork<ElemType, WeightType>::AdjListDirNetwork(ElemType es[],
                                                           int vertexNum, int vertexMaxNum, WeightType infinit)
// ������������춥������Ϊes[],������ΪnumVex,�������ΪvertexNum,infinit��ʾ�����,����Ϊ0��������
{
    if (vertexMaxNum < 0)
        throw Error("����Ķ��������Ŀ����Ϊ��!");        // �׳��쳣

    if (vertexMaxNum < vertexNum)
        throw Error("������Ŀ���ܴ�������Ķ��������Ŀ!");// �׳��쳣

    vexNum = vertexNum;
    vexMaxNum = vertexMaxNum;
    arcNum = 0;
    infinity = infinit;

    tag = new Status[vexMaxNum];
    vexTable = new AdjListNetWorkVex<ElemType, WeightType>[vexMaxNum];

    for (int v = 0; v < vexNum; v++) {
        tag[v] = UNVISITED;
        vexTable[v].data = es[v];
        vexTable[v].firstarc = NULL;
    }
}

template<class ElemType, class WeightType>
AdjListDirNetwork<ElemType, WeightType>::AdjListDirNetwork(int vertexMaxNum, WeightType infinit)
// ������������춥�������ĿΪvertexMaxNum,infinit��ʾ�����Ŀ�������
{
    if (vertexMaxNum < 0)
        throw Error("����Ķ��������Ŀ����Ϊ��!");// �׳��쳣

    vexNum = 0;
    vexMaxNum = vertexMaxNum;
    arcNum = 0;
    infinity = infinit;

    tag = new Status[vexMaxNum];
    vexTable = new AdjListNetWorkVex<ElemType, WeightType>[vexMaxNum];
}

template<class ElemType, class WeightType>
AdjListDirNetwork<ElemType, WeightType>::~AdjListDirNetwork()
// ����������ͷ��ڽӱ���������ռ�ÿռ�
{
    Clear();                                // �ͷű߽��
    delete[]tag;                            // �ͷű�־
    delete[]vexTable;                        // �ͷ��ڽӱ�
}

template<class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::Clear()
// ����������ͷ����еı߽�㣬�����������Ķ������ͱ�������Ϊ0.
{
    AdjListNetworkArc<WeightType> *p;
    for (int v = 0; v < vexNum; v++) {    // �ͷű߽��
        p = vexTable[v].firstarc;
        while (p != NULL) {
            vexTable[v].firstarc = p->nextarc;
            delete p;
            p = vexTable[v].firstarc;
        }
    }
    vexNum = 0;
    arcNum = 0;
}

template<class ElemType, class WeightType>
bool AdjListDirNetwork<ElemType, WeightType>::IsEmpty()
// ������������������Ϊ�շ���true,���򷵻�false.
{
    return vexNum == 0;
}

template<class ElemType, class WeightType>
int AdjListDirNetwork<ElemType, WeightType>::GetOrder(ElemType &d) const
// ����������󶥵�d�����.�������Ŵ�0��ʼ��ͼ�в����ڶ���dʱ����-1.
{
    int v;
    for (v = 0; v < vexNum; v++)
        if (d == vexTable[v].data)
            break;

    if (v < 0 || v >= vexNum)
        return -1;    // ����d������,����-1
    else
        return v;    // ����d������,�����������
}

template<class ElemType, class WeightType>
Status AdjListDirNetwork<ElemType, WeightType>::GetElem(int v, ElemType &d) const
// ��������������Ϊv�Ķ���ֵ, v��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ����
//	ͨ��dȡ�ö���ֵ��������ENTRY_FOUND������������NOT_PRESENT
{
    if (v < 0 || v >= vexNum)
        return NOT_PRESENT;            // Ԫ�ز�����
    else {
        d = vexTable[v].data;        // ������v��Ԫ��ֵ����d
        return ENTRY_FOUND;            // Ԫ�ش���
    }
}

template<class ElemType, class WeightType>
Status AdjListDirNetwork<ElemType, WeightType>::SetElem(int v, const ElemType &d)
// ������������ö����Ԫ��ֵv��ȡֵ��ΧΪ0 �� v �� vexNum, v�Ϸ�ʱ��������
//	SUCCESS, ����������RANGE_ERROR
{
    if (v < 0 || v >= vexNum)
        return RANGE_ERROR;            // λ�ô�
    else {
        vexTable[v].data = d;        // ����Ԫ��
        return SUCCESS;                // �ɹ�
    }
}

template<class ElemType, class WeightType>
WeightType AdjListDirNetwork<ElemType, WeightType>::GetInfinity() const
// �������������������ֵ
{
    return infinity;
}

template<class ElemType, class WeightType>
int AdjListDirNetwork<ElemType, WeightType>::GetVexNum() const
// ������������ض������
{
    return vexNum;
}

template<class ElemType, class WeightType>
int AdjListDirNetwork<ElemType, WeightType>::GetArcNum() const
// ������������ر�������
{
    return arcNum;
}

template<class ElemType, class WeightType>
int AdjListDirNetwork<ElemType, WeightType>::FirstAdjVex(int v) const
// ������������ض���v�ĵ�һ���ڽӵ�
{
    if (v < 0 || v >= vexNum)
        throw Error("v���Ϸ�!");// �׳��쳣

    if (vexTable[v].firstarc == NULL)
        return -1;              // �������ڽӵ�
    else
        return vexTable[v].firstarc->adjVex;
}

template<class ElemType, class WeightType>
int AdjListDirNetwork<ElemType, WeightType>::NextAdjVex(int v1, int v2) const
// ������������ض���v1�������v2����һ���ڽӵ�
{
    AdjListNetworkArc<WeightType> *p;
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1���Ϸ�!");    // �׳��쳣
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2���Ϸ�!");    // �׳��쳣
    if (v1 == v2)
        throw Error("v1���ܵ���v2!");// �׳��쳣

    p = vexTable[v1].firstarc;
    while (p != NULL && p->adjVex != v2)
        p = p->nextarc;

    if (p == NULL || p->nextarc == NULL)
        return -1;                   // ��������һ���ڽӵ�
    else
        return p->nextarc->adjVex;
}

template<class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::InsertVex(const ElemType &d)
// ����������ڶ����ı�β����Ԫ��ֵΪd�Ķ��㡣
{
    if (vexNum == vexMaxNum)
        throw Error("ͼ�Ķ��������ܳ�������������!");    // �׳��쳣
    for (int i = 0; i < vexNum; i++)
        if (d == vexTable[i].data)
            throw Error("Ҫ����Ķ����Ѵ��ڣ�");
    vexTable[vexNum].data = d;
    vexTable[vexNum].firstarc = NULL;
    tag[vexNum] = UNVISITED;
    vexNum++;
}

template<class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::InsertArc(int v1, int v2, WeightType w)
// ������������붥��Ϊv1��v2,ȨΪw�ı�
{
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1���Ϸ�!");    // �׳��쳣
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2���Ϸ�!");    // �׳��쳣
    if (v1 == v2)
        throw Error("v1���ܵ���v2!");// �׳��쳣
    if (w == infinity)
        throw Error("w����Ϊ�޿մ�!");// �׳��쳣

    AdjListNetworkArc<WeightType> *p, *q;
    p = vexTable[v1].firstarc;
    vexTable[v1].firstarc = new AdjListNetworkArc<WeightType>(v2, w, p);
    q = vexTable[v2].firstarc;
    vexTable[v2].firstarc = new AdjListNetworkArc<WeightType>(v1, w, q);
    arcNum++;
}

template<class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::DeleteVex(const ElemType &d)
// ���������ɾ��Ԫ��ֵΪd�Ķ���
{
    int v;
    AdjListNetworkArc<WeightType> *p, *q;
    for (v = 0; v < vexNum; v++)
        if (vexTable[v].data == d)
            break;
    if (v == vexNum)
        throw Error("ͼ�в�����Ҫɾ���Ķ���!");    // �׳��쳣

    for (int u = 0; u < vexNum; u++)           // ɾ��d��v�Ļ�
        if (u != v)
            DeleteArc(u, v);
    vexNum--;
    vexTable[v].data = vexTable[vexNum].data;
    vexTable[v].firstarc = vexTable[vexNum].firstarc;
    vexTable[vexNum].firstarc = NULL;
    tag[v] = tag[vexNum];
    for (int u = 0; u < vexNum; u++)        // �����ڽӱ�ͷ ����нڵ�������vexNum���ڵ� ����Ǩ����v��
        if (u != v) {
            p = vexTable[u].firstarc;
            while (p != NULL) {
                if (p->adjVex == vexNum)
                    p->adjVex = v;
                p = p->nextarc;
            }
        }
}

template<class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::DeleteArc(int v1, int v2)
// ���������ɾ������Ϊv1��v2�ı�
{
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1���Ϸ�!");    // �׳��쳣
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2���Ϸ�!");    // �׳��쳣
    if (v1 == v2)
        throw Error("v1���ܵ���v2!");        // �׳��쳣

    AdjListNetworkArc<WeightType> *p, *q;
    p = vexTable[v1].firstarc;
    while (p != NULL && p->adjVex != v2) {
        q = p;
        p = p->nextarc;
    }
    if (p != NULL) {  // p == NULL ��ʾ�����ڵ�v2�ı�
        if (vexTable[v1].firstarc == p)
            vexTable[v1].firstarc = p->nextarc;
        else
            q->nextarc = p->nextarc;
        delete p;
    } else return;

    p = vexTable[v2].firstarc;
    while (p != NULL && p->adjVex != v1) {
        q = p;
        p = p->nextarc;
    }
    if (vexTable[v2].firstarc == p)
        vexTable[v2].firstarc = p->nextarc;
    else
        q->nextarc = p->nextarc;
    delete p;
    arcNum--;
}

template<class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::DeleteArc(WeightType w) {
    AdjListNetworkArc<WeightType> *p, *q, *temp;
    for (int i = 0; i < vexNum; i++) {
        q = p = vexTable[i].firstarc;
        while (p != NULL) {
            if (p->weight == w) {
                if (p == vexTable[i].firstarc) {
                    vexTable[i].firstarc = vexTable[i].firstarc->nextarc;
                    delete p;
                    q = p = vexTable[i].firstarc;
                } else {
                    q->nextarc = p->nextarc;
                    temp = p;
                    p = p->nextarc;
                    delete temp;
                }
            } else {
                q = p;
                p = p->nextarc;
            }
        }
    }
}

template<class ElemType, class WeightType>
WeightType AdjListDirNetwork<ElemType, WeightType>::GetWeight(int v1, int v2) const
// ������������ض���Ϊv1��v2�ıߵ�Ȩֵ
{
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1���Ϸ�!");    // �׳��쳣
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2���Ϸ�!");    // �׳��쳣
    if (v1 == v2) return 0;
    AdjListNetworkArc<WeightType> *p;
    p = vexTable[v1].firstarc;
    while (p != NULL && p->adjVex != v2)
        p = p->nextarc;
    if (p != NULL)
        return p->weight;            // ����Ȩֵ
    else
        return infinity;                // ����ȨֵΪinfinity����ʾ�߲�����
}

template<class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::SetWeight(int v1, int v2, WeightType w)
// ������������ö���Ϊv1��v2�ıߵ�Ȩֵ
{
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1���Ϸ�!");        // �׳��쳣
    if (v2 < 0 || v2 >= vexNum)
        throw Error("v2���Ϸ�!");        // �׳��쳣
    if (v1 == v2)
        throw Error("v1���ܵ���v2!");    // �׳��쳣
    if (w == infinity)
        throw Error("w����Ϊ�޿մ�!");   // �׳��쳣
    AdjListNetworkArc<WeightType> *p;
    p = vexTable[v1].firstarc;
    while (p != NULL && p->adjVex != v2)
        p = p->nextarc;
    if (p != NULL)                        // p == NULL ˵���߲�����
        p->weight = w;                    // �޸�Ȩֵ
    p = vexTable[v2].firstarc;
    while (p != NULL && p->adjVex != v1)
        p = p->nextarc;
    if (p != NULL)
        p->weight = w;
    return;
}

template<class ElemType, class WeightType>
Status AdjListDirNetwork<ElemType, WeightType>::GetTag(int v) const
// ������������ض���v�ı�־
{
    if (v < 0 || v >= vexNum)
        throw Error("v���Ϸ�!");        // �׳��쳣
    return tag[v];
}

template<class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::SetTag(int v, Status val) const
// ������������ö���v�ı�־Ϊval
{
    if (v < 0 || v >= vexNum)
        throw Error("v���Ϸ�!");        // �׳��쳣
    tag[v] = val;
}

template<class ElemType, class WeightType>
AdjListDirNetwork<ElemType, WeightType>::AdjListDirNetwork(const AdjListDirNetwork<ElemType, WeightType> &copy)
// ��������������������ڽӾ���copy���������������ڽӾ���copy�������ƹ��캯��
{
    AdjListNetworkArc<WeightType> *p, *q;
    infinity = copy.infinity;
    vexNum = copy.vexNum;
    vexMaxNum = copy.vexMaxNum;
    arcNum = copy.arcNum;
    tag = new Status[vexMaxNum];
    vexTable = new AdjListNetWorkVex<ElemType, WeightType>[vexMaxNum];
    for (int v = 0; v < vexNum; v++) {
        tag[v] = copy.tag[v];
        vexTable[v].data = copy.vexTable[v].data;
        vexTable[v].firstarc = NULL;
        p = copy.vexTable[v].firstarc;
        while (p != NULL)
            if (vexTable[v].firstarc == NULL) {
                vexTable[v].firstarc = new AdjListNetworkArc<WeightType>(p->adjVex, p->weight);
                q = vexTable[v].firstarc;
                p = p->nextarc;
            } else {
                q->nextarc = new AdjListNetworkArc<WeightType>(p->adjVex, p->weight);
                q = q->nextarc;
                p = p->nextarc;
            }
    }
}

template<class ElemType, class WeightType>
AdjListDirNetwork<ElemType, WeightType> &
AdjListDirNetwork<ElemType, WeightType>::operator=(const AdjListDirNetwork<ElemType, WeightType> &copy)
// ��������������������ڽӾ���copy��ֵ����ǰ���������ڽӾ��󡪡���ֵ�������
{
    if (&copy != this) {
        Clear();                                    // �ͷŵ�ǰ�������߽��
        delete[]tag;                                // �ͷŵ�ǰ��������־����
        delete[]vexTable;                            // �ͷŵ�ǰ�����������
        AdjListNetworkArc<WeightType> *p, *q;
        infinity = copy.infinity;
        vexNum = copy.vexNum;
        vexMaxNum = copy.vexMaxNum;
        arcNum = copy.arcNum;
        tag = new Status[vexMaxNum];
        vexTable = new AdjListNetWorkVex<ElemType, WeightType>[vexMaxNum];
        for (int v = 0; v < vexNum; v++) {
            tag[v] = copy.tag[v];
            vexTable[v].data = copy.vexTable[v].data;
            vexTable[v].firstarc = NULL;
            p = copy.vexTable[v].firstarc;
            while (p != NULL)
                if (vexTable[v].firstarc == NULL) {
                    vexTable[v].firstarc = new AdjListNetworkArc<WeightType>(p->adjVex, p->weight);
                    q = vexTable[v].firstarc;
                    p = p->nextarc;
                } else {
                    q->nextarc = new AdjListNetworkArc<WeightType>(p->adjVex, p->weight);
                    q = q->nextarc;
                    p = p->nextarc;
                }
        }
    }
    return *this;
}

template<class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::Display()
// �������: ��ʾ�ڽӾ���������
{
    AdjListNetworkArc<WeightType> *p;
    cout << "����������" << vexNum << "�����㣬" << arcNum << "���ߡ�" << endl;
    for (int v = 0; v < vexNum; v++) {    // ��ʾ��v���ڽ�����
        cout << v << ":\t" << vexTable[v].data;                // ��ʾ�����
        p = vexTable[v].firstarc;
        while (p != NULL) {
            cout << "-->(" << p->adjVex << "," << p->weight << ")";
            p = p->nextarc;
        }
        cout << endl;
    }
}

template<class ElemType, class WeightType>
int AdjListDirNetwork<ElemType, WeightType>::CountDegree(int v1) {
    if (v1 < 0 || v1 >= vexNum)
        throw Error("v1���Ϸ�!");
    int cnt = 0;
    AdjListNetworkArc<WeightType> *p = vexTable[v1].firstarc;
    while (p != NULL) {
        p = p->nextarc;
        cnt++;
    }
    return cnt;
}

template<class ElemType, class WeightType>
int AdjListDirNetwork<ElemType, WeightType>::ConnectedComponent() {
    Status *temp = new Status[vexNum];
    memcpy(temp, tag, sizeof tag);
    int cnt = 0;
    for (int i = 0; i < vexNum; i++)
        tag[i] = UNVISITED;
    for (int i = 0; i < vexNum; i++) {
        if (tag[i] == UNVISITED) {
            cnt++;
            ConnectedComponent_dfs(i);
        }
    }
    memcpy(tag, temp, sizeof temp);
    delete[]temp;
    return cnt;
}

template<class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::ConnectedComponent_dfs(int v) {
    tag[v] = VISITED;
    AdjListNetworkArc<WeightType> *p = vexTable[v].firstarc;
    while (p != NULL) {
        if (tag[p->adjVex] == UNVISITED)
            ConnectedComponent_dfs(p->adjVex);
        p = p->nextarc;
    }
}

template<class ElemType, class WeightType>
struct KEdge {
    ElemType v1, v2;
    WeightType w;

    KEdge() {
        v1 = v2 = -1;
        w = 0;
    }

    KEdge(int v11, int v22, ElemType w1) {
        v1 = v11;
        v2 = v22;
        w = w1;
    }

    bool operator<=(const KEdge<ElemType, WeightType> &Ed) {
        return w <= Ed.w;
    }

    bool operator>(const KEdge<ElemType, WeightType> &Ed) {
        return w > Ed.w;
    }

    struct KEdge<ElemType, WeightType> &operator=(KEdge<ElemType, WeightType> &Ed) {
        if (&Ed != this) {
            v1 = Ed.v1;
            v2 = Ed.v2;
            w = Ed.w;
        }
        return *this;
    }
};

template<class ElemType, class WeightType>
int AdjListDirNetwork<ElemType, WeightType>::MiniSpanTreeKruskal() {
    if (ConnectedComponent() > 1)
        throw Error("��ͼ����ͨ���磬�޷�����С������!");
    ElemType *kvex = new ElemType[vexNum];
    for (int i = 0; i < vexNum; i++)
        kvex[i] = vexTable[i].data;
    UFSets<ElemType> u(kvex, vexNum);
    MinHeap<KEdge<ElemType, WeightType>> ha(GetArcNum());
    for (int i = 0; i < vexNum; i++) {
        for (AdjListNetworkArc<WeightType> *p = vexTable[i].firstarc; p != NULL; p = p->nextarc) {
            if (i < p->adjVex) {
                KEdge<ElemType, WeightType> k(vexTable[i].data, vexTable[p->adjVex].data, p->weight);
                ha.Insert(k);
            }
        }
    }
    delete[]kvex;
    int cnt = 0, totalw = 0;
    while (cnt < vexNum - 1) {
        KEdge<ElemType, WeightType> k;
        ha.DeleteTop(k);
        ElemType e1 = k.v1, e2 = k.v2;
        WeightType w = k.w;
        if (u.Differ(e1, e2)) {
            u.Union(e1, e2);
            cout << '(' << e1 << ',' << e2 << ')' << '\t' << w << endl;
            totalw += GetWeight(GetOrder(e1), GetOrder(e2));
            cnt++;
        }
    }
    return totalw;
}

template<class ElemType, class WeightType>
int AdjListDirNetwork<ElemType, WeightType>::SuperOrigin(WeightType *origin) {
    const int NN = 510;
    WeightType w[NN][NN];
    WeightType dist[NN];
    bool st[NN];
    int pre[NN];
    memset(dist, infinity, sizeof dist);
    for (int i = 0; i < NN; i++)
        memset(w[i], infinity, sizeof w[i]);
    for (int i = 1; i <= vexNum; i++) {
        w[0][i] = origin[i];
        w[i][0] = w[0][i];
    }
    int start = 1;
    for (int i = 1; i <= vexNum; i++) {
        for (AdjListNetworkArc<WeightType> *mm = vexTable[i - 1].firstarc; mm != NULL; mm = mm->nextarc) {
            w[i][mm->adjVex + 1] = mm->weight;
        }
    }
    dist[0] = 0;
    int res = 0;
    for (int i = 0; i < vexNum + 1; i++) {
        int t = -1;
        for (int j = 0; j <= vexNum; j++)
            if (!st[j] && (t == -1 || dist[t] > dist[j]))
                t = j;
        st[t] = true;
        res += dist[t];
        if (pre[t] == 0 && t != 0) {
            cout << endl;
            cout << '(' << vexTable[t - 1].data << ')' << '\t' << dist[t] << endl;
        } else if (pre[t] != 0 && t != 0) {
            ElemType sta;
            GetElem(pre[t] - 1, sta);
            ElemType end;
            GetElem(t - 1, end);
            cout << '(' << sta << ',' << end << ')' << '\t' << dist[t] << endl;
        }
        for (int j = 0; j <= vexNum; j++) {
            if (dist[j] > w[t][j]) {
                dist[j] = w[t][j];
                pre[j] = t;
            }
        }
    }
    return res;
}

template<class ElemType, class WeightType>
int AdjListDirNetwork<ElemType, WeightType>::MiniSpanTreeKruskal(WeightType *wt, bool &no_unsigned) {
    if (ConnectedComponent() > 1)
        throw Error("��ͼ����ͨ���磬�޷�����С������!");
    ElemType *kvex = new ElemType[vexNum];
    for (int i = 0; i < vexNum; i++)
        kvex[i] = vexTable[i].data;
    UFSets<ElemType> u(kvex, vexNum);
    MinHeap<KEdge<ElemType, WeightType>> ha(GetArcNum());
    for (int i = 0; i < vexNum; i++) {
        for (AdjListNetworkArc<WeightType> *p = vexTable[i].firstarc; p != NULL; p = p->nextarc) {
            if (i < p->adjVex) {
                KEdge<ElemType, WeightType> k(vexTable[i].data, vexTable[p->adjVex].data, p->weight);
                ha.Insert(k);
            }
        }
    }
    delete[]kvex;
    int cnt = 0, totalw = 0;
    while (cnt < vexNum - 1) {
        KEdge<ElemType, WeightType> k;
        ha.DeleteTop(k);
        ElemType e1 = k.v1, e2 = k.v2;
        if (u.Differ(e1, e2)) {
            u.Union(e1, e2);
            int v1 = GetOrder(e1), v2 = GetOrder(e2);
            if (wt[GetWeight(v1, v2)] >= 2)
                no_unsigned = false;
            //cout << '(' << e1 << ',' << e2 << ')' << '\t' << GetWeight(v1, v2) << endl;
            totalw += GetWeight(GetOrder(e1), GetOrder(e2));
            cnt++;
        }
    }
    return totalw;
}

template<class ElemType, class WeightType>
struct CloseArc {
    WeightType w;
    int nearvex;
};

template<class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::MiniSpanTreePrim(int u0) {
    if (u0 < 0 || u0 >= vexNum)
        throw Error("����u0�����ڣ�");
    if (ConnectedComponent() > 1)
        throw Error("��ͼ����ͨ���磬�޷�����С������!");
    CloseArc<ElemType, WeightType> *closearcs = new CloseArc<ElemType, WeightType>[vexNum];
    for (int i = 0; i < vexNum; i++) {
        closearcs[i].w = GetWeight(u0, i);
        closearcs[i].nearvex = u0;
    }
    closearcs[u0].w = 0;
    closearcs[u0].nearvex = -1;
    int num_added_arc = 0;
    while (num_added_arc <= vexNum - 2) {
        WeightType minw = GetInfinity();
        int toadd = u0;
        for (int i = 0; i < vexNum; i++) {
            if (closearcs[i].w != 0 && closearcs[i].w < minw) {
                minw = closearcs[i].w;
                toadd = i;
            }
        }
        if (toadd != u0) {
            closearcs[toadd].w = 0;
            ElemType e1, e2;
            GetElem(toadd, e1);
            GetElem(closearcs[toadd].nearvex, e2);
            cout << '(' << e2 << ',' << e1 << ')' << '\t' << GetWeight(toadd, closearcs[toadd].nearvex) << endl;
            num_added_arc++;
            if (num_added_arc >= vexNum - 1)
                break;
            for (int i = FirstAdjVex(toadd); i != -1; i = NextAdjVex(toadd, i)) {
                if (closearcs[i].w != 0 && GetWeight(toadd, i) < closearcs[i].w) {
                    closearcs[i].w = GetWeight(toadd, i);
                    closearcs[i].nearvex = toadd;
                }
            }
        }
    }
    delete[]closearcs;
}

template<class ElemType, class WeightType>
bool AdjListDirNetwork<ElemType, WeightType>::HasUniqueMinTree() {  //�ο�����https://www.cnblogs.com/wkfvawl/p/9845689.html
    int *WeightNum = new int[infinity + 1]();
    for (int u = 0; u < vexNum - 1; u++) {
        for (int v = u + 1; v < vexNum; v++) {
            int w = GetWeight(u, v);
            WeightNum[w]++;
        }
    }
    bool no_unsigned = true;
    int w1 = MiniSpanTreeKruskal(WeightNum, no_unsigned), w2;
    if (no_unsigned == true) {
        return true;
    } else {
        AdjListDirNetwork<ElemType, WeightType> copy(*this);
        for (int i = 1; i <= infinity; i++) {
            if (WeightNum[i] >= 2) {
                DeleteArc(WeightNum[i]);
                WeightNum[i]--;
            }
        }
        w2 = MiniSpanTreeKruskal();
        *this = copy;
    }
    return w1 != w2;
}

template<class ElemType, class WeightType>
void AdjListDirNetwork<ElemType, WeightType>::MiniSpanTreeBoruvka() {
    if (ConnectedComponent() > 1)
        throw Error("��ͼ����ͨ���磬�޷�����С������!");
    ElemType *kvex = new ElemType[vexNum];
    for (int i = 0; i < vexNum; i++)
        kvex[i] = vexTable[i].data;
    UFSets<ElemType> u(kvex, vexNum);
    int treearc = 0;
    int *mn = new int[vexNum]; //mn[i]��ʾ���±�iԪ��Ϊ������������СȨ��ߵ��յ�
    int *ms = new int[vexNum]; //ms[i]��ʾ���±�iԪ��Ϊ������������СȨ��ߵ����
    int *minw = new int[vexNum];//minw[i]��ʾ���±�iΪ����������СȨ��ߵ�Ȩ
    bool *isroot = new bool[vexNum];
    for (int i = 0; i < vexNum; i++) {
        isroot[i] = 1;
        mn[i] = infinity;
        ms[i] = infinity;
        minw[i] = infinity;
    }
    while (treearc < vexNum - 1) {
        for (int i = 0; i < u.Getsize(); i++) {
            int fa = u.Find(u.GetElem(i));
            int archead = -1;
            for (int j = FirstAdjVex(i); j != -1; j = NextAdjVex(i, j)) {
                if (u.Differ(u.GetElem(i), u.GetElem(j)) && GetWeight(i, j) < minw[fa]) {
                    minw[fa] = GetWeight(i, j);
                    archead = j;
                }
            }
            if (archead < mn[fa]) {
                ms[fa] = i;
                mn[fa] = archead;
            }
        }
        for (int i = 0; i < vexNum; i++) {
            ElemType e1, e2;
            GetElem(i, e1);
            GetElem(mn[i], e2);
            if (mn[i] != infinity && u.Differ(e1, e2)) {
                u.Union(u.GetElem(i), u.GetElem(mn[i]));
                cout << '(' << u.GetElem(i) << ',' << u.GetElem(mn[i]) << ")\t" << minw[i] << endl;
                isroot[u.Find(u.GetElem(mn[i]))] = false;
                treearc++;
                if (treearc == vexNum - 1)
                    break;
            }
        }
    }
    delete[]mn;
    delete[]ms;
    delete[]minw;
}

#endif