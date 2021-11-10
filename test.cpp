#include "spreadsheet.hpp"
#include "select.hpp"
#include "gtest/gtest.h"
#include <sstream>

class PopulatedSpreadsheet : public ::testing::Test {
    public:
        Spreadsheet sheet;
        std::ostringstream ss;
        PopulatedSpreadsheet() { 
            sheet.set_column_names({"First","Last","Age","Major"});
            sheet.add_row({"Amanda","Andrews","22","business"});
            sheet.add_row({"Brian","Becker","21","computer science"});
            sheet.add_row({"Carol","Conners","21","computer science"});
            sheet.add_row({"Joe","Jackson","21","mathematics"});
            sheet.add_row({"Sarah","Summers","21","computer science"});
            sheet.add_row({"Diane","Dole","20","computer engineering"});
            sheet.add_row({"David","Dole","22","electrical engineering"});
            sheet.add_row({"Dominick","Dole","22","communications"});
            sheet.add_row({"George","Genius","9","astrophysics"});
        }
        void TearDown() {
            sheet.clear();
        }
};

TEST_F(PopulatedSpreadsheet, HasStuff) {
     sheet.set_selection(
         new Select_Or(
             new Select_Contains(&sheet,"First","Amanda"),
             new Select_Or(
                 new Select_Contains(&sheet,"Last","on"),
                 new Select_Contains(&sheet,"Age","9"))));

    sheet.print_selection(ss);
    ASSERT_EQ(ss.str(), "Amanda Andrews 22 business\nCarol Conners 21 computer science\nJoe Jackson 21 mathematics\nGeorge Genius 9 astrophysics");
}

TEST_F(PopulatedSpreadsheet, EmptyTargetTest) {
    sheet.set_selection(new Select_Contains(&sheet, "First", ""));
    sheet.print_selection(ss);
    ASSERT_EQ(ss.str(), "");
}

TEST_F(PopulatedSpreadsheet, OutputAll) {
    sheet.print_selection(ss);
    ASSERT_EQ(ss.str(), "Amanda Andrews 22 business\nBrian Becker 21 computer science\nCarol Conners 21 computer science\nJoe Jackson 21 mathematics\nSarah Summers 21 computer science\nDiane Dole 20 computer engineering\nDavid Dole 22 electrical engineering\nDominick Dole 22 communications\nGeorge Genius 9 astrophysics");
}

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

class OnlyColumnNamesSpreadsheet : public ::testing::Test {
  public:
    Spreadsheet sheet;
    std::ostringstream ss;
    OnlyColumnNamesSpreadsheet(){
      sheet.set_column_names({"First","Last","Age","Major"});
    }
    void SetUp() {
    }
    void TearDown() {
      sheet.clear();
    }
};

TEST_F(OnlyColumnNamesSpreadsheet, SelectContainsTest) {
  sheet.set_selection(new Select_Contains(&sheet,"Last","Dole"));
  sheet.print_selection(ss);
  ASSERT_EQ(ss.str(), "");
}

TEST_F(OnlyColumnNamesSpreadsheet, NotContaintsTest) {
  sheet.set_selection(new Select_Not(new Select_Contains(&sheet,"Last","Dole")));
  sheet.print_selection(ss);
  ASSERT_EQ(ss.str(), "");
}

TEST_F(OnlyColumnNamesSpreadsheet, AndContainsTest) {
  sheet.set_selection(new Select_And(new Select_Contains(&sheet,"Last","Dole"),new Select_Contains(&sheet,"Last","Dole")));
  sheet.print_selection(ss);
  ASSERT_EQ(ss.str(), "");
}

TEST_F(OnlyColumnNamesSpreadsheet, OrContainsTest) {
  sheet.set_selection(new Select_Or(new Select_Contains(&sheet,"Last","Dole"),new Select_Contains(&sheet,"Last","Dole")));
  sheet.print_selection(ss);
  ASSERT_EQ(ss.str(), "");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
