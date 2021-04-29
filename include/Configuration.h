#pragma once

#include "Spelunky2.h"
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>

using nlohmann::ordered_json;

namespace S2Plugin
{
    class Configuration
    {
      public:
        Configuration();

        bool isValid() const noexcept;
        std::string lastError() const noexcept;

        const std::unordered_map<MemoryFieldType, MemoryFieldType>& entityClassHierarchy() const noexcept;
        const std::unordered_map<std::string, MemoryFieldType>& defaultEntityClassTypes() const noexcept;
        const std::vector<MemoryField>& typeFields(const MemoryFieldType& type) const;
        std::string flagTitle(const std::string& fieldName, uint8_t flagNumber);

        Spelunky2* spelunky2() const noexcept;

      private:
        bool mIsValid = false;
        std::string mErrorString;
        std::unique_ptr<Spelunky2> mSpelunky2;

        std::unordered_map<MemoryFieldType, MemoryFieldType> mEntityClassHierarchy;
        std::unordered_map<std::string, MemoryFieldType> mDefaultEntityClassTypes;
        std::unordered_map<MemoryFieldType, std::vector<MemoryField>> mTypeFields;
        std::unordered_map<std::string, std::unordered_map<uint8_t, std::string>> mFlagTitles; // fieldname => (flagnr 1-based => title)

        void processJSON(const ordered_json& j);
    };
} // namespace S2Plugin