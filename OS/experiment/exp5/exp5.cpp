typedef struct {
  string name;
  int size;
  int num_block;
  int address[100];
} iNode;

vector<iNode> FCB;

iNode search(string name) {
  for (int i = 0; i < FCB.size(); i++) {
    if (FCB[i].name == name) {
      return FCB[i];
    }
  }
}

void remove(string name) {
  for (int i = 0; i < FCB.size(); i++) {
    if (FCB[i].name == name) {
      FCB.erase(FCB.begin() + i);
      break;
    }
  }
}

void Print() {
  for (int i = 0; i < FCB.size(); i++) {
    cout << FCB[i].name << " " ;
    for (int j = 0; j < FCB[i].num_block; j++) cout << FCB[i].address[j] << " ";
    cout << endl;
  }
}
#include <iostream>
#include <sstream>
#include <math.h>
#include <stdlib.h>
#include <vector>
#define randint(start, end) (rand()%(end-start) + start)
#define BLOCK_NUM 500
#define BLOCK_SIZE 2000

typedef struct node_ {
  int address;
  struct node_ *next;
} Node, *List;

List FLLM_init();
void FLLM_create(string name, int size, List L);
void FLLM_remove(string name, List L);
void FLLM_print(List L);
void FLLM_free(List L);

int main(int argc, char* argv[]){
  if (argc < 2) {
    cout << "Please input file management algorithm and retry" << endl;
    return 1;
  }
  string mode = argv[1];
  cout << mode << endl;
  srand(1);

  List L = FLLM_init();

  for (int i = 0; i < 50; i++) {
    int size = randint(2000, 5001);
    stringstream namestream;
    string name;
    namestream << i+1 << ".txt";
    name = string(namestream.str());
    FLLM_create(name, size, L);
  }

  for (int i = 1; i < 50; i += 2) {
    stringstream namestream;
    string name;
    namestream << i << ".txt";
    name = string(namestream.str());
    FLLM_remove(name, L);
  }

  string names[5] = {"A.txt", "B.txt", "C.txt", "D.txt", "E.txt"};
  int sizes[5] = {7000, 5000, 2000, 9000, 3500};
  for (int i = 0; i < 5; i++) {
    FLLM_create(names[i], sizes[i], L);
  }

  Print();
  FLLM_print(L);

  FLLM_free(L);
  return 0;
}

List FLLM_init() {
  List head = new Node;
  head->address = BLOCK_NUM;
  List rear = head;
  for (int i = 0; i < BLOCK_NUM; i++) {
    List node = new Node;
    node->address = i;
    rear->next = node;
    rear = node;
  }
  rear->next = NULL;
  return head;
}

void FLLM_create(string name, int size, List L) {
  int block_num = ceil(1.0 * size / BLOCK_SIZE);
  if (L->address < block_num) return;
  List rear = L;

  iNode i_node;
  i_node.name = name;
  i_node.size = size;
  i_node.num_block = block_num;

  for (int i = 0; i < block_num; i++) {
    List tmp = rear->next;
    rear->next = rear->next->next;
    i_node.address[i] = tmp->address;
    L->address--;
    delete tmp;
  }
  FCB.push_back(i_node);
}

void FLLM_remove(string name, List L) {
  iNode i_node = search(name);
  remove(name);

  List rear = L;
  while (rear->next) rear = rear->next;
  for (int i = 0; i < i_node.num_block; i++) {
    List node = new Node;
    node->address = i_node.address[i];
    rear->next = node;
    rear = node;
    L->address++;
  }
  rear->next = NULL;
}

void FLLM_print(List L) {
  List rear = L->next;
  int cnt = 0;
  while (rear) {
    printf("%3d ", rear->address);
    cnt++;
    if (cnt % 20 == 0) cout << endl;
    rear = rear->next;
  }
  cout << endl << "free block number:" << L->address << endl;
}

void FLLM_free(List L) {
  List rear = L->next;
  while (L) {
    delete L;
    L = rear;
    if (rear) rear = rear->next;
  }
}
