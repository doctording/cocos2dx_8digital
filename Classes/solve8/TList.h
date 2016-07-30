#ifndef __TLIST_H__
#define __TLIST_H__

template<class Type> class TList;            //���Ա�ǰ�Ӷ���   

template<class Type> class TNode            //���Ա�����ģ��   
{
	friend class TList<Type>;
public:
	TNode(){}
	TNode(const Type& dat);
private:
	TNode<Type>* Next;
	Type Data;
};

template<class Type> class TList
{
public:
	TList(){ Last = First = 0; Length = 0; }   //���캯��   
	int Getlen()const{ return Length; }   //��Ա�������������Ա���   
	int Append(const Type& T);           //��Ա�������ӱ�β������   
	int Insert(const Type& T, int k);       //��Ա������������   
	Type GetData(int i);                         //��Ա���������ؽ�����ݳ�Ա   
	void SetData(const Type& T, int k); //��Ա���������ý�����ݳ�Ա      
private:
	TNode<Type> *First, *Last;             //���ݳ�Ա�����Ա��ס�βָ��     
	int Length;                                         //���ݳ�Ա�����Ա���   
};

template<class Type> int TList<Type>::Append(const Type& T)
{
	Insert(T, Length);
	return 1;
}

template<class Type> int TList<Type>::Insert(const Type& T, int k)
{
	TNode<Type> *p = new TNode<Type>;
	p->Data = T;
	if (First)
	{
		if (k <= 0)
		{
			p->Next = First;
			First = p;
		}
		if (k>Length - 1)
		{
			Last->Next = p;
			Last = Last->Next;
			Last->Next = 0;
		}
		if (k>0 && k<Length)
		{
			k--;
			TNode<Type> *q = First;
			while (k-->0)
				q = q->Next;
			p->Next = q->Next;
			q->Next = p;
		}
	}
	else
	{
		First = Last = p;
		First->Next = Last->Next = 0;
	}
	Length++;
	return 1;
}

template<class Type> Type TList<Type>::GetData(int k)
{
	TNode<Type> *p = First;
	while (k-->0)
		p = p->Next;
	return p->Data;
}

template<class Type> void TList<Type>::SetData(const Type& T, int k)
{
	TNode<Type> *p = First;
	while (k-->0)
		p = p->Next;
	p->Data = T;
}

#endif