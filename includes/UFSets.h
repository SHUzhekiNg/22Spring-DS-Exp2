#ifndef __ELEM_NODE_H__
#define __ELEM_NODE_H__

#include "Assistance.h"

// ���鼯Ԫ�ؽ����
template<class ElemType>
struct ElemNode {
// ���ݳ�Ա:
    ElemType data;                // ������
    int parent;                    // ˫����
};

// ���鼯
template<class ElemType>
class UFSets {
protected:
// ���鼯�����ݳ�Ա:
    ElemNode<ElemType> *sets;             // �洢����˫��
    int size;                             // ������
// ��������
    int CollapsingFind(ElemType e) const;// ����Ԫ��e���ڵȼ���ĸ�
public:
// ���鼯�ĺ�����Ա:
    UFSets() {
        size = 0;
        sets = NULL;
    };

    UFSets(ElemType es[], int n);         // ����sz���������(�ȼ���)
    virtual ~UFSets();                     // ��������
    ElemType GetElem(int p) const;        // ȡָ��Ԫ���������е��±�
    int GetOrder(ElemType e) const;       // ����ָ���±�ȡԪ��ֵ
    int Getsize() const;

    int Find(ElemType e) const;             // ����Ԫ��e���ڵȼ���ĸ�
    void Union(ElemType a, ElemType b);     // �ϲ�a��b���ڵĵȼ���
    void WeightedUnion(ElemType a, ElemType b);     // ���ݽ����ٺϲ�a��b���ڵĵȼ���
    bool Differ(ElemType a, ElemType b); // �ж�Ԫ��a��b�Ƿ���ͬһ���ȼ���
    UFSets(UFSets &copy);             // ���ƹ��캯��
    UFSets &operator=(const UFSets &copy);    // ��ֵ�����
};


// ���鼯��ʵ�ֲ���
template<class ElemType>
UFSets<ElemType>::UFSets(ElemType es[], int n)
// �����������������es�е�Ԫ�أ�����n����Ԫ�صȼ���
{
    size = n;                                    // ��������
    sets = new ElemNode<ElemType>[size];        // ����ռ�
    for (int i = 0; i < size; i++) {
        sets[i].data = es[i];
        sets[i].parent = -1;
    }
}

template<class ElemType>
int UFSets<ElemType>::Find(ElemType e) const
// �������������Ԫ��e�������ĸ�
{
    int p = 0;
    while (p < size && sets[p].data != e)
        p++;
    if (p == size)
        throw Error("FindԪ�ز�����!");                // �׳��쳣
    while (sets[p].parent > -1)
        p = sets[p].parent;                     // ���Ҹ�
    return p;
}

template<class ElemType>
int UFSets<ElemType>::CollapsingFind(ElemType e) const
// �����������ѹ��·�����ܣ�����Ԫ��e�������ĸ�
{
    int i, k, p = 0;
    while (p < size && sets[p].data != e)
        p++;
    if (p == size)
        throw Error("Ԫ�ز�����!");                // �׳��쳣
    for (i = p; sets[i].parent >= 0; i = sets[i].parent); //����p�ĸ��������i
    while (i != sets[p].parent) {  //��p��ʼ�������ѹ��
        k = sets[p].parent;
        sets[p].parent = i;
        p = k;
    }
    return i;
}


template<class ElemType>
UFSets<ElemType>::~UFSets()
// ����������ͷŶ���ռ�õĿռ䡪����������
{
    delete[]sets;                            // �ͷ�����parent
}

template<class ElemType>
int UFSets<ElemType>::Getsize() const {
    return size;
}

template<class ElemType>
ElemType UFSets<ElemType>::GetElem(int p) const
// ������������±�Ϊp��Ԫ��ֵ 
{
    if (p < 0 || p >= size)
        throw Error("GetElemԪ�ز�����!");            // �׳��쳣
    return sets[p].data;                    // ����Ԫ��ֵ
}

template<class ElemType>
int UFSets<ElemType>::GetOrder(ElemType e) const
// ���������ȡָ��Ԫ��e���±� 
{
    int p = 0;
    while (p < size && sets[p].data != e)
        p++;
    if (p == size)
        throw Error("Ԫ�ز�����!");            // �׳��쳣
    return p;                                // ��Ԫ���±�
}

template<class ElemType>
void UFSets<ElemType>::Union(ElemType a, ElemType b)
// ����������ϲ�a��b���ڵĵȼ���
{
    int r1 = Find(a);                    // ����a���ڵȼ���ĸ�
    int r2 = Find(b);                    // ����b���ڵȼ���ĸ�
    if (r1 != r2) {
        sets[r1].parent += sets[r2].parent;
        sets[r2].parent = r1;            // �ϲ��ȼ���
    }
}

template<class ElemType>
void UFSets<ElemType>::WeightedUnion(ElemType a, ElemType b)
// ������������ݽ����ٺϲ�a��b���ڵĵȼ���
{
    int r1 = Find(a);                    // ����a���ڵȼ���ĸ�
    int r2 = Find(b);                    // ����b���ڵȼ���ĸ�
    if (r1 != r2) {
        int temp = sets[r1].parent + sets[r2].parent;
        if (sets[r1].parent <= sets[r2].parent) {
            sets[r2].parent = r1;
            sets[r1].parent = temp;
        } else {
            sets[r1].parent = r2;       //r1�еĽ������٣�r1ָ��r2
            sets[r2].parent = temp;
        }
    }
}

template<class ElemType>
bool UFSets<ElemType>::Differ(ElemType a, ElemType b)
// ������������a��b����ͬһ�ȼ����ϣ�����true�����򷵻�false
{
    int root1 = Find(a);                    // ����a���ڵȼ���ĸ�
    int root2 = Find(b);                    // ����b���ڵȼ���ĸ�
    return root1 != root2;
}

template<class ElemType>
UFSets<ElemType>::UFSets(UFSets &copy)
// �����������copy�����¶��󡪡����ƹ��캯��
{
    size = copy.Getsize();                        // ��������
    sets = new ElemNode<ElemType>[size];    // ����ռ�
    for (int i = 0; i < size; i++)
        sets[i] = copy.sets[i];             // ����ÿ��Ԫ��
}

template<class ElemType>
UFSets<ElemType> &UFSets<ElemType>::operator=(const UFSets<ElemType> &copy)
// �����������copy��ֵ����ǰ���󡪡���ֵ�����
{
    if (&copy != this) {
        size = copy.size;                    // ��������
        if (sets != NULL)
            delete[]sets;                        // �ͷ�ԭ�ռ�
        sets = new ElemNode<ElemType>[size];// �����¿ռ�
        for (int i = 0; i < size; i++)
            sets[i] = copy.sets[i];            // ����ÿ��Ԫ��
    }
    return *this;
}

#endif
