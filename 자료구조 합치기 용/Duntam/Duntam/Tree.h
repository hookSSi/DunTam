#pragma once
#include "DLinkedList.h"

template<class DataType>
class Tree
{
public:
	typedef Tree<DataType> Node;
	DataType m_data;
	Node* m_parent;
	DLinkedList<Node*> m_children;

	Tree()
	{
		m_parent = nullptr;
	}
	~Tree()
	{
		Destroy();
	}
	void Destroy() // Ʈ���� ��������� ����
	{
		DListIterator<Node*> itr = m_children.GetIterator();
		Node* node = nullptr;
		itr.Start();
		while (itr.Valid())
		{
			node = itr.Item();
			m_children.Remove(itr);
			delete node;
		}
	}
	int Count() // Ʈ�� ������ ���� ��ȯ
	{
		int c = 1;
		DListIterator<Node*> itr = m_children.GetIterator();
		for (itr.Start(); itr.Valid(); itr.Forth())
			c += itr.Item()->Count();
		return c;
	}
};

template<class DataType>
class TreeIterator
{
public:
	typedef Tree<DataType> Node;
	Node* m_node; // ���� ���(�θ�) �ݺ���
	DListIterator<Node*> m_childitr; // ���� ����� �ڽ� �ݺ���

	TreeIterator(Node* p_node = nullptr)
	{
		*this = p_node;
	}
	void operator= (Node* p_node)
	{
		m_node = p_node;
		ResetIterator();
	}
	// �θ� �ݺ��� ó��
	void Root()
	{
		if (m_node != nullptr)
		{
			while (m_node->m_parent != nullptr)
				m_node = m_node->m_parent;
		}		
		ResetIterator();
	}
	void Up()
	{
		if (m_node != nullptr)
		{
			m_node = m_node->m_parent;
		}
		ResetIterator();
	}
	void Down()
	{
		if (m_childitr.Valid())
		{
			m_node = m_childitr.Item();
			ResetIterator();
		}
	}
	bool Valid()
	{
		return(m_node != nullptr);
	}
	DataType& Item()
	{
		return m_node->m_data;
	}
	void Remove()
	{
		if(m_node != nullptr)
			m_node->Destroy();
	}
	// �ڽ� �ݺ��� ó��
	void ChildForth()
	{
		m_childitr.Forth();
	}
	void ChildBack()
	{
		m_childitr.Back();
	}
	void ChildStart()
	{
		m_childitr.Start();
	}
	void ChildEnd()
	{
		m_childitr.End();
	}
	bool ChildValid()
	{
		return m_childitr.Valid();
	}
	DataType& ChildItem()
	{
		return m_childitr.Item()->m_data;
	}
	void AppendChild(Node* p_node) // �� �ڿ� �ֱ�
	{
		if (m_node != nullptr)
		{
			m_node->m_children.Append(p_node);
			p_node->m_parent = m_node;
		}
	}
	void PrependChild(Node* p_node) // �� �տ� �ֱ�
	{
		if (m_node != nullptr)
		{
			m_node->m_children.Prepend(p_node);
			p_node->m_parent = m_node;
		}
	}
	void InsertChildAfter(Node* p_node) // ���� �ڽ� �ڿ�
	{
		if (m_node != nullptr)
		{
			m_node->m_children.InsertAfter(p_node);
			p_node->m_parent = m_node;
		}
	}
	void InsertChildBefore(Node* p_node)
	{
		if (m_node != nullptr)
		{
			m_node->m_children.InsertBefore(p_node);
			p_node->m_parent = m_node;
		}
	}
	void RemoveChild()
	{
		if (m_node != nullptr && m_childitr.Valid())
		{
			m_childitr.Item()->m_parent = nullptr;
			m_node->m_children.Remove(m_childitr);
		}
	}
	void ResetIterator() // �ڽ� �ݺ��ڰ� �ڽ� ����� ù ��° ��带 ����Ű���� ��
	{
		if (m_node != nullptr)
		{
			m_childitr = m_node->m_children.GetIterator();
		}
		else
		{
			m_childitr.m_list = nullptr;
			m_childitr.m_node = nullptr;
		}
	}
};


template<class DataType>
void Postorder(Tree<DataType>* p_node, void(*p_process)(Tree<DataType>*))
{
	DListIterator<Tree<DataType>*> itr = p_node->m_children.GetIterator();
	for (itr.Start(); itr.Valid(); itr.Valid())
	{
		Postorder(itr.Item(),p_process);
	}
	p_process(p_node);
}