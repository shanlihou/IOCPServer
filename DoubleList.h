#ifndef __DOUBLE_LIST_H_
#define __DOUBLE_LIST_H_

///////////////////////////////////////////////////////////////
#define	MSG(msg) { cout <<"shanlihou"<< (msg) <<endl; }
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
#include <list>
///////////////////////////////////////////////////////////////

template<class T, int COUNT>
class CDoubleList
{
public:
	typedef std::list<T*> LIST;
	typedef typename std::list<T*>::iterator ITERATOR;
public:
	CDoubleList();
	virtual ~CDoubleList();
private:
	CRITICAL_SECTION	m_critical_section;
protected:
	LIST				m_0_list;
	LIST				m_1_list;
private:
	inline void			Base_InitSize(LIST &list,int count);
	inline void			Base_RemoveAll(LIST &list);

	inline void			Init();
	inline void			RemoveAll();
public:
	int					GetCount();
	int					GetBlankCount();

	T*					GetBlank();
	T*					RemoveAt(ITERATOR	pos);
	T*					RemoveAt(T*			lp_t);

	void				GetHeadPosition(ITERATOR&pos, bool &bState);
	T*					GetNext(ITERATOR&pos, bool &bState);

	T*					GetHead();
	T*					RemoveHead();

	T*					GetOwnCycleNext();

	void				PutToBlank();

	////////////////////////////////////////////////////////////

	T*					GetFromBlank();
	T*					PutToBlank(T*lp_t);
	T*					GetFromUse();
	T*					PutToUse(T*lp_t);
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*---------------------------------------------------------------------------------
功能：构造函数
说明：
返回：
---------------------------------------------------------------------------------*/
template<class T,int COUNT>
CDoubleList<T,COUNT>::CDoubleList()
{
	::InitializeCriticalSection(&m_critical_section);

	Init();
}

/*---------------------------------------------------------------------------------
功能：析构函数
说明：
返回：
---------------------------------------------------------------------------------*/
template<class T,int COUNT>
CDoubleList<T,COUNT>::~CDoubleList()
{
	RemoveAll();

	::DeleteCriticalSection(&m_critical_section);
}

/*---------------------------------------------------------------------------------
功能：初始化一个列表，并申请所需的内存
说明：
返回：
---------------------------------------------------------------------------------*/
template<class T,int COUNT>
void CDoubleList<T,COUNT>::Base_InitSize(LIST &list,int count)
{
	T	*lp_t = NULL;

	for( int i = 0; i < count; i++ )
	{
		lp_t = new T;

		list.push_back( lp_t );
	}
}

/*---------------------------------------------------------------------------------
功能：删除一个列表中所有元素，并释放内存
说明：
返回：
---------------------------------------------------------------------------------*/
template<class T,int COUNT>
void CDoubleList<T,COUNT>::Base_RemoveAll(LIST &list)
{
	for( ITERATOR i = list.begin(); i != list.end(); i++ )
	{
		delete *i;
	}

	list.clear();
}

/*---------------------------------------------------------------------------------
功能：初始化
说明：
返回：
---------------------------------------------------------------------------------*/
template<class T,int COUNT>
void CDoubleList<T,COUNT>::Init()
{
	EnterCriticalSection( &m_critical_section );

	Base_RemoveAll( m_0_list );
	Base_RemoveAll( m_1_list );
	Base_InitSize( m_0_list, COUNT );

	LeaveCriticalSection( &m_critical_section );
}

/*---------------------------------------------------------------------------------
功能：清空所有内存
说明：
返回：
---------------------------------------------------------------------------------*/
template<class T,int COUNT>
void CDoubleList<T,COUNT>::RemoveAll()
{
	EnterCriticalSection( &m_critical_section );

	Base_RemoveAll( m_0_list );
	Base_RemoveAll( m_1_list );

	LeaveCriticalSection( &m_critical_section );
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*---------------------------------------------------------------------------------
功能：得到使用表的结点数量
说明：
返回：
---------------------------------------------------------------------------------*/
template<class T,int COUNT>
int CDoubleList<T,COUNT>::GetCount()
{
	int		count = 0;

	EnterCriticalSection( &m_critical_section );

	count = m_1_list.size();

	LeaveCriticalSection( &m_critical_section );

	return count;
}

/*---------------------------------------------------------------------------------
功能：得到空表的结点数量
说明：
返回：
---------------------------------------------------------------------------------*/
template<class T,int COUNT>
int CDoubleList<T,COUNT>::GetBlankCount()
{
	int		count = 0;

	EnterCriticalSection( &m_critical_section );

	count = m_0_list.size();

	LeaveCriticalSection( &m_critical_section );

	return count;
}

/*---------------------------------------------------------------------------------
功能：从空表，或者向系统申请一个结点
说明：如果空表已经无结点，且系统已无可用内存，此函数才会失败。
返回：成功，返回申请的结点；失败，NULL
---------------------------------------------------------------------------------*/
template<class T,int COUNT>
T* CDoubleList<T,COUNT>::GetBlank()
{
	T*	lp_t =	NULL;
	ITERATOR	pos;

	EnterCriticalSection( &m_critical_section );

	pos = m_0_list.begin();

	if( pos == m_0_list.end() )
	{
		lp_t = new T;
	}
	else
	{
		lp_t = *pos;
		m_0_list.pop_front();
	}

	//因为有可能内存不足而申请内存失败
	if( lp_t != NULL )
	{
		m_1_list.push_back( lp_t );
	}

	LeaveCriticalSection( &m_critical_section );

	return lp_t;
}

/*---------------------------------------------------------------------------------
功能：根据叠代器，删除使用表中的一个结点
说明：
返回：
---------------------------------------------------------------------------------*/
template<class T,int COUNT>
T* CDoubleList<T,COUNT>::RemoveAt(ITERATOR pos)
{
	T*	lp_t = NULL;

	EnterCriticalSection( &m_critical_section );

	lp_t = *pos;

	m_1_list.erase( pos );

	m_0_list.push_back( lp_t );

	LeaveCriticalSection( &m_critical_section );

	return lp_t;
}

/*---------------------------------------------------------------------------------
功能：根据结点指针，删除使用表中的一个结点
说明：
返回：
---------------------------------------------------------------------------------*/
template<class T,int COUNT>
T* CDoubleList<T,COUNT>::RemoveAt(T* lp_t)
{
	EnterCriticalSection( &m_critical_section );

	m_1_list.remove( lp_t );

	m_0_list.push_back( lp_t );

	LeaveCriticalSection( &m_critical_section );

	return lp_t;
}

/*---------------------------------------------------------------------------------
功能：得到使用表头结点的叠代器
说明：
返回：
---------------------------------------------------------------------------------*/
template<class T,int COUNT>
void CDoubleList<T,COUNT>::GetHeadPosition(ITERATOR&pos, bool &bState)
{
	EnterCriticalSection( &m_critical_section );//进入临界区

	pos = m_1_list.begin();

	bState =true;
	if( pos == m_1_list.end() )
	{
		bState = false;
	}

	LeaveCriticalSection( &m_critical_section );//退出临界区
}

/*---------------------------------------------------------------------------------
功能：根据叠代器，得到结点。并使叠代器向表尾方向移动一个结点
说明：如果返回NULL，说明已经到了表尾
返回：
---------------------------------------------------------------------------------*/
template<class T,int COUNT>
T* CDoubleList<T,COUNT>::GetNext(ITERATOR&pos, bool &bState)
{
	T*	lp_t = NULL;

	EnterCriticalSection( &m_critical_section );

	lp_t = *pos;

	pos++;
	bState = true;
	if( pos == m_1_list.end() )
	{
		bState = false;
	}
	LeaveCriticalSection( &m_critical_section );
	

	return lp_t;
}

/*---------------------------------------------------------------------------------
功能：得到使用表的表头结点，但不移走
说明：
返回：
---------------------------------------------------------------------------------*/
template<class T,int COUNT>
T* CDoubleList<T,COUNT>::GetHead()
{
	T*	lp_t = NULL;
	ITERATOR	pos;

	EnterCriticalSection( &m_critical_section );

	pos = m_1_list.begin();

	if( pos != m_1_list.end() )
	{
		lp_t = *pos;
	}

	LeaveCriticalSection( &m_critical_section );

	return lp_t;
}

/*---------------------------------------------------------------------------------
功能：移走使用表的表头结点到空表中。
说明：
返回：
---------------------------------------------------------------------------------*/
template<class T,int COUNT>
T* CDoubleList<T,COUNT>::RemoveHead()
{
	T*			lp_t = NULL;
	ITERATOR	pos;

	EnterCriticalSection( &m_critical_section );

	pos = m_1_list.begin();

	if( pos != m_1_list.end() )
	{
		lp_t = *pos;
		m_1_list.pop_front();
		m_0_list.push_back( lp_t );
	}

	LeaveCriticalSection( &m_critical_section );

	return lp_t;
}

/*---------------------------------------------------------------------------------
功能：从空表、使用表中取出一个结点，放到使用表的表头
说明：
返回：
---------------------------------------------------------------------------------*/
template<class T,int COUNT>
T* CDoubleList<T,COUNT>::GetOwnCycleNext()
{
	T*			lp_t = NULL;
	ITERATOR	pos;

	EnterCriticalSection( &m_critical_section );

	pos = m_0_list.begin();

	if( pos != m_0_list.end() )
	{
		lp_t = *pos;
		m_0_list.pop_front();
	}
	else
	{
		pos = m_1_list.begin();

		if( pos != m_1_list.end() )
		{
			lp_t = *pos;

			m_1_list.pop_front();
		}
	}

	if( lp_t != NULL )
	{
		m_1_list.push_back( lp_t );
	}

	LeaveCriticalSection( &m_critical_section );

	return lp_t;
}

/*---------------------------------------------------------------------------------
功能：将使用表中的所有结点都移到空表中
说明：
返回：
---------------------------------------------------------------------------------*/
template<class T,int COUNT>
void CDoubleList<T,COUNT>::PutToBlank()
{
	ITERATOR	pos;

	EnterCriticalSection( &m_critical_section );

	for( pos = m_1_list.begin(); pos != m_1_list.end(); pos++ )
	{
		m_0_list.push_back( *pos );
	}

	m_1_list.clear();

	LeaveCriticalSection( &m_critical_section );
}

/*---------------------------------------------------------------------------------
功能：从空表取得一个结点，但并不放到使用表中。此结点暂时悬空
说明：
返回：
---------------------------------------------------------------------------------*/
template<class T,int COUNT>
T* CDoubleList<T,COUNT>::GetFromBlank()
{
	T*	lp_t =	NULL;
	ITERATOR	pos;

	EnterCriticalSection( &m_critical_section );

	pos = m_0_list.begin();

	if( pos == m_0_list.end() )
	{
		lp_t = new T;
	}
	else
	{
		lp_t = *pos;
		m_0_list.pop_front();
	}

	LeaveCriticalSection( &m_critical_section );

	return lp_t;
}

/*---------------------------------------------------------------------------------
功能：将一个结点放到空表中。
说明：
返回：
---------------------------------------------------------------------------------*/
template<class T,int COUNT>
T* CDoubleList<T,COUNT>::PutToBlank(T* lp_t)
{
	EnterCriticalSection( &m_critical_section );

	m_0_list.push_back( lp_t );

	LeaveCriticalSection( &m_critical_section );

	return lp_t;
}

/*---------------------------------------------------------------------------------
功能：从使用表取得一个结点，但并不放到空表中。此结点暂时悬空
说明：
返回：
---------------------------------------------------------------------------------*/
template<class T,int COUNT>
T* CDoubleList<T,COUNT>::GetFromUse()
{
	T*	lp_t =	NULL;
	ITERATOR	pos;

	EnterCriticalSection( &m_critical_section );

	pos = m_1_list.begin();

	if( pos != m_1_list.end() )
	{
		lp_t = *pos;
		m_1_list.pop_front();
	}
	
	LeaveCriticalSection( &m_critical_section );

	return lp_t;
}

/*---------------------------------------------------------------------------------
功能：将一个结点放到使用表中。
说明：
返回：
---------------------------------------------------------------------------------*/
template<class T,int COUNT>
T* CDoubleList<T,COUNT>::PutToUse(T* lp_t)
{
	EnterCriticalSection( &m_critical_section );

	m_1_list.push_back( lp_t );

	LeaveCriticalSection( &m_critical_section );

	return lp_t;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif	//__DOUBLE_LIST_H_