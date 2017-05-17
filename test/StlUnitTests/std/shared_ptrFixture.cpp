#pragma hdrstop
#include "../TestBase.h"

#include <std_compat/memory>

using namespace std;

TDOG_SUITE(stl_compat)
{
  TDOG_SUITE(shared_ptr)
  {
    struct MyObjectInterface
    {
      int* dtorFlag;
      MyObjectInterface(int* dtorFlag) : dtorFlag(dtorFlag) {}
      ~MyObjectInterface() { *dtorFlag |= 1; }
      virtual int Hello() = 0;
    };

    struct MyObject : public MyObjectInterface
    {
      MyObject(int* dtorFlag) : MyObjectInterface(dtorFlag) {}

      ~MyObject() { *dtorFlag |= 2; }
      virtual int Hello() { return 10; }
    };

    TDOG_TEST_CASE(should_call_both_dtors)
    {
      int dtorFlag = 0;
      MyObject * myObject = new MyObject(&dtorFlag);

      std::shared_ptr<MyObject> myObjectPtr(myObject);

      myObjectPtr.reset();

      TDOG_ASSERT_EQ(3, dtorFlag);
    }

    TDOG_TEST_CASE(should_cast_shared_ptr_and_call_both_dtor)
    {
      int dtorFlag = 0;
      MyObject * myObject = new MyObject(&dtorFlag);

      std::shared_ptr<MyObject> myObjectPtr(myObject);

      std::shared_ptr<MyObjectInterface> myObjectInterfacePtr(myObjectPtr);

      myObjectPtr.reset();
      myObjectInterfacePtr.reset();

      TDOG_ASSERT_EQ(3, dtorFlag);
    }

    TDOG_TEST_CASE(should_fail_dtor_if_shared_ptr_based_on_interface)
    {
      int dtorFlag = 0;
      MyObject * myObject = new MyObject(&dtorFlag);
      MyObjectInterface * myObjectInterface = myObject;

      std::shared_ptr<MyObjectInterface> myObjectInterfacePtr(myObjectInterface);

      myObjectInterfacePtr.reset();

      TDOG_ASSERT_EQ(1, dtorFlag);
    }

    TDOG_CLOSE_SUITE
  }

  TDOG_CLOSE_SUITE
}
