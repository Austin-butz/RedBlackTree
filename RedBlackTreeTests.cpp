#include "RedBlackTree.h"
#include <cstdlib>
#include <ctime>

int main() {
  RedBlackTree rbt = RedBlackTree();
  cout << "tree made" << endl;
  rbt.Insert(30);
  cout << "added" << endl;
  rbt.Insert(15);
  rbt.Insert(45);
  rbt.Insert(10);
  rbt.Insert(17);
  rbt.Insert(7);
  rbt.Insert(5);
  rbt.printTree();
  cout << endl << endl;
  cout << "size: " << rbt.Size() << endl;
  cout << "Postfix: " << rbt.ToPostfixString() << endl;
  cout << "Prefix: " << rbt.ToPrefixString() << endl;
  cout << "Infix: " << rbt.ToInfixString() << endl;
  cout << "Contains 25: " << rbt.Contains(25) << endl;
  /*cout << "Deleting" << endl;
  rbt.deletenode(15);
  rbt.deletenode(7);
  rbt.deletenode(17);
  rbt.deletenode(10);
  rbt.deletenode(45);
  rbt.deletenode(5);
  rbt.deletenode(30);
  cout << "Done Deleting" << endl;
  cout << rbt.ToInfixString() << endl;
  RedBlackTree rbt2 = RedBlackTree(rbt);
  rbt2.printTree();*/
  return 0;

  /*const int N = 3700000;

  clock_t start = clock();
  RedBlackTree rbt = RedBlackTree();
  for(int i = 0; i < N; i++) rbt.Insert(i);
  clock_t stop = clock();
  double duration = (static_cast<double>(stop - start)) / CLOCKS_PER_SEC;
  cout << "Collected " << rbt.Size() << " ID numbers in " << (duration) << " seconds." << endl;
  int rand1 = rand() % 3700000;
  int rand2 = rand() % 3700000;
  int rand3 = rand() % 3700000;
  int rand4 = rand() % 3700000;
  int rand5 = rand() % 3700000;

  clock_t start1 = clock();
  rbt.deletenode(rand1);
  clock_t stop1 = clock();
  
  clock_t start2 = clock();
  rbt.deletenode(rand2);
  clock_t stop2 = clock();
  
  clock_t start3 = clock();
  rbt.deletenode(rand3);
  clock_t stop3 = clock();
  
  clock_t start4 = clock();
  rbt.deletenode(rand4);
  clock_t stop4 = clock();
  
  clock_t start5 = clock();
  rbt.deletenode(rand5);
  clock_t stop5 = clock();

  
  clock_t start6 = clock();
  rbt.Insert(rand1);
  clock_t stop6 = clock();
  
  clock_t start7 = clock();
  rbt.Insert(rand2);
  clock_t stop7 = clock();
  
  clock_t start8 = clock();
  rbt.Insert(rand3);
  clock_t stop8 = clock();
  
  clock_t start9 = clock();
  rbt.Insert(rand4);
  clock_t stop9 = clock();
  
  clock_t start10 = clock();
  rbt.Insert(rand5);
  clock_t stop10 = clock();

  double duration1 = (static_cast<double>(stop1 - start1)) / CLOCKS_PER_SEC;
  double duration2 = (static_cast<double>(stop2 - start2)) / CLOCKS_PER_SEC;
  double duration3 = (static_cast<double>(stop3 - start3)) / CLOCKS_PER_SEC;
  double duration4 = (static_cast<double>(stop4 - start4)) / CLOCKS_PER_SEC;
  double duration5 = (static_cast<double>(stop5 - start5)) / CLOCKS_PER_SEC;
  double duration6 = (static_cast<double>(stop6 - start6)) / CLOCKS_PER_SEC;
  double duration7 = (static_cast<double>(stop7 - start7)) / CLOCKS_PER_SEC;
  double duration8 = (static_cast<double>(stop8 - start8)) / CLOCKS_PER_SEC;
  double duration9 = (static_cast<double>(stop9 - start9)) / CLOCKS_PER_SEC;
  double duration10 = (static_cast<double>(stop10 - start10)) / CLOCKS_PER_SEC;

  int i = 1;
  cout << "Insert: " << endl;
  cout << "Duration " << i << ": " << duration1 << endl; i+= 1;
  cout << "Duration " << i << ": " << duration2 << endl; i+= 1;
  cout << "Duration " << i << ": " << duration3 << endl; i+= 1;
  cout << "Duration " << i << ": " << duration4 << endl; i+= 1;
  cout << "Duration " << i << ": " << duration5 << endl; i+= 1;
  i = 1;
  cout << endl << "Remove: " << endl;
  cout << "Duration " << i << ": " << duration6 << endl; i+= 1;
  cout << "Duration " << i << ": " << duration7 << endl; i+= 1;
  cout << "Duration " << i << ": " << duration8 << endl; i+= 1;
  cout << "Duration " << i << ": " << duration9 << endl; i+= 1;
  cout << "Duration " << i << ": " << duration10 << endl; i+= 1;
  return 0;*/
}