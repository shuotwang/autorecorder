#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/rapidjson.h"
#include "rapidjson/memorystream.h"
#include "rapidjson/filewritestream.h"
#include "RISCVConsoleApplication.h"
#include "AutoRecorder.h"
#include "RISCVConsole.h"
#include "FileDataSink.h"
#include "FileDataSource.h"
#include "Path.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <map>

const std::string CAutoRecorder::DIRECTION_UP_STRING = "DirectionUp";
const std::string CAutoRecorder::DIRECTION_DOWN_STRING = "DirectionDown";
const std::string CAutoRecorder::DIRECTION_LEFT_STRING = "DirectionLeft";
const std::string CAutoRecorder::DIRECTION_RIGHT_STRING = "DirectionRight";
const std::string CAutoRecorder::DIRECTION_UP_RELEASE_STRING = "DirectionUpRelease";
const std::string CAutoRecorder::DIRECTION_DOWN_RELEASE_STRING = "DirectionDownRelease";
const std::string CAutoRecorder::DIRECTION_LEFT_RELEASE_STRING = "DirectionLeftRelease";
const std::string CAutoRecorder::DIRECTION_RIGHT_RELEASE_STRING = "DirectionRightRelease";
const std::string CAutoRecorder::U_BUTTON_STRING = "UBtn";
const std::string CAutoRecorder::I_BUTTON_STRING = "IBtn";
const std::string CAutoRecorder::J_BUTTON_STRING = "JBtn";
const std::string CAutoRecorder::K_BUTTON_STRING = "KBtn";
const std::string CAutoRecorder::U_BUTTON_RELEASE_STRING = "UBtnRelease";
const std::string CAutoRecorder::I_BUTTON_RELEASE_STRING = "IBtnRelease";
const std::string CAutoRecorder::J_BUTTON_RELEASE_STRING = "JBtnRelease";
const std::string CAutoRecorder::K_BUTTON_RELEASE_STRING = "KBtnRelease";
const std::string CAutoRecorder::INSERT_FW_STRING = "InsertFW";
const std::string CAutoRecorder::INSERT_CR_STRING = "InsertCart";
const std::string CAutoRecorder::REMOVE_CR_STRING = "RemoveCart";
const std::string CAutoRecorder::CMD_BUTTON_STRING = "CMDBtn"; 


bool CAutoRecorder::AddFWEvent(std::string &data) {
    rapidjson::Document::AllocatorType &Allocator = DOutputJSONDocument.GetAllocator();
    
    rapidjson::Value Root(rapidjson::kObjectType);
    rapidjson::Value Data(rapidjson::kStringType);
    Data.SetString(data.c_str(), Allocator);

    Root.AddMember("Cycle", DCycleCount, Allocator);  
    Root.AddMember("Type", "InsertFW", Allocator);
    Root.AddMember("Data", Data, Allocator);

    DOutputJSONObjectArray.PushBack(Root, Allocator);

    return true;
}

bool CAutoRecorder::AddCREvent(std::string &data) {
    rapidjson::Document::AllocatorType &Allocator = DOutputJSONDocument.GetAllocator();
    
    rapidjson::Value Root(rapidjson::kObjectType);
    rapidjson::Value Data(rapidjson::kStringType);
    Data.SetString(data.c_str(), Allocator);

    Root.AddMember("Cycle", DCycleCount, Allocator);  
    Root.AddMember("Type", "InsertCR", Allocator);
    Root.AddMember("Data", Data, Allocator);

    DOutputJSONObjectArray.PushBack(Root, Allocator);

    return true;
}
bool CAutoRecorder::AddDirectionEvent(std::string &type){
    rapidjson::Document::AllocatorType &Allocator = DOutputJSONDocument.GetAllocator();
    
    rapidjson::Value Root(rapidjson::kObjectType);
    rapidjson::Value Type(rapidjson::kStringType);
    Type.SetString(type.c_str(), Allocator);

    Root.AddMember("Cycle", DCycleCount, Allocator);  
    Root.AddMember("Type", Type, Allocator);
    Root.AddMember("Data", "", Allocator);

    DOutputJSONObjectArray.PushBack(Root, Allocator);

    return true;
}

bool CAutoRecorder::AddButtonEvent(std::string &type) {
    rapidjson::Document::AllocatorType &Allocator = DOutputJSONDocument.GetAllocator();
    
    rapidjson::Value Root(rapidjson::kObjectType);
    rapidjson::Value Type(rapidjson::kStringType);
    Type.SetString(type.c_str(), Allocator);

    Root.AddMember("Cycle", DCycleCount, Allocator);  
    Root.AddMember("Type", Type, Allocator);
    Root.AddMember("Data", "", Allocator);

    DOutputJSONObjectArray.PushBack(Root, Allocator);

    return true;
}

void CAutoRecorder::OutputJSONFile(std::string &path) {
    rapidjson::Document::AllocatorType &OutputAllocator = DOutputJSONDocument.GetAllocator();
    DOutputJSONDocument.AddMember("Members", DOutputJSONObjectArray, OutputAllocator);

    FILE* f = fopen(path.c_str(), "w");
	char WriteBuffer[65535];
	rapidjson::FileWriteStream os(f, WriteBuffer, sizeof(WriteBuffer));

	rapidjson::PrettyWriter<rapidjson::FileWriteStream> Writer(os);
	DOutputJSONDocument.Accept(Writer);
	fclose(f);
}

CAutoRecorder::CAutoRecorder() {
    DCycleCount = 0;
       
    DOutputJSONDocument.SetObject();
    rapidjson::Value TempValue(rapidjson::kArrayType);
    DOutputJSONObjectArray = TempValue;
}


void CAutoRecorder::Reset() {
    DCycleCount = 0;
}

void CAutoRecorder::IncrementCycle() {
    DCycleCount++;
}
