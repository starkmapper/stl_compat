#pragma hdrstop
#include "../TestBase.h"

#include <std_compat/memory>

TDOG_SUITE(stl_compat)
{
  TDOG_SUITE(enable_shared_from_this)
  {

    class TestDtor : public std_compat::enable_shared_from_this<TestDtor>
    {
    public:
      static bool hasSharedCtor;
      static bool hasSharedDtor;
      static bool hasSharedInitialize;

      TestDtor()
      {
        std::weak_ptr<TestDtor> pointer = this->weak_from_this();

        hasSharedCtor = !pointer.expired();
      }

      ~TestDtor()
      {
        std::weak_ptr<TestDtor> pointer = this->weak_from_this();

        hasSharedDtor = !pointer.expired();
      }

      void Initialize()
      {
        std::weak_ptr<TestDtor> pointer = this->weak_from_this();

        hasSharedInitialize = !pointer.expired();
      }
    };

    bool TestDtor::hasSharedCtor;
    bool TestDtor::hasSharedDtor;
    bool TestDtor::hasSharedInitialize;

    TDOG_TEST_CASE(should_not_have_shared_ptr_in_ctor)
    {
      std::shared_ptr<TestDtor> pointer = std::make_shared<TestDtor>();

      pointer.reset();

      TDOG_ASSERT_NOT(TestDtor::hasSharedCtor);
    }

    TDOG_TEST_CASE(should_not_have_shared_ptr_in_dtor)
    {
      std::shared_ptr<TestDtor> pointer = std::make_shared<TestDtor>();

      pointer.reset();

      TDOG_ASSERT_NOT(TestDtor::hasSharedDtor);
    }

    TDOG_TEST_CASE(should_have_shared_ptr_in_initialize)
    {
      std::shared_ptr<TestDtor> pointer = std::make_shared<TestDtor>();

      pointer->Initialize();

      pointer.reset();

      TDOG_ASSERT(TestDtor::hasSharedInitialize);
    }

    TDOG_CLOSE_SUITE
  }

  TDOG_CLOSE_SUITE
}
