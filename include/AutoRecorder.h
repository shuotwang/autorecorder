#ifndef AUTO_RECORDER_H
#define AUTO_RECORDER_H

#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "RISCVConsole.h"

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <unordered_map>
#include <memory>

class CAutoRecorder {
    protected:
        uint64_t DCycleCount = 0;

        rapidjson::Document DOutputJSONDocument;
        rapidjson::Value DOutputJSONObjectArray;

    public:
        static const std::string DIRECTION_UP_STRING;
        static const std::string DIRECTION_DOWN_STRING;
        static const std::string DIRECTION_LEFT_STRING;
        static const std::string DIRECTION_RIGHT_STRING;

        static const std::string DIRECTION_UP_RELEASE_STRING;
        static const std::string DIRECTION_DOWN_RELEASE_STRING;
        static const std::string DIRECTION_LEFT_RELEASE_STRING;
        static const std::string DIRECTION_RIGHT_RELEASE_STRING;

        static const std::string BUTTON_1_STRING;
        static const std::string BUTTON_2_STRING;
        static const std::string BUTTON_3_STRING;
        static const std::string BUTTON_4_STRING;

        static const std::string BUTTON_1_RELEASE_STRING;
        static const std::string BUTTON_2_RELEASE_STRING;
        static const std::string BUTTON_3_RELEASE_STRING;
        static const std::string BUTTON_4_RELEASE_STRING;

        static const std::string INSERT_FW_STRING;
        static const std::string INSERT_CR_STRING;
        static const std::string REMOVE_CR_STRING;

        static const std::string CMD_BUTTON_STRING;

        bool AddFWEvent(std::string &data);
        bool AddCREvent(std::string &data);
        bool RemoveCREvent();
        bool AddDirectionEvent(std::string &type);
        // bool AddDirectionReleaseEvent(std::string &type);

        bool AddButtonEvent(std::string &type);
        // bool AddButtonReleaseEvent(std::string &type);

        void OutputJSONFile(std::string &path);

        CAutoRecorder();

        void Reset();
        void IncrementCycle();

};

#endif