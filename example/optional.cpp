#pragma hdrstop

#include <std_compat/optional>
#include <vector>
#include <iostream>
using namespace std;

typedef vector<int> IntVector;
typedef optional<IntVector> VectorOptional;
IntVector v;

void init_vector()
{
  for (int i=0;i < 12; ++i)
    v.push_back(i);
}


VectorOptional GetRandomList(size_t minimumSize)
{
  if(v.size() > minimumSize)
    return VectorOptional(v);

  return VectorOptional();
}
void print_size(VectorOptional const & o)
{
  cout << "Using if and ->: ";
  if (o)
    cout << o->size() << endl;
  else
    cout << "No value" << endl;

  cout << "Using value(): ";
  try
  {
    cout << o.value().size() << endl;
  }
  catch(std_compat::bad_optional_access &e)
  {
    cout << e.what() << endl;
  }

  cout << "Using value_or(): ";
  cout << o.value_or(IntVector()).size() << endl;
}
int main()
{
  init_vector();
  VectorOptional o = GetRandomList(12);
  print_size(o);
  o = GetRandomList(11);
  print_size(o);

  size_t size = o.value_or(IntVector()).size();

  return size;
}
