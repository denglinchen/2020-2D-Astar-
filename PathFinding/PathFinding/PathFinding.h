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
	
	�ڱ��εĿ����У�����Ҫ�����������(Node��NodeFactory)������ʵ��Ѱ·�㷨����Ѱ·�㷨
�ο������A*Ѱ·�㷨���Ҹ������Լ�����������һЩ�Ż�����չ��ƣ�ʹ�ø��㷨ʹ����������
�������Ը���ʵ��ҵ��������е�����
	�������Ҫ���ֽ���һЩ���⡣
	
	Node�ࣺ
	������Ҫ���һ���ܱ�������λ��Position�ͼ���A*����ʽ�����Ϣ��·���ࡪ��Node��������
Ҫ�������Ϣ������·���λ��(Position position)��ָ��ǰһ��·���ָ��(Node* parent)������
���յ�����ֵ(float f)��
	ÿһ��Node����ֻ���𱣴���ص���Ϣ�������м���Ĺ��ܣ�Node�����C�����е�Structһ����
����ֵ�ļ����Լ�position��parent�ĸ�ֵ����һ����������ȥ��ɡ��ǵģ��Ҳ����˹������ģʽ��
�㷨������ϸ�ڶ��ɹ���ȥ���ƣ�����ʲô����ȥ�����Ϳ����ˡ�
	
	NodeFactory�ࣺ
	·��Ĺ����Ǹ��㷨�ĺ��ģ��㷨��ʵ���Լ��������еĸ������ܶ��ɸù���ȥʵ�ֵġ���ô
FindPath�������о�ֻ�м��м򵥵Ĵ����ˡ��ù�����Ҫ�������֡���Ʒ����·��Node�����·����
��vector<Position>�����е�·����������һ���������ֿ⡱(static unoredered_map)����ȥ���档
	���ȣ�������Ҫ����һЩ�����ͼ����Ϣ�����Ǿ���FindPathʵ���ṩ����Щ��Ϣ��Grid const& grid��
Position const starty�Լ�Position const end�������ɹ��캯�������ʼ����������Щ��Ϣ�Ϳ���
ȥ������������Ҫ���������·���Լ������ǵ�����ֵ��

	·����make_node��Ա������������Ҫ����Position����һ��·���ָ��Node*�������������ҷ�
�ع����õ�·���ָ�롣����·�㶼�����ڶ��ϣ����ǵ��������ں�NodeFactoryһ�£���NodeFactory
�����������н�����·����ڴ�delete��NodeFactory����unordered_map<int,unordered_map<int,Node*>> flag
��Ա��֤ÿһ��Postionֻ����һ��Noded�����ڸ���Postion����Node��ʱ�����flag[row][column]
�����˷ǿյ�ֵ�������·���Ѿ����ڣ����贴����ʹ��unordered_map�������ݽṹ����¼��Щ��Ϣ
�ȱ�֤���ٶ�Ҳ��ʡ�˿ռ䣬���ҿ������ά��������ʹ��������֮�������ڴ�ķ���ʮ�����ġ�
make_node�������е���ͷϷĪ��������ʽ��g��hֵ�ļ��㡣������㷽���鿴��������ע�͡�

	add_serround��Ա������������ǰ·�����Χ·����뿪���ϡ���Ҫ���뵱ǰ·����ΪNode* parent
��·�㿪���ϵ�����multiset<Node*,heuristic> open_set��Ϊ�����������ǰ˷����Ѱ·����������
�����������ĸ�����������ɵ����ԣ��������ĸ�boolֵ���б��棬б������ĸ������������������
��Ŀɴ��Բ��ҽ��IsWalkable�������жϡ����ձ��ж�Ϊ�ɴ��·����make_node��������make_node
�����ڴ����µ�·���ʱ���˳�㽫�����·�㿪���ϡ�

	get_next��������ѡ����һ��ǰ����·�㣬���ҽ���ѡ���·��ӿ�������ȥ�����ú�����Ҫ����
������multiset<Node*,heuristic> open_set��Ϊ������������һ��·���ָ�롣��Ҫע����ǣ�����
����û��Ϊ�ռ��������������һЩ��־������ͨ��һ��������߼�ȥ�ж����·���Ƿ��Ǳռ����е�
һԱ������NodeFactory��֤��ÿ��Positionֻ�����ڶ�����һ��Node���󣬲�����make_nodeʱ����˳��
������open_set,���Ե�һ��Node�����ָ�뱻��open_set���޳��Ժ�㱻��Ϊ�����˱ռ�����������
��get_next�������ҵ�������Node������Ȼ�ڶ��ϴ���������ְ��get_nextͨ��·������ֵf��ѡ
�����ŵ�·����Ϊ��һ��·�㷵�ء�����ֵf=g*g_d+h*h_d,����ϵ��g_d��h_d����ͨ��NodeFactor������
�ã����Ը���ʵ�ʵ�ҵ��״����������ϵ������ȣ���������ۼ�PathFindingDll.cpp�е�ע�͡�

	fill_path������Ϊ�㷨����Ҫ��ܺ�ʵ�֣����Ҹ���waypointList���ʵ��FindPath�Ĺ��ܡ���
������Ҫ����waypointList������Ϊ��������fill_path���������Ȼ��ѯ·�������д洢���Ѿ������
��·����ǰ������Ҫ����NodeFactory�ļ��书�ܣ�����Ѿ��м���õ�·����ֱ�ӷ��ز��ٽ��м��㡣
����ͽ��к���A*���㷨�Ĳ������·�����ٵ���make_path����һ����Node��ɵĿɴ�·����������
make_path������Position����waypointList����������˼��书�ܻ��Ὣ�µļ���vector<Position>
�洢������ֿ⣬���´β�ѯʹ�á�
	
	����ר�Ž���һ��·�����书�ܵ�ʵ�֣�
	һ��·������Ϊһ��vector<Position>���󣬴����һ����ά��unordered_map����routing_memory�У�
����start��end��row��columnֵ����Ϊ�ĸ�key��ȡ��routing_memory��NodeFactory��һ��static����
���������ڶ�����NodeFactory���󣬰������������������ڣ������ÿ��FindPath�����õ�ʱ����ǰ��
���䶼���ڣ���find_memory��ѯ������·����ʱ�򣬻�򵥵Ķ�·������Ч����һ���жϣ����Ƕ�·����
ÿһ��Position����һ��IsWalkable�������������������һ��Position���ɴ��˵������Ŀͻ�������
�µĵ�ͼ���ɵ�ͼ�ĵ�·�������Ѿ�������ʹ�ã���ʱ�����clear_memory���������м��������
	������뿪�����书������ʡ�ռ�����Խ�NodeFactory��bool use_memory��Ϊfalse�����㷨�в���
�����κ��й�routing_memory����Ч������
	ͬʱ��������ͨ������NodeFactory��static int memory_nums��static int max_mem_nums�����ü���
�����������make_path��ÿ�����Ӽ���·��֮�󶼻���������ֵ�Ĵ�С������ﵽ����������void clear_memory
��������ռ��䡣
	
	���ϣ�����ͨ��NodeFactory�����ÿ��Ƹ�Ѱ·�㷨�����ܺ���Ϊ���������ù��̲ο�PathFindingDll.cpp
�е����ע�͡�

	��󣬸�л���θ�У��Ϸ�������������췽�ٰ�˴ξ��������ڽ���������Ĺ�����ѧϰ���˺ܶ౦
���֪ʶ���������憪�µ��ܽ�Ϳ��Կ�������
	�ٴθ�л��ף����Խ��Խ�ã�
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
