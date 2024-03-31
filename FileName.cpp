#include <iostream>
#include <vector>
#include <queue>
using namespace std;
struct EdgeNode //������ڵ�
{
    int tgtIdx;
    EdgeNode* link;
};
struct GraphInAdjList
{
    int NumOfVertex;
    EdgeNode** adjLists;
};
GraphInAdjList* createGraph(int NumOfVer)
{
    GraphInAdjList* graph = (GraphInAdjList*)malloc(sizeof(GraphInAdjList));
    if (graph == NULL)
        return NULL;
    graph->NumOfVertex = NumOfVer;
    graph->adjLists = (EdgeNode**)malloc(sizeof(EdgeNode*) * NumOfVer);
    for (int i = 0; i < NumOfVer; i++)
        graph->adjLists[i] = NULL;
    return graph;
};
bool checkTopoOrder(int* topoArray, GraphInAdjList* graph)
{
    //����������һ��������ڴ���Ϊ��������ʱʹ�ã���˱����ں�������֮ǰfree����
    //��������ڴ�й©��Ϊ��������Ҫ�����п��ܵķ���·�����˳���
    int* topoOrder = (int*)malloc(sizeof(int) * graph->NumOfVertex);

    //�����ͻ��orderʵ���ϼ�¼�˶���i���ڵ�topoOrder[i]��λ���ϡ�
    for (int i = 0; i < graph->NumOfVertex; i++)
        topoOrder[topoArray[i]] = i;
    for (int v = 0; v < graph->NumOfVertex; v++) //�������ж���
    {
        int topoOrderOfV = topoOrder[v];    //����v������λ�á�
        //����v�����г���
        for (EdgeNode* cur = graph->adjLists[v]; cur != NULL; cur = cur->link)
        {
            int topoOrderOfTgt = topoOrder[cur->tgtIdx]; //Ŀ�궥�������λ��
            if (topoOrderOfTgt < topoOrderOfV)
            {    //���Ŀ�궥�������λ��С��v������λ��,������Ҫ��
                free(topoOrder);        //����ǰ�Ƿ��ڴ棬��������ڴ�й©
                return false;
            }
        }
    }
    free(topoOrder);    //����ǰ�ͷ��ڴ棬��������ڴ�й©
    cout << "YES";
    return true;
}
int main()
{
    int n;
    cin >> n;
    GraphInAdjList* graph = createGraph(n);
    int* preNum = new int[n];
    for (int i = 0;i < n; i++) {
        preNum[i] = 0;
    }
    for (int i = 0;i < n;i++) {
        int num;
        cin >> num;
        while (num--) {
            int index;
            cin >> index;
            preNum[index]++;
            EdgeNode* temp = new EdgeNode;
            temp->tgtIdx = index;
            temp->link = graph->adjLists[i];
            graph->adjLists[i] = temp;
        }
    }
    int* topoArray = new int[n];
    int sortedNum = 0;
    queue<int> q0;
    for (int i = 0;i < n;i++) {
        if (preNum[i] == 0) q0.push(i);
    }
    while (!q0.empty()) {
        int curNum = q0.front();
        q0.pop();
        topoArray[sortedNum++] = curNum;
        for (EdgeNode* cur = graph->adjLists[curNum];cur != NULL;cur = cur->link) {
            preNum[cur->tgtIdx]--;
            if (preNum[cur->tgtIdx] == 0) {
                q0.push(cur->tgtIdx);
            }
        }
    }
    checkTopoOrder(topoArray, graph);
    return 0;
}