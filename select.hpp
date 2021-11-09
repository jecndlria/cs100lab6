#ifndef __SELECT_HPP__
#define __SELECT_HPP__

#include <cstring>
#include <string> 
#include <iostream>

class Select
{
public:
    virtual ~Select() = default;

    // Return true if the specified row should be selected.
    virtual bool select(const Spreadsheet* sheet, int row) const = 0;
};

// A common type of criterion for selection is to perform a comparison based on
// the contents of one column.  This class contains contains the logic needed
// for dealing with columns. Note that this class is also an abstract base
// class, derived from Select.  It introduces a new select function (taking just
// a string) and implements the original interface in terms of this.  Derived
// classes need only implement the new select function.  You may choose to
// derive from Select or Select_Column at your convenience.
class Select_Column: public Select
{
protected:
public:
    int column;
    Select_Column() : column(0) {};
    Select_Column(const Spreadsheet* sheet, const std::string& name)
    {
        column = sheet->get_column_by_name(name);
    }

    virtual bool select(const Spreadsheet* sheet, int row) const
    {
        return select(sheet->cell_data(row, column));
    }

    // Derived classes can instead implement this simpler interface.
    virtual bool select(const std::string& s) const = 0;
};

class Select_Contains : public Select_Column
{
protected:
    std::string target; 
public:
    Select_Contains() : target("") {};
    Select_Contains(Spreadsheet* sheet, std::string column, std::string target) : Select_Column(sheet, column), target(target) {}

    virtual bool select(const Spreadsheet* sheet, int row) const
    {
        return select(sheet->cell_data(row, column));
    }

    // Derived classes can instead implement this simpler interface.
    virtual bool select(const std::string& s) const {
        if (s.find(target) != std::string::npos)
        {
            return true;
        }
        else
        {
            return false;
        }
        return false;
    };
};

class Select_Not : public Select_Column
{
protected:
    Select_Column* targetSelection;
public:
    Select_Not() : Select_Column(), targetSelection(targetSelection) {}
    Select_Not(Select_Column* targetSelection) : targetSelection(targetSelection) {}
    ~Select_Not() {delete targetSelection;};
    virtual bool select(const Spreadsheet* sheet, int row) const
    {
        return select(sheet->cell_data(row, targetSelection->column));
    }

    // Derived classes can instead implement this simpler interface.
    virtual bool select(const std::string& s) const 
    {
        return !targetSelection->select(s);
    };
};

class Select_And : public Select_Column
{
protected:
    Select_Column* targetSelection1;
    Select_Column* targetSelection2;
public:
    Select_And();
    ~Select_And() {delete targetSelection1; delete targetSelection2;}
    Select_And(Select_Column* targetSelection1, Select_Column* targetSelection2) : targetSelection1(targetSelection1), targetSelection2(targetSelection2) {}

    virtual bool select(const Spreadsheet* sheet, int row) const
    {
        return select(sheet->cell_data(row, targetSelection1->column), targetSelection1) && select(sheet->cell_data(row, targetSelection2->column), targetSelection2);
    }

    // Derived classes can instead implement this simpler interface.
    virtual bool select(const std::string& s, Select_Column* selectTarget) const {
        return selectTarget->select(s);
    }

    // Derived classes can instead implement this simpler interface.
    virtual bool select(const std::string& s) const 
    {
        return true; 
    };
};
#endif //__SELECT_HPP__
