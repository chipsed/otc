#include "../../framework.h"

HMODULE Utils::GetModule (const char* module) {

   HMODULE hModule = GetModuleHandleA (module);

   if (!hModule) {
       hModule = LoadLibraryA (module);
   }

   return hModule;
}

MODULEINFO Utils::GetModuleInfo (const char* module) {

    MODULEINFO modinfo = { 0 };

    GetModuleInformation (GetCurrentProcess(), GetModule(module), &modinfo, sizeof(MODULEINFO));

    return modinfo;
}

DWORD Utils::GetFunction (const char* module, const char* function) {
   return reinterpret_cast<DWORD> (GetProcAddress(GetModule(module), function));
}

template <typename T>
size_t split (__in const T& str, __in const T& delimiter, __out std::vector<T>& tokens) {
    tokens.clear();

    size_t start = 0;
    size_t end = str.find(delimiter);
    size_t delimLength = delimiter.length();

    while (end != T::npos) {
        tokens.emplace_back(str.substr(start, end - start));
        start = end + delimLength;
        end = str.find(delimiter, start);
    }

    tokens.emplace_back(str.substr(start));
    return tokens.size();
}

bool UnpackSignature (const char* packedSignature, std::vector<unsigned char>& pattern, std::string& mask) {

    std::vector<std::string> tokens;
    size_t count = split<std::string>(std::string (packedSignature), " ", tokens);
    if (!count) return false;
    pattern.reserve(count);
    mask.reserve(count);
    for (const auto& token : tokens) {
        if (token == "?") {
            pattern.push_back(0x00);
            mask += "?";
        }
        else {
            pattern.push_back(static_cast<unsigned char>(std::stoi(token, nullptr, 16)));
            mask += ".";
        }
    }
    return true;
}

DWORD SearchSignature (DWORD baseAddress, DWORD moduleSize, const char* pattern, const char* mask) {

    DWORD patternLength = strlen (mask);

    if (patternLength > moduleSize) return NULL;
    if (baseAddress == 0) return NULL;

    for (DWORD offset = 0; offset < baseAddress - patternLength; offset++) {

        bool isFound = true;

        for (DWORD charIterator = 0; charIterator < patternLength; charIterator++) {
            isFound &= mask[charIterator] == '?' || pattern[charIterator] == * reinterpret_cast<const char*> (baseAddress + offset + charIterator);
        }

        if (isFound) {
            return baseAddress + offset;
        }
    }

    return NULL;
}

void Utils::FindOffsetsToVec (const char* module, std::vector<const char*> signatures, std::vector<DWORD>& vector, bool isPanic) {

    MODULEINFO moduleInfo = GetModuleInfo(module);

    std::vector<unsigned char> pattern;
    std::string mask;

    for (const auto& signature : signatures) {

        if (!UnpackSignature (signature, pattern, mask)) {
            if (isPanic) {
                std::stringstream stream;
                stream << "Can't find offset. " << "Signature: " << signature;
                PanicUtils::Release (PanicUtils::Layers::ROUTINE, stream.str().c_str());
            }
        }

        DWORD offset = SearchSignature (reinterpret_cast<DWORD> (moduleInfo.lpBaseOfDll), moduleInfo.SizeOfImage, reinterpret_cast<const char*> (std::data(pattern)), mask.c_str());

        if (offset) {
            vector.push_back (offset);
        } else if (isPanic) {
            std::stringstream stream;
            stream << "Can't find offset. " << "Signature: " << signature;
            PanicUtils::Release (PanicUtils::Layers::ROUTINE, stream.str().c_str());
        }

        pattern.clear ();
        mask.clear ();
    }

}