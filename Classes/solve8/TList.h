#ifndef __TLIST_H__
#define __TLIST_H__

template<class Type> class TList;            //线性表前视定义   

template<class Type> class TNode            //线性表结点类模板   
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
	TList(){ Last = First = 0; Length = 0; }   //构造函数   
	int Getlen()const{ return Length; }   //成员函数，返回线性表长度   
	int Append(const Type& T);           //成员函数，从表尾加入结点   
	int Insert(const Type& T, int k);       //成员函数，插入结点   
	Type GetData(int i);                         //成员函数，返回结点数据成员   
	void SetData(const Type& T, int k); //成员函数，设置结点数据成员      
private:
	TNode<Type> *First, *Last;             //数据成员，线性表首、尾指针     
	int Length;                                         //数据成员，线性表长度   
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