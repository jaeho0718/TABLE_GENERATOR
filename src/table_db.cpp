#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include "table_db.h"

using namespace std;

vector<Table> TableDatabase::query(TableQuery tableQuery) {
    vector<Table> result;
    if (tableQuery.id)
}

void TableDatabase::insert(Table &table) {	
	tables.push_back(table);
}

void TableDatabase::update(Table &table) {
    auto toUpdate = find_if(tables.begin(), tables.end(), [&table](const Table &t) { 
            return t.get_id() == table.get_id();
    });
  
    if (toUpdate != tables.end()) {
        tables.erase(toUpdate);
        tables.push_back(table);
    }
    else {
        cerr << "조건에 맞는 시간표가 없습니다. 다시 검색해주세요." << endl;
    }
}

void TableDatabase::remove(int id) {
    auto toRemove = find_if(tables.begin(), tables.end(), [id](const Table &t) { 
        return t.get_id() == id; 
    });

    if (toRemove != tables.end()) {
        tables.erase(toRemove);
    }
}

void TableDatabase::load() {
    fstream file("my_time_table.txt");
    if (file.is_open()) {

    }
    else {
        cerr << "파일을 열 수 없습니다." << endl;
    }

}

void TableDatabase::save() {
    fstream file("my_time_table.txt");
    
    int table_index = 0;
    int course_index = 0;

    if (file.is_open()) {
        file << "<Table Database>\n\n";
        file << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n\n";

        for (Table table : tables) {
            file << "<Table " << table_index << ">\n";
            file << "- - - - - - - - - - - - - - - - - - - - - - - - - - - -\n";
            file << table.get_id() << "\n";
            file << table.get_year() << " " << encode_semester(table.get_semester()) << "\n";
            file << table.get_user_id() << " " << table.get_name() << "\n";

            for (Course course : table.get_course()) {
                file << "- Course " << course_index << "\n";
                file << "name: " << course.get_name() << "\n";
                file << "type: " << encode_course_type(course.get_type()) << "\n";
                file << "english a: ";
                if (course.is_english_a()) {
                    file << "YES\n";
                }
                else {
                    file << "NO\n";
                }
                file << "professor: " << course.get_professor() << "\n";
                file << "grade: " << course.get_grade() << "\n";

                course_index++;
            }
            table_index++;
        }
        file.close();
    }
    else {
        cerr << "파일을 열 수 없습니다." << endl;
    }
}

// getter

vector<Table> TableDatabase::get_tables() const {
    return tables;
}

string encode_semester(Semester semester)
{
    if (semester == Semester::Spring)
    {
        return "Spring";
    }
    else if (semester == Semester::Summer)
    {
        return "Summer";
    }
    else if (semester == Semester::Fall)
    {
        return "Fall";
    }
    else if (semester == Semester::Winter)
    {
        return "Winter";
    }
}

string encode_course_type(CourseType course_type) {
    /*
    * General_Education,
    CoreCommunication,
    CoreCreativity,
    CoreChallenge,
    CoreConvergence,
    CoreTrust,
    ElectiveCommunication,
    ElectiveCreativity,
    ElectiveChallenge,
    ElectiveConvergence,
    Major,
    MajorRequired,
    MajorFundamental
    */

    if (course_type == CourseType::General_Education)
        return "General Eduaction";
    else if (course_type == CourseType::CoreCommunication)
        return "Core Communication";
    else if (course_type == CourseType::CoreCreativity)
        return "Core Creativity";
    else if (course_type == CourseType::CoreChallenge)
        return "Core Challenge";
    else if (course_type == CourseType::CoreConvergence)
        return "Core Convergencw";
    else if (course_type == CourseType::CoreTrust)
        return "Core Trust";
    else if (course_type == CourseType::ElectiveCommunication)
        return "Elective Communication";
    else if (course_type == CourseType::ElectiveCreativity)
        return "Elective Creativity";
    else if (course_type == CourseType::ElectiveChallenge)
        return "Elective Challenge";
    else if (course_type == CourseType::ElectiveConvergence)
        return "Elective Convergencw";
    else if (course_type == CourseType::Major)
        return "Major";
    else if (course_type == CourseType::MajorRequired)
        return "Major Requied";
    else if (course_type == CourseType::MajorFundamental)
        return "Major Fundamental";
}