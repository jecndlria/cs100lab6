#include "spreadsheet.hpp"
#include "select.hpp"
#include "gtest/gtest.h"
#include <sstream>

class EmptySpreadsheet : public ::testing::Test {
  public:
    Spreadsheet sheet;
    std::ostringstream ss;
    EmptySpreadsheet() {
    }
    void SetUp() {
    }
    void TearDown() {
      sheet.clear();
    }
};

// class OnlyColumnNamesSpreadsheet : public ::testing::Test {
//   public:
//     Spreadsheet* sheet;
//     std::ostringstream ss;
//     OnlyColumnNamesSpreadsheet(){
//       sheet->set_column_names({"First","Last","Age","Major"});
//     }
//     void SetUp() {
//     }
//     void TearDown() {
//       sheet->clear();
//       delete sheet;
//     }
// };

TEST_F(EmptySpreadsheet, SelectContainsTest) {
  sheet.set_selection(new Select_Contains(&sheet,"Last","Dole"));
  sheet.print_selection(ss);
  ASSERT_EQ(ss.str(), "");
}

TEST_F(EmptySpreadsheet, NotContaintsTest) {
  sheet.set_selection(new Select_Not(new Select_Contains(&sheet,"Last","Dole")));
  sheet.print_selection(ss);
  ASSERT_EQ(ss.str(), "");
}

TEST_F(EmptySpreadsheet, AndContainsTest) {
  sheet.set_selection(new Select_And(new Select_Contains(&sheet,"Last","Dole"),new Select_Contains(&sheet,"Last","Dole")));
  sheet.print_selection(ss);
  ASSERT_EQ(ss.str(), "");
}

TEST_F(EmptySpreadsheet, OrContainsTest) {
  sheet.set_selection(new Select_Or(new Select_Contains(&sheet,"Last","Dole"),new Select_Contains(&sheet,"Last","Dole")));
  sheet.print_selection(ss);
  ASSERT_EQ(ss.str(), "");
}

TEST(Test, TrueTest) 
{
  ASSERT_TRUE(true);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
