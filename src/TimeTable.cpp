#include "TimeTable.h"

static vector<string> parseCSVLine(const string& line){
    vector<string> result;
    string field;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size(); i++)
    {
        char c = line[i];

        if (c == '"')
        {
            inQuotes = !inQuotes;
        }
        else if (c == ',' && !inQuotes)
        {
            result.push_back(field);
            field.clear();
        }
        else
        {
            field += c;
        }
    }

    result.push_back(field);
    return result;
}

vector<TimetableEntry> loadTimetableCSV(const string& filename){
    vector<TimetableEntry> entries;
    ifstream file(filename);

    if (!file.is_open())
        return entries;

    string line;

    // skip header
    getline(file, line);

    while (getline(file, line))
    {
        auto fields = parseCSVLine(line);

        if (fields.size() < 2)
            continue;

        TimetableEntry entry;
        entry.day = fields[0];
        entry.className = fields[1];

        for (size_t i = 2; i < fields.size(); i++)
            entry.paths.push_back(fields[i]);

        entries.push_back(entry);
    }

    return entries;
}