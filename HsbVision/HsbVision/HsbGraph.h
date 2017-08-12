// Graph.h: interface for the CHsbGraph class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPH_H__79E5F761_60DB_455C_A13B_DB53D271A0B8__INCLUDED_)
#define AFX_GRAPH_H__79E5F761_60DB_455C_A13B_DB53D271A0B8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CHsbGraph:public CObject
{
	DECLARE_SERIAL(CHsbGraph)
public:
	void Draw(CDC* pDC);
	CPoint m_ptOrigin;
	CPoint m_ptEnd;
	UINT m_nDrawType;
	CHsbGraph();
	CHsbGraph(UINT m_nDrawType,CPoint m_ptOrigin,CPoint m_ptEnd);
	void Serialize(CArchive& ar);
	virtual ~CHsbGraph();

};

#endif // !defined(AFX_GRAPH_H__79E5F761_60DB_455C_A13B_DB53D271A0B8__INCLUDED_)
