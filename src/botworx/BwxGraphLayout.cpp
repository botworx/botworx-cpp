#include "stdafx.h"
#include <bwbotworx/BwxGraphLayout.h>

#include <wx/ogl/ogl.h> // base header of OGL, includes and adjusts wx/deprecated/setup.h
/*
 * Abstract tree
 *
 */

IMPLEMENT_ABSTRACT_CLASS(BwxTreeLayout, wxObject)

BwxTreeLayout::BwxTreeLayout()
{
    m_xSpacing = 16;
    m_ySpacing = 20;
    m_topMargin = 5;
	m_bottomMargin = 5;
    m_leftMargin = 5;
	m_rightMargin = 5;
    m_orientation = false;
    m_parentNode = 0;
	//
    m_lastY = 0 ;
    m_lastX = 0 ;
    m_maxY = 0 ;
    m_maxX = 0 ;
}

void BwxTreeLayout::DoLayout(wxDC& dc, long topId)
{
    if (topId != wxID_ANY)
        SetTopNode(topId);

    long actualTopId = GetTopNode();
    long id = actualTopId;
    while (id != wxID_ANY)
    {
        //SetNodeX(id, 0);
        //SetNodeY(id, 0);
		//MoveNode(id, 0, 0, dc) ;
        //ActivateNode(id, false);
        id = GetNextNode(id);
    }
    m_lastY = m_topMargin;
    m_lastX = m_leftMargin;
    m_maxY = 0 ;
    m_maxX = 0 ;
    CalcLayout(actualTopId, 0, dc);
}

void BwxTreeLayout::Draw(wxDC& dc)
{
    dc.Clear();
    DrawBranches(dc);
    DrawNodes(dc);
}

void BwxTreeLayout::DrawNodes(wxDC& dc)
{
    long id = GetTopNode();
    while (id != wxID_ANY)
    {
        if (NodeActive(id))
            DrawNode(id, dc);
        id = GetNextNode(id);
    }
}

void BwxTreeLayout::DrawBranches(wxDC& dc)
{
    long id = GetTopNode();
    while (id != wxID_ANY)
    {
        if (GetNodeParent(id) != wxID_ANY)
        {
            long parent = GetNodeParent(id);
            if (NodeActive(parent))
                DrawBranch(parent, id, dc);
        }
        id = GetNextNode(id);
    }
}

void BwxTreeLayout::DrawNode(long id, wxDC& dc)
{
    wxChar buf[80];
    wxString name(GetNodeName(id));
    if (name != wxT(""))
        wxSprintf(buf, wxT("%s"), (const wxChar*) name);
    else
        wxSprintf(buf, wxT("<unnamed>"));

    long x = 80;
    long y = 20;
    dc.GetTextExtent(buf, &x, &y);
    dc.DrawText(buf, GetNodeX(id), (long)(GetNodeY(id) - (y/2.0)));
}

void BwxTreeLayout::DrawBranch(long from, long to, wxDC& dc)
{
    long w, h;
    GetNodeSize(from, &w, &h, dc);
    dc.DrawLine(GetNodeX(from)+w, GetNodeY(from),
        GetNodeX(to), GetNodeY(to));
}

void BwxTreeLayout::Initialize(void)
{
}

void BwxTreeLayout::GetNodeSize(long id, long *x, long *y, wxDC& dc)
{
    wxString name(GetNodeName(id));
    if (name != wxT(""))
        dc.GetTextExtent(name, x, y);
    else
    {
        *x = 70; *y = 20;
    }
}

void BwxTreeLayout::CalcLayout(long nodeId, int level, wxDC& dc)
{
    wxList children;
    GetChildren(nodeId, children);
    size_t n = children.GetCount();

    if (m_orientation == false)
    {
        // Left to right
        // X Calculations
        if (level == 0)
            SetNodeX(nodeId, m_leftMargin, dc);
        else
        {
            long x = 0;
            long y = 0;
            long parentId = GetNodeParent(nodeId);
            if (parentId != wxID_ANY)
                GetNodeSize(parentId, &x, &y, dc);
            SetNodeX(nodeId, (long)(GetNodeX(parentId) + m_xSpacing + x), dc);
        }

        wxList::compatibility_iterator node = children.GetFirst();
        while (node)
        {
            CalcLayout((long)node->GetData(), level+1, dc);
            node = node->GetNext();
        }

        // Y Calculations
        long averageY;
        ActivateNode(nodeId, true);

        if (n > 0)
        {
            averageY = 0;
            node = children.GetFirst();
            while (node)
            {
                averageY += GetNodeY((long)node->GetData());
                node = node->GetNext();
            }
            averageY = averageY / n;
            SetNodeY(nodeId, averageY, dc);
        }
        else
        {
            SetNodeY(nodeId, m_lastY, dc);
            long x, y;
            GetNodeSize(nodeId, &x, &y, dc);

            m_lastY = m_lastY + y + m_ySpacing;
        }
    }
    else
    {
        // Top to bottom

        // Y Calculations
        if (level == 0)
            SetNodeY(nodeId, m_topMargin, dc);
        else
        {
            long x = 0;
            long y = 0;
            long parentId = GetNodeParent(nodeId);
            if (parentId != wxID_ANY)
                GetNodeSize(parentId, &x, &y, dc);
            SetNodeY(nodeId, (long)(GetNodeY(parentId) + m_ySpacing + y), dc);
        }

        wxList::compatibility_iterator node = children.GetFirst();
        while (node)
        {
            CalcLayout((long)node->GetData(), level+1, dc);
            node = node->GetNext();
        }

        // X Calculations
        long averageX;
        ActivateNode(nodeId, true);

        if (n > 0)
        {
            averageX = 0;
            node = children.GetFirst();
            while (node)
            {
                averageX += GetNodeX((long)node->GetData());
                node = node->GetNext();
            }
            averageX = averageX / n;
            SetNodeX(nodeId, averageX, dc);
        }
        else
        {
            SetNodeX(nodeId, m_lastX, dc);
            long x, y;
            GetNodeSize(nodeId, &x, &y, dc);

            m_lastX = m_lastX + x + m_xSpacing;
        }
    }
}

/*
 * Tree with storage
 *
 */

IMPLEMENT_DYNAMIC_CLASS(BwxTreeLayoutStored, BwxTreeLayout)

BwxTreeLayoutStored::BwxTreeLayoutStored(int n):BwxTreeLayout()
{
    m_nodes = NULL;
    m_maxNodes = 0;
    Initialize(n);
}

BwxTreeLayoutStored::~BwxTreeLayoutStored(void)
{
    if (m_nodes)
        delete[] m_nodes;
}

void BwxTreeLayoutStored::Initialize(int n)
{
    m_maxNodes = n;
    BwxTreeLayout::Initialize();
    if (m_nodes) delete[] m_nodes;
    m_nodes = new wxStoredNode[m_maxNodes];
    int i;
    for (i = 0; i < n; ++i)
    {
        m_nodes[i].m_name = wxT("");
        m_nodes[i].m_active = false;
        m_nodes[i].m_parentId = wxID_ANY;
        //m_nodes[i].m_x = 0;
        //m_nodes[i].m_y = 0;
		m_nodes[i].p_shape = NULL ;

    }
    m_num = 0;
}

long BwxTreeLayoutStored::AddChild(wxShape* pShape, const wxString& name, const wxString& parent)
{
    if (m_num < (m_maxNodes -1 ))
    {
        long i = -1;
        if (parent != wxT(""))
            i = NameToId(parent);
        else m_parentNode = m_num;

        m_nodes[m_num].m_parentId = i;
        m_nodes[m_num].m_name = name;
        //m_nodes[m_num].m_x = m_nodes[m_num].m_y = 0;
		m_nodes[m_num].p_shape = pShape ;
        m_nodes[m_num].m_clientData = 0;
        m_num ++;

        return (m_num - 1);
    }
    else
        return -1;
}

long BwxTreeLayoutStored::AddChild(wxShape* pShape, const wxString& name, long parent)
{
    if (m_num < (m_maxNodes -1 ) && parent < m_num)
    {
        long i = -1;
        if (parent != -1)
        {
          i = parent;
        }
        else
        {
          m_parentNode = m_num;
        }

        m_nodes[m_num].m_parentId = i;
        m_nodes[m_num].m_name = name;
        //m_nodes[m_num].m_x = m_nodes[m_num].m_y = 0;
		m_nodes[m_num].p_shape = pShape ;
        m_nodes[m_num].m_clientData = 0;
        m_num ++;

        return (m_num - 1);
    }
    else
        return -1;
}

long BwxTreeLayoutStored::NameToId(const wxString& name)
{
    long i;
    for (i = 0; i < m_num; ++i)
        if (name == m_nodes[i].m_name)
            return i;
        return -1;
}

void BwxTreeLayoutStored::GetChildren(long id, wxList& list)
{
    long currentId = GetTopNode();
    while (currentId != wxID_ANY)
    {
        if (id == GetNodeParent(currentId))
            list.Append((wxObject *)currentId);
        currentId = GetNextNode(currentId);
    }
}

wxStoredNode* BwxTreeLayoutStored::GetNode(long idx) const
{
    wxASSERT(idx < m_num);

    return &m_nodes[idx];
};

long BwxTreeLayoutStored::GetNodeX(long id)
{
    wxASSERT(id < m_num);

    //return (long)m_nodes[id].m_x;
	//return (long)m_nodes[id].p_shape->GetX() ;
	double _x, _y ;
	m_nodes[id].p_shape->GetBoundingBoxMax(&_x, &_y) ;
	return (long)m_nodes[id].p_shape->GetX() - (_x / 2) ;
}

long BwxTreeLayoutStored::GetNodeY(long id)
{
    wxASSERT(id < m_num);

    //return (long)m_nodes[id].m_y;
	//return (long)m_nodes[id].p_shape->GetY() ;
	double _x, _y ;
	m_nodes[id].p_shape->GetBoundingBoxMax(&_x, &_y) ;
	return (long)m_nodes[id].p_shape->GetY() - ( _y  / 2) ;
}

void BwxTreeLayoutStored::SetNodeX(long id, long x, wxDC& dc)
{
    wxASSERT(id < m_num);

    //m_nodes[id].m_x = (int)x;
	//m_nodes[id].p_shape->SetX((int)x) ;
	MoveNode(id, x, GetNodeY(id), dc) ;
}

void BwxTreeLayoutStored::SetNodeY(long id, long y, wxDC& dc)
{
    wxASSERT(id < m_num);

    //m_nodes[id].m_y = (int)y;
	//m_nodes[id].p_shape->SetY((int)y) ;
	MoveNode(id, GetNodeX(id), y, dc) ;
}
void BwxTreeLayoutStored::MoveNode(long id, long x, long y, wxDC& dc)
{
	//fromShape->Move(dc, fromShape->GetX(), fromShape->GetY());
	double _x, _y ;
	m_nodes[id].p_shape->GetBoundingBoxMax(&_x, &_y) ;
	m_nodes[id].p_shape->Move(dc, x + (_x / 2), y + (_y / 2), false);

	long extentX = x+_x+m_rightMargin ;
	long extentY = y+_y+m_bottomMargin ;
	if(extentX > m_maxX)
		m_maxX = extentX ;
	if(extentY > m_maxY)
		m_maxY = extentY ;
}
void BwxTreeLayoutStored::GetNodeSize(long id, long *x, long *y, wxDC& dc)
{
    /*wxString name(GetNodeName(id));
    if (name != wxT(""))
        dc.GetTextExtent(name, x, y);
    else
    {
        *x = 70; *y = 20;
    }*/
	double _x, _y ;
	m_nodes[id].p_shape->GetBoundingBoxMax(&_x, &_y) ;
	*x = _x ;
	*y = _y ;
	//*x = m_nodes[id].p_shape->GetWidth() ;
	//*y = m_nodes[id].p_shape->GetHeight() ;
}
void BwxTreeLayoutStored::SetNodeName(long id, const wxString& name)
{
    wxASSERT(id < m_num);

    m_nodes[id].m_name = name;
}

wxString BwxTreeLayoutStored::GetNodeName(long id)
{
    wxASSERT(id < m_num);

    return m_nodes[id].m_name;
}

long BwxTreeLayoutStored::GetNodeParent(long id)
{
    if (id != wxID_ANY)
    {
        wxASSERT(id < m_num);

        return m_nodes[id].m_parentId;
    }
    else
        return wxNOT_FOUND;
}

long BwxTreeLayoutStored::GetNextNode(long id)
{
    wxASSERT(id < m_num);

    if ((id != wxID_ANY) && (id < (m_num - 1)))
        return id + 1;
    else
        return wxNOT_FOUND;
}

void BwxTreeLayoutStored::SetClientData(long id, long clientData)
{
    wxASSERT(id < m_num);

    m_nodes[id].m_clientData = clientData;
}

long BwxTreeLayoutStored::GetClientData(long id) const
{
    wxASSERT(id < m_num);

    return m_nodes[id].m_clientData;
}

void BwxTreeLayoutStored::ActivateNode(long id, bool active)
{
    wxASSERT(id < m_num);

    m_nodes[id].m_active = active;
}

bool BwxTreeLayoutStored::NodeActive(long id)
{
    wxASSERT(id < m_num);

    return m_nodes[id].m_active;
}

/*wxString BwxTreeLayoutStored::HitTest(wxMouseEvent& event, wxDC& dc)
{
    wxPoint pt = event.GetPosition();
    wxCoord x = pt.x;
    wxCoord y = pt.y;

    int i;
    for (i = 0; i < m_maxNodes; ++i)
    {
        long width, height;
        dc.GetTextExtent(m_nodes[i].m_name, &width, &height);

        if ( (x >= (m_nodes[i].m_x-10)) && (x < (m_nodes[i].m_x + width+10)) &&
            (y >= m_nodes[i].m_y-10) && (y < (m_nodes[i].m_y + height+10)) )
        {
            return m_nodes[i].m_name;
        }
    }

    return wxString( wxT("") );
}*/