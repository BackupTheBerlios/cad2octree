#include <octree/idx_holder.h>

#include <iostream>

int main(int argc, char *argv[]) {
  IdxHolder pool(2);

  for (int i= 1; i < 10; ++i) {
    NodeIndex idx(i, 0, 0);
    idx.print();
    cout << endl;
    pool.put(NodeIndex(idx));
  }

  cout << endl << endl;

  while (!pool.isEmpty()) {
    NodeIndex idx= pool.get();
    idx.print();
    cout << endl;
  }

  cout << endl << endl << endl;

  for (int i= 1; i < 12; ++i) {
    NodeIndex idx(i, 0, 0);
    idx.print();
    cout << endl;
    pool.put(NodeIndex(idx));
  }

  cout << endl << endl;

  while (!pool.isEmpty()) {
    NodeIndex idx= pool.get();
    idx.print();
    cout << endl;
  }
  return 0;
}
