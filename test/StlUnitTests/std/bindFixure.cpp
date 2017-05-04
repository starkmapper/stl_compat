#pragma hdrstop
#include "../TestBase.h"

#include <std_compat/bind>

using namespace std;

TDOG_SUITE(stl_compat)
{
  TDOG_SUITE(bind)
  {
    struct bindFixture
    {
      bindFixture* castThis; // In the tests we don't have a pointer to bindFixture, but a pointer to the derived multi-unheritance class.
      int myMagic;

      int GetMagic()
      {
        return myMagic;
      }

      int DoSum(int b)
      {
        return myMagic + b;
      }

      int DoAddSubtract(int add, int subtract)
      {
        return myMagic + add - subtract;
      }

      bool setup()
      {
        castThis = this;

        myMagic = 42;

        return true;
      }

      void teardown()
      {

      }
    };

    TDOG_TEST_FIXTURE(bind_to_this, bindFixture)
    {
      std::function<int()> func = std::bind(&bindFixture::GetMagic, castThis);

      int result = func();

      TDOG_ASSERT_EQ(42, result);
    }

    TDOG_TEST_FIXTURE(bind_to_partial, bindFixture)
    {
      std::function<int(int b)> func = std::bind(&bindFixture::DoSum, castThis, _1);

      int result = func(2);

      TDOG_ASSERT_EQ(44, result);
    }

    TDOG_TEST_FIXTURE(bind_to_add_partial, bindFixture)
    {
      std::function<int(int b)> func = std::bind(&bindFixture::DoAddSubtract, castThis, _1, 1);

      int result = func(2);

      TDOG_ASSERT_EQ(43, result);
    }

    TDOG_TEST_FIXTURE(bind_to_subtract_partial, bindFixture)
    {
      std::function<int(int b)> func = std::bind(&bindFixture::DoAddSubtract, castThis, 3, _1);

      int result = func(2);

      TDOG_ASSERT_EQ(43, result);
    }

    TDOG_CLOSE_SUITE
  }

  TDOG_CLOSE_SUITE
}
