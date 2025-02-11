#include "FileManager.h"

using json = nlohmann::json;

bool saveRecordData(RecordSystem& rs) {
    json j;
    
    // 將 RecordSystem 中的資料轉換為 JSON
    const std::vector<Record>& records = rs.getRecords();
    for (const auto& record : records) {
        j[std::to_string(record.getId())] = {
            {"type", static_cast<U_Int32>(record.getType())},
            {"amount", record.getAmount()},
            {"name", record.getName()},
            {"date", {
                {"year", record.getDate().getYear()},
                {"month", record.getDate().getMonth()},
                {"day", record.getDate().getDay()}
            }},
            {"tags", record.getTags()},
        };
    }
    
    // 將 JSON 寫入文件
    std::ofstream file("./record.json", std::ios::out | std::ios::binary);
    if (file.is_open()) {
        file << j.dump(4);  // 使用 4 空格縮進以提高可讀性
        file.close();
        return true;
    }
    // 如果文件無法打開，則不需要關閉
    return false;
}

bool loadRecordData(RecordSystem& rs) {
    std::ifstream file("./record.json", std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        return false;
    }
    
    json j;
    file >> j;
    
    // 從 JSON 讀取資料並添加到 RecordSystem
    for (const auto& [_, record_json] : j.items()) {
        Record record(
            static_cast<RecordType>(record_json["type"].get<U_Int32>()),
            record_json["name"].get<std::string>(),
            record_json["amount"].get<U_Int64>()
        );
        
        record.setDate(Date(
            record_json["date"]["year"].get<U_Int32>(),
            record_json["date"]["month"].get<U_Octet>(),
            record_json["date"]["day"].get<U_Octet>()
        ));
        
        for (const auto& tag : record_json["tags"]) {
            record.insertTag(tag.get<std::string>());
        }
        
        rs.insertRecord(std::move(record));
    }
    
    file.close();
    return true;
}