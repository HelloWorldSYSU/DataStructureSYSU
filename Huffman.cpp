
#include <iostream>

#include <queue>

#include <vector>

using namespace std;


struct HuffmanNode{     //构建哈夫曼节点

    char character;

    int frequency;

    HuffmanNode *lchild,*rchild;

    HuffmanNode():character(0),frequency(0),lchild(NULL),rchild(NULL){}

};

typedef HuffmanNode *HTNode;

 

struct cmp{          //重定义排序

    bool operator()(HuffmanNode *a,HuffmanNode *b)

    {

        return a->frequency > b->frequency;

    }

};

int main()

{

    int n;

    priority_queue<HTNode,vector<HTNode>,cmp> pq;    //使用priority_queue进行节点存储，能够及时排序

    while( cin >> n)

    {

        for(int i = 0; i < n; i++)

        {

            HTNode tmpNode = new HuffmanNode;       //对节点进行存储

            cin >> tmpNode->character >> tmpNode->frequency;

            pq.push(tmpNode);

        }

        int BT = 0;

        while(pq.size()>1)

        {

            HTNode tmp1 = new HuffmanNode;  //获得频率最小的两个节点进行合并

            tmp1 = pq.top();

            pq.pop();

            HTNode tmp2 = new HuffmanNode;

            tmp2 = pq.top();

            pq.pop();

            HTNode tmp = new HuffmanNode;

            tmp->frequency = tmp1->frequency +tmp2->frequency;

            tmp->lchild = tmp1;

            tmp->rchild = tmp2;

            BT +=  tmp1->frequency + tmp2->frequency;

            pq.push(tmp);                 //每一次对priority_queue进行操作都会自动更新排序

        }

        cout << BT << endl;

    }

    return 0;

}                                 
