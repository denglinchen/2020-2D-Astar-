#ifndef IKPGAJDGHOFEKABFDAKEFLIFBAEBBKAK
#define IKPGAJDGHOFEKABFDAKEFLIFBAEBBKAK

#include <cstdlib>
#include <cstdint>
#include<math.h>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<set>
using namespace std;

class Position
{
public:
  std::size_t row;
  std::size_t column;
};

class Grid
{
public:
  std::uint8_t const * walkability;
  std::size_t numRows;
  std::size_t numColumns;

  bool IsWalkable(Position const & pos) const
  {
    return 0 == walkability[pos.row * numColumns + pos.column];
  }
};

class IWaypointList
{
public:
  virtual ~IWaypointList()
  {

  }

  virtual void Add(Position const &) = 0;
};

/////////////////////////////////////////////////////////////////////////////////////////
/*                                  ***�����ܽ�***
�����ߣ������
ѧУ���������պ����ѧ
�绰��15910922135
���䣺515143675@qq.com
������ڣ�2020��7��29��
visual studio�汾��Visual Studio 2019��v142�� Debug x86
*/

//·��
class Node
{
public:
	//��·�������
	Position position;
	//����ֵ
	float f;
	//��һ��·��
	Node* parent;
};

//��������·�����Ĺ�����
class PathBuilder
{
public:
	//·������
		//��������յ��ظ��������ֱ�ӻ�ȡ��һ�μ���õ�·��,�ռ任ʱ��
		//�ͳ�����һ�����������ڣ���NodeFactory����������ֻ��FindPath�������ڡ�
	static unordered_map<int, unordered_map<int, unordered_map<int, unordered_map<int, vector<Position>>>>> routing_memory;
	static int memory_nums;
	static int max_mem_nums;
	//�Ƿ�����·�����书��
		//ȡ�����ڴ��Ƿ��㹻
	bool use_memory;

	//����ʽϵ���趨
		//·���������ϵ��
	float h_d;
		//�յ������ϵ��
	float g_d;

	//����Ѱ·��Ҫ����Ϣ
	Grid const& grid;
	Position const start;
	Position const end;
	//��¼���������ĵ�
		//�ڸõ㼯���д��ڲ����ڿ�����nodes�в����ڵ�·������Ϊ�ռ�
	unordered_map<int,unordered_map<int,Node*>> flag;

	struct heuristic
	{
		bool operator()(Node* const& node1, const Node* const& node2)const
		{
			//��Node������ֵ��С��������
			return node1->f < node2->f;
		}
	};
	//·�㼯�ϣ������ϣ�
	multiset<Node*,heuristic> open_set;//����ȡ�����ӶȾ�Ϊlogn������vector��n���Ӷ�

	PathBuilder(Grid const &grid_, Position const &start_, Position const &end_,bool use_mem=true)
		:grid(grid_), start(start_), end(end_),use_memory(use_mem)
	{
		if (use_memory == false)
			clear_memory();
		//������ϵ��Ĭ��Ϊ1
		h_d = 1.0;
		g_d = 1.0;
	}

	//����·��
	Node* make_node(Position const p,Node* parent)
	{
		/*
		Debug��־��
			FindPath�ӿ�ò�ƻᴫ��һЩ����grid��Χ��position
			������ʹ��һ��if�жϽ������Ļ�����˵����Խ�����Bug
		*/
		//��黵��
		if (p.column < grid.numColumns && p.row < grid.numRows)
		{
			//ÿ��·��ֻ�ܱ�����һ��
			if (flag[p.row][p.column] != nullptr)
				return nullptr;

			Node* this_node = new Node();
			this_node->position = p;

			this_node->parent = parent;

			/****����ʽ�����ش���****/
			//·������g�ļ���
			float g = 0;
			Node* iter = this_node;
			while (iter->parent != nullptr)
			{
				//б��·������
				if(abs(int(iter->position.column-iter->parent->position.column))
					+abs(int(iter->position.row - iter->parent->position.row))==2)
					g += sqrtf(2);
				//ֱ�Ǳ�·������
				else
				{
					g += 1;
				}
				iter = iter->parent;
			}

			//������h�ļ���
			float h = 0;
				//����ʹ�ð˷�������g�����б�ѩ��ȷ�������Ҽٶ�б�߾���Ϊֱ�Ǳߵĸ���2��
			float dx = abs(float(float(this_node->position.column) - float(end.column)));
			float dy = abs(float(float(this_node->position.row) - float(end.row)));
			h = (dx+dy)+ (sqrtf(2) - 2) * min(dx, dy);

			//����ֵ
			this_node->f = g * g_d + h * h_d;
			/****����ʽ�����ش���****/
			
			flag[p.row][p.column] = this_node;
			return this_node;
		}
		else
		{
			return nullptr;
		}
		
	}

	//�������·�㣬���Ҽ��뿪����
	void add_serround(Node* parent, multiset<Node*,heuristic> &open_set)
	{
		bool up_flag=false,down_flag=false,right_flag=false,left_flag=false;
		//�������ҵ����
		//�����·��
		Position tmp = parent->position;
		tmp.row -= 1;
		if (tmp.row >= 0 && grid.IsWalkable(tmp))
		{
			up_flag = true;
			Node* this_node = make_node(tmp, parent);
			if (this_node != nullptr)open_set.insert(this_node);
		}
		//�����·��
		tmp = parent->position;
		tmp.row += 1;
		if (tmp.row < grid.numRows && grid.IsWalkable(tmp))
		{
			down_flag = true;
			Node* this_node = make_node(tmp, parent);
			if (this_node != nullptr)open_set.insert(this_node);
		}
		//�����·��
		tmp = parent->position;
		tmp.column -= 1;
		if (tmp.column >= 0 && grid.IsWalkable(tmp))
		{
			left_flag = true;
			Node* this_node = make_node(tmp, parent);
			if (this_node != nullptr)open_set.insert(this_node);
		}
		//�����·��
		tmp = parent->position;
		tmp.column += 1;
		if (tmp.column < grid.numColumns && grid.IsWalkable(tmp))
		{
			right_flag = true;
			Node* this_node = make_node(tmp, parent);
			if (this_node != nullptr)open_set.insert(this_node);
		}

		//б�ߵ�����
		//�������
		tmp = parent->position;
		tmp.row -= 1;
		tmp.column -= 1;
		if (up_flag && left_flag && grid.IsWalkable(tmp))
		{
			Node* this_node = make_node(tmp, parent);
			if (this_node != nullptr)open_set.insert(this_node);
		}
		//�������
		tmp = parent->position;
		tmp.row -= 1;
		tmp.column +=1 ;
		if (right_flag && up_flag && grid.IsWalkable(tmp))
		{
			Node* this_node = make_node(tmp, parent);
			if (this_node != nullptr)open_set.insert(this_node);
		}
		//�������
		tmp = parent->position;
		tmp.column += 1;
		tmp.row += 1;
		if (right_flag && down_flag&&grid.IsWalkable(tmp))
		{
			Node* this_node = make_node(tmp, parent);
			if (this_node != nullptr)open_set.insert(this_node);
		}
		//�������
		tmp = parent->position;
		tmp.column -= 1;
		tmp.row += 1;
		if (left_flag && down_flag&&grid.IsWalkable(tmp))
		{
			Node* this_node = make_node(tmp, parent);
			if (this_node != nullptr)open_set.insert(this_node);
		}
	}

	//�ӿ������л�ȡ��һ��������·�㲢�ҽ���ӿ�������ɾ������Ϊ����ռ���
	Node* get_next(multiset<Node*,heuristic>& open_set)
	{
		//�ڿ�������Ѱ�Ҵ�ɾ����·��
		Node* next = nullptr;
		//�Ӷ������ȡ����С����ֵ��Node��Ϊnext����
		if (open_set.size() > 0)
		{
			next = *open_set.begin();
			open_set.erase(open_set.begin());
		}
		
		//����ɾ���ĵ㷵��,�����µ�parent
		return next;
	}

	//��ȡ����
	bool find_memory(IWaypointList& waypointList)
	{
		vector<Position> mem;
		//��ѯ���м���
		if (routing_memory[start.row][start.column][end.row][end.column].size() > 0)
		{
			mem = routing_memory[start.row][start.column][end.row][end.column];
			//����ͼ�Ƿ���¹�
			for (Position& p : mem)
			{
				if (grid.IsWalkable(p) == false)
				{
					//��⵽���£�����������¼���
					clear_memory();
					return false;
				}
			}
			//û�и��¹���ͼ,�������
			for (Position& p : mem)
				waypointList.Add(p);
			return true;
		}
		//û�м���
		return false;
		
	}

	//���·���ͼ���·��
	void make_path(IWaypointList& waypointList, Node* end_node)
	{
		vector<Node*> nodes;
		while (end_node != nullptr)
		{
			nodes.push_back(end_node);
			end_node = end_node->parent;
		}
		if (nodes.size() == 0)return;
		reverse(nodes.begin(), nodes.end());
		vector<Position> new_routing;
		for (int i = 0; i < nodes.size(); ++i)
		{
			waypointList.Add(nodes[i]->position);
			if (use_memory)
				new_routing.push_back(nodes[i]->position);
		}
		if (use_memory)
		{
			routing_memory[start.row][start.column][end.row][end.column] = new_routing;
			++memory_nums;
			//���������� �������ƾ����
			if (memory_nums > max_mem_nums)
				clear_memory();
		}

	}	

	//��������api
	void clear_memory()
	{
		memory_nums = 0;
		routing_memory.clear();
	}

	//��ȡ�յ�·��
	Node* get_end_node()
	{
		return flag[end.row][end.column];
	}

	void fill_path(IWaypointList& waypointList)
	{
		//�Ȳ��Ҽ���
		if (use_memory&&find_memory(waypointList))
			return;

		//��ʼ·��
		Node* start_node =make_node(start, nullptr);
		//�޳���ֵ��Ӱ��
		if (start_node == nullptr)return;

		//��������Χ��·��
		add_serround(start_node, open_set);
		//�����һ��parent·��
		Node* next = get_next(open_set);

		//����·����ʱѭ��
		while (next!=nullptr)
		{
			//�Ƿ��ߵ����յ�
			if (next->position.column == end.column && next->position.row == end.row)
				break;

			//���µ���Χ·����뿪����
			add_serround(next, open_set);
			//ѡ����һ��ǰ����·�㣬���ҽ�next·��ӿ�����ȥ������Ϊ����ռ���
			next =get_next(open_set);
		}
	
		//���û�н�
		Node* end_node = get_end_node();
		if (end_node == nullptr)
			return;
	
		//����н�next����end_node
		//���·��
		make_path(waypointList, end_node);
	}

	//�ͷ����д�������·��
	~PathBuilder()
	{
		for (auto it_1 = flag.begin(); it_1 != flag.end(); ++it_1)
		{
			for (auto it_2 = (*it_1).second.begin(); it_2 != (*it_1).second.end(); ++it_2)
				delete (*it_2).second;
		}
	}
private:
};

#endif
