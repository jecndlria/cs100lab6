#include "spreadsheet.hpp"
#include "select.hpp"
#include "gtest/gtest.h"
#include "test.cpp"
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