//���Ա�����ʽ��ʾ
// ѭ������
// ��ͷ��㿪ʼ��ָ��������ָ����һ�����ݵĴ洢��ַ��β�ڵ��ָ����ָ��ͷ���洢��ַ ���ɻ� 
/*
���Ա���˳��洢�ṹ���߼�λ�ú�����λ�ö����ڣ�
����ʽ�洢�ṹ���߼�λ�����ڣ�������λ�ò�һ�����ڣ�
���˳��洢�ṹ�������������ȡ��
���ڲ����ɾ������ʱ����Ҫ�ƶ�Ԫ�أ�
�����������Ӻ�ɾ��Ԫ�ص�Ч�ʡ�

˳��洢�ṹ��ȡԪ�ص�Ч�ʱȽϸߣ���ʽ�洢�ṹ���Ӻ�ɾ��Ԫ�ص�Ч�ʱȽϸߡ�
�ο� https://www.cnblogs.com/rookiefly/p/3451310.html

�������� 
*/ 
#include <stdio.h>  //��׼�� ������� 
#include <stdlib.h> //��׼��  

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2

//  �ȼ� �������� ���� 
typedef int Status;  //״̬ 
typedef int ElemType;//�� Ԫ������ 

/*
 * �洢�ṹ
 */
typedef struct LNode
{
    ElemType data;//Ԫ��  
    
    struct LNode *next;//���ָ�� 
}LNode, *LinkList;//���� �ṹ�����  �ṹ��ָ�� 

/*
 * ��ʼ�����Ա�
 */
void InitList(LinkList *L)
{
    *L = (LinkList) malloc(sizeof(LNode));// ����ͷ���  һ��Ԫ�� + һ��ָ�����  ���ڴ��С 
    if (*L == NULL) //����ʧ��
    {
        exit(OVERFLOW);
    }
    (*L)->next = *L;  //ָ����ָ��������
}

/*
 * �������Ա�
 */
void DestroyList(LinkList *L)
{
    LinkList temp,p;
    *L = (*L)->next;  //����βָ��ָ��ͷ��㣬��Ȼ�ͷ����һ�����ʱβָ�룬�޷�ָ��ͷ��� 
    p = (*L)->next;  //pָ���һ�����
    while (p!=*L)   //pδ����ͷʱ ��β��ָ���ͷ 
    {
        temp = p->next;//�����̵Ľڵ� 
        free(p);//ɾ����ǰ�ڵ��ڴ� 
        p = temp;//��һ���ڵ� 
    }
    (*L)->next = *L; //ͷ���ָ����ָ���䱾��
    
}

/*
 * ������Ա�
 */
void ClearList(LinkList L)
{
    DestroyList(&L);//����ڴ� 
    free(L); //�ͷ�ͷ���
    L->next = NULL;//���ָ��ΪNULL 
}

/*
 * �ж��Ƿ�Ϊ��
 */
Status isEmpty(LinkList L)
{
    if (L->next==L)//ָ����ָ�����������϶����ǿ��ˣ��ý�㼴Ϊͷ���
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

/*
 * ��ȡ����
 */
int GetLength(LinkList L)
{
    int i = 0;
    LinkList p = L->next->next;  //pָ���һ�����
    while (p!= L->next)//pδ����ͷʱ
    {
        ++i;//��̽ڵ� ���� 
        p = p->next;//���α�����̽ڵ� 
    }
    return i;
}

/*
 * ����λ�û�ȡԪ��
 */
Status GetElem(LinkList L, int i, ElemType *e)
{
    int j = 0;
    LinkList p = L->next;//ͷ��� 
   if (i<1 || i>GetLength(L))//Խ�� 
    {
        return ERROR;
    }
    
    while (j < i)
    {
        ++j;//λ�ü��� 
        p = p->next;//��һ���󼶽ڵ� 
    }

    *e = p->data;
    return OK;
}

/*
 * �Ƚ�����Ԫ���Ƿ����
 */
Status compare(ElemType e1, ElemType e2)
{
    if (e1 == e2)
    {
        return 0;
    }
    else if (e1 < e2)
    {
        return -1;//ǰ���С�ں���� 
    }
    else
    {
        return 1;//ǰ��Ĵ��ں���� 
    }
}

/*
 * ����ָ��Ԫ�ص�λ��
 */
int FindElem(LinkList L, ElemType e, Status (*compare)(ElemType, ElemType))
{
    int i = 0;
    LinkList p = L->next->next;//pָ��������һ��Ԫ��
    while(p != L->next) //pδ����ͷʱ
    {
        ++i;//λ�ü��� +1 
        if (!compare(p->data, e))//�Ƚϵ�ǰ�ڵ�Ԫ��ֵ�� Ŀ��Ԫ��ֵ 
        {
            return i;//��ȷ��� λ�ü���ֵ 
        }
        p = p->next;//ָ����  
    }
    return 0;
}

/*
 * ��ȡǰ��Ԫ��
 */
Status PreElem(LinkList L, ElemType cur_e, ElemType *pre_e)
{
    LinkList q, p = L->next->next;//pָ��������һ��Ԫ��
    while (p != L->next) //pδ����ͷʱ
    {
        q = p->next;//p�ڵ�ĺ��Ϊq 
        if ( q!=L->next && q->data == cur_e)//q�ڵ��Ԫ����Ŀ�� Ԫ�������qδ��β 
        {
            *pre_e = p->data;//q��ǰ�� p��Ԫ��Ϊ Ŀ��Ԫ�ص�ǰ�� 
            return OK;
        }
        p = q;//pָ����һ����� 
    }
    return ERROR;
}

/*
 * ��ȡ���Ԫ��
 */
Status NextElem(LinkList L, ElemType cur_e, ElemType *next_e)
{
    LinkList p = L->next->next;//pָ��������һ��Ԫ��
    LinkList q; 
    while (p != L->next) //pδ����ͷʱ
    {   
        q=p->next;//qָ��p�ĺ�� 
        if (q!=L->next && p->data == cur_e)//�ڵ�Ԫ����Ŀ��Ԫ�����  ������Ϊָ��ͷ 
        {
            *next_e = q->data;//��ǰ�ڵ�ĺ�̽ڵ��Ԫ��Ϊ Ŀ��Ԫ�صĺ��Ԫ�� 
            return OK;
        }
        p = q;//ָ����һ����� 
    }
    return ERROR;
}

/*
 * ����Ԫ��
 */
Status InsertElem(LinkList L, int i, ElemType e)
{
    int j = 0;
    LinkList s, p = L->next;//pָ���ͷ	
    if (i<1 || i>GetLength(L)+1)//λ��Խ�� 
    {
        return ERROR;
    }       
    while ( j < i - 1)//λ�ú������ҵ���i-1�����
    {
        ++j;//λ�ü��� +1 
        p = p->next;//ָ���� ���� 
    }

    s = (LinkList) malloc(sizeof(LNode));//�¿���һ���ڴ�ռ� 
    s->data = e;//Ԫ��ֵ 
    s->next = p->next;//���ָ��p�ĺ�� 
    p->next = s;//p�ĺ��ָ���µ�Ԫ�ؽڵ� 
    
    if (p == L)//p ��β ָ����ڱ�β���� 
      L  = s;

    return OK;
}

/*
 * ɾ��Ԫ�ز�����ֵ
 */
Status DeleteElem(LinkList L, int i, ElemType *e)
{
    int j = 0;
    LinkList q, p = L->next;//pָ���ͷ	
   if (i<1 || i>GetLength(L)+1)//λ��Խ�� 
    {
        return ERROR;
    }
        
    while (j < i - 1)
    {
        j++;
        p = p->next;//�ҵ� Ŀ��λ�ýڵ� 
    }

    q = p->next;//����ڵ�ĺ�� ΪĿ��λ�ýڵ� 
    p->next = q->next;//�ڵ�ĺ�� ָ���̵ĺ�� 
    *e = q->data;//�ڵ��� ��ֵ Ŀ��λ�ýڵ��Ԫ��ֵ 
    if (q == L)   //ɾ�����Ǳ�βԪ�أ���βָ�뷢���ı�
      L = p;
    free(q);//����ռ� 
    return OK;
}

/*
 * ����Ԫ��
 */
void visit(ElemType e)
{
    printf("%d ", e);
}

/*
 * �������Ա�
 */
void TraverseList(LinkList L, void (*visit)(ElemType))
{
    LinkList p = L->next->next;//pָ��������һ��Ԫ��
    while (p != L->next)  //pδ����ͷ
    {
        visit(p->data);//���� 
        p = p->next;//ָ���� 
    }
}

int main()
{
    LinkList L;
    InitList(&L);
    ElemType e;
    int i;
    if (L)
    {
        printf("init success\n");
    }

    if (isEmpty(L))
    {
        printf("list is empty\n");    
    }

    for (i = 0; i < 10; i++)
    {
        InsertElem(L, i + 1, i);
    }

    if (GetElem(L, 1, &e)) {
        printf("The first element is %d\n", e);
    }

    printf("length is %d\n", GetLength(L));

    printf("The 5 at %d\n", FindElem(L, 5, *compare));

    PreElem(L, 6, &e);
    printf("The 6's previous element is %d\n", e);

    NextElem(L, 6, &e);
    printf("The 6's next element is %d\n", e);

    DeleteElem(L, 1, &e);
    printf("delete first element is %d\n", e);

    printf("list:");
    TraverseList(L,visit);

    DestroyList(&L);
    if (!L) {
        printf("\ndestroy success\n");    
    }
}